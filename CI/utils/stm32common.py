import os
import re
import shutil


# Create a folder if not exists
def createFolder(path):
    try:
        if not os.path.exists(path):
            os.makedirs(path)
    except OSError:
        print("Error: Creating directory. " + path)


# Delete targeted folder recursively
def deleteFolder(path):
    if os.path.isdir(path):
        shutil.rmtree(path, ignore_errors=True)


# copy src folder recursively to dest
def copyFolder(src, dest, ign_patt=set()):
    try:
        if os.path.isdir(src):
            shutil.copytree(src, dest, ignore=shutil.ignore_patterns(*ign_patt))
    except OSError as e:
        print("Error: Folder %s not copied. %s" % src, e)


def genSTM32List(path, pattern):
    stm32_list = []  # Serie
    dir_pattern = re.compile("^STM32(.*)xx_HAL_Driver$", re.IGNORECASE)

    if pattern is not None:
        serie_pattern = re.compile(pattern, re.IGNORECASE)
    else:
        serie_pattern = re.compile(".*", re.IGNORECASE)

    for file in os.listdir(path):
        res = dir_pattern.match(file)
        if res and serie_pattern.search(res.group(1)):
            stm32_list.append(res.group(1))
    stm32_list.sort()
    return stm32_list
