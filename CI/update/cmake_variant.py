#!/usr/bin/env python3

import sys
from pathlib import Path
from jinja2 import Environment, FileSystemLoader

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils.cmake_gen import *

if len(sys.argv) != 2 :
    print("Usage: cmake_variant.py <.../variants>")
    print("Generates a CMakeLists.txt describing a variant folder")
    print("The resulting static library will be named \"variant\".")

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

for family in rootdir.iterdir() :
    if not family.is_dir() :
        continue
    for variant in family.iterdir() :
        # technically several variants may be gathered in the same folder
        if not variant.is_dir() :
            continue

        config = config_for_bareflat(variant, force_recurse=True)
        config["target"] = "variant"
        config["objlib"] = False
        render(variant, cmake_template, config)
