#!/usr/bin/env python3

import argparse
from pathlib import Path
from jinja2 import Environment, FileSystemLoader
from cmake_gen import config_for_bareflat, render

script_path = Path(__file__).parent.resolve()

parser = argparse.ArgumentParser()
parser.add_argument("variantspath", type=Path, help="path to .../variants/")

shargs = parser.parse_args()

templates_dir = script_path / ".." / "templates"
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
cmake_template = j2_env.get_template("CMakeLists.txt")


for family in shargs.variantspath.iterdir():
    if not family.is_dir():
        continue
    for variant in family.iterdir():
        # technically several variants may be gathered in the same folder
        if not variant.is_dir():
            continue

        config = config_for_bareflat(variant, force_recurse=True)
        config["target"] = "variant"
        config["objlib"] = False
        render(variant, cmake_template, config)
