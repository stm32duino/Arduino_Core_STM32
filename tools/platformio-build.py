# Copyright 2014-present PlatformIO <contact@platformio.org>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
Arduino

Arduino Wiring-based Framework allows writing cross-platform software to
control devices attached to a wide range of Arduino boards to create all
kinds of creative coding, interactive objects, spaces or physical experiences.

https://github.com/stm32duino/Arduino_Core_STM32
"""


from os.path import isfile, isdir, join

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
platform = env.PioPlatform()
board = env.BoardConfig()

FRAMEWORK_DIR = platform.get_package_dir("framework-arduinoststm32")
CMSIS_DIR = join(platform.get_package_dir("framework-arduinoststm32"), "CMSIS", "CMSIS")
assert isdir(FRAMEWORK_DIR)
assert isdir(CMSIS_DIR)


mcu = env.BoardConfig().get("build.mcu", "")
board_name = env.subst("$BOARD")
mcu_type = mcu[:-2]
variant = board.get("build.variant")
series = mcu_type[:7].upper() + "xx"
variants_dir = (
    join("$PROJECT_DIR", board.get("build.variants_dir"))
    if board.get("build.variants_dir", "")
    else join(FRAMEWORK_DIR, "variants")
)
variant_dir = join(variants_dir, variant)
upload_protocol = env.subst("$UPLOAD_PROTOCOL")


def process_standard_library_configuration(cpp_defines):
    if "PIO_FRAMEWORK_ARDUINO_STANDARD_LIB" in cpp_defines:
        env["LINKFLAGS"].remove("--specs=nano.specs")
    if "PIO_FRAMEWORK_ARDUINO_NANOLIB_FLOAT_PRINTF" in cpp_defines:
        env.Append(LINKFLAGS=["-u_printf_float"])
    if "PIO_FRAMEWORK_ARDUINO_NANOLIB_FLOAT_SCANF" in cpp_defines:
        env.Append(LINKFLAGS=["-u_scanf_float"])


def process_usart_configuration(cpp_defines):
    if "PIO_FRAMEWORK_ARDUINO_SERIAL_DISABLED" in cpp_defines:
        env["CPPDEFINES"].remove("HAL_UART_MODULE_ENABLED")

    elif "PIO_FRAMEWORK_ARDUINO_SERIAL_WITHOUT_GENERIC" in cpp_defines:
        env.Append(CPPDEFINES=["HWSERIAL_NONE"])


def process_usb_speed_configuration(cpp_defines):
    if "PIO_FRAMEWORK_ARDUINO_USB_HIGHSPEED" in cpp_defines:
        env.Append(CPPDEFINES=["USE_USB_HS"])

    elif "PIO_FRAMEWORK_ARDUINO_USB_HIGHSPEED_FULLMODE" in cpp_defines:
        env.Append(CPPDEFINES=["USE_USB_HS", "USE_USB_HS_IN_FS"])


def process_usb_configuration(cpp_defines):
    if "PIO_FRAMEWORK_ARDUINO_ENABLE_CDC" in cpp_defines:
        env.Append(CPPDEFINES=["USBD_USE_CDC"])

    elif "PIO_FRAMEWORK_ARDUINO_ENABLE_CDC_WITHOUT_SERIAL" in cpp_defines:
        env.Append(CPPDEFINES=["USBD_USE_CDC", "DISABLE_GENERIC_SERIALUSB"])

    elif "PIO_FRAMEWORK_ARDUINO_ENABLE_HID" in cpp_defines:
        env.Append(CPPDEFINES=["USBD_USE_HID_COMPOSITE"])

    if any(f in env["CPPDEFINES"] for f in ("USBD_USE_CDC", "USBD_USE_HID_COMPOSITE")):
        env.Append(CPPDEFINES=["HAL_PCD_MODULE_ENABLED"])


def get_arm_math_lib(cpu):
    core = board.get("build.cpu")[7:9]
    if core == "m4":
        return "arm_cortexM4lf_math"
    elif core == "m7":
        return "arm_cortexM7lfsp_math"

    return "arm_cortex%sl_math" % core.upper()


def configure_application_offset(mcu, upload_protocol):
    offset = 0

    if upload_protocol == "hid":
        if mcu.startswith("stm32f1"):
            offset = 0x800
        elif mcu.startswith("stm32f4"):
            offset = 0x4000

        env.Append(CPPDEFINES=["BL_HID"])

    elif upload_protocol == "dfu":
        # STM32F103 series doesn't have embedded DFU over USB
        # stm32duino bootloader (v1, v2) is used instead
        if mcu.startswith("stm32f103"):
            if board.get("upload.boot_version", 2) == 1:
                offset = 0x5000
            else:
                offset = 0x2000
            env.Append(CPPDEFINES=["BL_LEGACY_LEAF"])

    if offset != 0:
        env.Append(CPPDEFINES=[("VECT_TAB_OFFSET", "%s" % hex(offset))],)

    # LD_FLASH_OFFSET is mandatory even if there is no offset
    env.Append(LINKFLAGS=["-Wl,--defsym=LD_FLASH_OFFSET=%s" % hex(offset)])


if any(mcu in board.get("build.cpu") for mcu in ("cortex-m4", "cortex-m7")):
    env.Append(
        CCFLAGS=["-mfpu=fpv4-sp-d16", "-mfloat-abi=hard"],
        LINKFLAGS=["-mfpu=fpv4-sp-d16", "-mfloat-abi=hard"],
    )

env.Append(
    ASFLAGS=["-x", "assembler-with-cpp"],
    CFLAGS=["-std=gnu11"],
    CXXFLAGS=[
        "-std=gnu++14",
        "-fno-threadsafe-statics",
        "-fno-rtti",
        "-fno-exceptions",
        "-fno-use-cxa-atexit",
    ],
    CCFLAGS=[
        "-Os",  # optimize for size
        "-mcpu=%s" % env.BoardConfig().get("build.cpu"),
        "-mthumb",
        "-ffunction-sections",  # place each function in its own section
        "-fdata-sections",
        "-Wall",
        "-nostdlib",
        "--param",
        "max-inline-insns-single=500",
    ],
    CPPDEFINES=[
        series,
        ("ARDUINO", 10808),
        "ARDUINO_ARCH_STM32",
        "ARDUINO_%s" % board_name.upper(),
        ("BOARD_NAME", '\\"%s\\"' % board_name.upper()),
        "HAL_UART_MODULE_ENABLED",
    ],
    CPPPATH=[
        join(FRAMEWORK_DIR, "cores", "arduino", "avr"),
        join(FRAMEWORK_DIR, "cores", "arduino", "stm32"),
        join(FRAMEWORK_DIR, "cores", "arduino", "stm32", "LL"),
        join(FRAMEWORK_DIR, "cores", "arduino", "stm32", "usb"),
        join(FRAMEWORK_DIR, "cores", "arduino", "stm32", "usb", "hid"),
        join(FRAMEWORK_DIR, "cores", "arduino", "stm32", "usb", "cdc"),
        join(FRAMEWORK_DIR, "system", "Drivers", series + "_HAL_Driver", "Inc"),
        join(FRAMEWORK_DIR, "system", "Drivers", series + "_HAL_Driver", "Src"),
        join(FRAMEWORK_DIR, "system", series),
        join(
            FRAMEWORK_DIR,
            "system",
            "Middlewares",
            "ST",
            "STM32_USB_Device_Library",
            "Core",
            "Inc",
        ),
        join(
            FRAMEWORK_DIR,
            "system",
            "Middlewares",
            "ST",
            "STM32_USB_Device_Library",
            "Core",
            "Src",
        ),
        join(CMSIS_DIR, "Core", "Include"),
        join(
            FRAMEWORK_DIR,
            "system",
            "Drivers",
            "CMSIS",
            "Device",
            "ST",
            series,
            "Include",
        ),
        join(CMSIS_DIR, "DSP", "Include"),
        join(
            FRAMEWORK_DIR,
            "system",
            "Drivers",
            "CMSIS",
            "Device",
            "ST",
            series,
            "Source",
            "Templates",
            "gcc",
        ),
        join(FRAMEWORK_DIR, "cores", "arduino"),
        variant_dir,
    ],
    LINKFLAGS=[
        "-Os",
        "-mthumb",
        "-mcpu=%s" % env.BoardConfig().get("build.cpu"),
        "--specs=nano.specs",
        "-Wl,--gc-sections,--relax",
        "-Wl,--check-sections",
        "-Wl,--entry=Reset_Handler",
        "-Wl,--unresolved-symbols=report-all",
        "-Wl,--warn-common",
        "-Wl,--defsym=LD_MAX_SIZE=%d" % board.get("upload.maximum_size"),
        "-Wl,--defsym=LD_MAX_DATA_SIZE=%d" % board.get("upload.maximum_ram_size"),
    ],
    LIBS=[
        get_arm_math_lib(env.BoardConfig().get("build.cpu")),
        "c",
        "m",
        "gcc",
        "stdc++",
    ],
    LIBPATH=[variant_dir, join(CMSIS_DIR, "DSP", "Lib", "GCC")],
)

env.ProcessFlags(board.get("build.framework_extra_flags.arduino", ""))

configure_application_offset(mcu, upload_protocol)

#
# Linker requires preprocessing with correct RAM|ROM sizes
#

if not board.get("build.ldscript", ""):
    if not isfile(join(env.subst(variant_dir), "ldscript.ld")):
        print("Warning! Cannot find linker script for the current target!\n")
    env.Replace(LDSCRIPT_PATH=join(variant_dir, "ldscript.ld"))

#
# Process configuration flags
#

cpp_defines = env.Flatten(env.get("CPPDEFINES", []))

process_standard_library_configuration(cpp_defines)
process_usb_configuration(cpp_defines)
process_usb_speed_configuration(cpp_defines)
process_usart_configuration(cpp_defines)

# copy CCFLAGS to ASFLAGS (-x assembler-with-cpp mode)
env.Append(ASFLAGS=env.get("CCFLAGS", [])[:])

env.Append(
    LIBSOURCE_DIRS=[
        join(FRAMEWORK_DIR, "libraries", "__cores__", "arduino"),
        join(FRAMEWORK_DIR, "libraries"),
    ]
)

#
# Target: Build Core Library
#

libs = []

if "build.variant" in env.BoardConfig():
    env.Append(CPPPATH=[variant_dir])
    env.BuildSources(join("$BUILD_DIR", "FrameworkArduinoVariant"), variant_dir)

env.BuildSources(
    join("$BUILD_DIR", "FrameworkArduino"), join(FRAMEWORK_DIR, "cores", "arduino")
)

env.BuildSources(
    join("$BUILD_DIR", "SrcWrapper"), join(FRAMEWORK_DIR, "libraries", "SrcWrapper")
)

env.Prepend(LIBS=libs)
