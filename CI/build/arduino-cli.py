import argparse
import collections
import concurrent.futures
from datetime import timedelta
import json
import os
from packaging import version
import re
import shutil
import subprocess
import sys
import tempfile
import textwrap
import time

if sys.platform.startswith("win32"):
    from colorama import init

    init(autoreset=True)

home = os.path.expanduser("~")
tempdir = tempfile.gettempdir()
build_id = time.strftime("_%Y-%m-%d_%H-%M-%S")
script_path = os.path.dirname(os.path.abspath(__file__))
path_config_filename = os.path.join(script_path, "path_config.json")

arduino_cli_path = ""
stm32_url = "https://github.com/stm32duino/BoardManagerFiles/raw/master/package_stmicroelectronics_index.json"
sketches_path_list = []
default_build_output_dir = os.path.join(tempdir, "build_arduinoCliOutput")
build_output_dir = os.path.join(tempdir, "build_arduinoCliOutput" + build_id)
build_output_cache_dir = os.path.join(build_output_dir, "cache")
root_output_dir = os.path.join(home, "Documents", "arduinoCliOutput")

output_dir = ""
log_file = ""

# Ouput directory path
bin_dir = "binaries"

# Default
sketch_default = os.path.join(script_path, "examples", "BareMinimum")
exclude_file_default = os.path.join(script_path, "conf", "exclude_list.txt")
cores_config_file_default = os.path.join(script_path, "conf", "cores_config.json")
cores_config_file_ci = os.path.join(script_path, "conf", "cores_config_ci.json")

maintainer_default = "STMicroelectronics"
arch_default = "stm32"
arduino_platform_default = maintainer_default + ":" + arch_default

core_config = None
maintainer = maintainer_default
arch = arch_default
arduino_platform = arduino_platform_default
arduino_cli = ""
arduino_cli_default_version = "0.18.0"
arduino_cli_version = arduino_cli_default_version

# List
sketch_list = []
exclude_list = []

# Dict
board_fqbn = collections.OrderedDict()  # (key: board name, value: fqbn)
board_custom_fqbn = {}  # key: board name, value: custom fqbn
board_options = {}  # key: board name, value: options
sketch_options = {}  # key: sketch pattern, value: options
na_sketch_pattern = {}  # key: board name, value: sketch pattern list

all_warnings = False

# Counter
nb_build_passed = 0
nb_build_failed = 0
nb_build_skipped = 0

# Timing
full_buildTime = time.time()

success_count = 0
fail_count = 0
skip_count = 0

# format
build_format_header = "| {:^8} | {:42} | {:^10} | {:^7} |"
build_format_result = "| {:^8} | {:42} | {:^19} | {:^6.2f}s |"
build_separator = "-" * 80


# Create a folder if not exists
def createFolder(folder):
    try:
        if not os.path.exists(folder):
            os.makedirs(folder)
    except OSError:
        print("Error: Creating directory. " + folder)


# Delete targeted folder recursively
def deleteFolder(folder):
    if os.path.isdir(folder):
        shutil.rmtree(folder, ignore_errors=True)


def cat(file):
    with open(file, "r") as f:
        print(f.read())
    print("")


# Create the log output file and folders
def create_output_log_tree():
    # Log output file
    with open(log_file, "w") as file:
        file.write(build_separator + "\nStarts ")
        file.write(time.strftime("%A %d %B %Y %H:%M:%S "))
        file.write(
            "\nLog will be available here:\n{}\n".format(os.path.abspath(output_dir))
        )
        file.write(build_separator + "\n")
    # Folders
    for board in board_fqbn:
        createFolder(os.path.join(output_dir, board, bin_dir))
        createFolder(os.path.join(output_dir, board))
        createFolder(os.path.join(build_output_dir, board))


def create_config():
    global arduino_cli_path
    global sketches_path_list
    global build_output_dir
    global root_output_dir
    # Create a Json file for a better path management
    print(
        "'{}' file created. Please check the configuration.".format(
            path_config_filename
        )
    )
    path_config_file = open(path_config_filename, "w")
    path_config_file.write(
        json.dumps(
            {
                "ARDUINO_CLI_PATH": arduino_cli_path,
                "SKETCHES_PATHS": sketches_path_list,
                "BUILD_OUPUT_DIR": default_build_output_dir,
                "ROOT_OUPUT_DIR": root_output_dir,
            },
            indent=2,
        )
    )
    path_config_file.close()
    exit(1)


def check_config():
    global arduino_cli
    global arduino_cli_version
    global arduino_cli_path
    global sketches_path_list
    global build_output_dir
    global root_output_dir
    global output_dir
    global log_file
    global stm32_url

    if args.ci is False:
        if os.path.isfile(path_config_filename):
            try:
                path_config_file = open(path_config_filename, "r")
                path_config = json.load(path_config_file)
                # Common path
                arduino_cli_path = path_config["ARDUINO_CLI_PATH"]
                sketches_path_list = path_config["SKETCHES_PATHS"]
                build_output_dir = path_config["BUILD_OUPUT_DIR"] + build_id
                root_output_dir = path_config["ROOT_OUPUT_DIR"]
                path_config_file.close()
            except IOError:
                print("Failed to open " + path_config_file)
        else:
            create_config()

    output_dir = os.path.join(root_output_dir, "build" + build_id)
    log_file = os.path.join(output_dir, "build_result.log")

    if arduino_cli_path != "":
        assert os.path.exists(
            arduino_cli_path
        ), "Path does not exist: {} . Please check the path in the json config file".format(
            arduino_cli_path
        )

    if sys.platform.startswith("win32"):
        arduino_cli = os.path.join(arduino_cli_path, "arduino-cli.exe")
    elif sys.platform.startswith("linux"):
        arduino_cli = os.path.join(arduino_cli_path, "arduino-cli")
    elif sys.platform.startswith("darwin"):
        arduino_cli = os.path.join(arduino_cli_path, "arduino-cli")
    else:
        arduino_cli = "arduino-cli"

    try:
        output = subprocess.check_output(
            [arduino_cli, "version"], stderr=subprocess.STDOUT,
        )
    except subprocess.CalledProcessError as e:
        print('"' + " ".join(e.cmd) + '" failed with code: {}!'.format(e.returncode))
        print(e.stdout.decode("utf-8"))
        quit(e.returncode)
    else:
        res = re.match(r".*Version:\s+(\d+\.\d+\.\d+).*", output.decode("utf-8"))
        if res:
            arduino_cli_version = res.group(1)
            print("Arduino CLI version used: " + arduino_cli_version)
        else:
            print(
                "Unable to define Arduino CLI version, use default: "
                + arduino_cli_default_version
            )

    if args.url:
        stm32_url = args.url

    try:
        output = subprocess.check_output(
            [arduino_cli, "core", "search", "stm32", "--additional-urls", stm32_url],
            stderr=subprocess.STDOUT,
        )
    except subprocess.CalledProcessError as e:
        print('"' + " ".join(e.cmd) + '" failed with code: {}!'.format(e.returncode))
        print(e.stdout.decode("utf-8"))
        quit(e.returncode)
    else:
        if arduino_platform not in output.decode("utf-8"):
            print(arduino_platform + " is not installed!")
            quit(1)
        # Add core and library path to sketches_path_list
        try:
            output = subprocess.check_output(
                [arduino_cli, "config", "dump", "--format", "json"],
                stderr=subprocess.STDOUT,
            ).decode("utf-8")
        except subprocess.CalledProcessError as e:
            print(
                '"' + " ".join(e.cmd) + '" failed with code: {}!'.format(e.returncode)
            )
            print(e.stdout.decode("utf-8"))
            quit(e.returncode)
        else:
            cli_config = json.loads(output)
            if cli_config is not None:
                if cli_config["directories"]["data"] is not None:
                    sketches_path_list.append(cli_config["directories"]["data"])
                else:
                    print("No data directory")
                    quit(1)
                if cli_config["directories"]["user"] is not None:
                    sketches_path_list.append(cli_config["directories"]["user"])
                else:
                    print("No user directory!")
                    quit(1)
            else:
                print("No arduino-cli config!")
                quit(1)


def load_core_config():
    global core_config
    global maintainer
    global arch
    cores_config_filename = ""
    if args.config:
        assert os.path.exists(
            args.config
        ), "User core configuration JSON file does not exist"
        cores_config_filename = args.config
    else:
        if args.ci:
            cores_config_filename = cores_config_file_ci
        else:
            cores_config_filename = cores_config_file_default
    print("Cores configuration JSON file that will be used:")
    print(cores_config_filename)
    try:
        cores_config_file = open(cores_config_filename, "r")
        cores_config = json.load(cores_config_file)
        cores_config_file.close()

        if args.arch:
            arch = args.arch
        for core in cores_config["cores"]:
            if arch == core["architecture"]:
                core_config = core
                maintainer = core["maintainer"]
                print(
                    "Build configuration for '"
                    + maintainer
                    + "' maintainer and '"
                    + arch
                    + "' architecture"
                )
                break
        else:
            print(
                "Core architecture '" + arch + "' not found in " + cores_config_filename
            )
            arch = arch_default
            core_config = None
    except IOError:
        print(
            "Can't open {} file. Build configuration will not be used.".format(
                cores_config_filename
            )
        )
    finally:
        if core_config is None:
            print(
                "Using default configuration for '"
                + maintainer_default
                + "' maintainer and '"
                + arch_default
                + "' architecture"
            )


# Board list have to be initialized before call this function
def parse_core_config():
    assert board_fqbn, "Board list not initialized"
    # Extract boards names to create a set
    board_name_set = set([board for board in board_fqbn])
    for sketch in core_config["sketches"]:
        if sketch["applicable"] is True:
            # Remove boards in the list
            na_board_set = board_name_set - set(sketch["boards"])
        else:
            # Add boards in the list
            na_board_set = set(sketch["boards"]) - (
                set(sketch["boards"]) - board_name_set
            )
        if "options" in sketch:
            sketch_options[sketch["pattern"]] = sketch["options"]
        if len(na_board_set):
            for board_name in na_board_set:
                if board_name in na_sketch_pattern:
                    na_sketch_pattern[board_name].append(sketch["pattern"])
                else:
                    na_sketch_pattern[board_name] = [sketch["pattern"]]

    for board in core_config["boards"]:
        if "fqbn" in board:
            board_custom_fqbn[board["name"]] = board["fqbn"]
        if "options" in board:
            board_options[board["name"]] = board["options"]

    # for key, value in na_sketch_pattern.items():
    #    print("{}: {}\n".format(key, value))
    # for key, value in board_custom_fqbn.items():
    #    print("{}: {}\n".format(key, value))
    # for key, value in board_options.items():
    #    print("{}: {}\n".format(key, value))


def manage_exclude_list(file):
    with open(file, "r") as f:
        for line in f.readlines():
            if line.rstrip():
                exclude_list.append(line.rstrip())
    if exclude_list:
        for pattern in exclude_list:
            exclude_pattern = re.compile(".*" + pattern + ".*", re.IGNORECASE)
            for s in reversed(sketch_list):
                if exclude_pattern.search(s):
                    sketch_list.remove(s)


# Manage sketches list
def manage_inos():

    # Find all inos or all patterned inos
    if args.all or args.sketches or args.list == "sketch":
        find_inos()
        if args.exclude:
            assert os.path.exists(args.exclude), "Excluded list file does not exist"
            manage_exclude_list(args.exclude)
        elif os.path.exists(exclude_file_default):
            manage_exclude_list(exclude_file_default)
    # Only one sketch
    elif args.ino:
        if os.path.exists(args.ino):
            # Store only the path
            if os.path.isfile(args.ino):
                sketch_list.append(os.path.dirname(args.ino))
            else:
                sketch_list.append(args.ino)
        else:
            for path in sketches_path_list:
                fp = os.path.join(path, args.ino)
                if os.path.exists(fp):
                    # Store only the path
                    if os.path.isfile(fp):
                        sketch_list.append(os.path.dirname(fp))
                    else:
                        sketch_list.append(fp)
                    break
            else:
                print("Sketch {} path does not exist!".format(args.ino))
                quit(1)
    # Sketches listed in a file
    elif args.file:
        assert os.path.exists(args.file), "Sketches list file does not exist"
        with open(args.file, "r") as f:
            for line in f.readlines():
                if line.rstrip():
                    ino = line.rstrip()
                    if os.path.exists(ino):
                        # Store only the path
                        if os.path.isfile(ino):
                            sketch_list.append(os.path.dirname(ino))
                        else:
                            sketch_list.append(ino)
                    else:
                        for path in sketches_path_list:
                            fp = os.path.join(path, ino)
                            if os.path.exists(fp):
                                # Store only the path
                                if os.path.isfile(fp):
                                    sketch_list.append(os.path.dirname(fp))
                                else:
                                    sketch_list.append(fp)
                                break
                        else:
                            print("Ignore {} as it does not exist.".format(ino))
    # Default sketch to build
    else:
        sketch_list.append(sketch_default)
    if len(sketch_list) == 0:
        print("No sketch to build for " + arduino_platform + "!")
        quit(1)


# Find all .ino files and save directory
def find_inos():
    global sketch_list
    # key: path, value: name
    if args.sketches:
        arg_sketch_pattern = re.compile(args.sketches, re.IGNORECASE)
    for path in sketches_path_list:
        for root, dirs, files in os.walk(path, followlinks=True):
            for file in files:
                if file.endswith((".ino", ".pde")):
                    if args.sketches:
                        if arg_sketch_pattern.search(os.path.join(root, file)) is None:
                            continue
                    sketch_list.append(root)
    sketch_list = sorted(set(sketch_list))


# Return a list of all board using the arduino-cli for the specified architecture
def find_board():
    global board_fqbn
    board_found = {}

    if args.board:
        arg_board_pattern = re.compile(args.board, re.IGNORECASE)

    if version.parse(arduino_cli_version) >= version.parse("0.18.0"):
        fqbn_key = "fqbn"
    else:
        fqbn_key = "FQBN"
    fqbn_list_tmp = []
    try:
        output = subprocess.check_output(
            [arduino_cli, "board", "listall", "--format", "json"],
            stderr=subprocess.STDOUT,
        ).decode("utf-8")
    except subprocess.CalledProcessError as e:
        print('"' + " ".join(e.cmd) + '" failed with code: {}!'.format(e.returncode))
        print(e.stdout.decode("utf-8"))
        quit(e.returncode)
    else:
        boards_list = json.loads(output)
        if boards_list is not None:
            for board in boards_list["boards"]:
                if arduino_platform in board[fqbn_key]:
                    fqbn_list_tmp.append(board[fqbn_key])
        if not len(fqbn_list_tmp):
            print("No boards found for " + arduino_platform)
            quit(1)

    # For STM32 core, pnum is requested
    for fqbn in fqbn_list_tmp:
        try:
            output = subprocess.check_output(
                [arduino_cli, "board", "details", "--additional-urls", stm32_url, "--format", "json", fqbn],
                stderr=subprocess.STDOUT,
            ).decode("utf-8")
        except subprocess.CalledProcessError as e:
            print(
                '"' + " ".join(e.cmd) + '" failed with code: {}!'.format(e.returncode)
            )
            print(e.stdout.decode("utf-8"))
            quit(e.returncode)
        else:
            board_detail = json.loads(output)
            if board_detail is not None:
                if "config_options" not in board_detail:
                    print("No config_options found for " + fqbn)
                    quit(1)
                for option in board_detail["config_options"]:
                    if option["option"] == "pnum":
                        for value in option["values"]:
                            if args.board:
                                if arg_board_pattern.search(value["value"]) is None:
                                    continue
                            board_found[value["value"]] = (
                                fqbn + ":pnum=" + value["value"]
                            )
                    break
            else:
                print('No detail found for:"' + fqbn + '"!')
    if board_found:
        board_fqbn = collections.OrderedDict(sorted(board_found.items()))
    else:
        print("No board found for " + arduino_platform + "!")
        quit(1)


# Check the status
def check_status(status, build_conf, boardKo):
    global nb_build_passed
    global nb_build_failed
    sketch_name = os.path.basename(build_conf[4][-1])

    if status[1] == 0:
        result = "\033[32msucceeded\033[0m"
        nb_build_passed += 1
    elif status[1] == 1:
        # Check if failed due to a region overflowed
        logFile = os.path.join(build_conf[3], sketch_name + ".log")
        # error or fatal error
        fork_pattern = re.compile(r"^Error during build: fork/exec")
        error_pattern = re.compile(r":\d+:\d+:\s.*error:\s|^Error:")
        ld_pattern = re.compile("arm-none-eabi/bin/ld:")
        overflow_pattern = re.compile(
            r"(will not fit in |section .+ is not within )?region( .+ overflowed by [\d]+ bytes)?"
        )
        error_found = False
        for i, line in enumerate(open(logFile)):
            if error_pattern.search(line):
                error_found = True
            elif fork_pattern.search(line):
                error_found = True
            elif ld_pattern.search(line):
                # If one ld line is not for region overflowed --> failed
                if overflow_pattern.search(line) is None:
                    error_found = True
            if error_found:
                result = "\033[31mfailed\033[0m"
                boardKo.append(build_conf[0])
                if args.ci:
                    cat(logFile)
                nb_build_failed += 1
                break
        else:
            # else consider it succeeded
            result = "\033[32msucceeded*\033[0m"
            nb_build_passed += 1
    else:
        result = "\033[31merror\033[0m"

    print(
        (build_format_result).format(
            "{}/{}".format(build_conf[1], build_conf[2]),
            build_conf[0],
            result,
            status[0],
        )
    )


# Log sketch build result
def log_sketch_build_result(sketch, boardKo, boardSkipped):
    # Log file
    with open(log_file, "a") as f:
        f.write(build_separator + "\n")
        f.write(
            "Sketch: {} ({}/{})\n".format(
                os.path.basename(sketch),
                sketch_list.index(sketch) + 1,
                len(sketch_list),
            )
        )
        f.write(os.path.dirname(sketch))
        f.write(
            "\n{} {}, {} {}, {} {}\n".format(
                len(board_fqbn) - len(boardKo) - len(boardSkipped),
                "succeeded",
                len(boardKo),
                "failed",
                len(boardSkipped),
                "skipped",
            )
        )

        if len(boardKo):
            f.write(
                "Failed boards :\n"
                + "\n".join(
                    textwrap.wrap(", ".join(boardKo), 80, break_long_words=False)
                )
            )
            # f.write("Failed boards :\n" + "\n".join(boardKo))
            f.write("\n")
        if len(boardSkipped):
            f.write(
                "Skipped boards :\n"
                + "\n".join(
                    textwrap.wrap(", ".join(boardSkipped), 80, break_long_words=False)
                )
            )
            # f.write("Skipped boards :\n" + "\n".join(boardSkipped))
            f.write("\n")
        f.write(build_separator + "\n")

    # Standard output
    print(build_separator)
    print(
        "Build Summary: {} {}, {} {}, {} {}".format(
            len(board_fqbn) - len(boardKo) - len(boardSkipped),
            "\033[32msucceeded\033[0m",
            len(boardKo),
            "\033[31mfailed\033[0m",
            len(boardSkipped),
            "\033[33mskipped\033[0m",
        )
    )
    print(build_separator)


# Log final result
def log_final_result():
    # Also equal to len(board_fqbn) * len(sketch_list)
    nb_build_total = nb_build_passed + nb_build_failed + nb_build_skipped
    stat_passed = round(nb_build_passed * 100.0 / nb_build_total, 2)
    stat_failed = round(nb_build_failed * 100.0 / nb_build_total, 2)
    stat_skipped = round(nb_build_skipped * 100.0 / nb_build_total, 2)
    duration = str(timedelta(seconds=time.time() - full_buildTime))

    # Log file
    with open(log_file, "a") as f:
        f.write("\n" + build_separator + "\n")
        f.write("| {:^76} |\n".format("Build summary"))
        f.write(build_separator + "\n")
        f.write(
            "{} {} ({}%), {} {} ({}%), {} {} ({}%) of {} builds\n".format(
                nb_build_passed,
                "succeeded",
                stat_passed,
                nb_build_failed,
                "failed",
                stat_failed,
                nb_build_skipped,
                "skipped",
                stat_skipped,
                nb_build_total,
            )
        )
        f.write("Ends ")
        f.write(time.strftime("%A %d %B %Y %H:%M:%S\n"))
        f.write("Duration: ")
        f.write(duration)
        f.write("\nLogs are available here:\n")
        f.write(output_dir + "\n")
        f.write(build_separator + "\n\n")

    # Standard output
    print(
        "Builds Summary: {} {} ({}%), {} {} ({}%), {} {} ({}%) of {} builds".format(
            nb_build_passed,
            "\033[32msucceeded\033[0m",
            stat_passed,
            nb_build_failed,
            "\033[31mfailed\033[0m",
            stat_failed,
            nb_build_skipped,
            "\033[33mskipped\033[0m",
            stat_skipped,
            nb_build_total,
        )
    )
    print("Duration: " + duration)
    print("Logs are available here:")
    print(output_dir)


# Set up specific options to customise arduino builder command
def get_fqbn(b_name):
    if b_name in board_custom_fqbn and board_custom_fqbn[b_name]:
        return board_custom_fqbn[b_name]
    else:
        if b_name in board_options and board_options[b_name]:
            return board_fqbn[b_name] + "," + board_options[b_name]
        else:
            return board_fqbn[b_name]


# Generate arduino builder basic command
def genBasicCommand(b_name):
    cmd = []
    cmd.append(arduino_cli)
    cmd.append("compile")
    # cmd.append("-warnings=all")
    cmd.append("--build-path")
    cmd.append(os.path.join(build_output_dir, b_name))
    cmd.append("--build-cache-path")
    cmd.append(build_output_cache_dir)
    if args.verbose:
        cmd.append("--verbose")
    if version.parse(arduino_cli_version) <= version.parse("0.10.0"):
        cmd.append("--output")
        cmd.append(os.path.join(output_dir, b_name, bin_dir, "dummy_sketch"))
    else:
        cmd.append("--output-dir")
        cmd.append(os.path.join(output_dir, b_name, bin_dir))
    cmd.append("--fqbn")
    cmd.append(get_fqbn(b_name))
    cmd.append("dummy_sketch")
    return cmd


def create_build_conf_list():
    build_conf_list = []
    idx = 1
    for b_name in board_fqbn:
        build_conf_list.append(
            (
                b_name,
                idx,
                len(board_fqbn),
                os.path.join(output_dir, b_name),
                genBasicCommand(b_name),
            )
        )
        idx += 1
    return build_conf_list


def build_config(sketch, boardSkipped):
    global nb_build_skipped
    build_conf_list = create_build_conf_list()

    for idx in reversed(range(len(build_conf_list))):
        build_conf_list[idx][4][-1] = sketch
        build_conf_list[idx][4][-4] = build_conf_list[idx][4][-4].replace(
            "dummy_sketch", os.path.basename(sketch)
        )
        if na_sketch_pattern:
            if build_conf_list[idx][0] in na_sketch_pattern:
                for pattern in na_sketch_pattern[build_conf_list[idx][0]]:
                    if re.search(pattern, sketch, re.IGNORECASE):
                        print(
                            (build_format_result).format(
                                "{}/{}".format(
                                    build_conf_list[idx][1], build_conf_list[idx][2]
                                ),
                                build_conf_list[idx][0],
                                "\033[33mskipped\033[0m",
                                0.00,
                            )
                        )

                        boardSkipped.append(build_conf_list[idx][0])
                        del build_conf_list[idx]
                        nb_build_skipped += 1
                        break
                else:
                    # get specific sketch options to append to the fqbn
                    for pattern in sketch_options:
                        print
                        if pattern in sketch_options:
                            if re.search(pattern, sketch, re.IGNORECASE):
                                if build_conf_list[idx][4][-2].count(":") == 3:
                                    build_conf_list[idx][4][-2] += (
                                        "," + sketch_options[pattern]
                                    )
                                else:
                                    build_conf_list[idx][4][-2] += (
                                        ":" + sketch_options[pattern]
                                    )
    return build_conf_list


# Automatic run
def build_all():
    create_output_log_tree()
    wrapper = textwrap.TextWrapper(width=76)

    for sketch_nb, sketch in enumerate(sketch_list, start=1):
        boardKo = []
        boardSkipped = []
        print("\n")
        print(build_separator)
        print(
            "| {:^85} |".format(
                "Sketch \033[34m{}\033[0m ({}/{})".format(
                    os.path.basename(sketch), sketch_nb, len(sketch_list)
                )
            )
        )
        wrapped_path_ = wrapper.wrap(text=os.path.dirname(sketch))
        for line in wrapped_path_:
            print("| {:^76} |".format("{}".format(line)))
        print(build_separator)
        print((build_format_header).format("Num", "Board", "Result", "Time"))
        print(build_separator)

        build_conf_list = build_config(sketch, boardSkipped)
        with concurrent.futures.ProcessPoolExecutor(os.cpu_count() - 1) as executor:
            for build_conf, res in zip(
                build_conf_list, executor.map(build, build_conf_list)
            ):
                check_status(res, build_conf, boardKo)
        log_sketch_build_result(sketch, boardKo, boardSkipped)
        # Ensure no cache issue
        deleteFolder(build_output_cache_dir)
    log_final_result()


# Run arduino-cli command
def build(build_conf):
    cmd = build_conf[4]
    status = [time.monotonic()]
    with open(
        os.path.join(build_conf[3], os.path.basename(cmd[-1]) + ".log"), "w"
    ) as stdout:
        res = subprocess.Popen(cmd, stdout=stdout, stderr=subprocess.STDOUT)
        res.wait()
        status[0] = time.monotonic() - status[0]
        status.append(res.returncode)
        return status


# Parser
parser = argparse.ArgumentParser(
    description="Manage arduino-cli to build sketche(s) for STM32 boards."
)

g0 = parser.add_mutually_exclusive_group()
g0.add_argument(
    "-l",
    "--list",
    help="list available board(s) or sketch(es)",
    nargs="?",
    const="board",
    choices=("board", "sketch"),
)
g0.add_argument(
    "-a",
    "--all",
    help="build all sketches found for all available boards",
    action="store_true",
)

parser.add_argument(
    "-b", "--board", metavar="pattern", help="pattern to build one or more board(s)"
)

parser.add_argument(
    "-c", "--clean", help="clean output directory.", action="store_true"
)
parser.add_argument(
    "--arch",
    metavar="architecture",
    help="core architecture to build. Default build architecture is '"
    + arch_default
    + "'",
)
parser.add_argument(
    "--config",
    metavar="<core configuration file>",
    help="JSON file containing the build configuration for one or more\
    maintainer/architecture. Board options for build, applicability of\
    sketches for boards or required options. If sketch is not listed\
    then applicable to all board. Default core configuration is for '"
    + arch_default
    + " 'architecture in: "
    + cores_config_file_default,
)

parser.add_argument(
    "-u", "--url", metavar="<string>", help="additional URL for the board manager\
    Default url : "
    + stm32_url,
)

parser.add_argument(
    "-v", "--verbose", help="enable arduino-cli verbose mode", action="store_true"
)

g1 = parser.add_mutually_exclusive_group()
g1.add_argument("--ci", help="custom configuration for CI build", action="store_true")

# Sketch options
sketchg0 = parser.add_argument_group(
    title="Sketch(es) options", description="By default build " + sketch_default
)

sketchg1 = sketchg0.add_mutually_exclusive_group()
sketchg1.add_argument(
    "-i", "--ino", metavar="<shetch filepath>", help="single sketch file to build"
)
sketchg1.add_argument(
    "-f",
    "--file",
    metavar="<sketches list filepath>",
    help="file containing list of sketches to build",
)
sketchg1.add_argument(
    "-s",
    "--sketches",
    metavar="pattern",
    help="pattern to find one or more sketch to build",
)
sketchg1.add_argument(
    "-e",
    "--exclude",
    metavar="<excluded sketches list filepath>",
    help="file containing sketches pattern to ignore.\
    Default path : "
    + exclude_file_default,
)

args = parser.parse_args()


def main():
    # check config have to be done first
    check_config()
    if args.clean:
        deleteFolder(root_output_dir)

    load_core_config()
    find_board()
    if args.list == "board":
        print("%i board(s) available" % len(board_fqbn))
        for board in board_fqbn:
            print(board)
        quit()

    manage_inos()
    if args.list == "sketch":
        for sketch in sketch_list:
            print(sketch)
        print("%i sketches found" % len(sketch_list))
        quit()

    if core_config:
        parse_core_config()

    createFolder(build_output_dir)
    createFolder(output_dir)

    build_all()

    deleteFolder(build_output_dir)

    sys.exit(nb_build_failed)


if __name__ == "__main__":
    main()
