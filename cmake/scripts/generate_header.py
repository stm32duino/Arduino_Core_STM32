#!/usr/bin/env python3

import argparse
import pathlib

parser = argparse.ArgumentParser()
parser.add_argument(
    "--source", "-i", type=pathlib.Path, required=True, help="ctags's output"
)
parser.add_argument(
    "--out", "-o", type=pathlib.Path, required=True, help="header to generate"
)

shargs = parser.parse_args()


with open(shargs.source, "r") as infile:
    with open(shargs.out, "w") as outfile:
        for line in infile:
            line = line.strip()
            if line.startswith("!") or not line:
                continue

            fields = line.split("\t")
            kind = fields[3].split(":", 1)[1]
            if kind == "function":
                symname = fields[0]
                signature = fields[5].split(":", 1)[1]
                rtype = fields[6].split(":", 1)[1]
                print(f"{rtype} {symname}{signature};", file=outfile)
