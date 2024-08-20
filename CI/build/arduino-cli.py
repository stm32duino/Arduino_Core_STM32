import argparse
import collections
import concurrent.futures
from datetime import timedelta
from glob import glob
import json
import os
from packaging import version
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile
import textwrap
import time

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils import createFolder, deleteFolder

if sys.platform.startswith("win32"):
    from colorama import init

    init(autoreset=True)

home = Path.home()
tempdir = Path(tempfile.gettempdir())
build_id = time.strftime(".%Y-%m-%d_%H-%M-%S")
path_config_filename = script_path / "path_config.json"

arduino_cli_path = Path("")
stm32_url_base = "https://github.com/stm32duino/BoardManagerFiles/raw/main/"
stm32_url = f"{stm32_url_base}package_stmicroelectronics_index.json"
sketches_path_list = []
search_path_list = []
default_build_output_dir = tempdir / "build_arduinoCliOutput"
build_output_dir = tempdir / f"build_arduinoCliOutput{build_id}"
build_output_cache_dir = build_output_dir / "cache"
root_output_dir = home / "Documents" / "arduinoCliOutput"

output_dir = Path("")
log_file = Path("")

# Output directory path
bin_dir = "binaries"

# Default
sketch_default = script_path / "examples" / "BareMinimum"
exclude_file_default = script_path / "conf" / "exclude_list.txt"
cores_config_file_default = script_path / "conf" / "cores_config.json"
cores_config_file_ci = script_path / "conf" / "cores_config_ci.json"

maintainer_default = "STMicroelectronics"
arch_default = "stm32"
arduino_platform_default = maintainer_default + ":" + arch_default

core_config = None
maintainer = maintainer_default
arch = arch_default
arduino_platform = arduino_platform_default
arduino_cli = ""
arduino_cli_default_ver = "0.19.0"
arduino_cli_ver = arduino_cli_default_ver

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

# error or fatal error
fork_pattern = re.compile(r"^Error during build: fork/exec")
error_pattern = re.compile(r":\d+:\d*:?\s.*error:\s|^Error:|fatal error:")
ld_pattern = re.compile(r"arm-none-eabi/bin/ld\.?e?x?e?:")
overflow_pattern = re.compile(
    r"(will not fit in |section .+ is not within )?region( .+ overflowed by [\d]+ bytes)?"
)

# format
build_format_header = "| {:^8} | {:42} | {:^10} | {:^7} |"
build_format_result = "| {:^8} | {:42} | {:^19} | {:^6.2f}s |"
build_separator = "-" * 80
fsucc = "\033[32msucceeded\033[0m"
ffail = "\033[31mfailed\033[0m"
fskip = "\033[33mskipped\033[0m"
nl = "\n"

# index build configuration
idx_b_name = 0
idx_build = 1
idx_log = 2
idx_cmd = 3


def cat(file):
    with open(file, "r") as f:
        print(f.read())
    print("")


# Create the log output file and folders
def create_output_log_tree():
    # Log output file
    with open(log_file, "w") as file:
        file.write(f"{build_separator}\nStarts ")
        file.write(time.strftime("%A %d %B %Y %H:%M:%S "))
        file.write(f"\nLog will be available here:\n{output_dir.resolve()}\n")
        file.write(f"{build_separator}\n")
    # Folders
    for board in board_fqbn:
        createFolder(output_dir / board / bin_dir)
        createFolder(output_dir / board)
        createFolder(build_output_dir / board)


def create_config():
    global arduino_cli_path
    global sketches_path_list
    global build_output_dir
    global root_output_dir
    # Create a Json file for a better path management
    print(f"'{path_config_filename}' file created.")
    print("Please check the configuration.")
    path_config_file = open(path_config_filename, "w")
    path_config_file.write(
        json.dumps(
            {
                "ARDUINO_CLI_PATH": str(arduino_cli_path),
                "SKETCHES_PATHS": [str(fp) for fp in sketches_path_list],
                "BUILD_OUPUT_DIR": str(default_build_output_dir),
                "ROOT_OUPUT_DIR": str(root_output_dir),
            },
            indent=2,
        )
    )
    path_config_file.close()
    exit(1)


def check_config():
    global arduino_cli
    global arduino_cli_ver
    global arduino_cli_path
    global sketches_path_list
    global search_path_list
    global build_output_dir
    global root_output_dir
    global output_dir
    global log_file
    global stm32_url

    if args.ci is False:
        if path_config_filename.is_file():
            try:
                path_config_file = open(path_config_filename, "r")
                path_config = json.load(path_config_file)
                # Common path
                arduino_cli_path = Path(path_config["ARDUINO_CLI_PATH"])
                sketches_path_list = [Path(fp) for fp in path_config["SKETCHES_PATHS"]]
                build_output_dir = Path(path_config["BUILD_OUPUT_DIR"])
                build_output_dir = build_output_dir.with_suffix(build_id)
                root_output_dir = Path(path_config["ROOT_OUPUT_DIR"])
                path_config_file.close()
            except IOError:
                print("Failed to open " + path_config_file)
        else:
            create_config()

    output_dir = root_output_dir / f"build{build_id}"
    log_file = output_dir / "build_result.log"

    if arduino_cli_path != Path():
        assert arduino_cli_path.exists(), (
            f"Path {arduino_cli_path} does not exist."
            f" Please check path in the json config file."
        )

    if sys.platform.startswith("win32"):
        arduino_cli = str(arduino_cli_path / "arduino-cli.exe")
    else:
        arduino_cli = str(arduino_cli_path / "arduino-cli")

    # Check arduino-cli version
    try:
        output = subprocess.check_output(
            [arduino_cli, "version"],
            stderr=subprocess.STDOUT,
        )
    except subprocess.CalledProcessError as e:
        print(f"'{' '.join(e.cmd)}' failed with code: {e.returncode}!")
        print(e.stdout.decode("utf-8"))
        quit(e.returncode)
    else:
        res = re.match(r".*Version:\s+(\d+\.\d+\.\d+).*", output.decode("utf-8"))
        if res:
            arduino_cli_ver = res.group(1)
            print(f"Arduino CLI version used: {arduino_cli_ver}")
            if version.parse(arduino_cli_ver) < version.parse(arduino_cli_default_ver):
                print(f"Arduino CLI version < {arduino_cli_default_ver} not supported")
        else:
            print("Unable to define Arduino CLI version.")
            print(f"Use default: {arduino_cli_default_ver}")

    if args.url:
        stm32_url = args.url

    # Ensure a configuration exists
    try:
        print("Check/update arduino-cli configuration")
        # Try to create configuration file
        output = subprocess.check_output(
            [arduino_cli, "config", "init", "--additional-urls", stm32_url],
            stderr=subprocess.STDOUT,
        ).decode("utf-8")
    except subprocess.CalledProcessError:
        try:
            output = subprocess.check_output(
                [
                    arduino_cli,
                    "config",
                    "dump",
                ],
                stderr=subprocess.STDOUT,
            )
        except subprocess.CalledProcessError as e:
            print(f"'{' '.join(e.cmd)}' failed with code: {e.returncode}!")
            print(e.stdout.decode("utf-8"))
            quit(e.returncode)
        else:
            # Check if url is already part of the arduino-cli config
            if stm32_url not in output.decode("utf-8"):
                # Add it to the config
                try:
                    output = subprocess.check_output(
                        [
                            arduino_cli,
                            "config",
                            "add",
                            "board_manager.additional_urls",
                            stm32_url,
                        ],
                        stderr=subprocess.STDOUT,
                    )
                except subprocess.CalledProcessError as e:
                    print(f"'{' '.join(e.cmd)}' failed with code: {e.returncode}!")
                    print(e.stdout.decode("utf-8"))
                    quit(e.returncode)
    # Check if requested platform is installed
    try:
        output = subprocess.check_output(
            [
                arduino_cli,
                "core",
                "search",
                "stm32",
            ],
            stderr=subprocess.STDOUT,
        )
    except subprocess.CalledProcessError as e:
        print(f"'{' '.join(e.cmd)}' failed with code: {e.returncode}!")
        print(e.stdout.decode("utf-8"))
        quit(e.returncode)
    else:
        if arduino_platform not in output.decode("utf-8"):
            print(f"{arduino_platform} is not installed!")
            quit(1)
        # Add core and library path to sketches_path_list
        try:
            output = subprocess.check_output(
                [arduino_cli, "config", "dump", "--format", "json"],
                stderr=subprocess.STDOUT,
            ).decode("utf-8")
        except subprocess.CalledProcessError as e:
            print(f"'{' '.join(e.cmd)}' failed with code: {e.returncode}!")
            print(e.stdout.decode("utf-8"))
            quit(e.returncode)
        else:
            cli_config = json.loads(output)
            if cli_config is not None:
                # Since arduino-cli 1.x new level "config"
                if "config" in cli_config.keys():
                    cli_config = cli_config["config"]
                # Since arduino-cli 1.x config init does not create full config
                if "directories" in cli_config.keys():
                    if "data" in cli_config["directories"].keys():
                        if cli_config["directories"]["data"] is not None:
                            sketches_path_list.append(
                                Path(cli_config["directories"]["data"])
                            )
                    else:
                        print("No data directory")
                    if "user" in cli_config["directories"].keys():
                        if cli_config["directories"]["user"] is not None:
                            sketches_path_list.append(
                                Path(cli_config["directories"]["user"])
                            )
                    else:
                        print("No user directory!")
                else:
                    print("No directories in config!")
                # Fill search_path_list to avoid search on the same path
                sorted_spl = sorted(set(sketches_path_list))
                search_path_list = []
                while sorted_spl:
                    p = sorted_spl.pop(0)
                    if not any(root in p.parents for root in search_path_list):
                        search_path_list.append(Path(p))
            else:
                print("No arduino-cli config!")
                quit(1)


def load_core_config():
    global core_config
    global maintainer
    global arch
    cores_config_filename = ""
    if args.config:
        cores_config_filename = Path(args.config)
        assert cores_config_filename.exists(), f"{args.config} not found"
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
                print("Build configuration for:")
                print(f"- '{maintainer}' maintainer")
                print(f"- '{arch}' architecture")
                break
        else:
            print(f"Core architecture '{arch}' not found in:")
            print(f"{cores_config_filename}")
            arch = arch_default
            core_config = None
    except IOError:
        print(f"Can't open {cores_config_filename} file.")
        print("Build configuration will not be used.")
    finally:
        if core_config is None:
            print("Using default configuration for:")
            print(f"- '{maintainer_default}' maintainer")
            print(f"- '{arch_default}' architecture")


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


def manage_exclude_list(exfile):
    with open(exfile, "r") as f:
        for line in f.readlines():
            if line.rstrip():
                exclude_list.append(line.rstrip())
    if exclude_list:
        for pattern in exclude_list:
            exclude_pattern = re.compile(f".*{pattern}.*", re.IGNORECASE)
            for s in reversed(sketch_list):
                if exclude_pattern.search(str(s)):
                    sketch_list.remove(s)


# Manage sketches list
def manage_inos():
    # Find all inos or all patterned inos
    if args.all or args.sketches or args.list == "sketch":
        find_inos()
        if args.exclude:
            exclude_file = Path(args.exclude)
            assert exclude_file.exists(), "Excluded list file does not exist"
            manage_exclude_list(exclude_file)
        elif exclude_file_default.exists():
            manage_exclude_list(exclude_file_default)
    # Only one sketch
    elif args.ino:
        ino_file = Path(args.ino)
        if ino_file.exists():
            # Store only the path
            if ino_file.is_file():
                sketch_list.append(ino_file.parent)
            else:
                sketch_list.append(ino_file)
        else:
            for path in sketches_path_list:
                fp = path / ino_file
                if fp.exists():
                    # Store only the path
                    if fp.is_file():
                        sketch_list.append(fp.parent)
                    else:
                        sketch_list.append(fp)
                    break
            else:
                print(f"Sketch {args.ino} path does not exist!")
                quit(1)
    # Sketches listed in a file
    elif args.file:
        sketches_files = Path(args.file)
        assert sketches_files.exists(), f"{sketches_files} not found"
        with open(sketches_files, "r") as f:
            for line in f.readlines():
                if line.rstrip():
                    ino = Path(line.rstrip())
                    if ino.exists():
                        # Store only the path
                        if ino.is_file():
                            sketch_list.append(ino.parent)
                        else:
                            sketch_list.append(ino)
                    else:
                        for path in sketches_path_list:
                            fp = path / ino
                            if fp.exists():
                                # Store only the path
                                if fp.is_file():
                                    sketch_list.append(fp.parent)
                                else:
                                    sketch_list.append(fp)
                                break
                        else:
                            print(f"Ignore {ino} as it does not exist.")
    # Default sketch to build
    else:
        sketch_list.append(sketch_default)
    if len(sketch_list) == 0:
        print(f"No sketch to build for {arduino_platform}!")
        quit(1)


# Find all .ino files and save directory
def find_inos():
    global sketch_list
    # key: path, value: name
    if args.sketches:
        arg_sketch_pattern = re.compile(args.sketches, re.IGNORECASE)
    for spath in search_path_list:
        # Due to issue with Path.glob() which does not follow symlink
        # use glob.glob
        # See: https://bugs.python.org/issue33428
        # for spath_object in spath.glob("**/*.[ip][nd][oe]"):
        #     if args.sketches:
        #         if arg_sketch_pattern.search(str(spath_object)) is None:
        #             continue
        #     if spath_object.is_file():
        #         sketch_list.append(spath_object.parent)
        for sk_ino in glob(str(spath / "**" / "*.[ip][nd][oe]"), recursive=True):
            if args.sketches:
                if arg_sketch_pattern.search(sk_ino) is None:
                    continue
            p_ino = Path(sk_ino)
            if p_ino.is_file():
                sketch_list.append(p_ino.parent)
    sketch_list = sorted(set(sketch_list))


# Return a list of all board using the arduino-cli for the specified
# architecture
def find_board():
    global board_fqbn
    board_found = {}

    if args.board:
        arg_board_pattern = re.compile(args.board, re.IGNORECASE)

    try:
        output = subprocess.check_output(
            [arduino_cli, "board", "search", arduino_platform, "--format", "json"],
            stderr=subprocess.STDOUT,
        ).decode("utf-8")
    except subprocess.CalledProcessError as e:
        print(f"'{' '.join(e.cmd)}' failed with code: {e.returncode}!")
        print(e.stdout.decode("utf-8"))
        quit(e.returncode)
    else:
        boards = json.loads(output)
        # Since arduino-cli 1.x new level "boards" and is a dict
        if type(boards) is dict:
            boards = boards["boards"]
        fqbn_list_tmp = [board["fqbn"] for board in boards]
        if not len(fqbn_list_tmp):
            print(f"No boards found for {arduino_platform}")
            quit(1)

    # For STM32 core, pnum is requested
    for fqbn in fqbn_list_tmp:
        try:
            output = subprocess.check_output(
                [
                    arduino_cli,
                    "board",
                    "details",
                    "--format",
                    "json",
                    "-b",
                    fqbn,
                ],
                stderr=subprocess.STDOUT,
            ).decode("utf-8")
        except subprocess.CalledProcessError as e:
            print(f"'{' '.join(e.cmd)}' failed with code: {e.returncode}!")
            print(e.stdout.decode("utf-8"))
            quit(e.returncode)
        else:
            board_detail = json.loads(output)
            for val in next(
                (
                    item
                    for item in board_detail.get("config_options", [])
                    if item["option"] == "pnum"
                ),
                {},
            ).get("values", []):
                if args.board:
                    if arg_board_pattern.search(val["value"]) is None:
                        continue
                board_found[val["value"]] = f"{fqbn}:pnum={val['value']}"
    if board_found:
        board_fqbn = collections.OrderedDict(sorted(board_found.items()))
    else:
        print(f"No board found for {arduino_platform}!")
        quit(1)


# Check the status
def check_status(status, build_conf, boardKo, nb_build_conf):
    global nb_build_passed
    global nb_build_failed
    sketch_name = build_conf[idx_cmd][-1].name

    if status[1] == 0:
        result = fsucc
        nb_build_passed += 1
    elif status[1] == 1:
        # Check if failed due to a region overflowed
        logFile = build_conf[idx_log] / f"{sketch_name}.log"
        error_found = False
        overflow_found = False
        for i, line in enumerate(open(logFile)):
            if error_pattern.search(line):
                error_found = True
            elif fork_pattern.search(line):
                error_found = True
            elif ld_pattern.search(line):
                # If one ld line is not for region overflowed --> failed
                if overflow_pattern.search(line) is None:
                    error_found = True
                else:
                    overflow_found = True
            if error_found:
                break
        # Succeeded if overflow is found and no other error found
        if overflow_found and not error_found:
            result = "\033[32msucceeded*\033[0m"
            nb_build_passed += 1
        else:
            result = ffail
            boardKo.append(build_conf[idx_b_name])
            if args.ci:
                cat(logFile)
            nb_build_failed += 1
    else:
        result = "\033[31merror\033[0m"
        boardKo.append(build_conf[idx_b_name])
        nb_build_failed += 1
    print(
        f"{build_format_result}".format(
            f"{build_conf[idx_build]}/{nb_build_conf}",
            build_conf[idx_b_name],
            result,
            status[0],
        )
    )


# Log sketch build result
def log_sketch_build_result(sketch, boardKo, boardSkipped):
    nb_ok = len(board_fqbn) - len(boardKo) - len(boardSkipped)
    nb_ko = len(boardKo)
    nb_na = len(boardSkipped)
    # Log file
    with open(log_file, "a") as f:
        f.write(build_separator + "\n")
        bcounter = f"{sketch_list.index(sketch) + 1}/{len(sketch_list)}"
        f.write(f"Sketch: {sketch.name} ({bcounter})\n")
        f.write(str(sketch.parent))
        f.write(f"\n{nb_ok} succeeded, {nb_ko} failed, {nb_na} skipped\n")

        if len(boardKo):
            sKo = ", ".join(boardKo)
            wKo = textwrap.wrap(sKo, 80, break_long_words=False)
            f.write(f"Failed boards :\n{nl.join(wKo)}")
            # f.write("Failed boards :\n" + "\n".join(boardKo))
            f.write("\n")
        if len(boardSkipped):
            sskipped = ", ".join(boardSkipped)
            wskipped = textwrap.wrap(sskipped, 80, break_long_words=False)
            f.write(f"Skipped boards :\n{nl.join(wskipped)}")
            # f.write("Skipped boards :\n" + "\n".join(boardSkipped))
            f.write("\n")
        f.write(f"{build_separator}\n")

    # Standard output
    print(build_separator)

    print(f"Build Summary: {nb_ok} {fsucc}, {nb_ko} {ffail}, {nb_na} {fskip}")
    print(build_separator)


# Log final result
def log_final_result():
    # Also equal to len(board_fqbn) * len(sketch_list)
    nb_build_total = nb_build_passed + nb_build_failed
    if nb_build_total != 0:
        stat_passed = round(nb_build_passed * 100.0 / nb_build_total, 2)
        stat_failed = round(nb_build_failed * 100.0 / nb_build_total, 2)
    else:
        stat_passed = 0
        stat_failed = 0
    duration = str(timedelta(seconds=time.time() - full_buildTime))

    # Log file
    with open(log_file, "a") as f:
        f.write(f"\n{build_separator}\n")
        f.write("| {:^76} |\n".format("Build summary"))
        f.write(build_separator + "\n")
        ssucc = f"{nb_build_passed} succeeded ({stat_passed}%)"
        sfail = f"{nb_build_failed} failed ({stat_failed}%)"
        sskip = f"{nb_build_skipped} skipped)"
        f.write(f"{ssucc}, {sfail}  of {nb_build_total} builds ({sskip})\n")
        f.write(f"Ends {time.strftime('%A %d %B %Y %H:%M:%S')}\n")
        f.write(f"Duration: {duration}\n")
        f.write(f"Logs are available here:\n{output_dir}\n")
        f.write(f"{build_separator}\n\n")

    # Standard output
    ssucc = f"{nb_build_passed} {fsucc} ({stat_passed}%)"
    sfail = f"{nb_build_failed} {ffail} ({stat_failed}%)"
    sskip = f"{nb_build_skipped} {fskip}"
    print(f"Builds Summary: {ssucc}, {sfail} of {nb_build_total} builds ({sskip})")
    print(f"Duration: {duration}")
    print("Logs are available here:")
    print(output_dir)


# Set up specific options to customise arduino-cli command
def get_fqbn(b_name):
    if b_name in board_custom_fqbn and board_custom_fqbn[b_name]:
        return board_custom_fqbn[b_name]
    else:
        if b_name in board_options and board_options[b_name]:
            return f"{board_fqbn[b_name]},{board_options[b_name]}"
        else:
            return board_fqbn[b_name]


# Generate arduino-cli basic command
def genBasicCommand(b_name):
    cmd = []
    cmd.append(arduino_cli)
    cmd.append("compile")
    # cmd.append("-warnings=all")
    cmd.append("--build-path")
    cmd.append(build_output_dir / b_name)
    cmd.append("--build-cache-path")
    cmd.append(build_output_cache_dir)
    if args.verbose:
        cmd.append("--verbose")
    cmd.append("--output-dir")
    cmd.append(output_dir / b_name / bin_dir)
    cmd.append("--fqbn")
    cmd.append(get_fqbn(b_name))
    cmd.append("dummy_sketch")
    return cmd


def create_build_conf_list():
    build_conf_list = []
    for idx, b_name in enumerate(board_fqbn, start=1):
        build_conf_list.append(
            [
                b_name,
                idx,
                output_dir / b_name,
                genBasicCommand(b_name),
            ]
        )
    return build_conf_list


def build_config(sketch, boardSkipped):
    global nb_build_skipped
    build_conf_list = []
    build_conf_list_tmp = create_build_conf_list()

    while len(build_conf_list_tmp):
        build_conf = build_conf_list_tmp.pop(0)
        build_conf[idx_cmd][-1] = sketch
        b_name = build_conf[idx_b_name]
        s_sketch = str(sketch)
        build_conf[idx_build] = len(build_conf_list) + 1
        if b_name in na_sketch_pattern:
            for pattern in na_sketch_pattern[b_name]:
                if re.search(pattern, s_sketch, re.IGNORECASE):
                    boardSkipped.append(b_name)
                    nb_build_skipped += 1
                    break
            else:
                # Get specific sketch options to append to the fqbn
                for pattern in sketch_options:
                    if re.search(pattern, s_sketch, re.IGNORECASE):
                        if build_conf[idx_cmd][-2].count(":") == 3:
                            build_conf[idx_cmd][-2] += f",{sketch_options[pattern]}"
                        else:
                            build_conf[idx_cmd][-2] += f":{sketch_options[pattern]}"
                build_conf_list.append(build_conf)
        else:
            build_conf_list.append(build_conf)
    return build_conf_list


# Automatic run
def build_all():
    create_output_log_tree()
    wrapper = textwrap.TextWrapper(width=76)
    if args.dry:
        print("Performing a dry run (no build)")
        build = dry_build
    else:
        build = real_build

    for sketch_nb, sketch in enumerate(sketch_list, start=1):
        boardKo = []
        boardSkipped = []
        print(f"\n{build_separator}")
        print(
            "| {:^85} |".format(
                f"Sketch \033[34m{sketch.name}\033[0m ({sketch_nb}/{len(sketch_list)})"
            )
        )
        wrapped_path_ = wrapper.wrap(text=str(sketch.parent))
        for line in wrapped_path_:
            print("| {:^76} |".format(f"{line}"))
        print(build_separator)
        print((build_format_header).format("Num", "Board", "Result", "Time"))
        print(build_separator)

        build_conf_list = build_config(sketch, boardSkipped)
        nb_build_conf = len(build_conf_list)
        with concurrent.futures.ProcessPoolExecutor(os.cpu_count() - 1) as executor:
            for build_conf, res in zip(
                build_conf_list, executor.map(build, build_conf_list)
            ):
                check_status(res, build_conf, boardKo, nb_build_conf)
        log_sketch_build_result(sketch, boardKo, boardSkipped)
        # Ensure no cache issue
        deleteFolder(build_output_cache_dir)
    log_final_result()


# Run arduino-cli command
def real_build(build_conf):
    cmd = build_conf[idx_cmd]
    status = [time.monotonic()]
    with open(build_conf[idx_log] / f"{cmd[-1].name}.log", "w") as stdout:
        res = subprocess.Popen(cmd, stdout=stdout, stderr=subprocess.STDOUT)
        res.wait()
        status[0] = time.monotonic() - status[0]
        status.append(res.returncode)
        return status


# Run arduino-cli command
def dry_build(build_conf):
    # cmd = build_conf[4]
    status = [random.random() * 10, random.randint(0, 1)]
    if status[1] == 1:
        # Create dummy log file
        logFile = build_conf[idx_log] / f"{ build_conf[idx_cmd][-1].name}.log"
        # random failed
        dummy = open(logFile, "w")
        if random.randint(0, 1) == 1:
            dummy.writelines("region `FLASH' overflowed by 5612 bytes")
        else:
            dummy.writelines("Error:")
        dummy.close()
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
    "-d", "--dry", help="perform a dry run (no build)", action="store_true"
)

parser.add_argument(
    "--arch",
    metavar="architecture",
    help=f"core architecture to build. Default build architecture is {arch_default}",
)
parser.add_argument(
    "--config",
    metavar="<core configuration file>",
    help=f"JSON file containing the build configuration for one or more\
    maintainer/architecture. Board options for build, applicability of\
    sketches for boards or required options. If sketch is not listed\
    then applicable to all board. Default core configuration is for\
    '{arch_default}' architecture in: {cores_config_file_default}",
)

parser.add_argument(
    "-u",
    "--url",
    metavar="<string>",
    help=f"additional URL for the board manager\
    Default url : {stm32_url}",
)

parser.add_argument(
    "-v", "--verbose", help="enable arduino-cli verbose mode", action="store_true"
)

g1 = parser.add_mutually_exclusive_group()
g1.add_argument("--ci", help="custom configuration for CI build", action="store_true")

# Sketch options
sketchg0 = parser.add_argument_group(
    title="Sketch(es) options", description=f"By default build {sketch_default}"
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
    help=f"file containing sketches pattern to ignore.\
    Default path : {exclude_file_default}",
)

args = parser.parse_args()


def main():
    # check config have to be done first
    check_config()
    if args.clean:
        deleteFolder(root_output_dir)

    load_core_config()
    if args.list != "sketch":
        find_board()
    if args.list == "board":
        for board in board_fqbn:
            print(board)
        print(f"{len(board_fqbn)} board(s) available")
        quit()

    manage_inos()
    if args.list == "sketch":
        for sketch in sketch_list:
            print(sketch)
        print(f"{len(sketch_list)} sketches found")
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
