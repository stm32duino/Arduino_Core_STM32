#!/usr/bin/env python3

import io
import re
import sys
import pathlib
import subprocess

logline = re.compile("^\.* .+$") # a series of dots, a space, a filename

outfd = pathlib.Path(sys.argv[1])
infile = pathlib.Path(sys.argv[2])
cmd = sys.argv[sys.argv.index("--")+1:]

proc = subprocess.run(cmd, capture_output=True, encoding="ascii")
if proc.returncode != 0 :
    exit(proc.returncode)

file = open(outfd/(infile.name+".log"), "w")

print(" "+str(infile), file=file)
for line in io.StringIO(proc.stderr) :
    if logline.match(line) :
        print(line.rstrip(), file=file) # remove trailing '\n'

file.close()
