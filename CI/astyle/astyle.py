# -*- coding: utf-8 -*-

# File name            : astyle.py
# Author               : Frederic PILLON <frederic.pillon@st.com>
# Created              : 11/16/2018
# Python Version       :
# Requirements         : Artistic Style Version 3.1
# Description          : Launch astyle on found source files

import argparse
import os
import re
import subprocess
import sys

script_path = os.path.dirname(os.path.abspath(__file__))
ignore_filename = ".astyleignore"
def_filename = ".astylerc"
astyle_out_filename = "astyle.out"
if os.getcwd() != script_path:
    src_path = os.getcwd()
else:
    src_path = os.path.realpath(os.path.join("..", ".."))
ignore_path = os.path.join(script_path, ignore_filename)
def_path = os.path.join(script_path, def_filename)
astyle_out_path = astyle_out_filename
git_branch = "remotes/origin/master"

astyle_major = 3
astyle_minor = 1
astyle_path = ""
if sys.platform.startswith("win32"):
    astyle_cmd = "astyle.exe"
elif sys.platform.startswith("linux") or sys.platform.startswith("darwin"):
    astyle_cmd = "astyle"
else:
    print("Platform unknown.")
    sys.exit(1)

# List
source_list = []
exclude_list = []


# Check if path exists
def checkPath(path, msg):
    if not os.path.exists(path):
        print(msg)
        sys.exit(1)


# Check Astyle exists and version
def checkAstyle():
    try:
        output = subprocess.check_output(
            [os.path.join(astyle_path, astyle_cmd), "--version"],
            stderr=subprocess.STDOUT,
        )

        res = re.match("\\D*(\\d+)\\.(\\d+)\\.*(\\d*)", output.decode("utf-8"))
        if res:
            major = int(res.group(1))
            minor = int(res.group(2))
            if major >= astyle_major and minor >= astyle_minor:
                print(output.decode("utf-8").rstrip())
            else:
                print(
                    "Required Astyle version {}.{} (Current: {}.{})".format(
                        astyle_major, astyle_minor, major, minor
                    )
                )
                sys.exit(1)
        else:
            raise subprocess.CalledProcessError(1, "No version found")
    except FileNotFoundError:
        print("Astyle binary not found.")
        print("Check if it is in the PATH environment or use '-p <path>'.")
        sys.exit(1)
    except subprocess.CalledProcessError as e:
        print(e.output)
        sys.exit(1)


# Find changes files in source root path
def gitdiff_files():
    try:
        output = subprocess.check_output(
            ["git", "rev-parse", "--show-toplevel"], stderr=subprocess.STDOUT
        )
    except subprocess.CalledProcessError as e:
        print(e.output)
        sys.exit(1)

    gitroot = output.decode("utf-8").rstrip()
    rel_src = re.sub("^[/\\]+]", "", re.sub(gitroot, "", src_path))

    cmd = []
    cmd.append("git")
    cmd.append("diff")
    cmd.append("--name-only")
    cmd.append("--diff-filter=d")
    cmd.append(git_branch)
    cmd.append("--relative=" + rel_src)

    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    while True:
        line = proc.stdout.readline().decode("utf-8").rstrip()
        if line == "" and proc.poll() is not None:
            break
        if line:
            if line.endswith((".h", ".c", ".hpp", ".cpp")):
                source_list.append(os.path.join(gitroot, line.rstrip()))
    if proc.poll() != 0:
        sys.exit(1)
    source_list.sort()


# Find all files in source root path
def find_files():
    for root, dirs, files in os.walk(src_path, followlinks=True):
        for f in files:
            if f.endswith((".h", ".c", ".hpp", ".cpp")):
                source_list.append(os.path.join(root, f))
    source_list.sort()


# Filter source files list
def manage_exclude_list():
    with open(ignore_path, "r") as f:
        for line in f.readlines():
            if line.rstrip():
                exclude_list.append(line.rstrip())
    if exclude_list:
        for pattern in exclude_list:
            if sys.platform.startswith("win32"):
                winpattern = os.path.join(src_path, pattern.replace("/","\\")) .replace("\\","\\\\")
                exclude_pattern = re.compile(winpattern + ".*")
            else:
                exclude_pattern = re.compile(os.path.join(src_path, pattern) + ".*")
            for s in reversed(source_list):
                if exclude_pattern.search(s):
                    source_list.remove(s)


# Launch Astyle on all source files
def astyle():
    cmd = []
    cmd.append(os.path.join(astyle_path, astyle_cmd))
    cmd.append("-n")
    cmd.append("--options=" + def_path)
    cmd.append("dummy_file")

    stddout_name = astyle_out_path

    for s in source_list:
        cmd[-1] = s
        with open(stddout_name, "a") as stdout:
            res = subprocess.Popen(cmd, stdout=stdout, stderr=subprocess.STDOUT)
            res.wait()
            # res.returncode


# Parser
parser = argparse.ArgumentParser(
    description="Launch astyle on source files found at specified root path."
)

parser.add_argument(
    "-d",
    "--definition",
    metavar="<code style definition file>",
    help="Code style definition file for Astyle. Default: " + def_path,
)
g0 = parser.add_mutually_exclusive_group()
g0.add_argument(
    "-g",
    "--gitdiff",
    help="Use changes files from git default branch. Default: " + git_branch,
    action="store_true",
)
g0.add_argument(
    "-b",
    "--branch",
    metavar="<branch name>",
    help="Use changes files from git specified branch.",
)
parser.add_argument(
    "-i",
    "--ignore",
    metavar="<ignore file>",
    help="File containing path to ignore. Default: " + ignore_path,
)
parser.add_argument(
    "-p", "--path", metavar="<astyle install path>", help="Astyle installation path"
)
parser.add_argument(
    "-r",
    "--root",
    metavar="<source root path>",
    help="Source root path to use. Default: " + src_path,
)
args = parser.parse_args()


def main():
    global ignore_path
    global def_path
    global src_path
    global astyle_path
    global git_branch

    if args.root:
        src_path = os.path.realpath(args.root)

    if args.definition:
        def_path = os.path.realpath(args.definition)

    if args.ignore:
        ignore_path = os.path.realpath(args.ignore)

    if args.path:
        astyle_path = os.path.realpath(args.path)
        checkPath(
            os.path.join(astyle_path, astyle_cmd), "Could not find Astyle binary!"
        )

    checkPath(src_path, "Source root path does not exist!")
    checkPath(def_path, "Code style definition file does not exist!")
    checkPath(ignore_path, "Ignore file does not exist!")
    checkAstyle()
    try:
        os.remove(astyle_out_path)
    except OSError:
        pass

    if args.gitdiff or args.branch:
        if args.branch:
            git_branch = args.branch
        gitdiff_files()
    else:
        find_files()
    manage_exclude_list()
    if len(source_list):
        astyle()
    else:
        print("No file found to apply Astyle")


if __name__ == "__main__":
    main()
