import argparse
from pathlib import Path
import re
import subprocess
import sys

script_path = Path(__file__).parent.resolve()
ignore_filename = ".astyleignore"
def_filename = ".astylerc"
astyle_out_filename = "astyle.out"
if Path.cwd() != script_path:
    src_path = Path.cwd()
else:
    src_path = script_path.parent.parent
ignore_path = script_path / ignore_filename
def_path = script_path / def_filename
astyle_out_path = Path(astyle_out_filename)
git_branch = "remotes/origin/main"

script_version = "1.0.0"
astyle_major = 3
astyle_minor = 1
astyle_path = Path()
astyle_cmd = "astyle"
if sys.platform.startswith("win32"):
    astyle_cmd += ".exe"
elif not sys.platform.startswith("linux") and not sys.platform.startswith("darwin"):
    print("Platform unknown.")
    sys.exit(1)

# List
source_list = []
exclude_list = []


# Check if path exists
def checkPath(p, msg):
    if not p.exists():
        print(msg)
        sys.exit(1)


# Check Astyle exists and version
def checkAstyle():
    try:
        output = subprocess.check_output(
            [astyle_path, "--version"],
            stderr=subprocess.STDOUT,
        )

        res = re.match("\\D*(\\d+)\\.(\\d+)\\.*(\\d*)", output.decode("utf-8"))
        if res:
            major = int(res.group(1))
            minor = int(res.group(2))
            if major >= astyle_major and minor >= astyle_minor:
                print(output.decode("utf-8").rstrip())
            else:
                print(f"Astyle minimum version required {astyle_major}.{astyle_minor}.")
                print(f"Current is {major}.{minor}.")
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

    gitroot = Path(output.decode("utf-8").rstrip())
    try:
        rel_src = src_path.relative_to(gitroot)
    except ValueError:
        print(f"{src_path} not in git repository.")
        sys.exit(1)

    cmd = ["git"]
    cmd.append("diff")
    cmd.append("--name-only")
    cmd.append("--diff-filter=d")
    cmd.append(git_branch)
    # Relative only if source root path specified
    if args.root:
        cmd.append(f"--relative={rel_src}")

    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    while True:
        line = proc.stdout.readline().decode("utf-8").rstrip()
        if line == "" and proc.poll() is not None:
            break
        if line:
            if line.endswith((".h", ".c", ".hpp", ".cpp")):
                source_list.append(gitroot / line.rstrip())
    if proc.poll() != 0:
        sys.exit(1)
    source_list.sort()


# Find all files in source root path
def find_files():
    for spath_object in src_path.glob("**/*"):
        if spath_object.is_file() and spath_object.suffix in [
            ".h",
            ".c",
            ".hpp",
            ".cpp",
        ]:
            source_list.append(spath_object)
    source_list.sort()


# Filter source files list
def manage_exclude_list():
    with open(ignore_path, "r") as f:
        for line in f.readlines():
            if line.rstrip():
                exclude_list.append(line.rstrip())
    if exclude_list:
        for pattern in exclude_list:
            exclude_path = src_path / pattern
            for s in reversed(source_list):
                if s.is_relative_to(exclude_path):
                    source_list.remove(s)


# Launch Astyle on all source files
def astyle():
    cmd = [astyle_path]
    cmd.append("-n")
    cmd.append(f"--options={def_path}")
    cmd.append("dummy_file")

    stddout_name = astyle_out_path

    for s in source_list:
        cmd[-1] = s
        with open(stddout_name, "a") as stdout:
            res = subprocess.Popen(cmd, stdout=stdout, stderr=subprocess.STDOUT)
            res.wait()
            # res.returncode


# Parser
parser = argparse.ArgumentParser(description="Launch astyle on source files.")

parser.add_argument(
    "-d",
    "--definition",
    metavar="<code style definition file>",
    help=f"Code style definition file for Astyle. Default: {def_path}",
)
g0 = parser.add_mutually_exclusive_group()
g0.add_argument(
    "-g",
    "--gitdiff",
    help=f"Use changes files from git default branch. Default: {git_branch}",
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
    help=f"File containing path to ignore. Default: {ignore_path}",
)
parser.add_argument(
    "-p", "--path", metavar="<astyle install path>", help="Astyle installation path"
)
parser.add_argument(
    "-r",
    "--root",
    metavar="<source root path>",
    help=f"Source root path to use. Default: {src_path}",
)
args = parser.parse_args()


def main():
    global ignore_path
    global def_path
    global src_path
    global astyle_path
    global git_branch

    print(f"Script {Path(__file__).name} version {script_version}")
    if args.root:
        src_path = Path(args.root).resolve()

    if args.definition:
        def_path = Path(args.definition).resolve()

    if args.ignore:
        ignore_path = Path(args.ignore).resolve()

    if args.path:
        astyle_path = Path(args.path).resolve() / astyle_cmd
        checkPath(astyle_path, "Could not find Astyle binary!")
    else:
        astyle_path = Path(astyle_cmd)

    checkPath(src_path, "Source root path does not exist!")
    checkPath(def_path, "Code style definition file does not exist!")
    checkPath(ignore_path, "Ignore file does not exist!")
    checkAstyle()
    try:
        astyle_out_path.unlink()
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
