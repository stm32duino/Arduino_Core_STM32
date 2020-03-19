import argparse
import glob
import re
import os
from stm32common import createFolder, deleteFolder, genSTM32List

script_path = os.path.dirname(os.path.abspath(__file__))
home = os.path.expanduser("~")
# Base path
core_path = os.path.abspath(os.path.join(script_path, "..", ".."))
SrcWrapper_path = ""
HALDrivers_path = ""
CMSIS_Device_ST_path = ""
CMSIS_DSP_lib_path = ""

# CMSIS outside of the core. Can be updated by arg
CMSIS_path = os.path.abspath(
    os.path.join(core_path, "..", "ArduinoModule-CMSIS", "CMSIS_5")
)
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
        core_path = arg_core
        CMSIS_path = os.path.abspath(
            os.path.join(core_path, "..", "ArduinoModule-CMSIS", "CMSIS_5")
        )

    if not os.path.isdir(core_path):
        print("Could not find " + core_path)
        exit(1)

    SrcWrapper_path = os.path.join(core_path, "libraries", "SrcWrapper")
    HALDrivers_path = os.path.join(core_path, "system", "Drivers")
    CMSIS_Device_ST_path = os.path.join(
        core_path, "system", "Drivers", "CMSIS", "Device", "ST"
    )
    CMSIS_DSP_lib_path = os.path.join(core_path, "libraries", "CMSIS_DSP")
    CMSIS_DSP_outSrc_path = os.path.join(CMSIS_DSP_lib_path, "src")
    CMSIS_Startupfile = os.path.join(
        core_path, "cores", "arduino", "stm32", "stm32_def_build.h"
    )

    HALoutSrc_path = os.path.join(SrcWrapper_path, "src", "HAL")
    LLoutSrc_path = os.path.join(SrcWrapper_path, "src", "LL")
    LLoutInc_path = os.path.join(core_path, "cores", "arduino", "stm32", "LL")

    if arg_cmsis is not None:
        CMSIS_path = arg_cmsis
    CMSIS_DSPSrc_path = os.path.join(CMSIS_path, "CMSIS", "DSP", "Source")


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
    filelist = glob.glob(
        os.path.join(
            CMSIS_Device_ST_path, "STM32*", "Source", "Templates", "gcc", "startup_*.s",
        )
    )
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
        fn = os.path.basename(filelist.pop(0))
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
                fn = os.path.basename(fp)
                valueline = re.split("_|\\.", fn)
                upper = (
                    valueline[1].upper().replace("X", "x").replace("MP15xx", "MP1xx")
                )
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
    if os.path.isfile(CMSIS_Startupfile):
        os.remove(CMSIS_Startupfile)
    full_ll_list = []
    # Search all files for each series
    for serie in stm32_series:
        src = os.path.join(HALDrivers_path, "STM32" + serie + "xx_HAL_Driver", "Src")
        inc = os.path.join(HALDrivers_path, "STM32" + serie + "xx_HAL_Driver", "Inc")

        if os.path.exists(src):
            if log:
                print("Generating for " + serie + "...")
            lower = serie.lower()
            # Generate stm32yyxx_[hal|ll]*.c file
            filelist = glob.glob(os.path.join(src, "stm32" + lower + "xx_*.c"))
            for fp in filelist:
                if "_template" in fp:
                    continue
                outp = HALoutSrc_path
                # File name
                fn = os.path.basename(fp)
                if "_ll_" in fn:
                    outp = LLoutSrc_path
                # Compute generic file name with path
                gp = os.path.join(outp, fn.replace(lower, "yy"))
                out_file = open(gp, "a", newline="\n")
                # Amend file name under serie switch
                out_file.write("#ifdef STM32" + serie + "xx\n")
                out_file.write('  #include "' + fn + '"\n')
                out_file.write("#endif\n")
                out_file.close()
            # Generate stm32yyxx_ll_*.h file
            filelist = glob.glob(os.path.join(inc, "stm32" + lower + "xx_ll_*.h"))
            for fp in filelist:
                outp = LLoutInc_path
                # File name
                fn = os.path.basename(fp)
                # Compute generic file name
                gn = fn.replace(lower, "yy")
                # with path
                gp = os.path.join(outp, gn)
                out_file = open(gp, "a", newline="\n")
                if os.path.getsize(gp) == 0:
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
    full_ll_file = open(os.path.join(LLoutInc_path, all_LL_file), "w", newline="\n")
    print_LL_header(full_ll_file, all_LL_file)
    full_ll_file.write("/* Include Low Layers drivers */\n")
    full_ll_list = sorted(set(full_ll_list))
    for hn in full_ll_list:
        full_ll_file.write('#include "' + hn + '"\n')
    full_ll_file.close()

    # Search all LL header files to end guard
    filelist = glob.glob(os.path.join(LLoutInc_path, "stm32yyxx_ll*.h"))
    for fp in filelist:
        out_file = open(fp, "a", newline="\n")
        upper = os.path.basename(fp).upper().replace(".", "_")
        out_file.write("#pragma GCC diagnostic pop\n")
        out_file.write("#endif /* _" + upper + "_ */\n")
        out_file.close()

    # CMSIS startup files
    printCMSISStartup(log)

    # CMSIS DSP C source file
    if not os.path.isdir(CMSIS_path):
        print("Could not find " + CMSIS_path)
        print("CMSIS DSP generation skipped.")
    else:
        # Delete all subfolders
        deleteFolder(os.path.join(CMSIS_DSP_outSrc_path, "*"))
        dirlist = []
        for root, dirs, files in os.walk(CMSIS_DSPSrc_path):
            for file in files:
                if file.endswith(".c"):
                    dirlist.append(root.replace(CMSIS_DSPSrc_path, "")[1:])
        dirlist = sorted(set(dirlist))
        for dn in dirlist:
            fdn = os.path.join(CMSIS_DSP_outSrc_path, dn)
            if not os.path.isdir(fdn):
                createFolder(fdn)
                out_file = open(os.path.join(fdn, dn + ".c"), "w", newline="\n")
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
        help="Root path of the STM32 core. Default: " + core_path,
    )
    wrapparser.add_argument(
        "-s",
        "--cmsis",
        metavar="cmsis_path",
        help="Root path of the CMSIS. Default: " + CMSIS_path,
    )

    wrapargs = wrapparser.parse_args()

    wrap(wrapargs.core, wrapargs.cmsis, True)
