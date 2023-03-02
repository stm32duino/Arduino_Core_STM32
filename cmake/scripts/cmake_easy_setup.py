#!/usr/bin/env python3

import argparse
import subprocess
import shutil
import tempfile
import os
import pathlib
import json
from jinja2 import Environment, FileSystemLoader
import difflib

from parse_boards import parse_file

parser = argparse.ArgumentParser()
parser.add_argument(
    "--cli",
    "-x",
    type=pathlib.Path,
    required=False,
    default=shutil.which("arduino-cli"),
    help="path to arduino-cli",
)
parser.add_argument("--board", "-b", type=str, default="", help="board name")
parser.add_argument(
    "--fire",
    action="store_true",
    default=False,
    help="launch the build immediately (use with caution!)",
)
output_args = parser.add_mutually_exclusive_group(required=True)
output_args.add_argument(
    "--output", "-o", type=pathlib.Path, help="output file (CMake) with placeholders"
)
output_args.add_argument(
    "--sketch",
    "-s",
    type=pathlib.Path,
    help="output file (CMake) filled given a sketch folder",
)

shargs = parser.parse_args()
shargs.board = shargs.board.upper()

if shargs.sketch and not shargs.board:
    print(
        """
    Warning: you did not specify which board you were targeting;
    please review the generated CMakeLists.txt to remove the placeholder
    value before calling `cmake`.
    """
    )

if shargs.cli is None:
    print(
        """
    Error: `arduino-cli` not found in $PATH.
    Please install arduino-cli and make it available from your system $PATH,
    or give its location through the `--cli` argument.
    """
    )
    exit(-1)


def arduino(*args):
    # return (out.stdout, logfile)
    # raises an exception if the command fails
    handle, logfile = tempfile.mkstemp()
    os.close(handle)
    out = subprocess.run(
        (shargs.cli, "--log-file", logfile, "--log-format", "json", *args),
        capture_output=True,
        encoding="utf-8",
        check=True,
    ).stdout
    return (out, logfile)


def get_log(fname):
    with open(fname) as file:
        for line in file:
            yield json.loads(line)


def get_boards(boardstxt):

    # we "reject" everything because we don't care about the values, only the keys
    families = parse_file(boardstxt, lambda x: True)
    del families["menu"]

    boards = set()
    for fam, famcfg in families.items():
        boards.update(famcfg.menu.pnum.keys())

    return boards


_, logf = arduino("lib", "list")

allboards = get_boards(pathlib.Path(__file__).parent.parent.parent / "boards.txt")


if shargs.board and shargs.board not in allboards:
    print(f"Unrecognized board name: '{shargs.board}'")
    print("Possible matches:")
    options = difflib.get_close_matches(shargs.board, allboards, n=9, cutoff=0.0)
    print("0. (keep as-is)")
    for i, x in enumerate(options, start=1):
        print(f"{i}. {x}")
    choice = input("Choice number: ")
    while not choice.isdecimal():
        choice = input("Invalid choice *number*. Select a board: ")
    choice = int(choice)
    if choice != 0:
        choice -= 1
        shargs.board = options[choice]


libpaths = dict()
for line in get_log(logf):
    if line["msg"] == "Adding libraries dir":
        libpaths[line["location"]] = pathlib.Path(line["dir"])

# platform lib path is already known, obviously, since that's where this script resides
if "user" in libpaths.keys():
    userlibs = pathlib.Path(libpaths["user"])
    if userlibs.exists():
        userlibs = userlibs.resolve()
        libs = [u.name for u in userlibs.iterdir() if u.is_dir()]
    else:
        print(
            f"""Warning: Cannot find {userlibs}.
        This has likely to do with your arduino-cli configuration.
        Please refer to the following link for setup details:
        https://arduino.github.io/arduino-cli/latest/getting-started/#create-a-configuration-file
        """
        )
        libs = list()
else:
    userlibs = pathlib.Path.home() / "Arduino/libraries"
    print(
        f"""No user library path found through arduino-cli (falling back to {userlibs}).
    This has likely to do with your arduino-cli configuration.
    Please refer to the following link for setup details:
    https://arduino.github.io/arduino-cli/latest/getting-started/#create-a-configuration-file
    """
    )
    libs = list()

corepath = pathlib.Path(__file__).parent.parent.parent.resolve()

j2_env = Environment(
    loader=FileSystemLoader(str(corepath / "cmake" / "templates")),
    trim_blocks=True,
    lstrip_blocks=True,
)
cmake_template = j2_env.get_template("easy_cmake.cmake")


userhome = pathlib.Path.home()
if userlibs.is_relative_to(userhome):
    userlibs = "~/" + str(userlibs.relative_to(userhome))
if corepath.is_relative_to(userhome):
    corepath = "~/" + str(corepath.relative_to(userhome))

if shargs.sketch:
    SOURCEFILE_EXTS = (".c", ".cpp", ".S", ".ino")
    sources = {
        file.relative_to(shargs.sketch)
        for file in shargs.sketch.glob("*")
        if file.is_file() and file.suffix in SOURCEFILE_EXTS
    }
    sources |= {
        file.relative_to(shargs.sketch)
        for file in shargs.sketch.rglob("src/*")
        if file.is_file() and file.suffix in SOURCEFILE_EXTS
    }
    tgtname = shargs.sketch.resolve().name
else:
    tgtname = ""
    sources = set()

scriptname = pathlib.Path(__file__)
if scriptname.is_relative_to(userhome):
    scriptname = "~/" + str(scriptname.relative_to(userhome))

with open(shargs.output or shargs.sketch / "CMakeLists.txt", "w") as out:
    out.write(
        cmake_template.render(
            corepath=str(corepath).replace(
                "\\", "\\\\"
            ),  # escape backslashes for CMake
            userlibs=str(userlibs).replace("\\", "\\\\"),
            libs=libs,
            scriptfile=scriptname,
            tgtname=tgtname,
            scrcfiles=sources,
            boardname=shargs.board,
        )
    )


print("Generated", shargs.output or shargs.sketch / "CMakeLists.txt")
print(
    """
Unless you are building a very simple sketch with no library (e.g., Blink),
you are advised to edit this file to fill in any missing dependency relationship.
For details, please refer to
https://github.com/stm32duino/Arduino_Core_STM32/wiki/Arduino-%28in%29compatibility#library-management
    """
)

if shargs.fire:
    if not (shargs.sketch and shargs.board):
        print(
            "There remains some placeholder in the output file; I won't build _that_."
        )
        exit(1)
    subprocess.run(("cmake", "-S", shargs.sketch, "-B", shargs.sketch / "build"))
    subprocess.run(("cmake", "--build", shargs.sketch / "build"))
