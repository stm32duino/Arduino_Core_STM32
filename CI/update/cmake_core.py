#!/usr/bin/env python3

import sys
from pathlib import Path
from jinja2 import Environment, FileSystemLoader

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils.cmake_gen import *

if len(sys.argv) != 2 :
    print("Usage: cmake_core.py <.../cores/arduino>")
    print("Generates a CMakeLists.txt describing a core")
    print("The resulting static library will be named \"core\".")

rootdir = Path(sys.argv[1]).resolve()
script_path = Path(__file__).parent.resolve()
templates_dir = script_path / "templates"
j2_env = Environment(
loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
cmake_template = j2_env.get_template("CMakeLists.txt")

if not (rootdir.exists() and rootdir.is_dir()) :
    print(f"Can't find {rootdir}/")
    exit(1)


config = config_for_bareflat(rootdir, force_recurse=True)
config["target"] = "core"
config["objlib"] = False
render(rootdir, cmake_template, config)
