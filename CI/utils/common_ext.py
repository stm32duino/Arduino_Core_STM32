import json
import re
import subprocess
import shutil
import sys
from pathlib import Path


# Add default key/value pair to config file
def defaultConfig(config_file_path: Path, data: dict):
    print(f"Please check the default configuration '{config_file_path}'.")
    config_file = open(config_file_path, "w")
    config_file.write(json.dumps(data, indent=2))
    config_file.close()
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
def copyFolder(src, dest, ign_patt=set()):
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


# get list of STM32 series from HAL driver directory
def genSTM32List(path: Path, pattern: str = None):
    stm32_list = []  # series
    dir_pattern = re.compile(r"^STM32(.*)xx_HAL_Driver$", re.IGNORECASE)

    if pattern is not None:
        serie_pattern = re.compile(pattern, re.IGNORECASE)
    else:
        serie_pattern = re.compile(".*", re.IGNORECASE)

    for file in path.iterdir():
        res = dir_pattern.match(file.name)
        if res and serie_pattern.search(res.group(1)):
            stm32_list.append(res.group(1))
    stm32_list.sort()
    return stm32_list


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
