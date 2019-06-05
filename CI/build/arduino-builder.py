# -*- coding: utf-8 -*-

# File name            : arduino-builder.py
# Author               : Angela RANDOLPH <angela.randolph@reseau.eseo.fr>
# Other contributors   : Frederic PILLON <frederic.pillon@st.com>
# Created              : 26/04/2018
# Python Version       : >= 3.2 (due to concurrent.futures usage)

# Description         : Used to build sketch(es) thanks to Arduino Builder
#                       See https://github.com/arduino/arduino-builder
import os
import re
import sys
import json
import time
import shutil
import subprocess
import tempfile
import argparse
import concurrent.futures
import collections
from datetime import timedelta

# Create a Json file for a better path management
path_config_filename = "path_config.json"
home = os.path.expanduser("~")
tempdir = tempfile.gettempdir()
build_id = time.strftime("_%Y-%m-%d_%H-%M-%S")
script_path = os.path.dirname(os.path.abspath(__file__))

try:
    path_config_file = open(path_config_filename, "r")
except IOError:
    print(
        "Please set your configuration in '{}' file".format(
            os.path.join(script_path, path_config_filename)
        )
    )
    path_config_file = open(path_config_filename, "w")
    if sys.platform.startswith("win32"):
        print("Default config set for Windows environment.")
        arduino_path = "C:\\Program Files (x86)\\Arduino"  # arduino default path
        arduino_packages = home + "\\AppData\\Local\\Arduino15\\packages"  # Windows 7
        arduino_user_sketchbook = home + "\\My Documents\\Arduino"
        # Windows 7 temporary directory using by arduino builder
        build_output_dir = tempdir + "\\temp_arduinoBuilderOutput"
        root_output_dir = home + "\\arduinoBuilderOutput"  # output directory
    elif sys.platform.startswith("linux"):
        print("Default config set for Linux environment.")
        arduino_path = home + "/Documents/arduino-1.8.5"
        arduino_packages = home + "/.arduino15/packages"
        arduino_user_sketchbook = home + "/Documents/Arduino"
        build_output_dir = tempdir + "/temp_arduinoBuilderOutput"
        root_output_dir = home + "/Documents/arduinoBuilderOutput"
    elif sys.platform.startswith("darwin"):
        print("Default config set for Mac OSX environment.")
        arduino_path = home + "/Applications/Arduino/"
        arduino_packages = home + "/Library/Arduino15/packages"
        arduino_user_sketchbook = home + "/Documents/Arduino"
        build_output_dir = tempdir + "/temp_arduinoBuilderOutput"
        root_output_dir = home + "/Documents/arduinoBuilderOutput"
    else:
        print("Platform unknown.")
        arduino_path = "<Set Arduino install path>"
        arduino_packages = "<Set Arduino packages install path>"
        arduino_user_sketchbook = "<Set the user sketchbook location>"
        build_output_dir = "<Set arduino builder temporary folder install path>"
        root_output_dir = "<Set your output directory path>"
    path_config_file.write(
        json.dumps(
            {
                "ARDUINO_PATH": arduino_path,
                "ARDUINO_PACKAGES": arduino_packages,
                "ARDUINO_USER_SKETCHBOOK": arduino_user_sketchbook,
                "BUILD_OUPUT_DIR": build_output_dir,
                "ROOT_OUPUT_DIR": root_output_dir,
            },
            indent=2,
        )
    )
    path_config_file.close()
    exit(1)

path_config = json.load(path_config_file)
path_config_file.close()

# Common path
arduino_path = path_config["ARDUINO_PATH"]
arduino_packages = path_config["ARDUINO_PACKAGES"]
arduino_user_sketchbook = path_config["ARDUINO_USER_SKETCHBOOK"]
build_output_dir = path_config["BUILD_OUPUT_DIR"] + build_id
root_output_dir = path_config["ROOT_OUPUT_DIR"]

assert os.path.exists(
    arduino_path
), "Path does not exist: {} . Please set this path in the json config file".format(
    arduino_path
)
assert os.path.exists(
    arduino_packages
), "Path does not exist: {} . Please set this path in the json config file".format(
    arduino_packages
)

assert os.path.exists(
    arduino_user_sketchbook
), "Path does not exist: {} . Please set this path in the json config file".format(
    arduino_user_sketchbook
)

arduino_builder = os.path.join(arduino_path, "arduino-builder")
arduino_hardware_path = os.path.join(arduino_path, "hardware")
arduino_lib_path = os.path.join(arduino_path, "libraries")
arduino_sketchbook_path = os.path.join(arduino_path, "examples")
arduino_user_lib_path = os.path.join(arduino_user_sketchbook, "libraries")
tools_path = os.path.join(arduino_path, "tools-builder")
output_dir = os.path.join(root_output_dir, "build" + build_id)
log_file = os.path.join(output_dir, "build_result.log")

# Ouput directory path
bin_dir = "binaries"

# Default
sketch_default = os.path.join(
    arduino_sketchbook_path, "01.Basics", "BareMinimum", "BareMinimum.ino"
)
exclude_file_default = os.path.join("conf", "exclude_list.txt")
cores_config_file_default = os.path.join("conf", "cores_config.json")
cores_config_file_travis = os.path.join("conf", "cores_config_travis.json")

maintainer_default = "STM32"
arch_default = "stm32"

core_config = None
maintainer = maintainer_default
arch = arch_default
core_path = ""

# List
sketch_list = []
exclude_list = []

# Dict
board_type = collections.OrderedDict()  # (key: board name, value: board type)
board_fqbn = {}  # key: board name, value: fqbn
board_options = {}  # key: board name, value: options
sketch_options = {}  # key: sketch pattern, value: options
na_sketch_pattern = {}  # key: board name, value: sketch pattern list
core_api_version = "10805"

# Counter
nb_build_passed = 0
nb_build_failed = 0
nb_build_skipped = 0

# Timing
startTime = time.time()


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
        file.write("************************************** \n")
        file.write("*********** OUTPUT / RESULT ********** \n")
        file.write("************************************** \n")
        file.write(time.strftime("%A %d %B %Y %H:%M:%S "))
        file.write("\nPath : {} \n".format(os.path.abspath(output_dir)))
    # Folders
    for board in board_type:
        createFolder(os.path.join(output_dir, board))
        if args.bin:
            createFolder(os.path.join(output_dir, board, bin_dir))
        createFolder(os.path.join(build_output_dir, board))


def get_ide_version():
    global core_api_version
    try:
        output = subprocess.check_output(
            [os.path.join(arduino_path, "arduino"), "--version"],
            stderr=subprocess.DEVNULL,
        )
        res = re.match("\\D*(\\d)\\.(\\d+)\\.(\\d+)", output.decode("utf-8"))
        if res:
            core_api_version = (
                res.group(1) + res.group(2).zfill(2) + res.group(3).zfill(2)
            )
            print("Arduino IDE version used: " + core_api_version)
        else:
            raise subprocess.CalledProcessError(1, "re")
    except subprocess.CalledProcessError:
        print("Unable to define Arduino IDE version, use default: " + core_api_version)


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
        if args.travis:
            cores_config_filename = cores_config_file_travis
        else:
            cores_config_filename = cores_config_file_default
    print("Cores configuration JSON file that will be used: " + cores_config_filename)
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
    assert board_type, "Board list not initialized"
    # Extract boards names to create a set
    board_name_set = set([board for board in board_type])
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
            board_fqbn[board["name"]] = board["fqbn"]
        if "options" in board:
            board_options[board["name"]] = board["options"]

    # for key, value in na_sketch_pattern.items():
    #    print("{}: {}\n".format(key, value))
    # for key, value in board_fqbn.items():
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
            sketch_list.append(args.ino)
        else:
            assert os.path.exists(
                os.path.join(arduino_path, args.ino)
            ), "Sketch path does not exist"
            sketch_list.append(os.path.join(arduino_path, args.ino))
    # Sketches listed in a file
    elif args.file:
        assert os.path.exists(args.file), "Sketches list file does not exist"
        with open(args.file, "r") as f:
            for line in f.readlines():
                if line.rstrip():
                    ino = line.rstrip()
                    if os.path.exists(ino):
                        sketch_list.append(ino)
                    elif os.path.exists(os.path.join(arduino_path, ino)):
                        sketch_list.append(os.path.join(arduino_path, ino))
                    else:
                        print("Ignore {} as does not exist.".format(ino))
    # Default sketch to build
    else:
        sketch_list.append(sketch_default)
    assert len(sketch_list), "No sketch to build!"


# Find all .ino files
def find_inos():
    # Path list order must be kept as we avoid duplicated sketch name
    # Last one found will be kept
    # Preferred order is: user, core then offical
    pathList = [
        arduino_sketchbook_path,
        arduino_lib_path,
        core_path,
        arduino_user_sketchbook,
    ]
    # key: path, value: name
    ordered_path = collections.OrderedDict()
    # key: name, value: path
    ordered_name = collections.OrderedDict()
    if args.sketches:
        arg_sketch_pattern = re.compile(args.sketches, re.IGNORECASE)
    for path in pathList:
        for root, dirs, files in os.walk(path, followlinks=True):
            for file in files:
                if file.endswith((".ino", ".pde")):
                    if args.sketches:
                        if arg_sketch_pattern.search(os.path.join(root, file)) is None:
                            continue
                    if root in ordered_path:
                        # If several sketch are in the same path
                        # Check which one to kept
                        # Commonly, example structure is:
                        # dirname/dirname.ino
                        if (
                            os.path.basename(root)
                            == os.path.splitext(ordered_path[root])[0]
                        ):
                            continue
                    ordered_path[root] = file
    # Remove duplicated sketch name
    for path, name in ordered_path.items():
        ordered_name[name] = path
    for name, path in ordered_name.items():
        sketch_list.append(os.path.join(path, name))
    sketch_list.sort()


# Return a list of all board using the board.txt file for the specified architecture
def find_board():
    global core_path
    global board_type
    board_found = {}
    # board can be available at 2 differents menu levels:
    #  - First:
    # genericSTM32F103C.build.variant=generic_stm32f103c
    #  - Second:
    # Nucleo_144.menu.pnum.NUCLEO_L496ZG-P.build.variant=NUCLEO_L496ZG
    # genericSTM32F103C.menu.device_variant.STM32F103C8=
    # genericSTM32F103R.menu.device_variant.STM32F103R8.build.variant
    board_pattern = re.compile(
        "([^#\\.]+)(?:\\.menu\\.(?:pnum|device_variant)\\.)?([^\\.]+)?(?:\\.build\\.variant)?="
    )
    core_pattern = re.compile(
        "\\"
        + os.path.sep
        + maintainer
        + "\\"
        + os.path.sep
        + "[^\\"
        + os.path.sep
        + "]*\\"
        + os.path.sep
        + "?"
        + arch
    )
    if args.board:
        arg_board_pattern = re.compile(args.board, re.IGNORECASE)
    for path in [arduino_packages, arduino_hardware_path]:
        for root, dirs, files in os.walk(path, followlinks=True):
            if "boards.txt" in files and core_pattern.search(root):
                core_path = root
                with open(os.path.join(root, "boards.txt"), "r") as f:
                    for line in f.readlines():
                        res = board_pattern.match(line)
                        if res:
                            if args.board:
                                if res.lastindex == 1:
                                    if arg_board_pattern.search(res.group(1)) is None:
                                        continue
                                else:
                                    if arg_board_pattern.search(res.group(2)) is None:
                                        continue

                            if res.lastindex == 1:
                                board_found[res.group(1)] = ""
                            else:
                                if res.group(1) in board_found:
                                    del board_found[res.group(1)]
                                board_found[res.group(2)] = res.group(1)
                if board_found:
                    board_type = collections.OrderedDict(sorted(board_found.items()))
                    return
    assert board_type, "No board found!"


# Check the status
def check_status(status, build_conf, boardKo):
    global nb_build_passed
    global nb_build_failed
    sketch_name = os.path.basename(build_conf[4][-1])
    if status == 0:
        print("  --> " + build_conf[0] + " SUCESS")
        if args.bin:
            bin_copy(build_conf[0], sketch_name)
        nb_build_passed += 1
    elif status == 1:
        print("  --> " + build_conf[0] + " FAILED")
        boardKo.append(build_conf[0])
        if args.travis:
            cat(os.path.join(build_conf[3], sketch_name + ".log"))
        nb_build_failed += 1
    else:
        print("Error ! Check the run_command exit status ! Return code = " + status)


# Log sketch build result
def log_sketch_build_result(sketch, boardKo, boardSkipped):
    with open(log_file, "a") as f:
        f.write(
            """
Sketch: {0}/{1}
{2}
Build PASSED: {3}/{4}
Build FAILED: {5}/{4}
Build SKIPPED: {6}/{4}
""".format(
                sketch_list.index(sketch) + 1,
                len(sketch_list),
                sketch,
                len(board_type) - len(boardKo) - len(boardSkipped),
                len(board_type),
                len(boardKo),
                len(boardSkipped),
            )
        )
        if len(boardKo):
            f.write("Failed boards :\n" + "\n".join(boardKo))
            f.write("\n")
        if len(boardSkipped):
            f.write("Skipped boards :\n" + "\n".join(boardSkipped))
            f.write("\n")


# Log final result
def log_final_result():
    # Also equal to len(board_type) * len(sketch_list)
    nb_build_total = nb_build_passed + nb_build_failed + nb_build_skipped
    passed = "TOTAL PASSED = {}/{} ({}%) ".format(
        nb_build_passed,
        nb_build_total,
        round(nb_build_passed * 100.0 / nb_build_total, 2),
    )
    failed = "TOTAL FAILED = {}/{} ({}%) ".format(
        nb_build_failed,
        nb_build_total,
        round(nb_build_failed * 100.0 / nb_build_total, 2),
    )
    skipped = "TOTAL SKIPPED = {}/{} ({}%) ".format(
        nb_build_skipped,
        nb_build_total,
        round(nb_build_skipped * 100.0 / nb_build_total, 2),
    )
    duration = str(timedelta(seconds=time.time() - startTime))
    with open(log_file, "a") as f:
        f.write("\n****************** PROCESSING COMPLETED ******************\n")
        f.write(time.strftime("%A %d %B %Y %H:%M:%S\n"))
        f.write("{}\n".format(passed))
        f.write("{}\n".format(failed))
        f.write("{}\n".format(skipped))
        f.write("Logs are available here: {}\n".format(output_dir))
        f.write("Build duration: " + duration)
    print("\n****************** PROCESSING COMPLETED ******************")
    print(passed)
    print(failed)
    print(skipped)
    print("Logs are available here: " + output_dir)
    print("Build duration: " + duration)


# Create a "bin" directory for each board and copy all binary files
# from the builder output directory into it
def bin_copy(board_name, sketch_name):
    try:
        shutil.copy(
            os.path.join(build_output_dir, board_name, sketch_name + ".bin"),
            os.path.abspath(os.path.join(output_dir, board_name, bin_dir)),
        )
    except OSError as e:
        print(
            "Impossible to copy the binary from the arduino builder output: "
            + e.strerror
        )
        raise


# Set up specific options to customise arduino builder command
def get_fqbn(b_name, b_type):
    if b_name in board_fqbn and board_fqbn[b_name]:
        return board_fqbn[b_name]
    else:
        if b_type:
            if arch == "stm32":
                opt = b_type + ":pnum=" + b_name
            else:
                opt = b_type + ":device_variant=" + b_name
            if b_name in board_options and board_options[b_name]:
                opt += "," + board_options[b_name]
        else:
            opt = b_name
            if b_name in board_options and board_options[b_name]:
                opt += ":" + board_options[b_name]
    return maintainer + ":" + arch + ":" + opt


# Generate arduino builder basic command
def genBasicCommand(b_name, b_type):
    cmd = []
    cmd.append(arduino_builder)
    cmd.append("-hardware")
    cmd.append(arduino_hardware_path)
    cmd.append("-hardware")
    cmd.append(arduino_packages)
    cmd.append("-tools")
    cmd.append(tools_path)
    cmd.append("-tools")
    cmd.append(arduino_packages)
    cmd.append("-libraries")
    cmd.append(arduino_lib_path)
    cmd.append("-libraries")
    cmd.append(arduino_user_lib_path)
    cmd.append("-core-api-version=" + core_api_version)
    cmd.append("-warnings=all")
    if args.verbose:
        cmd.append("-verbose")
    cmd.append("-build-path")
    cmd.append(os.path.join(build_output_dir, b_name))
    cmd.append("-fqbn")
    cmd.append(get_fqbn(b_name, b_type))
    cmd.append("dummy_sketch")
    return cmd


def create_build_conf_list():
    build_conf_list = []
    idx = 1
    for b_name in board_type:
        build_conf_list.append(
            (
                b_name,
                idx,
                len(board_type),
                os.path.join(output_dir, b_name),
                genBasicCommand(b_name, board_type[b_name]),
            )
        )
        idx += 1
    return build_conf_list


def build_config(sketch, boardSkipped):
    global nb_build_skipped
    build_conf_list = create_build_conf_list()

    for idx in reversed(range(len(build_conf_list))):
        build_conf_list[idx][4][-1] = sketch
        if na_sketch_pattern:
            if build_conf_list[idx][0] in na_sketch_pattern:
                for pattern in na_sketch_pattern[build_conf_list[idx][0]]:
                    if re.search(pattern, sketch, re.IGNORECASE):
                        print(
                            "Build {} ({}/{})... SKIPPED".format(
                                build_conf_list[idx][0],
                                build_conf_list[idx][1],
                                build_conf_list[idx][2],
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

    for sketch_nb, sketch in enumerate(sketch_list, start=1):
        boardKo = []
        boardSkipped = []
        print("\nBuilding : {} ({}/{}) ".format(sketch, sketch_nb, len(sketch_list)))
        build_conf_list = build_config(sketch, boardSkipped)
        with concurrent.futures.ProcessPoolExecutor() as executor:
            for build_conf, res in zip(
                build_conf_list, executor.map(build, build_conf_list)
            ):
                check_status(res, build_conf, boardKo)
        log_sketch_build_result(sketch, boardKo, boardSkipped)
    log_final_result()


# Run arduino builder command
def build(build_conf):
    print("Build {} ({}/{})... ".format(build_conf[0], build_conf[1], build_conf[2]))
    cmd = build_conf[4]
    with open(
        os.path.join(build_conf[3], os.path.basename(cmd[-1]) + ".log"), "w"
    ) as stdout:
        res = subprocess.Popen(cmd, stdout=stdout, stderr=subprocess.STDOUT)
        res.wait()
        return res.returncode


# Parser
parser = argparse.ArgumentParser(
    description="Manage arduino-builder command line tool for compiling\
    Arduino sketch(es)."
)

g0 = parser.add_mutually_exclusive_group()
g0.add_argument(
    "-l",
    "--list",
    help="list available board(s) or sketch(es)",
    nargs="?",
    const="board",
    # default="board",
    choices=("board", "sketch"),
)
g0.add_argument(
    "-a",
    "--all",
    help="build all sketches found for all available boards",
    action="store_true",
)
parser.add_argument(
    "-b",
    "--board",
    metavar="pattern",
    help="pattern to find one or more board(s) to build",
)
parser.add_argument(
    "-c",
    "--clean",
    help="clean output directory " + root_output_dir,
    action="store_true",
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
    + os.path.join(script_path, cores_config_file_default),
)

parser.add_argument(
    "-v", "--verbose", help="enable arduino-builder verbose mode", action="store_true"
)

g1 = parser.add_mutually_exclusive_group()
g1.add_argument("--bin", help="save binaries", action="store_true")
g1.add_argument(
    "--travis", help="Custom configuration for Travis CI build", action="store_true"
)

# Sketch options
sketchg0 = parser.add_argument_group(
    title="Sketch(es) options", description="By default build " + sketch_default
)

sketchg1 = sketchg0.add_mutually_exclusive_group()
sketchg1.add_argument(
    "-i", "--ino", metavar="<shetch filepath>", help="single ino file to build"
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
    help="file containing pattern of sketches to ignore.\
    Default path : "
    + os.path.join(script_path, exclude_file_default),
)

args = parser.parse_args()


def main():
    if args.clean:
        deleteFolder(root_output_dir)

    get_ide_version()

    load_core_config()

    find_board()
    if args.list == "board":
        print("%i board(s) available" % len(board_type))
        for board in board_type:
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

    if nb_build_failed:
        sys.exit(1)


if __name__ == "__main__":
    main()
