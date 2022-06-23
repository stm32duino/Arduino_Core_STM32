#!/usr/bin/env python3

import sys
from pathlib import Path
from jinja2 import Environment, FileSystemLoader

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils.cmake_gen import *

if len(sys.argv) != 2 :
    print("Usage: cmake_libs.py <.../libraries>")
    print("Generates a CMakeLists.txt for each library in the folder")
    print("Usage: cmake_libs.py <.../AwesomeArduinoLibrary>")
    print("Generates a CMakeLists.txt for the specified library")
    print("The resulting library targets will be named like their folders.")


rootdir = Path(sys.argv[1]).resolve()
script_path = Path(__file__).parent.resolve()
templates_dir = script_path / "templates"
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
cmake_template = j2_env.get_template("CMakeLists.txt")

if not rootdir.exists() :
    print(f"Can't find {rootdir}/")
    exit(1)

if rootdir.name == "libraries" :
    for lib in rootdir.iterdir() :
        if not lib.is_dir() :
            continue

        config = autoconfig(lib)
        config["extra_libs"].add("core")
        render(lib, cmake_template, config)
else :
    config = autoconfig(rootdir)
    config["extra_libs"].add("core")
    render(rootdir, cmake_template, config)
