import argparse
import collections
import fileinput
import json
import re
import subprocess
import stm32wrapper
import sys
from jinja2 import Environment, FileSystemLoader
from packaging import version
from pathlib import Path
from urllib.parse import urljoin
from xml.dom.minidom import parse

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils import copyFile, copyFolder, createFolder, deleteFolder, genSTM32List
from utils import defaultConfig, execute_cmd, getRepoBranchName

if sys.platform.startswith("win32"):
    from colorama import init

    init(autoreset=True)

home = Path.home()

# GitHub
gh_st = "https://github.com/STMicroelectronics/"
gh_core = "https://github.com/stm32duino/Arduino_Core_STM32.git"
gh_ble = "https://github.com/stm32duino/STM32duinoBLE.git"
repo_generic_name = "STM32Cube"
repo_core_name = "Arduino_Core_STM32"
repo_ble_name = "STM32duinoBLE"
repo_local_path = home / "STM32Cube_repo"
local_cube_path = Path("")

# From
# Relative to repo path
hal_src_path = "Drivers"
system_path = "system"
cmsis_src_path = Path(hal_src_path, "CMSIS", "Device", "ST")
# To
system_dest_path = Path(system_path)
hal_dest_path = system_dest_path / hal_src_path
cmsis_dest_path = system_dest_path / hal_src_path / "CMSIS" / "Device" / "ST"

stm32_list = []  # series
cube_versions = collections.OrderedDict()  # key: serie name, value: cube version
cube_HAL_versions = collections.OrderedDict()  # key: serie name, value: HAL version
cube_CMSIS_versions = collections.OrderedDict()  # key: serie name, value: CMSIS version
core_HAL_versions = collections.OrderedDict()  # key: serie name, value: HAL version
core_CMSIS_versions = collections.OrderedDict()  # key: serie name, value: CMSIS version

# MD to update
md_CMSIS_path = "STM32YYxx_CMSIS_version.md"
md_HAL_path = "STM32YYxx_HAL_Driver_version.md"

# Pattern list of files to skip
hal_skip_pattern = {"*.chm"}
cmsis_skip_pattern = {"iar", "arm"}
common_skip_pattern = {
    ".github",
    "CODE_OF_CONDUCT.md",
    "CONTRIBUTING.md",
    "SECURITY.md",
}

# stm32 def file to update
stm32_def = "stm32_def.h"

# Templating
templates_dir = script_path / "templates"
stm32yyxx_hal_conf_file = "stm32yyxx_hal_conf.h"
# Create the jinja2 environment.
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
stm32yyxx_hal_conf_file_template = j2_env.get_template(stm32yyxx_hal_conf_file)

# Format
out_format_Header = "| {:^22} | {:^31} | {:^31} |"
out_subheader = "| {:^4} | {:^7} | {:^8} | {:^8} | {:^1} | {:^8} | {:^8} | {:^1} |"
out_format = "| {:^12} | {:^7} | {:^8} | {:^8} | {:^1} | {:^8} | {:^8} | {:^1} |"
out_separator = "-" * 70


def checkConfig():
    global repo_local_path
    global hal_dest_path
    global cmsis_dest_path
    global system_dest_path
    global md_HAL_path
    global md_CMSIS_path
    global stm32_def

    config_file_path = script_path / "update_config.json"
    if config_file_path.is_file():
        try:
            config_file = open(config_file_path, "r")
            path_config = json.load(config_file)
            config_file.close()
            # Common path
            if "REPO_LOCAL_PATH" not in path_config:
                path_config["REPO_LOCAL_PATH"] = str(repo_local_path)
                defaultConfig(config_file_path, path_config)
            else:
                repo_local_path = Path(path_config["REPO_LOCAL_PATH"])
            hal_dest_path = repo_local_path / repo_core_name / hal_dest_path
            md_HAL_path = hal_dest_path / md_HAL_path
            cmsis_dest_path = repo_local_path / repo_core_name / cmsis_dest_path
            system_dest_path = repo_local_path / repo_core_name / system_dest_path
            md_CMSIS_path = cmsis_dest_path / md_CMSIS_path
            stm32_def = (
                repo_local_path
                / repo_core_name
                / "libraries"
                / "SrcWrapper"
                / "inc"
                / stm32_def
            )
        except IOError:
            print(f"Failed to open {config_file}!")
    else:
        defaultConfig(config_file_path, {"REPO_LOCAL_PATH": str(repo_local_path)})
    createFolder(repo_local_path)


def updateStm32Def(serie):
    print(f"Adding top HAL include for {serie}...")
    regex_serie = re.compile(r"defined\(STM32(\w+)xx\)")
    # Add the new STM32YY entry
    added = False
    serie_found = ""
    nb_serie = 0
    for line in fileinput.input(stm32_def, inplace=True):
        m = regex_serie.search(line)
        if m:
            serie_found = m.group(1)
            nb_serie += 1
        if (
            not added
            and serie_found
            and ((serie_found > serie) or (not m and "include" not in line))
        ):
            if nb_serie == 1:
                pcond = "if"
            else:
                pcond = "elif"
            print(f"#{pcond} defined(STM32{serie}xx)")
            print(f'  #include "stm32{serie.lower()}xx.h"')
            print(line.replace("#if", "#elif"), end="")
            added = True
        else:
            print(line, end="")


def updateHalConfDefault(serie):
    system_serie = system_dest_path / f"STM32{serie}xx"
    hal_conf_base = f"stm32{serie.lower()}xx_hal_conf"
    hal_conf_default = system_serie / f"{hal_conf_base}_default.h"

    regex_module = re.compile(r"#define HAL_(\w+)_MODULE_ENABLED")

    old_guard = f"STM32{serie}xx_HAL_CONF_H"
    new_guard = f"STM32{serie}xx_HAL_CONF_DEFAULT_H"
    module_sel = "Module Selection"

    new_include = """/**
  * @brief Include the default list of modules to be used in the HAL driver
  *        and manage module deactivation
  */
#include "stm32yyxx_hal_conf.h"
#if 0
"""
    module_found = False
    end_guard_added = False
    for line in fileinput.input(hal_conf_default, inplace=True):
        if old_guard in line:
            print(line.replace(old_guard, new_guard), end="")
        elif "@file" in line:
            print(line.replace("conf.h", "conf_default.h"), end="")
        elif "@brief" in line:
            print(line.replace("HAL config", "HAL default config"), end="")
        elif "@author" not in line:
            m = regex_module.search(line)
            if m:
                module_found = True
            elif module_found and not end_guard_added:
                end_guard_added = True
                print("#endif")
            print(line, end="")
            if module_sel in line:
                print(new_include, end="")


def createSystemFiles(serie):
    print(f"Creating system files for {serie}...")
    system_serie = system_dest_path / f"STM32{serie}xx"
    createFolder(system_serie)
    # Generate stm32yyxx_hal_conf_file.h
    stm32_hal_conf_file = system_serie / stm32yyxx_hal_conf_file.replace(
        "yy", serie.lower()
    )
    out_file = open(stm32_hal_conf_file, "w", newline="\n")
    out_file.write(stm32yyxx_hal_conf_file_template.render(serie=serie))
    out_file.close()
    # Copy system_stm32*.c file from CMSIS device template
    system_stm32_path = cmsis_dest_path / f"STM32{serie}xx" / "Source" / "Templates"
    filelist = sorted(system_stm32_path.glob("system_stm32*.c"))
    file_number = len(filelist)
    if file_number:
        if file_number == 1:
            file_number = 0
        else:
            menu_list = "Several system stm32 files exist:\n"
            for index, fp in enumerate(filelist):
                menu_list += f"{index}. {fp.name}\n"
            menu_list += "Your choice: "
            while file_number >= len(filelist):
                file_number = int(input(menu_list))
        copyFile(filelist[file_number], system_serie)
    else:
        print("No system files found!")
    # Copy stm32yyxx_hal_conf_default.h file
    hal_conf_base = f"stm32{serie.lower()}xx_hal_conf"
    hal_serie_path = hal_dest_path / f"STM32{serie}xx_HAL_Driver"
    hal_conf_file = hal_serie_path / "Inc" / f"{hal_conf_base}_template.h"
    hal_conf_default = system_serie / f"{hal_conf_base}_default.h"
    copyFile(hal_conf_file, hal_conf_default)


def updateCoreRepo():
    # Handle core repo
    repo_path = repo_local_path / repo_core_name
    print(f"Updating {repo_core_name}...")
    if repo_path.exists():
        rname, bname = getRepoBranchName(repo_path)
        # Get new tags from the remote
        git_cmds = [
            ["git", "-C", repo_path, "fetch"],
            [
                "git",
                "-C",
                repo_path,
                "checkout",
                "-B",
                bname,
                f"{rname}/{bname}",
            ],
        ]
    else:
        # Clone it as it does not exists yet
        git_cmds = [["git", "-C", repo_local_path, "clone", gh_core]]
    for cmd in git_cmds:
        execute_cmd(cmd, None)


def checkSTLocal():
    global local_cube_path
    global stm32_list
    # Handle local STM32Cube
    local_cube_path = Path(upargs.local)
    if not local_cube_path.exists():
        print(f"Could not find local copy: {local_cube_path}!")
        exit(1)
    cube_release = "Unknown"
    # Define the serie based on package.xml
    package_file = local_cube_path / "package.xml"
    if package_file.is_file():
        xml_file = parse(str(package_file))
        PackDescription_item = xml_file.getElementsByTagName("PackDescription")
        for item in PackDescription_item:
            cube_release = item.attributes["Release"].value
            if item.hasAttribute("Patch"):
                cube_release = item.attributes["Patch"].value
    else:
        print(f"Could not find: {package_file}!")
        exit(1)
    # Process Cube release
    release_regex = r"FW.(.+).(\d+.\d+.\d+.*)$"
    release_match = re.match(release_regex, cube_release)
    if release_match:
        serie = release_match.group(1)
        cube_release = release_match.group(2)
        print(f"Local STM32Cube {serie} release {cube_release}\n")
    else:
        print(
            f"Unable to define local STM32Cube serie and version of {local_cube_path}!"
        )
        exit(1)
    cube_versions[serie] = cube_release
    # Manage only one STM32Cube
    stm32_list = [serie.upper()]
    checkVersion(serie, local_cube_path)


def updateSTRepo():
    # Handle STM32Cube repo
    for serie in stm32_list:
        repo_name = f"{repo_generic_name}{serie}"
        repo_path = repo_local_path / repo_name
        gh_STM32Cube = urljoin(gh_st, f"{repo_name}.git")
        print(f"Updating {repo_name}...")
        if repo_path.exists():
            rname, bname = getRepoBranchName(repo_path)
            # Get new tags from the remote
            execute_cmd(["git", "-C", repo_path, "fetch"], None)
            execute_cmd(
                [
                    "git",
                    "-C",
                    repo_path,
                    "checkout",
                    "-B",
                    bname,
                    f"{rname}/{bname}",
                ],
                None,
            )
            gitmodule_path = repo_path / ".gitmodules"
            if gitmodule_path.exists():
                execute_cmd(
                    [
                        "git",
                        "-C",
                        repo_path,
                        "submodule",
                        "update",
                        "--init",
                        "--recursive",
                    ],
                    None,
                )
        else:
            # Clone it as it does not exists yet
            execute_cmd(
                ["git", "-C", repo_local_path, "clone", "--recursive", gh_STM32Cube],
                None,
            )
        latestTag(serie, repo_name, repo_path)
        checkVersion(serie, repo_path)


def latestTag(serie, repo_name, repo_path):
    global cube_versions
    # Checkout the latest tag

    sha1_id = execute_cmd(
        ["git", "-C", repo_path, "rev-list", "--tags", "--max-count=1"], None
    )

    version_tag = execute_cmd(
        ["git", "-C", repo_path, "describe", "--tags", sha1_id], None
    )
    execute_cmd(
        ["git", "-C", repo_path, "checkout", "-f", "--recurse-submodules", version_tag],
        subprocess.DEVNULL,
    )
    cube_versions[serie] = version_tag
    # print(f"Latest tagged version available for {repo_name} is {version_tag}")


def parseVersion(path, patterns):
    main_found = False
    sub1_found = False
    sub2_found = False
    rc_found = False

    for i, line in enumerate(open(path, encoding="utf8", errors="ignore")):
        for match in re.finditer(patterns[0], line):
            VERSION_MAIN = int(match.group(1), 16)
            main_found = True
        for match in re.finditer(patterns[1], line):
            VERSION_SUB1 = int(match.group(1), 16)
            sub1_found = True
        for match in re.finditer(patterns[2], line):
            VERSION_SUB2 = int(match.group(1), 16)
            sub2_found = True
        for match in re.finditer(patterns[3], line):
            VERSION_RC = int(match.group(1), 16)
            rc_found = True
        if main_found and sub1_found and sub2_found and rc_found:
            break
    else:
        print(f"Could not find the full version in {path}")
        if main_found:
            print(f"main version found: {VERSION_MAIN}")
        VERSION_MAIN = "FF"
        if sub1_found:
            print(f"sub1 version found: {VERSION_SUB1}")
        VERSION_SUB1 = "FF"
        if sub2_found:
            print(f"sub2 version found: {VERSION_SUB2}")
        VERSION_SUB2 = "FF"
        if rc_found:
            print(f"rc version found: {VERSION_RC}")
        VERSION_RC = "FF"

    ret = f"{VERSION_MAIN}.{VERSION_SUB1}.{VERSION_SUB2}"

    if VERSION_RC != 0:
        ret = f"{ret}RC{VERSION_RC}"

    return ret


def checkVersion(serie, repo_path):
    lserie = serie.lower()
    userie = serie.upper()

    patterns = [re.compile(r"HAL_VERSION_MAIN.*0x([\dA-Fa-f]+)")]
    patterns.append(re.compile(r"HAL_VERSION_SUB1.*0x([\dA-Fa-f]+)"))
    patterns.append(re.compile(r"HAL_VERSION_SUB2.*0x([\dA-Fa-f]+)"))
    patterns.append(re.compile(r"HAL_VERSION_RC.*0x([\dA-Fa-f]+)"))

    HAL_file = (
        repo_path
        / hal_src_path
        / f"STM32{userie}xx_HAL_Driver"
        / "Src"
        / f"stm32{lserie}xx_hal.c"
    )
    with open(HAL_file, "r") as fp:
        data = fp.read()
        if "HAL_VERSION_MAIN" not in data:
            HAL_file = (
                repo_path
                / hal_src_path
                / f"STM32{userie}xx_HAL_Driver"
                / "Inc"
                / f"stm32{lserie}xx_hal.h"
            )
    cube_HAL_versions[serie] = parseVersion(HAL_file, patterns)
    if upargs.add:
        core_HAL_versions[serie] = "0.0.0"
    else:
        HAL_file = (
            hal_dest_path
            / f"STM32{userie}xx_HAL_Driver"
            / "Src"
            / f"stm32{lserie}xx_hal.c"
        )
        with open(HAL_file, "r") as fp:
            data = fp.read()
            if "HAL_VERSION_MAIN" not in data:
                HAL_file = (
                    repo_path
                    / hal_dest_path
                    / f"STM32{userie}xx_HAL_Driver"
                    / "Inc"
                    / f"stm32{lserie}xx_hal.h"
                )
        core_HAL_versions[serie] = parseVersion(HAL_file, patterns)

    patterns = [
        re.compile(r"(?:CMSIS|DEVICE|CMSIS_DEVICE)_VERSION_MAIN.*0x([\dA-Fa-f]+)")
    ]
    patterns.append(
        re.compile(r"(?:CMSIS|DEVICE|CMSIS_DEVICE)_VERSION_SUB1.*0x([\dA-Fa-f]+)")
    )
    patterns.append(
        re.compile(r"(?:CMSIS|DEVICE|CMSIS_DEVICE)_VERSION_SUB2.*0x([\dA-Fa-f]+)")
    )
    patterns.append(
        re.compile(r"(?:CMSIS|DEVICE|CMSIS_DEVICE)_VERSION_RC.*0x([\dA-Fa-f]+)")
    )
    CMSIS_file = (
        repo_path
        / cmsis_src_path
        / f"STM32{userie}xx"
        / "Include"
        / f"stm32{lserie}xx.h"
    )
    cube_CMSIS_versions[serie] = parseVersion(CMSIS_file, patterns)
    if upargs.add:
        core_CMSIS_versions[serie] = "0.0.0"
    else:
        CMSIS_file = (
            cmsis_dest_path / f"STM32{userie}xx" / "Include" / f"stm32{lserie}xx.h"
        )
        core_CMSIS_versions[serie] = parseVersion(CMSIS_file, patterns)

    # print(f"STM32Cube{serie} HAL version: {cube_HAL_versions[serie]}")
    # print(f"STM32Core{serie} HAL version: {core_HAL_versions[serie]}")
    # print(f"STM32Cube{serie} CMSIS version: {cube_CMSIS_versions[serie]}")
    # print(f"STM32Core{serie} CMSIS version: {core_CMSIS_versions[serie]}")


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
                f"\033[1m{serie}\033[0m",
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
    # Check if there is something to commit
    status = execute_cmd(
        ["git", "-C", repo_path, "status", "--untracked-files", "--short"], None
    )
    if not status:
        return False
    # Staged all files: new, modified and deleted
    execute_cmd(["git", "-C", repo_path, "add", "--all"], subprocess.DEVNULL)
    # Commit all stage files with signoff and message
    execute_cmd(
        [
            "git",
            "-C",
            repo_path,
            "commit",
            "--all",
            "--signoff",
            f"--message={commit_msg}",
        ],
        subprocess.DEVNULL,
    )
    # Remove trailing space
    execute_cmd(
        ["git", "-C", repo_path, "rebase", "--whitespace=fix", "HEAD~1"],
        subprocess.DEVNULL,
    )
    return True


# Apply all patches found for the dedicated serie
def applyPatch(serie, HAL_updated, CMSIS_updated, openamp_updated, repo_path):
    # First check if some patch need to be applied
    patch_path = script_path / "patch"
    patch_list = []
    if HAL_updated:
        HAL_patch_path = patch_path / "HAL" / serie
        if HAL_patch_path.is_dir():
            for file in HAL_patch_path.iterdir():
                if file.name.endswith(".patch"):
                    patch_list.append(HAL_patch_path / file)
    if CMSIS_updated:
        CMSIS_patch_path = patch_path / "CMSIS" / serie
        if CMSIS_patch_path.is_dir():
            for file in CMSIS_patch_path.iterdir():
                if file.name.endswith(".patch"):
                    patch_list.append(CMSIS_patch_path / file)
    if openamp_updated:
        openamp_patch_path = patch_path / "openamp"
        if openamp_patch_path.is_dir():
            for file in openamp_patch_path.iterdir():
                if file.name.endswith(".patch"):
                    patch_list.append(openamp_patch_path / file)

    if len(patch_list):
        patch_failed = []
        print(
            f"Apply {len(patch_list)} patch{'' if len(patch_list) == 1 else 'es'} for {serie}"
        )
        for patch in patch_list:
            try:
                # Test the patch before apply it
                status = execute_cmd(
                    ["git", "-C", repo_path, "apply", "--check", patch],
                    subprocess.STDOUT,
                )
                if status:
                    # print(f"patch {patch} can't be applied")
                    patch_failed.append([patch, status])
                    continue
                # Apply the patch
                status = execute_cmd(
                    [
                        "git",
                        "-C",
                        repo_path,
                        "am",
                        "--keep-non-patch",
                        "--quiet",
                        "--signoff",
                        patch,
                    ],
                    None,
                )
            except subprocess.CalledProcessError as e:
                patch_failed.append([patch, e.cmd, e.output.decode("utf-8")])
                # print(f"Failed command: {e.cmd}")
        if len(patch_failed):
            for fp in patch_failed:
                e_out = "" if len(fp) == 2 else f"\n--> {fp[2]}"
                print(f"Failed to apply {fp[0]}:\n{fp[1]}{e_out}")


def updateMDFile(md_file, serie, version):
    regexmd_up = re.compile(rf"(STM32{serie}:\s+)\d+.\d+.\d+")
    regexmd_serie = re.compile(r"STM32(\w+):\s+\d+.\d+.\d+")
    regexmd_add = re.compile(r"(STM32)\w+(:\s+)\d+.\d+.\d+")
    # Update MD file
    if upargs.add:  # Add the new STM32YY entry
        added = False
        new_line = ""
        serie_found = ""
        for line in fileinput.input(md_file, inplace=True):
            m = regexmd_serie.search(line)
            if m:
                serie_found = m.group(1)
                if not new_line:
                    new_line = regexmd_add.sub(rf"\g<1>{serie}\g<2>{version}", line)
            if not added and serie_found and (serie_found > serie or not m):
                print(new_line, end="")
                added = True
            print(line, end="")
    else:  # Update the version
        for line in fileinput.input(md_file, inplace=True):
            print(regexmd_up.sub(rf"\g<1>{version}", line), end="")


def updateBleRepo():
    # Handle BLE library repo
    repo_path = repo_local_path / repo_ble_name
    print(f"Updating {repo_ble_name}...")
    if repo_path.exists():
        rname, bname = getRepoBranchName(repo_path)
        # Get new tags from the remote
        git_cmds = [
            ["git", "-C", repo_path, "fetch"],
            [
                "git",
                "-C",
                repo_path,
                "checkout",
                "-B",
                bname,
                f"{rname}/{bname}",
            ],
        ]
    else:
        # Clone it as it does not exists yet
        git_cmds = [["git", "-C", repo_local_path, "clone", gh_ble]]
    for cmd in git_cmds:
        execute_cmd(cmd, None)


ble_file_list = [
    "Middlewares/ST/STM32_WPAN/ble/core/ble_bufsize.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/hw.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci/shci.c",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci/shci.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/mbox_def.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/shci_tl.c",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/shci_tl.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/tl.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/tl_mbox.c",
    "Middlewares/ST/STM32_WPAN/stm32_wpan_common.h",
    "Middlewares/ST/STM32_WPAN/utilities/stm_list.c",
    "Middlewares/ST/STM32_WPAN/utilities/stm_list.h",
    "Middlewares/ST/STM32_WPAN/LICENSE.md",
    "Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_TransparentMode/Core/Inc/app_conf.h",
    "Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/"
    + "hw_ipcc.c",
]


def applyBlePatch():
    print(" Applying patches to ble library")
    BLE_patch_path = repo_local_path / repo_ble_name / "extras" / "STM32_WPAN"
    patch_list = []

    if BLE_patch_path.is_dir():
        for file in sorted(BLE_patch_path.iterdir()):
            if file.name.endswith(".patch"):
                patch_list.append(BLE_patch_path / file)

    if len(patch_list):
        patch_failed = []
        print(
            f" Apply {len(patch_list)} patch{'' if len(patch_list) == 1 else 'es'} for BLE library"
        )
        for patch in patch_list:
            try:
                # Test the patch before apply it
                status = execute_cmd(
                    [
                        "git",
                        "-C",
                        repo_local_path / repo_ble_name,
                        "apply",
                        "--check",
                        patch,
                    ],
                    subprocess.STDOUT,
                )
                if status:
                    print(f"patch {patch} can't be applied")
                    patch_failed.append([patch, status])
                    continue

                # Apply the patch
                status = execute_cmd(
                    [
                        "git",
                        "-C",
                        repo_local_path / repo_ble_name,
                        "am",
                        "--keep-non-patch",
                        "--quiet",
                        "--signoff",
                        patch,
                    ],
                    None,
                )
            except subprocess.CalledProcessError as e:
                patch_failed.append([patch, e.cmd, e.output.decode("utf-8")])
                # print(f"Failed command: {e.cmd}")
        if len(patch_failed):
            for fp in patch_failed:
                e_out = "" if len(fp) == 2 else f"\n--> {fp[2]}"
                print(f"Failed to apply {fp[0]}:\n{fp[1]}{e_out}")


def updateBleReadme(filepath, version):
    print(" Updating README.md in ble library")
    for line in fileinput.input(filepath, inplace=True):
        print(re.sub(r"v\d+.\d+.\d+", f"{version}", line), end="")


def updateBleLibrary():
    if upargs.local:
        cube_path = local_cube_path
    else:
        cube_name = f"{repo_generic_name}WB"
        cube_path = repo_local_path / cube_name
    ble_path = repo_local_path / repo_ble_name / "src" / "utility" / "STM32_WPAN"
    cube_version = cube_versions["WB"]

    ble_commit_msg = f"chore: update STM32_WPAN from Cube version {cube_version}"

    for file in ble_file_list:
        file_path = Path(cube_path / file)
        file_name = file_path.name
        if file_path.exists:
            # copy each file to destination
            if not Path(ble_path / file_name).parent.exists():
                Path(ble_path / file_name).parent.mkdir(parents=True)
            if file_name == "app_conf.h":
                # rename app_conf.h to app_conf_default.h
                copyFile(file_path, ble_path / "app_conf_default.h")
            else:
                copyFile(file_path, ble_path / file_name)
        else:
            print(f"File : {file_path} not found")
            print("Abort")
            sys.exit()

    updateBleReadme(ble_path / "README.md", cube_version)

    # Commit all BLE files
    commitFiles(ble_path, ble_commit_msg)

    # Apply BLE Arduino specific patch
    applyBlePatch()


def updateBle():
    print("Updating WB BLE library")
    updateBleRepo()
    updateBleLibrary()


def updateOpenAmp():
    print("Updating OpenAmp Middleware")
    repo_path = repo_local_path / repo_core_name
    if upargs.local:
        cube_path = local_cube_path
    else:
        cube_name = f"{repo_generic_name}MP1"
        cube_path = repo_local_path / cube_name
    OpenAmp_cube_path = cube_path / "Middlewares" / "Third_Party" / "OpenAMP"
    OpenAmp_core_path = repo_path / "system" / "Middlewares" / "OpenAMP"

    # First delete old HAL version
    deleteFolder(OpenAmp_core_path)

    # Copy new one
    copyFolder(OpenAmp_cube_path, OpenAmp_core_path)


def updateCore():
    for serie in stm32_list:
        if upargs.local:
            cube_path = local_cube_path
        else:
            cube_name = f"{repo_generic_name}{serie}"
            cube_path = repo_local_path / cube_name
        core_path = repo_local_path / repo_core_name
        core_HAL_ver = core_HAL_versions[serie]
        cube_HAL_ver = cube_HAL_versions[serie]
        core_CMSIS_ver = core_CMSIS_versions[serie]
        cube_CMSIS_ver = cube_CMSIS_versions[serie]
        cube_version = cube_versions[serie]
        HAL_updated = False
        CMSIS_updated = False
        openamp_updated = False
        hal_commit_msg = """system({0}) {3} STM32{0}xx HAL Drivers to v{1}

Included in STM32Cube{0} FW {2}""".format(
            serie, cube_HAL_ver, cube_version, "add" if upargs.add else "update"
        )
        cmsis_commit_msg = """system({0}): {3} STM32{0}xx CMSIS Drivers to v{1}

Included in STM32Cube{0} FW {2}""".format(
            serie, cube_CMSIS_ver, cube_version, "add" if upargs.add else "update"
        )
        wrapper_commit_msg = (
            f"core({serie}): {'add' if upargs.add else 'update'} wrapped files"
        )

        # Update HAL part if needed
        if version.parse(core_HAL_ver) < version.parse(cube_HAL_ver):
            if upargs.add:
                print(f"Adding {serie} HAL version {cube_HAL_ver}...")
            else:
                print(
                    f"Updating {serie} HAL from version {core_HAL_ver} to {cube_HAL_ver}..."
                )
            # First delete old HAL version
            HAL_serie_core_path = hal_dest_path / f"STM32{serie}xx_HAL_Driver"
            deleteFolder(HAL_serie_core_path)
            # Copy new one
            HAL_serie_cube_path = (
                cube_path / hal_src_path / f"STM32{serie}xx_HAL_Driver"
            )
            copyFolder(
                HAL_serie_cube_path,
                HAL_serie_core_path,
                hal_skip_pattern.union(common_skip_pattern),
            )
            # Update MD file
            updateMDFile(md_HAL_path, serie, cube_HAL_ver)
            # Commit all HAL files
            HAL_updated = commitFiles(core_path, hal_commit_msg)

        if version.parse(core_CMSIS_ver) < version.parse(cube_CMSIS_ver):
            if upargs.add:
                print(f"Adding {serie} CMSIS version {cube_CMSIS_ver}...")
            else:
                print(
                    f"Updating {serie} CMSIS from version {core_CMSIS_ver} to {cube_CMSIS_ver}..."
                )
            # First delete CMSIS folder
            CMSIS_serie_dest_path = cmsis_dest_path / f"STM32{serie}xx"
            deleteFolder(CMSIS_serie_dest_path)
            # Copy new one
            CMSIS_serie_cube_path = cube_path / cmsis_src_path / f"STM32{serie}xx"
            copyFolder(
                CMSIS_serie_cube_path,
                CMSIS_serie_dest_path,
                cmsis_skip_pattern.union(common_skip_pattern),
            )
            # Update MD file
            updateMDFile(md_CMSIS_path, serie, cube_CMSIS_ver)
            # Commit all CMSIS files
            CMSIS_updated = commitFiles(core_path, cmsis_commit_msg)

        if upargs.add:
            system_commit_msg = (
                f"system({serie}): add STM32{serie}xx system source files"
            )
            update_hal_conf_commit_msg = (
                f"system({serie}): update STM32{serie}xx hal default config"
            )
            update_stm32_def_commit_msg = f"core({serie}): add top HAL include"
            # Create system files
            createSystemFiles(serie)
            # Commit all system files
            commitFiles(core_path, system_commit_msg)
            # Update default HAL configuration
            updateHalConfDefault(serie)
            commitFiles(core_path, update_hal_conf_commit_msg)
            print("\tPlease, review carefully all the system files added!")
            print("\tAdd #ifndef/#endif to all definitions which should be")
            print(f"\tredefinable in the stm32{serie.lower()}xx_hal_conf_default.h")
            # Update stm32_def to add top HAL include
            updateStm32Def(serie)
            commitFiles(core_path, update_stm32_def_commit_msg)

        if serie == "MP1":
            print(f"Updating {serie} OpenAmp Middleware to Cube {cube_version} ...")
            updateOpenAmp()
            openAmp_commit_msg = (
                f"system(openamp): update middleware to MP1 Cube version {cube_version}"
            )
            openamp_updated = commitFiles(core_path, openAmp_commit_msg)
            print(
                "WARNING: OpenAmp MW has been updated, please check whether Arduino implementation:"
            )
            print("          * cores/arduino/stm32/OpenAMP/mbox_ipcc.h")
            print("          * cores/arduino/stm32/OpenAMP/mbox_ipcc.c")
            print("          * cores/arduino/stm32/OpenAMP/rsc_table.h")
            print("          * cores/arduino/stm32/OpenAMP/rsc_table.c")
            print("          * cores/arduino/stm32/OpenAMP/openamp.h")
            print("          * cores/arduino/stm32/OpenAMP/openamp.c")
            print("          * cores/arduino/stm32/OpenAMP/openamp_conf.h")
            print("       should be updated from Cube project:")
            print(
                "          --> Projects/STM32MP157C-DK2/Applications/OpenAMP/OpenAMP_TTY_echo"
            )

        if serie == "WB":
            updateBle()

        if HAL_updated or CMSIS_updated or openamp_updated:
            # Generate all wrapper files
            # Assuming the ArduinoModule-CMSIS repo available
            # at the same root level than the core
            print(f"{'Adding' if upargs.add else 'Updating'} {serie} wrapped files...")
            if stm32wrapper.wrap(core_path, None, False) == 0:
                commitFiles(core_path, wrapper_commit_msg)
            # Apply all related patch if any
            applyPatch(serie, HAL_updated, CMSIS_updated, openamp_updated, core_path)


# Parser
upparser = argparse.ArgumentParser(
    description="Manage HAL drivers and CMSIS devices from STM32cube released on GitHub"
)

upparser.add_argument(
    "-c", "--check", help="Check versions. Default all.", action="store_true"
)
upparser.add_argument(
    "-l",
    "--local",
    metavar="local",
    help="Use local copy of one STM32cube instead of GitHub",
)
group = upparser.add_mutually_exclusive_group()
group.add_argument(
    "-s", "--serie", metavar="pattern", help="Pattern of the STM32 serie(s) to update"
)
group.add_argument(
    "-a", "--add", metavar="name", help="STM32 serie name to add. Ex: 'F1'"
)


upargs = upparser.parse_args()


def main():
    global stm32_list
    # check config have to be done first
    checkConfig()
    updateCoreRepo()
    stm32_list = genSTM32List(hal_dest_path, upargs.serie)
    if upargs.add:
        if upargs.add.upper() not in stm32_list:
            stm32_list = [upargs.add.upper()]
        else:
            print(f"{upargs.add} can't be added as it already exists!")
            exit(1)
    if upargs.local:
        checkSTLocal()
    else:
        updateSTRepo()
    if upargs.check:
        printVersion()
    else:
        updateCore()


if __name__ == "__main__":
    main()
