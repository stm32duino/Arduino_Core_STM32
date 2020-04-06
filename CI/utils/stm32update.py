import argparse
import collections
import fileinput
import json
import os
from packaging import version
import re
import subprocess
import sys
from urllib.parse import urljoin
import stm32wrapper
from stm32common import createFolder, deleteFolder, copyFolder, genSTM32List

if sys.platform.startswith("win32"):
    from colorama import init

    init(autoreset=True)

script_path = os.path.dirname(os.path.abspath(__file__))
home = os.path.expanduser("~")
path_config_filename = "update_config.json"

# GitHub
gh_st = "https://github.com/STMicroelectronics/"
gh_core = "https://github.com/stm32duino/Arduino_Core_STM32.git"
repo_generic_name = "STM32Cube"
repo_core_name = "Arduino_Core_STM32"
repo_local_path = os.path.join(home, "STM32Cube_repo")

# From
# Relative to repo path
hal_src_path = "Drivers"
cmsis_src_path = os.path.join("Drivers", "CMSIS", "Device", "ST")
# To
hal_dest_path = os.path.join("system", "Drivers")
cmsis_dest_path = os.path.join("system", "Drivers", "CMSIS", "Device", "ST")

stm32_list = []  # Serie
cube_versions = collections.OrderedDict()  # key: serie name, value: cube version
cube_HAL_versions = collections.OrderedDict()  # key: serie name, value: HAL version
cube_CMSIS_versions = collections.OrderedDict()  # key: serie name, value: CMSIS version
core_HAL_versions = collections.OrderedDict()  # key: serie name, value: HAL version
core_CMSIS_versions = collections.OrderedDict()  # key: serie name, value: CMSIS version

# MD to update
md_CMSIS_path = "STM32YYxx_CMSIS_version.md"
md_HAL_path = "STM32YYxx_HAL_Driver_version.md"

# Format
out_format_Header = "| {:^22} | {:^31} | {:^31} |"
out_subheader = "| {:^4} | {:^7} | {:^8} | {:^8} | {:^1} | {:^8} | {:^8} | {:^1} |"
out_format = "| {:^12} | {:^7} | {:^8} | {:^8} | {:^1} | {:^8} | {:^8} | {:^1} |"
out_separator = "-" * 70


def create_config():
    global repo_local_path

    # Create a Json file for a better path management
    print(
        "'{}' file created. Please check the configuration.".format(
            os.path.join(script_path, path_config_filename)
        )
    )
    path_config_file = open(path_config_filename, "w")
    path_config_file.write(json.dumps({"REPO_LOCAL_PATH": repo_local_path}, indent=2))
    path_config_file.close()
    exit(1)


def checkConfig():
    global repo_local_path
    global hal_dest_path
    global cmsis_dest_path
    global md_HAL_path
    global md_CMSIS_path
    if os.path.isfile(os.path.join(script_path, path_config_filename)):
        try:
            path_config_file = open(
                os.path.join(script_path, path_config_filename), "r"
            )
            path_config = json.load(path_config_file)
            # Common path
            repo_local_path = path_config["REPO_LOCAL_PATH"]
            path_config_file.close()
            hal_dest_path = os.path.join(repo_local_path, repo_core_name, hal_dest_path)
            md_HAL_path = os.path.join(hal_dest_path, md_HAL_path)
            cmsis_dest_path = os.path.join(
                repo_local_path, repo_core_name, cmsis_dest_path
            )
            md_CMSIS_path = os.path.join(cmsis_dest_path, md_CMSIS_path)
        except IOError:
            print("Failed to open " + path_config_file)
    else:
        create_config()
    createFolder(repo_local_path)


def updateCoreRepo():
    # Handle core repo
    repo_path = os.path.join(repo_local_path, repo_core_name)
    print("Updating " + repo_core_name + "...")
    if os.path.exists(repo_path):
        # Get new tags from the remote
        git_cmds = [
            ["git", "-C", repo_path, "clean", "-fdx"],
            ["git", "-C", repo_path, "fetch"],
            ["git", "-C", repo_path, "reset", "--hard", "origin/master"],
        ]
    else:
        # Clone it as it does not exists yet
        git_cmds = [["git", "-C", repo_local_path, "clone", gh_core]]
    try:
        for cmd in git_cmds:
            subprocess.check_output(cmd).decode("utf-8")
    except subprocess.CalledProcessError as e:
        print("Failed command: ")
        print(e.cmd)
        sys.exit(e.returncode)


def updateSTRepo():
    # Handle STM32Cube repo
    for serie in stm32_list:
        repo_name = repo_generic_name + serie
        repo_path = os.path.join(repo_local_path, repo_name)
        gh_STM32Cube = urljoin(gh_st, repo_name + ".git")
        print("Updating " + repo_name + "...")
        if os.path.exists(repo_path):
            # Get new tags from the remote
            git_cmds = [
                ["git", "-C", repo_path, "clean", "-fdx"],
                ["git", "-C", repo_path, "fetch", "--tags"],
                ["git", "-C", repo_path, "reset", "--hard", "origin/master"],
            ]
        else:
            # Clone it as it does not exists yet
            git_cmds = [["git", "-C", repo_local_path, "clone", gh_STM32Cube]]
        try:
            for cmd in git_cmds:
                subprocess.check_output(cmd).decode("utf-8")
        except subprocess.CalledProcessError as e:
            print("Failed command: ")
            print(e.cmd)
            sys.exit(e.returncode)
        latestTag(serie, repo_name, repo_path)
        checkVersion(serie, repo_path)


def latestTag(serie, repo_name, repo_path):
    global cube_versions
    # Checkout the latest tag
    try:
        sha1_id = (
            subprocess.check_output(
                ["git", "-C", repo_path, "rev-list", "--tags", "--max-count=1"]
            )
            .decode("utf-8")
            .strip()
        )
        version_tag = (
            subprocess.check_output(
                ["git", "-C", repo_path, "describe", "--tags", sha1_id]
            )
            .decode("utf-8")
            .strip()
        )
        subprocess.check_output(
            ["git", "-C", repo_path, "checkout", version_tag], stderr=subprocess.DEVNULL
        )
        cube_versions[serie] = version_tag
        # print("Latest tagged version available for " + repo_name + " is " + version_tag)
    except subprocess.CalledProcessError as e:
        print("Failed command: ")
        print(e.cmd)
        sys.exit(e.returncode)


def parseVersion(path):
    main_found = False
    sub1_found = False
    sub2_found = False
    if "HAL" in path:
        main_pattern = re.compile(r"HAL_VERSION_MAIN.*0x([\dA-Fa-f]+)")
        sub1_pattern = re.compile(r"HAL_VERSION_SUB1.*0x([\dA-Fa-f]+)")
        sub2_pattern = re.compile(r"HAL_VERSION_SUB2.*0x([\dA-Fa-f]+)")
    else:
        main_pattern = re.compile(
            r"(?:CMSIS|DEVICE|CMSIS_DEVICE)_VERSION_MAIN.*0x([\dA-Fa-f]+)"
        )
        sub1_pattern = re.compile(
            r"(?:CMSIS|DEVICE|CMSIS_DEVICE)_VERSION_SUB1.*0x([\dA-Fa-f]+)"
        )
        sub2_pattern = re.compile(
            r"(?:CMSIS|DEVICE|CMSIS_DEVICE)_VERSION_SUB2.*0x([\dA-Fa-f]+)"
        )

    for i, line in enumerate(open(path, encoding="utf8", errors="ignore")):
        for match in re.finditer(main_pattern, line):
            VERSION_MAIN = int(match.group(1), 16)
            main_found = True
        for match in re.finditer(sub1_pattern, line):
            VERSION_SUB1 = int(match.group(1), 16)
            sub1_found = True
        for match in re.finditer(sub2_pattern, line):
            VERSION_SUB2 = int(match.group(1), 16)
            sub2_found = True
        if main_found and sub1_found and sub2_found:
            break
    else:
        print("Could not find the full version in " + path)
        if main_found:
            print("main version found: {}".format(VERSION_MAIN))
        VERSION_MAIN = "FF"
        if sub1_found:
            print("sub1 version found: {}".format(VERSION_SUB1))
        VERSION_SUB1 = "FF"
        if sub2_found:
            print("sub2 version found: {}".format(VERSION_SUB2))
        VERSION_SUB2 = "FF"
    return "{}.{}.{}".format(VERSION_MAIN, VERSION_SUB1, VERSION_SUB2)


def checkVersion(serie, repo_path):
    lserie = serie.lower()
    userie = serie.upper()
    HAL_file = os.path.join(
        repo_path,
        hal_src_path,
        "STM32{}xx_HAL_Driver".format(userie),
        "Src",
        "stm32{}xx_hal.c".format(lserie),
    )
    cube_HAL_versions[serie] = parseVersion(HAL_file)
    HAL_file = os.path.join(
        hal_dest_path,
        "STM32{}xx_HAL_Driver".format(userie),
        "Src",
        "stm32{}xx_hal.c".format(lserie),
    )
    core_HAL_versions[serie] = parseVersion(HAL_file)

    CMSIS_file = os.path.join(
        repo_path,
        cmsis_src_path,
        "STM32{}xx".format(userie),
        "Include",
        "stm32{}xx.h".format(lserie),
    )
    cube_CMSIS_versions[serie] = parseVersion(CMSIS_file)
    CMSIS_file = os.path.join(
        cmsis_dest_path,
        "STM32{}xx".format(userie),
        "Include",
        "stm32{}xx.h".format(lserie),
    )
    core_CMSIS_versions[serie] = parseVersion(CMSIS_file)

    # print("STM32Cube" + serie + " HAL version: " + cube_HAL_versions[serie])
    # print("STM32Core " + serie + " HAL version: " + core_HAL_versions[serie])
    # print("STM32Cube" + serie + " CMSIS version: " + cube_CMSIS_versions[serie])
    # print("STM32Core " + serie + " CMSIS version: " + core_CMSIS_versions[serie])


def printVersion():
    print(out_separator)
    print(
        (out_format_Header).format(
            "\033[1mCube Release\033[0m",
            "\033[1mHAL version\033[0m",
            "\033[1mCMSIS Version\033[0m",
        )
    )
    print(
        (out_subheader).format(
            "Name", "Version", "Current", "New", "?", "Current", "New", "?"
        )
    )
    print(out_separator)
    for serie in stm32_list:
        core_HAL_version = core_HAL_versions[serie]
        cube_HAL_version = cube_HAL_versions[serie]
        core_CMSIS_version = core_CMSIS_versions[serie]
        cube_CMSIS_version = cube_CMSIS_versions[serie]
        if version.parse(core_HAL_version) < version.parse(cube_HAL_version):
            updateHAL = "\033[1;32m+\033[0m"
        elif version.parse(core_HAL_version) == version.parse(cube_HAL_version):
            updateHAL = "\033[1;34m=\033[0m"
        else:
            updateHAL = "\033[1;31m-\033[0m"
        if version.parse(core_CMSIS_version) < version.parse(cube_CMSIS_version):
            updateCMSIS = "\033[1;32m+\033[0m"
        elif version.parse(core_CMSIS_version) == version.parse(cube_CMSIS_version):
            updateCMSIS = "\033[1;34m=\033[0m"
        else:
            updateCMSIS = "\033[1;31m-\033[0m"
        print(
            (out_format).format(
                "\033[1m{}\033[0m".format(serie),
                cube_versions[serie],
                core_HAL_version,
                cube_HAL_version,
                updateHAL,
                core_CMSIS_version,
                cube_CMSIS_version,
                updateCMSIS,
            )
        )
        print(out_separator)


# Commit files without trailing space
def commitFiles(repo_path, commit_msg):
    try:
        # Check if there is something to commit
        status = subprocess.check_output(
            ["git", "-C", repo_path, "status", "--untracked-files", "--short"]
        )
        if not status:
            return
        # Staged all files: new, modified and deleted
        subprocess.check_output(
            ["git", "-C", repo_path, "add", "--all"], stderr=subprocess.DEVNULL
        )
        # Commit all stage files with signoff and message
        subprocess.check_output(
            [
                "git",
                "-C",
                repo_path,
                "commit",
                "--all",
                "--signoff",
                "--message=" + commit_msg,
            ],
            stderr=subprocess.DEVNULL,
        )
        # Remove trailing space
        subprocess.check_output(
            ["git", "-C", repo_path, "rebase", "--whitespace=fix", "HEAD~1"],
            stderr=subprocess.DEVNULL,
        )
    except subprocess.CalledProcessError as e:
        print("Failed command: ")
        print(e.cmd)
        sys.exit(e.returncode)


# Apply all patches found for the dedicated serie
def applyPatch(serie, HAL_updated, CMSIS_updated, repo_path):
    # First check if some patch need to be applied
    patch_path = os.path.join(script_path, "patch")
    patch_list = []
    if HAL_updated:
        HAL_patch_path = os.path.join(patch_path, "HAL", serie)
        if os.path.isdir(HAL_patch_path):
            for file in os.listdir(HAL_patch_path):
                if file.endswith(".patch"):
                    patch_list.append(os.path.join(HAL_patch_path, file))
    if CMSIS_updated:
        CMSIS_patch_path = os.path.join(patch_path, "CMSIS", serie)
        if os.path.isdir(CMSIS_patch_path):
            for file in os.listdir(CMSIS_patch_path):
                if file.endswith(".patch"):
                    patch_list.append(os.path.join(CMSIS_patch_path, file))

    if len(patch_list):
        patch_failed = []
        print(
            "Apply {} patch{} for {}".format(
                len(patch_list), "" if len(patch_list) == 1 else "es", serie
            )
        )
        for patch in patch_list:
            try:
                # Test the patch before apply it
                status = subprocess.check_output(
                    ["git", "-C", repo_path, "apply", "--check", patch],
                    stderr=subprocess.STDOUT,
                )
                if status:
                    # print("patch {} can't be applied".format(patch))
                    patch_failed.append([patch, status])
                    continue
                # Apply the patch
                status = subprocess.check_output(
                    [
                        "git",
                        "-C",
                        repo_path,
                        "am",
                        "--keep-non-patch",
                        "--quiet",
                        "--signoff",
                        patch,
                    ]
                )
            except subprocess.CalledProcessError as e:
                patch_failed.append([patch, e.cmd, e.output.decode("utf-8")])
                # print("Failed command: {}".format(e.cmd))
        if len(patch_failed):
            for fp in patch_failed:
                print(
                    "Failed to apply {}:\n{}{}".format(
                        fp[0], fp[1], "" if len(fp) == 2 else "\n--> {}".format(fp[2])
                    )
                )


def updateCore():
    for serie in stm32_list:
        cube_name = repo_generic_name + serie
        cube_path = os.path.join(repo_local_path, cube_name)
        core_path = os.path.join(repo_local_path, repo_core_name)
        core_HAL_version = core_HAL_versions[serie]
        cube_HAL_version = cube_HAL_versions[serie]
        core_CMSIS_version = core_CMSIS_versions[serie]
        cube_CMSIS_version = cube_CMSIS_versions[serie]
        cube_version = cube_versions[serie]
        regexmd = re.compile(rf"(STM32{serie}:\s+)\d+.\d+.\d+")
        HAL_updated = False
        CMSIS_updated = False
        hal_commit_msg = """[{0}] Update STM32{0}xx HAL Drivers to v{1}

Included in STM32Cube{0} FW {2}""".format(
            serie, cube_HAL_version, cube_version
        )
        cmsis_commit_msg = """[{0}] Update STM32{0}xx CMSIS Drivers to v{1}

Included in STM32Cube{0} FW {2}""".format(
            serie, cube_CMSIS_version, cube_version
        )
        wrapper_commit_msg = "[{}] Update wrapped files".format(serie)

        # Update HAL part if needed
        if version.parse(core_HAL_version) < version.parse(cube_HAL_version):
            print(
                "Update "
                + serie
                + " HAL from version "
                + core_HAL_version
                + " to "
                + cube_HAL_version
            )
            # First delete old HAL version
            HAL_serie_core_path = os.path.join(
                core_path, hal_dest_path, "STM32{}xx_HAL_Driver".format(serie)
            )
            deleteFolder(HAL_serie_core_path)
            # Copy new one
            HAL_serie_cube_path = os.path.join(
                cube_path, hal_src_path, "STM32{}xx_HAL_Driver".format(serie)
            )
            copyFolder(HAL_serie_cube_path, HAL_serie_core_path, {"*.chm"})
            # Update MD file
            for line in fileinput.input(md_HAL_path, inplace=True):
                line = regexmd.sub(rf"\g<1>{cube_HAL_version}", line)
                print(line, end="")
            # Commit all HAL files
            commitFiles(core_path, hal_commit_msg)
            HAL_updated = True

        if version.parse(core_CMSIS_version) < version.parse(cube_CMSIS_version):
            print(
                "Update "
                + serie
                + " CMSIS from version "
                + core_CMSIS_version
                + " to "
                + cube_CMSIS_version
            )
            # First delete CMSIS folder
            CMSIS_serie_dest_path = os.path.join(
                core_path, cmsis_dest_path, "STM32{}xx".format(serie.upper())
            )
            deleteFolder(CMSIS_serie_dest_path)
            # Copy new one
            CMSIS_serie_cube_path = os.path.join(
                cube_path, cmsis_src_path, "STM32{}xx".format(serie.upper())
            )
            copyFolder(CMSIS_serie_cube_path, CMSIS_serie_dest_path, {"iar", "arm"})
            # Update MD file
            for line in fileinput.input(md_CMSIS_path, inplace=True):
                line = regexmd.sub(rf"\g<1>{cube_CMSIS_version}", line)
                print(line, end="")
            # Commit all CMSIS files
            commitFiles(core_path, cmsis_commit_msg)
            CMSIS_updated = True

        if HAL_updated or CMSIS_updated:
            # Generate all wrapper files
            # Assuming the ArduinoModule-CMSIS repo available
            # at the same root level than the core
            print("Update {} wrapped files".format(serie))
            if stm32wrapper.wrap(core_path, None, False) == 0:
                commitFiles(core_path, wrapper_commit_msg)
            # Apply all related patch if any
            applyPatch(serie, HAL_updated, CMSIS_updated, core_path)


# Parser
upparser = argparse.ArgumentParser(
    description="Update HAL drivers and CMSIS devices from STM32cube released on GitHub"
)

upparser.add_argument(
    "-c", "--check", help="Check versions. Default all.", action="store_true"
)
upparser.add_argument(
    "-s", "--serie", metavar="pattern", help="Pattern of the STM32 serie(s) to update"
)

upargs = upparser.parse_args()


def main():
    global stm32_list
    # check config have to be done first
    checkConfig()
    updateCoreRepo()
    stm32_list = genSTM32List(hal_dest_path, upargs.serie)
    updateSTRepo()

    if upargs.check:
        printVersion()
    else:
        updateCore()


if __name__ == "__main__":
    main()
