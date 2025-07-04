import json
import re
import subprocess
import shutil
import sys
from collections import OrderedDict
from pathlib import Path


# Add default key/value pair to config file
def defaultConfig(config_file_path: Path, data: dict):
    print(f"Please check the default configuration '{config_file_path}'.")
    with open(config_file_path, "w") as config_file:
        config_file.write(json.dumps(data, indent=2))
    exit(1)


# Create a folder if not exists
def createFolder(path: Path):
    try:
        path.mkdir(parents=True, exist_ok=True)
    except OSError:
        print(f"Error: Creating directory {path}")


# Delete targeted folder recursively
def deleteFolder(path: Path):
    if path.is_dir():
        shutil.rmtree(path, ignore_errors=True)


# copy src folder recursively to dest
def copyFolder(src, dest, ign_patt=None):
    if ign_patt is None:
        ign_patt = set()
    try:
        if src.is_dir():
            shutil.copytree(src, dest, ignore=shutil.ignore_patterns(*ign_patt))
    except OSError as e:
        print(f"Error: Folder {src} not copied. {e}")


# copy one file to dest
def copyFile(src: Path, dest: Path):
    try:
        if src.is_file():
            shutil.copy(str(src), str(dest))
    except OSError as e:
        print(f"Error: File {src} not copied. {e}")


# Get dict of STM32 series from HAL driver directory
def genSTM32Dict(path: Path, pattern: str = None):
    stm32_dict = OrderedDict()  # series: nx
    dir_pattern = re.compile(r"^STM32([^x]+)xx?_HAL_Driver$", re.IGNORECASE)

    for file in path.iterdir():
        if file.is_dir():
            if not any(file.iterdir()):
                file.rmdir()  # remove empty directories
                continue
            res = dir_pattern.match(file.name)
            if res:
                if pattern is not None and res.group(1) != pattern.upper():
                    continue
                if "xx" in file.name:
                    nx = "xx"
                elif "x" in file.name:
                    nx = "x"
                else:
                    # Error: no x or xx in series name
                    print(f"Error: No x or xx in series name {file.name}")
                    exit(1)
                stm32_dict[res.group(1)] = nx
    # stm32_list.sort()
    return stm32_dict


def execute_cmd(cmd: list, stderror: int):
    try:
        output = subprocess.check_output(cmd, stderr=stderror).decode("utf-8").strip()
    except subprocess.CalledProcessError as e:
        print(f"Command {e.cmd} failed with error code {e.returncode}")
        exit(e.returncode)
    return output


def getRepoBranchName(repo_path: Path):
    bname = ""
    rname = ""
    cmd = ["git", "-C", repo_path, "branch", "-r"]
    bnames = execute_cmd(cmd, None).split("\n")
    for b in bnames:
        name_match = re.match(r"\S+/\S+ -> (\S+)/(\S+)", b.strip())
        if name_match:
            rname = name_match.group(1)
            bname = name_match.group(2)
    if not bname:
        print(f"Could not find branch name for {repo_path}!")
        exit(1)
    return (rname, bname)


if __name__ == "__main__":
    print("This script is not intend to be called directly")
    sys.exit()
