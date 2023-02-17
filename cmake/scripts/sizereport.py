#!/usr/bin/env python3

import pathlib
import re
import subprocess
import argparse

parser = argparse.ArgumentParser()
parser.add_argument(
    "-x",
    "--tool",
    type=pathlib.Path,
    required=True,
    help="path to `arm-none-eabi-size`",
)
parser.add_argument(
    "-f",
    "--binfile",
    type=pathlib.Path,
    required=True,
    help="path to the binary to analyze",
)
parser.add_argument(
    "--progmem", type=int, required=True, help="max amount of program storage space"
)
parser.add_argument(
    "--datamem", type=int, required=True, help="max amount of dynamic memory"
)

shargs = parser.parse_args()


proc = subprocess.run(
    (shargs.tool, "-A", shargs.binfile), capture_output=True, encoding="UTF-8"
)
if proc.returncode != 0:
    print("Error running", (shargs.tool, "-A", shargs.binfile), end=":\n\n")
    print(proc.stderr)
    print("Return code :", proc.returncode)
    exit(1)


regex_all = re.compile(r"^(?:\.text|\.data|\.rodata)\s+([0-9]+).*", flags=re.MULTILINE)
regex_data = re.compile(r"^(?:\.data|\.bss|\.noinit)\s+([0-9]+).*", flags=re.MULTILINE)

allsz = sum(int(u) for u in regex_all.findall(proc.stdout))
datasz = sum(int(u) for u in regex_data.findall(proc.stdout))


print(
    f"""
Sketch uses {allsz} bytes ({allsz/shargs.progmem:.0%}) of program storage space. \
Maximum is {shargs.progmem} bytes.
Global variables use {datasz} bytes ({datasz/shargs.datamem:.0%}) of dynamic memory, \
leaving {shargs.datamem-datasz} bytes for local variables. \
Maximum is {shargs.datamem} bytes.
"""
)
