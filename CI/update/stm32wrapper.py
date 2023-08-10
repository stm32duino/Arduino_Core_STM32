import argparse
import re
import sys
from itertools import groupby
from jinja2 import Environment, FileSystemLoader, Template
from pathlib import Path

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils import createFolder, deleteFolder, genSTM32List

# Base path
core_path = script_path.parent.parent
SrcWrapper_path = ""
HALDrivers_path = ""
CMSIS_Device_ST_path = ""
CMSIS_DSP_lib_path = ""
system_path = ""

# CMSIS outside of the core. Can be updated by arg
CMSIS_path = core_path.parent / "ArduinoModule-CMSIS" / "CMSIS_5"
CMSIS_DSPSrc_path = ""

# Out sources files
HALoutSrc_path = ""
LLoutSrc_path = ""
CMSIS_DSP_outSrc_path = ""

# Out include files
LLoutInc_path = ""

# Out startup files
CMSIS_Startupfile = ""

# Out system stm32 files
system_stm32_outfile = ""

# List of STM32 series
stm32_series = []

# Templating
templates_dir = script_path / "templates"
all_ll_h_file = "stm32yyxx_ll.h"
ll_h_file = "stm32yyxx_ll_ppp.h"
c_file = "stm32yyxx_zz_ppp.c"
stm32_def_build_file = "stm32_def_build.h"
system_stm32_file = "system_stm32yyxx.c"

# Create the jinja2 environment.
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
all_ll_header_file_template = j2_env.get_template(all_ll_h_file)
ll_h_file_template = j2_env.get_template(ll_h_file)
c_file_template = j2_env.get_template(c_file)
dsp_file_template = Template('#include "../Source/{{ dsp_dir }}/{{ dsp_name }}"\n\n')
stm32_def_build_template = j2_env.get_template(stm32_def_build_file)
system_stm32_template = j2_env.get_template(system_stm32_file)

# re
peripheral_c_regex = re.compile(r"stm32\w+_[h]?[al][l]_(.*).c$")
peripheral_h_regex = re.compile(r"stm32\w+_(\w+).h$")


def checkConfig(arg_core, arg_cmsis):
    global core_path
    global CMSIS_path
    global CMSIS_DSPSrc_path
    global SrcWrapper_path
    global HALDrivers_path
    global CMSIS_Device_ST_path
    global CMSIS_DSP_lib_path
    global CMSIS_DSP_outSrc_path
    global CMSIS_Startupfile
    global system_path
    global system_stm32_outfile
    global HALoutSrc_path
    global LLoutSrc_path
    global LLoutInc_path

    if arg_core is not None:
        core_path = Path(arg_core).resolve()
        CMSIS_path = core_path.parent / "ArduinoModule-CMSIS" / "CMSIS_5"

    if not core_path.is_dir():
        print(f"Could not find {core_path}")
        exit(1)

    system_path = core_path / "system"
    SrcWrapper_path = core_path / "libraries" / "SrcWrapper"
    HALDrivers_path = system_path / "Drivers"
    CMSIS_Device_ST_path = system_path / "Drivers" / "CMSIS" / "Device" / "ST"
    CMSIS_DSP_lib_path = core_path / "libraries" / "CMSIS_DSP"
    CMSIS_DSP_outSrc_path = CMSIS_DSP_lib_path / "src"
    CMSIS_Startupfile = core_path / "cores" / "arduino" / "stm32" / stm32_def_build_file
    system_stm32_outfile = SrcWrapper_path / "src" / "stm32" / system_stm32_file

    HALoutSrc_path = SrcWrapper_path / "src" / "HAL"
    LLoutSrc_path = SrcWrapper_path / "src" / "LL"
    LLoutInc_path = core_path / "cores" / "arduino" / "stm32" / "LL"

    if arg_cmsis is not None:
        CMSIS_path = Path(arg_cmsis).resolve()
    CMSIS_DSPSrc_path = CMSIS_path / "CMSIS" / "DSP" / "Source"


def printCMSISStartup(log):
    filelist = sorted(CMSIS_Device_ST_path.glob("**/startup_*.s"))
    filelist = [pth.name for pth in filelist]
    if len(filelist):
        if log:
            print(f"Number of startup files: {len(filelist)}")
        # Some mcu have two startup files
        # Ex: WL one for cm0plus and one for cm4
        # In that case this is the same value line so add an extra defined
        # to use the correct one.
        group_startup_list = [
            list(g) for _, g in groupby(filelist, lambda x: re.split("_|\\.", x)[1])
        ]
        cmsis_list = []
        for fn_list in group_startup_list:
            if len(fn_list) == 1:
                valueline = re.split("_|\\.", fn_list[0])
                vline = valueline[1].upper().replace("X", "x")
                cmsis_list.append({"vline": vline, "fn": fn_list[0], "cm": ""})
            else:
                for fn in fn_list:
                    valueline = re.split("_|\\.", fn)
                    vline = valueline[1].upper().replace("X", "x")
                    cm = valueline[2].upper()
                    cmsis_list.append({"vline": vline, "fn": fn, "cm": cm})
        out_file = open(CMSIS_Startupfile, "w", newline="\n")
        out_file.write(stm32_def_build_template.render(cmsis_list=cmsis_list))
        out_file.close()
    else:
        if log:
            print("No startup files found!")


def printSystemSTM32(log):
    filelist = sorted(system_path.glob("STM32*/system_stm32*.c"))
    if len(filelist):
        if log:
            print(f"Number of system stm32 files: {len(filelist)}")
        system_list = []
        for fp in filelist:
            system_list.append({"serie": fp.parent.name, "fn": fp.name})
        out_file = open(system_stm32_outfile, "w", newline="\n")
        out_file.write(system_stm32_template.render(system_list=system_list))
        out_file.close()
    else:
        if log:
            print("No system stm32 files found!")


def wrap(arg_core, arg_cmsis, log):
    global stm32_series
    # check config have to be done first
    checkConfig(arg_core, arg_cmsis)
    stm32_series = genSTM32List(HALDrivers_path, "")

    # Remove old file
    deleteFolder(HALoutSrc_path)
    createFolder(HALoutSrc_path)
    deleteFolder(LLoutSrc_path)
    createFolder(LLoutSrc_path)
    deleteFolder(LLoutInc_path)
    createFolder(LLoutInc_path)
    if CMSIS_Startupfile.is_file():
        CMSIS_Startupfile.unlink()
    all_ll_h_list = []
    # key: peripheral, value: serie list
    ll_h_dict = {}
    ll_c_dict = {}
    hal_c_dict = {}
    # Search all files for each series
    for serie in stm32_series:
        src = HALDrivers_path / f"STM32{serie}xx_HAL_Driver" / "Src"
        inc = HALDrivers_path / f"STM32{serie}xx_HAL_Driver" / "Inc"

        if src.exists():
            if log:
                print(f"Generating for {serie}...")
            lower = serie.lower()

            # Search stm32yyxx_[hal|ll]*.c file
            filelist = src.glob(f"**/stm32{lower}xx_*.c")
            for fp in filelist:
                legacy = True if fp.parent.name == "Legacy" else False
                # File name
                fn = fp.name
                found = peripheral_c_regex.match(fn)
                if "_template" in fn:
                    continue
                peripheral = found.group(1) if found else "hal"
                if "_ll_" in fn:
                    if peripheral in ll_c_dict:
                        if legacy:
                            # Change legacy value if exists
                            current_list = ll_c_dict.pop(peripheral)
                            if current_list[-1][0] == lower:
                                current_list.pop()
                            current_list.append((lower, legacy))
                            ll_c_dict[peripheral] = current_list
                        else:
                            ll_c_dict[peripheral].append((lower, legacy))
                    else:
                        ll_c_dict[peripheral] = [(lower, legacy)]
                else:
                    if peripheral in hal_c_dict:
                        if legacy:
                            # Change legacy value if exists
                            current_list = hal_c_dict.pop(peripheral)
                            if current_list[-1][0] == lower:
                                current_list.pop()
                            current_list.append((lower, legacy))
                            hal_c_dict[peripheral] = current_list
                        else:
                            hal_c_dict[peripheral].append((lower, legacy))
                    else:
                        hal_c_dict[peripheral] = [(lower, legacy)]

            # Search stm32yyxx_ll_*.h file
            filelist = inc.glob(f"stm32{lower}xx_ll_*.h")
            for fp in filelist:
                # File name
                fn = fp.name
                found = peripheral_h_regex.match(fn)
                if not found:
                    continue
                peripheral = found.group(1)
                # Amend all LL header list
                all_ll_h_list.append(fn.replace(lower, "yy"))
                if peripheral in ll_h_dict:
                    ll_h_dict[peripheral].append(lower)
                else:
                    ll_h_dict[peripheral] = [lower]

    # Generate stm32yyxx_hal_*.c file
    for key, value in hal_c_dict.items():
        if key == "hal":
            filepath = HALoutSrc_path / c_file.replace("zz", "hal").replace("_ppp", "")
        else:
            filepath = HALoutSrc_path / c_file.replace("zz", "hal").replace("ppp", key)
        out_file = open(filepath, "w", newline="\n")
        out_file.write(c_file_template.render(periph=key, type="hal", serieslist=value))
        out_file.close()
    # Generate stm32yyxx_ll_*.c file
    for key, value in ll_c_dict.items():
        filepath = LLoutSrc_path / c_file.replace("zz", "ll").replace("ppp", key)
        out_file = open(filepath, "w", newline="\n")
        out_file.write(c_file_template.render(periph=key, type="ll", serieslist=value))
        out_file.close()
    # Generate stm32yyxx_ll_*.h file
    for key, value in ll_h_dict.items():
        filepath = LLoutInc_path / ll_h_file.replace("ppp", key)
        out_file = open(filepath, "w", newline="\n")
        out_file.write(ll_h_file_template.render(periph=key, serieslist=value))
        out_file.close()
    if log:
        print("done")

    # Filter all LL header file
    all_ll_h_list = sorted(set(all_ll_h_list))
    # Generate the all LL header file
    all_ll_file = open(LLoutInc_path / all_ll_h_file, "w", newline="\n")
    all_ll_file.write(all_ll_header_file_template.render(ll_header_list=all_ll_h_list))
    all_ll_file.close()

    # CMSIS startup files
    printCMSISStartup(log)
    # system stm32 files
    printSystemSTM32(log)

    # CMSIS DSP C source file
    if not CMSIS_path.is_dir():
        print(f"Could not find {CMSIS_path}")
        print("CMSIS DSP generation skipped.")
    else:
        # Delete all subfolders
        deleteFolder(CMSIS_DSP_outSrc_path / "*")
        for path_object in CMSIS_DSPSrc_path.glob("**/*"):
            if path_object.is_file():
                if path_object.name.endswith(".c"):
                    dn = path_object.parent.name
                    fn = path_object.name
                    if dn in fn:
                        fdn = CMSIS_DSP_outSrc_path / dn
                        out_file = open(fdn / (f"{fn}"), "w", newline="\n")
                        out_file.write(dsp_file_template.render(dsp_dir=dn, dsp_name=fn))
                        out_file.close()
    return 0


if __name__ == "__main__":
    # Parser
    wrapparser = argparse.ArgumentParser(
        description="Generate all wrappers files (HAL, LL, CMSIS, ...)"
    )
    wrapparser.add_argument(
        "-c",
        "--core",
        metavar="core_path",
        help=f"Root path of the STM32 core. Default: {core_path}",
    )
    wrapparser.add_argument(
        "-s",
        "--cmsis",
        metavar="cmsis_path",
        help=f"Root path of the CMSIS. Default: {CMSIS_path}",
    )

    wrapargs = wrapparser.parse_args()

    wrap(wrapargs.core, wrapargs.cmsis, True)
