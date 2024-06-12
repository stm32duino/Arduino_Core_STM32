#!/usr/bin/env python3

import argparse
import re
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("--source", "-i", type=Path, required=True, help="ctags's output")
parser.add_argument("--out", "-o", type=Path, required=True, help="header to generate")

shargs = parser.parse_args()
externC_regex = re.compile(r'extern\s+"C"')
with open(shargs.source, "r") as infile:
    with open(shargs.out, "w") as outfile:
        for line in infile:
            line = line.strip()
            if line.startswith("!") or not line:
                continue

            fields = line.split("\t")
            kind = fields[3].split(":", 1)[1]
            if kind == "function":
                decl = ""
                externC = externC_regex.search(fields[2])
                if externC:
                    decl = 'extern "C" '
                symname = fields[0]
                signature = fields[5].split(":", 1)[1]
                rtype = fields[6].split(":", 1)[1]
                print(f"{decl}{rtype} {symname}{signature};", file=outfile)
