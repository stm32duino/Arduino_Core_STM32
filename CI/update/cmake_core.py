#!/usr/bin/env python3

import argparse
import sys
from pathlib import Path
from jinja2 import Environment, FileSystemLoader

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils.cmake_gen import *

parser = argparse.ArgumentParser()
parser.add_argument("corepath", type=Path, help="path to .../cores/arduino")

shargs = parser.parse_args()

templates_dir = script_path / "templates"
j2_env = Environment(
loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
cmake_template = j2_env.get_template("CMakeLists.txt")

config = config_for_bareflat(shargs.corepath, force_recurse=True)
config["target"] = "core"
config["objlib"] = False
render(shargs.corepath, cmake_template, config)
