#!/usr/bin/env python3

import io
import re
import pathlib
import subprocess
import argparse

parser = argparse.ArgumentParser()
parser.add_argument(
    "--source", "-i", type=pathlib.Path, required=True, help="input file being compiled"
)
parser.add_argument(
    "--logdir", "-d", type=pathlib.Path, required=True, help="log directory"
)
parser.add_argument(
    "cmd",
    action="extend",
    nargs="+",
    help="full compilation command (including -H etc...)",
)

shargs = parser.parse_args()

logline = re.compile(r"^\.* .+$")  # a series of dots, a space, a filename


proc = subprocess.run(shargs.cmd, capture_output=True, encoding="ascii")
if proc.returncode != 0:
    exit(proc.returncode)

with open(shargs.logdir / (shargs.source.name + ".log"), "w") as file:
    print(" " + str(shargs.source), file=file)
    for line in io.StringIO(proc.stderr):
        if logline.match(line):
            print(line.rstrip(), file=file)  # remove trailing '\n'
