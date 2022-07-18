#!/usr/bin/env python3

import argparse
import subprocess
import shutil
import tempfile
import os
import pathlib
import json
from jinja2 import Environment, FileSystemLoader

parser = argparse.ArgumentParser()
parser.add_argument("--cli", "-x", type=pathlib.Path, required=False, default=shutil.which("arduino-cli"), help="path to arduino-cli")
parser.add_argument("--board", "-b", type=str, default="", help="board name")
parser.add_argument("--fire", action="store_true", default=False, help="launch the build immediately (use with caution!)")
output_args = parser.add_mutually_exclusive_group(required=True)
output_args.add_argument("--output", "-o", type=pathlib.Path, help="output file (CMake) with placeholders")
output_args.add_argument("--sketch", "-s", type=pathlib.Path, help="output file (CMake) filled given a sketch folder")

shargs = parser.parse_args()

if shargs.sketch and not shargs.board :
    print("""
    Warning: you did not specify which board you were targeting;
    please review the generated CMakeLists.txt to remove the placeholder value before calling `cmake`.
    """)

if shargs.cli is None :
    print("""
    Error: `arduino-cli` not found in $PATH.
    Please install arduino-cli and make it available from your system $PATH,
    or give its location through the `--cli` argument.
    """)
    exit(-1)

def arduino(*args) :
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

def get_log(fname) :
    with open(fname) as file :
        for line in file :
            yield json.loads(line)


_, logf = arduino("lib", "list")

libpaths = dict()
for line in get_log(logf) :
    if line["msg"] == "Adding libraries dir" :
        libpaths[line["location"]] = pathlib.Path(line["dir"])

# platform lib path is already known, obviously, since that's where this script resides
userlibs = pathlib.Path(libpaths["user"]).resolve()
libs = [u.name for u in userlibs.iterdir() if u.is_dir()]
corepath = pathlib.Path(__file__).parent.parent.resolve()

j2_env = Environment(
    loader=FileSystemLoader(str(corepath/"CI"/"update"/"templates")), trim_blocks=True, lstrip_blocks=True
)
cmake_template = j2_env.get_template("easy_cmake.cmake")


userhome = pathlib.Path.home()
if userlibs.is_relative_to(userhome) :
    userlibs = "~/" + str(userlibs.relative_to(userhome))
if corepath.is_relative_to(userhome) :
    corepath = "~/" + str(corepath.relative_to(userhome))

if shargs.sketch :
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
else :
    tgtname = ""
    sources = set()

scriptname = pathlib.Path(__file__)
if scriptname.is_relative_to(userhome) :
    scriptname = "~/" + str(scriptname.relative_to(userhome))

with open(shargs.output or shargs.sketch/"CMakeLists.txt", "w") as out :
    out.write(cmake_template.render(
        corepath=str(corepath).replace("\\", "\\\\"), # escape backslashes for CMake
        userlibs=str(userlibs).replace("\\", "\\\\"),
        libs=libs,
        scriptfile=scriptname,
        tgtname=tgtname,
        scrcfiles=sources,
        boardname=shargs.board,
    ))


if shargs.fire :
    if not (shargs.sketch and shargs.board) :
        print("There remains some placeholder in the output file; I won't build _that_.")
        exit(1)
    subprocess.run(("cmake", "-S", shargs.sketch, "-B", shargs.sketch/"build"))
    subprocess.run(("cmake", "--build", shargs.sketch/"build"))
