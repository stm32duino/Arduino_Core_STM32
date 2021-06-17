import argparse
import re
from jinja2 import Environment, FileSystemLoader, Template
from pathlib import Path
from stm32common import createFolder, deleteFolder, genSTM32List

script_path = Path(__file__).parent.resolve()
# Base path
core_path = script_path.parent.parent
SrcWrapper_path = ""
HALDrivers_path = ""
CMSIS_Device_ST_path = ""
CMSIS_DSP_lib_path = ""

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

# List of STM32 series
stm32_series = []

# Templating
templates_dir = script_path / "templates"
all_ll_h_file = "stm32yyxx_ll.h"
ll_h_file = "stm32yyxx_ll_ppp.h"
c_file = "stm32yyxx_zz_ppp.c"

# Create the jinja2 environment.
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
all_ll_header_file_template = j2_env.get_template(all_ll_h_file)
ll_h_file_template = j2_env.get_template(ll_h_file)
c_file_template = j2_env.get_template(c_file)
dsp_file_template = Template('#include "../Source/{{ dsp }}/{{ dsp }}.c"')

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
    global HALoutSrc_path
    global LLoutSrc_path
    global LLoutInc_path

    if arg_core is not None:
        core_path = Path(arg_core).resolve()
        CMSIS_path = core_path.parent / "ArduinoModule-CMSIS" / "CMSIS_5"

    if not core_path.is_dir():
        print("Could not find " + core_path)
        exit(1)

    SrcWrapper_path = core_path / "libraries" / "SrcWrapper"
    HALDrivers_path = core_path / "system" / "Drivers"
    CMSIS_Device_ST_path = core_path / "system" / "Drivers" / "CMSIS" / "Device" / "ST"
    CMSIS_DSP_lib_path = core_path / "libraries" / "CMSIS_DSP"
    CMSIS_DSP_outSrc_path = CMSIS_DSP_lib_path / "src"
    CMSIS_Startupfile = core_path / "cores" / "arduino" / "stm32" / "stm32_def_build.h"

    HALoutSrc_path = SrcWrapper_path / "src" / "HAL"
    LLoutSrc_path = SrcWrapper_path / "src" / "LL"
    LLoutInc_path = core_path / "cores" / "arduino" / "stm32" / "LL"

    if arg_cmsis is not None:
        CMSIS_path = Path(arg_cmsis).resolve()
    CMSIS_DSPSrc_path = CMSIS_path / "CMSIS" / "DSP" / "Source"


def printCMSISStartup(log):
    filelist = sorted(CMSIS_Device_ST_path.glob("**/startup_*.s"))
    if len(filelist):
        if log:
            print("Number of startup files: %i" % len(filelist))
        out_file = open(CMSIS_Startupfile, "w", newline="\n")
        # Header
        out_file.write(
            """#ifndef _STM32_DEF_BUILD_
#define _STM32_DEF_BUILD_

#if !defined(CMSIS_STARTUP_FILE) && !defined(CUSTOM_STARTUP_FILE)
"""
        )
        # File name
        fn = (filelist.pop(0)).name
        valueline = re.split("_|\\.", fn)
        upper = valueline[1].upper().replace("X", "x")
        out_file.write(
            """  #if defined({})
    #define CMSIS_STARTUP_FILE \"{}\"
""".format(
                upper, fn
            )
        )
        if len(filelist):
            for fp in filelist:
                # File name
                fn = fp.name
                valueline = re.split("_|\\.", fn)
                if "stm32mp15" in valueline[1] and not valueline[1].endswith("xx"):
                    valueline[1] += "xx"
                upper = valueline[1].upper().replace("X", "x")
                out_file.write(
                    """  #elif defined({})
    #define CMSIS_STARTUP_FILE \"{}\"
""".format(
                        upper, fn
                    )
                )
        # footer
        out_file.write(
            """  #else
    #error UNKNOWN CHIP
  #endif
#else
  #warning \"No CMSIS startup file defined, custom one should be used\"
#endif /* !CMSIS_STARTUP_FILE && !CUSTOM_STARTUP_FILE */
#endif /* _STM32_DEF_BUILD_ */
"""
        )
        out_file.close()
    else:
        if log:
            print("No startup files found!")


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
        src = HALDrivers_path / ("STM32" + serie + "xx_HAL_Driver") / "Src"
        inc = HALDrivers_path / ("STM32" + serie + "xx_HAL_Driver") / "Inc"

        if src.exists():
            if log:
                print("Generating for " + serie + "...")
            lower = serie.lower()

            # Search stm32yyxx_[hal|ll]*.c file
            filelist = src.glob("stm32" + lower + "xx_*.c")
            for fp in filelist:
                # File name
                fn = fp.name
                found = peripheral_c_regex.match(fn)
                if "_template" in fn:
                    continue
                peripheral = found.group(1) if found else "hal"
                if "_ll_" in fn:
                    if peripheral in ll_c_dict:
                        ll_c_dict[peripheral].append(lower)
                    else:
                        ll_c_dict[peripheral] = [lower]
                else:
                    if peripheral in hal_c_dict:
                        hal_c_dict[peripheral].append(lower)
                    else:
                        hal_c_dict[peripheral] = [lower]

            # Search stm32yyxx_ll_*.h file
            filelist = inc.glob("stm32" + lower + "xx_ll_*.h")
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
                    filepath = HALoutSrc_path / c_file.replace("zz", "hal").replace(
                        "_ppp", ""
                    )
                else:
                    filepath = HALoutSrc_path / c_file.replace("zz", "hal").replace(
                        "ppp", key
                    )
                out_file = open(filepath, "w", newline="\n")
                out_file.write(
                    c_file_template.render(periph=key, type="hal", serieslist=value)
                )
                out_file.close()
            # Generate stm32yyxx_ll_*.c file
            for key, value in ll_c_dict.items():
                filepath = LLoutSrc_path / c_file.replace("zz", "ll").replace(
                    "ppp", key
                )
                out_file = open(filepath, "w", newline="\n")
                out_file.write(
                    c_file_template.render(periph=key, type="ll", serieslist=value)
                )
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

    # CMSIS DSP C source file
    if not CMSIS_path.is_dir():
        print("Could not find {}").format(CMSIS_path)
        print("CMSIS DSP generation skipped.")
    else:
        # Delete all subfolders
        deleteFolder(CMSIS_DSP_outSrc_path / "*")
        dirlist = []
        for path_object in CMSIS_DSPSrc_path.glob("**/*"):
            if path_object.is_file():
                if path_object.name.endswith(".c"):
                    dirlist.append(path_object.parent.name)
        dirlist = sorted(set(dirlist))
        for dn in dirlist:
            fdn = CMSIS_DSP_outSrc_path / dn
            if not fdn.is_dir():
                createFolder(fdn)
                out_file = open(fdn / (dn + ".c"), "w", newline="\n")
                all_ll_file.write(dsp_file_template.render(dsp_path=dn))
                out_file.close()
    return 0


if __name__ == "__main__":
    # Parser
    wrapparser = argparse.ArgumentParser(
        description="Generate all wrappers files need by the STM32 core (HAL, LL, CMSIS, ...)"
    )
    wrapparser.add_argument(
        "-c",
        "--core",
        metavar="core_path",
        help="Root path of the STM32 core. Default: {}".format(core_path),
    )
    wrapparser.add_argument(
        "-s",
        "--cmsis",
        metavar="cmsis_path",
        help="Root path of the CMSIS. Default: {}".format(CMSIS_path),
    )

    wrapargs = wrapparser.parse_args()

    wrap(wrapargs.core, wrapargs.cmsis, True)
