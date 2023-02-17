#!/usr/bin/env python3

import argparse
from pathlib import Path
from jinja2 import Environment, FileSystemLoader
from cmake_gen import autoconfig, render

script_path = Path(__file__).parent.resolve()

parser = argparse.ArgumentParser()
input_dirs = parser.add_mutually_exclusive_group(required=True)
input_dirs.add_argument(
    "--library", "-l", type=Path, help="path to a single library to parse"
)
input_dirs.add_argument(
    "--libraries", "-L", type=Path, help="path to a folder of libraries"
)
parser.add_argument(
    "--depends",
    "-d",
    action="extend",
    nargs="*",
    default=list(),
    help="additional dependencies of the libraries to parse",
)

shargs = parser.parse_args()

templates_dir = script_path / ".." / "templates"
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
cmake_template = j2_env.get_template("CMakeLists.txt")

if shargs.libraries is not None:
    for lib in shargs.libraries.iterdir():
        if not lib.is_dir():
            continue

        config = autoconfig(lib)
        config["extra_libs"].update(shargs.depends)
        render(lib, cmake_template, config)
else:
    config = autoconfig(shargs.library)
    config["extra_libs"].update(shargs.depends)
    render(shargs.library, cmake_template, config)
