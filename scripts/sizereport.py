#!/usr/bin/env python3

import pathlib
import re
import subprocess
import sys

"""
Return codes :
- 0: OK
- 1: bad argc
- 2: invalid path
- 3: can't parse maxsz/maxdatasz
- 4: `size` internal error
"""
OK_OK = 0
BAD_ARGC = 1
BAD_PATH = 2
BAD_INT = 3
EXTERNAL_ERROR = 4

if len(sys.argv) != 5 :
    print("Usage : sizereport.py <toolpath> <exepath> <maxprogsize> <maxdatasize>")
    print("<toolpath> is an absolute path to a `size` binary.")
    print("<exepath> is an absolute path to a target ELF executable.")
    print("<maxprogsize> and <maxdatasize> must be integers representing the memory capacities of the target board.")
    print("This tool will run `<toolpath> -A <exepath>` and filter the output to display an Arduino-like report.")
    exit(BAD_ARGC)

arm_size = pathlib.Path(sys.argv[1])
if not (arm_size.exists() and arm_size.is_file()) :
    print("Error: Can't find", arm_size)
    exit(BAD_PATH)

binary = pathlib.Path(sys.argv[2])
if not (binary.exists() and binary.is_file()) :
    print("Error: Can't find", binary)
    exit(BAD_PATH)

try :
    maxsz = int(sys.argv[3])
except ValueError :
    print("Error: Can't convert", sys.argv[3], "to an integer")
    exit(BAD_INT)
maxdatasz = int(sys.argv[4])

try :
    maxdatasz = int(sys.argv[4])
except ValueError :
    print("Error: Can't convert", sys.argv[4], "to an integer")
    exit(BAD_INT)

proc = subprocess.run((arm_size, "-A", binary), capture_output=True, encoding="UTF-8")
if proc.returncode != 0 :
    print("Error running", (arm_size, "-A", binary), end=":\n\n")
    print(proc.stderr)
    print("Return code :", proc.returncode)
    exit(EXTERNAL_ERROR)


regex_all = re.compile(r"^(?:\.text|\.data|\.rodata)\s+([0-9]+).*", flags=re.MULTILINE)
regex_data = re.compile(r"^(?:\.data|\.bss|\.noinit)\s+([0-9]+).*", flags=re.MULTILINE)

allsz = sum(int(u) for u in regex_all.findall(proc.stdout))
datasz = sum(int(u) for u in regex_data.findall(proc.stdout))


print(f"""
Sketch uses {allsz} bytes ({allsz/maxsz:.0%}) of program storage space. Maximum is {maxsz} bytes.
Global variables use {datasz} bytes ({datasz/maxdatasz:.0%}) of dynamic memory, leaving {maxdatasz-datasz} bytes for local variables. Maximum is {maxdatasz} bytes.
""")
