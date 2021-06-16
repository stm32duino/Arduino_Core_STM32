import argparse
import re
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

all_LL_file = "stm32yyxx_ll.h"

stm32_series = []


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


# Add some pragma to ll header files to avoid several warnings
# which will be corrected along Cube update
def print_LL_header(open_file, name):
    upper = name.upper().replace(".", "_")
    open_file.write(
        """#ifndef _{0}_
#define _{0}_
/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored \"-Wunused-parameter\"
#pragma GCC diagnostic ignored \"-Wstrict-aliasing\"

""".format(
            upper
        )
    )


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
    full_ll_list = []
    # Search all files for each series
    for serie in stm32_series:
        src = HALDrivers_path / ("STM32" + serie + "xx_HAL_Driver") / "Src"
        inc = HALDrivers_path / ("STM32" + serie + "xx_HAL_Driver") / "Inc"

        if src.exists():
            if log:
                print("Generating for " + serie + "...")
            lower = serie.lower()
            # Generate stm32yyxx_[hal|ll]*.c file
            filelist = src.glob("stm32" + lower + "xx_*.c")
            for fp in filelist:
                # File name
                fn = fp.name
                if "_template" in fn:
                    continue
                outp = HALoutSrc_path
                if "_ll_" in fn:
                    outp = LLoutSrc_path
                # Compute generic file name with path
                gp = outp / fn.replace(lower, "yy")
                out_file = open(gp, "a", newline="\n")
                # Amend file name under serie switch
                out_file.write("#ifdef STM32" + serie + "xx\n")
                out_file.write('  #include "' + fn + '"\n')
                out_file.write("#endif\n")
                out_file.close()
            # Generate stm32yyxx_ll_*.h file
            filelist = inc.glob("stm32" + lower + "xx_ll_*.h")
            for fp in filelist:
                outp = LLoutInc_path
                # File name
                fn = fp.name
                # Compute generic file name
                gn = fn.replace(lower, "yy")
                # with path
                gp = outp / gn
                out_file = open(gp, "a", newline="\n")
                if gp.stat().st_size == 0:
                    print_LL_header(out_file, gn)
                # Amend full LL header file
                full_ll_list.append(gn)
                # Amend file name under serie switch
                out_file.write("#ifdef STM32" + serie + "xx\n")
                out_file.write('  #include "' + fn + '"\n')
                out_file.write("#endif\n")
                out_file.close()
            if log:
                print("done")

    # Filter full LL header file
    full_ll_file = open(LLoutInc_path / all_LL_file, "w", newline="\n")
    print_LL_header(full_ll_file, all_LL_file)
    full_ll_file.write("/* Include Low Layers drivers */\n")
    full_ll_list = sorted(set(full_ll_list))
    for hn in full_ll_list:
        full_ll_file.write('#include "' + hn + '"\n')
    full_ll_file.close()

    # Search all LL header files to end guard
    filelist = LLoutInc_path.glob("stm32yyxx_ll*.h")
    for fp in filelist:
        out_file = open(fp, "a", newline="\n")
        upper = fp.name.upper().replace(".", "_")
        out_file.write("#pragma GCC diagnostic pop\n")
        out_file.write("#endif /* _" + upper + "_ */\n")
        out_file.close()

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
                out_file.write('#include "../Source/{0}/{0}.c"\n'.format(dn))
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
