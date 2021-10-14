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
from stm32common import createFolder, deleteFolder, copyFolder, copyFile, genSTM32List
from urllib.parse import urljoin

if sys.platform.startswith("win32"):
    from colorama import init

    init(autoreset=True)

script_path = Path(__file__).parent.resolve()
home = Path.home()
path_config_filename = "update_config.json"

# GitHub
gh_st = "https://github.com/STMicroelectronics/"
gh_core = "https://github.com/stm32duino/Arduino_Core_STM32.git"
repo_generic_name = "STM32Cube"
repo_core_name = "Arduino_Core_STM32"
repo_local_path = home / "STM32Cube_repo"

# From
# Relative to repo path
hal_src_path = "Drivers"
system_path = "system"
cmsis_src_path = Path(hal_src_path, "CMSIS", "Device", "ST")
# To
system_dest_path = Path(system_path)
hal_dest_path = system_dest_path / hal_src_path
cmsis_dest_path = system_dest_path / hal_src_path / "CMSIS" / "Device" / "ST"

stm32_list = []  # Serie
cube_versions = collections.OrderedDict()  # key: serie name, value: cube version
cube_HAL_versions = collections.OrderedDict()  # key: serie name, value: HAL version
cube_CMSIS_versions = collections.OrderedDict()  # key: serie name, value: CMSIS version
core_HAL_versions = collections.OrderedDict()  # key: serie name, value: HAL version
core_CMSIS_versions = collections.OrderedDict()  # key: serie name, value: CMSIS version

# MD to update
md_CMSIS_path = "STM32YYxx_CMSIS_version.md"
md_HAL_path = "STM32YYxx_HAL_Driver_version.md"

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


def execute_cmd(cmd, stderror):
    try:
        output = subprocess.check_output(cmd, stderr=stderror).decode("utf-8").strip()
    except subprocess.CalledProcessError as e:
        print("Failed command: ")
        print(e.cmd)
        exit(e.returncode)
    return output


def create_config():
    global repo_local_path

    # Create a Json file for a better path management
    print(
        "'{}' file created. Please check the configuration.".format(
            script_path / path_config_filename
        )
    )
    path_config_file = open(path_config_filename, "w")
    path_config_file.write(
        json.dumps({"REPO_LOCAL_PATH": str(repo_local_path)}, indent=2)
    )
    path_config_file.close()
    exit(1)


def checkConfig():
    global repo_local_path
    global hal_dest_path
    global cmsis_dest_path
    global system_dest_path
    global md_HAL_path
    global md_CMSIS_path
    global stm32_def

    config_file_path = script_path / path_config_filename
    if config_file_path.is_file():
        try:
            config_file = open(config_file_path, "r")
            path_config = json.load(config_file)
            # Common path
            repo_local_path = Path(path_config["REPO_LOCAL_PATH"])
            config_file.close()
            hal_dest_path = repo_local_path / repo_core_name / hal_dest_path
            md_HAL_path = hal_dest_path / md_HAL_path
            cmsis_dest_path = repo_local_path / repo_core_name / cmsis_dest_path
            system_dest_path = repo_local_path / repo_core_name / system_dest_path
            md_CMSIS_path = cmsis_dest_path / md_CMSIS_path
            stm32_def = (
                repo_local_path
                / repo_core_name
                / "cores"
                / "arduino"
                / "stm32"
                / stm32_def
            )
        except IOError:
            print("Failed to open {}!".format(config_file))
    else:
        create_config()
    createFolder(repo_local_path)


def updateStm32Def(serie):
    print("Adding top HAL include for {}...".format(serie))
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
            print("#{} defined(STM32{}xx)".format(pcond, serie))
            print('  #include "stm32{}xx.h"'.format(serie.lower()))
            print(line.replace("#if", "#elif"), end="")
            added = True
        else:
            print(line, end="")


def updateHalConfDefault(serie):
    system_serie = system_dest_path / ("STM32{}xx".format(serie))
    hal_conf_base = "stm32{}xx_hal_conf".format(serie.lower())
    hal_conf_default = system_serie / (hal_conf_base + "_default.h")

    regex_module = re.compile(r"#define HAL_(\w+)_MODULE_ENABLED")

    old_guard = "STM32{}xx_HAL_CONF_H".format(serie)
    new_guard = "STM32{}xx_HAL_CONF_DEFAULT_H".format(serie)
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
    print("Creating system files for {}...".format(serie))
    system_serie = system_dest_path / ("STM32{}xx".format(serie))
    createFolder(system_serie)
    # Generate stm32yyxx_hal_conf_file.h
    stm32_hal_conf_file = system_serie / stm32yyxx_hal_conf_file.replace(
        "yy", serie.lower()
    )
    out_file = open(stm32_hal_conf_file, "w", newline="\n")
    out_file.write(stm32yyxx_hal_conf_file_template.render(serie=serie))
    out_file.close()
    # Copy system_stm32*.c file from CMSIS device template
    system_stm32_path = (
        cmsis_dest_path / "STM32{}xx".format(serie) / "Source" / "Templates"
    )
    filelist = sorted(system_stm32_path.glob("system_stm32*.c"))
    file_number = len(filelist)
    if file_number:
        if file_number == 1:
            file_number = 0
        else:
            menu_list = "Several system stm32 files exist:\n"
            for index, fp in enumerate(filelist):
                menu_list += "{}. {}\n".format(index, fp.name)
            menu_list += "Your choice: "
            while file_number >= len(filelist):
                file_number = int(input(menu_list))
        copyFile(filelist[file_number], system_serie)
    else:
        print("No system files found!")
    # Copy stm32yyxx_hal_conf_default.h file
    hal_conf_base = "stm32{}xx_hal_conf".format(serie.lower())
    hal_serie_path = hal_dest_path / "STM32{}xx_HAL_Driver".format(serie)
    hal_conf_file = hal_serie_path / "Inc" / (hal_conf_base + "_template.h")
    hal_conf_default = system_serie / (hal_conf_base + "_default.h")
    copyFile(hal_conf_file, hal_conf_default)


def getRepoBranchName(repo_path):
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
        print("Could not find branch name for {}!".format(repo_path))
        exit(1)
    return (rname, bname)


def updateCoreRepo():
    # Handle core repo
    repo_path = repo_local_path / repo_core_name
    print("Updating {}...".format(repo_core_name))
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
                "{}/{}".format(rname, bname),
            ],
        ]
    else:
        # Clone it as it does not exists yet
        git_cmds = [["git", "-C", repo_local_path, "clone", gh_core]]
    for cmd in git_cmds:
        execute_cmd(cmd, None)


def updateSTRepo():
    # Handle STM32Cube repo
    for serie in stm32_list:
        repo_name = repo_generic_name + serie
        repo_path = repo_local_path / repo_name
        gh_STM32Cube = urljoin(gh_st, repo_name + ".git")
        print("Updating " + repo_name + "...")
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
                    "{}/{}".format(rname, bname),
                ],
            ]
        else:
            # Clone it as it does not exists yet
            git_cmds = [["git", "-C", repo_local_path, "clone", gh_STM32Cube]]
        for cmd in git_cmds:
            execute_cmd(cmd, None)
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
    execute_cmd(["git", "-C", repo_path, "checkout", version_tag], subprocess.DEVNULL)
    cube_versions[serie] = version_tag
    # print("Latest tagged version available for " + repo_name + " is " + version_tag)


def parseVersion(path):
    main_found = False
    sub1_found = False
    sub2_found = False
    if "HAL" in str(path):
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
        print("Could not find the full version in {}".format(path))
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
    HAL_file = (
        repo_path
        / hal_src_path
        / "STM32{}xx_HAL_Driver".format(userie)
        / "Src"
        / "stm32{}xx_hal.c".format(lserie)
    )
    cube_HAL_versions[serie] = parseVersion(HAL_file)
    if upargs.add:
        core_HAL_versions[serie] = "0.0.0"
    else:
        HAL_file = (
            hal_dest_path
            / "STM32{}xx_HAL_Driver".format(userie)
            / "Src"
            / "stm32{}xx_hal.c".format(lserie)
        )
        core_HAL_versions[serie] = parseVersion(HAL_file)

    CMSIS_file = (
        repo_path
        / cmsis_src_path
        / "STM32{}xx".format(userie)
        / "Include"
        / "stm32{}xx.h".format(lserie)
    )
    cube_CMSIS_versions[serie] = parseVersion(CMSIS_file)
    if upargs.add:
        core_CMSIS_versions[serie] = "0.0.0"
    else:
        CMSIS_file = (
            cmsis_dest_path
            / "STM32{}xx".format(userie)
            / "Include"
            / "stm32{}xx.h".format(lserie)
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
    # Check if there is something to commit
    status = execute_cmd(
        ["git", "-C", repo_path, "status", "--untracked-files", "--short"], None
    )
    if not status:
        return
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
            "--message=" + commit_msg,
        ],
        subprocess.DEVNULL,
    )
    # Remove trailing space
    execute_cmd(
        ["git", "-C", repo_path, "rebase", "--whitespace=fix", "HEAD~1"],
        subprocess.DEVNULL,
    )


# Apply all patches found for the dedicated serie
def applyPatch(serie, HAL_updated, CMSIS_updated, repo_path):
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
                status = execute_cmd(
                    ["git", "-C", repo_path, "apply", "--check", patch],
                    subprocess.STDOUT,
                )
                if status:
                    # print("patch {} can't be applied".format(patch))
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
                # print("Failed command: {}".format(e.cmd))
        if len(patch_failed):
            for fp in patch_failed:
                print(
                    "Failed to apply {}:\n{}{}".format(
                        fp[0], fp[1], "" if len(fp) == 2 else "\n--> {}".format(fp[2])
                    )
                )


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


def updateCore():
    for serie in stm32_list:
        cube_name = repo_generic_name + serie
        cube_path = repo_local_path / cube_name
        core_path = repo_local_path / repo_core_name
        core_HAL_version = core_HAL_versions[serie]
        cube_HAL_version = cube_HAL_versions[serie]
        core_CMSIS_version = core_CMSIS_versions[serie]
        cube_CMSIS_version = cube_CMSIS_versions[serie]
        cube_version = cube_versions[serie]
        HAL_updated = False
        CMSIS_updated = False
        hal_commit_msg = """system: {0}: {3} STM32{0}xx HAL Drivers to v{1}

Included in STM32Cube{0} FW {2}""".format(
            serie, cube_HAL_version, cube_version, "add" if upargs.add else "update"
        )
        cmsis_commit_msg = """system: {0}: {3} STM32{0}xx CMSIS Drivers to v{1}

Included in STM32Cube{0} FW {2}""".format(
            serie, cube_CMSIS_version, cube_version, "add" if upargs.add else "update"
        )
        wrapper_commit_msg = "core: {}: {} wrapped files".format(
            serie, "add" if upargs.add else "update"
        )

        # Update HAL part if needed
        if version.parse(core_HAL_version) < version.parse(cube_HAL_version):
            if upargs.add:
                print("Adding {} HAL version {}...".format(serie, cube_HAL_version))
            else:
                print(
                    "Updating {} HAL from version {} to {}...".format(
                        serie, core_HAL_version, cube_HAL_version
                    )
                )
            # First delete old HAL version
            HAL_serie_core_path = hal_dest_path / "STM32{}xx_HAL_Driver".format(serie)
            deleteFolder(HAL_serie_core_path)
            # Copy new one
            HAL_serie_cube_path = (
                cube_path / hal_src_path / "STM32{}xx_HAL_Driver".format(serie)
            )
            copyFolder(HAL_serie_cube_path, HAL_serie_core_path, {"*.chm"})
            # Update MD file
            updateMDFile(md_HAL_path, serie, cube_HAL_version)
            # Commit all HAL files
            commitFiles(core_path, hal_commit_msg)
            HAL_updated = True

        if version.parse(core_CMSIS_version) < version.parse(cube_CMSIS_version):
            if upargs.add:
                print("Adding {} CMSIS version {}...".format(serie, cube_CMSIS_version))
            else:
                print(
                    "Updating {} CMSIS from version {} to {}...".format(
                        serie, core_CMSIS_version, cube_CMSIS_version
                    )
                )
            # First delete CMSIS folder
            CMSIS_serie_dest_path = cmsis_dest_path / "STM32{}xx".format(serie)
            deleteFolder(CMSIS_serie_dest_path)
            # Copy new one
            CMSIS_serie_cube_path = (
                cube_path / cmsis_src_path / "STM32{}xx".format(serie)
            )
            copyFolder(CMSIS_serie_cube_path, CMSIS_serie_dest_path, {"iar", "arm"})
            # Update MD file
            updateMDFile(md_CMSIS_path, serie, cube_CMSIS_version)
            # Commit all CMSIS files
            commitFiles(core_path, cmsis_commit_msg)
            CMSIS_updated = True

        if upargs.add:
            system_commit_msg = (
                "system: {0}: add STM32{0}xx system source files".format(serie)
            )
            update_hal_conf_commit_msg = (
                "system: {0}: update STM32{0}xx hal default config".format(serie)
            )
            update_stm32_def_commit_msg = "core: {0}: add top HAL include".format(serie)
            # Create system files
            createSystemFiles(serie)
            # Commit all system files
            commitFiles(core_path, system_commit_msg)
            # Update default HAL configuration
            updateHalConfDefault(serie)
            commitFiles(core_path, update_hal_conf_commit_msg)
            print("\tPlease, review carefully all the system files added!")
            print("\tAdd #ifndef/#endif to all definitions which should be")
            print(
                "\tredefinable in the stm32{}xx_hal_conf_default.h".format(
                    serie.lower()
                )
            )
            # Update stm32_def to add top HAL include
            updateStm32Def(serie)
            commitFiles(core_path, update_stm32_def_commit_msg)

        if HAL_updated or CMSIS_updated:
            # Generate all wrapper files
            # Assuming the ArduinoModule-CMSIS repo available
            # at the same root level than the core
            print(
                "{} {} wrapped files...".format(
                    "Adding" if upargs.add else "Updating", serie
                )
            )
            if stm32wrapper.wrap(core_path, None, False) == 0:
                commitFiles(core_path, wrapper_commit_msg)
            # Apply all related patch if any
            applyPatch(serie, HAL_updated, CMSIS_updated, core_path)


# Parser
upparser = argparse.ArgumentParser(
    description="Manage HAL drivers and CMSIS devices from STM32cube released on GitHub"
)

upparser.add_argument(
    "-c", "--check", help="Check versions. Default all.", action="store_true"
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
            print(upargs.add + " can't be added as it already exists!")
            exit(1)
    updateSTRepo()
    if upargs.check:
        printVersion()
    else:
        updateCore()


if __name__ == "__main__":
    main()
