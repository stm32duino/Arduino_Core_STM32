#!/usr/bin/env python3

"""
This file centralizes all the operations needed to regenerate the CMakeLists.txt
scattered along this repo.
Hint: it would be a good practice to run it before committing...
"""

import argparse
import subprocess
import pathlib
import sys

parser = argparse.ArgumentParser(
    usage="updater hook for CMake files. Fully automatic, takes no argument."
)
shargs = parser.parse_args()

script_dir = pathlib.Path(__file__).parent  # Arduino_Core_STM32/cmake/scripts
base_dir = script_dir.parent.parent  # Arduino_Core_STM32
templates_dir = base_dir / "cmake" / "templates"

print("Updating core/arduino...")
subprocess.run(
    (sys.executable, script_dir / "cmake_core.py", base_dir / "cores" / "arduino"),
    check=True,
)

print("Updating libraries/...")
subprocess.run(
    (sys.executable, script_dir / "cmake_libs.py", "-L", base_dir / "libraries"),
    check=True,
)

print("Updating variants/...")
subprocess.run(
    (sys.executable, script_dir / "cmake_variant.py", base_dir / "variants"),
    check=True,
)
print("Updating board database...")
subprocess.run(
    (
        sys.executable,
        script_dir / "update_boarddb.py",
        "-b",
        base_dir / "boards.txt",
        "-p",
        base_dir / "platform.txt",
        "-t",
        templates_dir / "boards_db.cmake",
        "-o",
        base_dir / "cmake" / "boards_db.cmake",
    ),
    check=True,
)

print("All done !")
