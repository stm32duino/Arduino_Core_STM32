import re
import shutil
import sys


# Create a folder if not exists
def createFolder(path):
    try:
        path.mkdir(parents=True, exist_ok=True)
    except OSError:
        print(f"Error: Creating directory {path}")


# Delete targeted folder recursively
def deleteFolder(path):
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
def copyFile(src, dest):
    try:
        if src.is_file():
            shutil.copy(str(src), str(dest))
    except OSError as e:
        print(f"Error: File {src} not copied. {e}")


def genSTM32List(path, pattern):
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


if __name__ == "__main__":
    print("This script is not intend to be called directly")
    sys.exit()
