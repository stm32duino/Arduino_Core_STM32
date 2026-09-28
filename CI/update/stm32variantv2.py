import argparse
import datetime
import json
import re
import sys
import textwrap
from argparse import RawTextHelpFormatter
from collections import Counter
from collections import OrderedDict
from itertools import groupby
from jinja2 import Environment, FileSystemLoader
from pathlib import Path
from xml.dom.minidom import parse

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils import (
    defaultConfig,
    deleteFolder,
    loadSTM32Series,
)

stm32_list = []  # series
stm32_dict = OrderedDict()  # key: series, value: nx
pinout_dict = OrderedDict()  # key: series, value: 'list of files'
aggregate_series_list = []  # series
io_list = []  # ['PIN','name']
alt_list = []  # ['PIN','name']
dualpad_list = []  # ['PIN','name']
remap_list = []  # ['PIN','name']
adclist = []  # ['PIN','instance','ADCSignal']
daclist = []  # ['PIN','instance','DACSignal']
i2cscl_list = []  # ['PIN','instance','I2CSCLSignal', 'af']
i2csda_list = []  # ['PIN','instance','I2CSDASignal', 'af']
i3cscl_list = []  # ['PIN','instance','I3CSCLSignal', 'af']
i3csda_list = []  # ['PIN','instance','I3CSDASignal', 'af']
tim_list = []  # ['PIN','instance','TIMSignal', 'af']
uarttx_list = []  # ['PIN','instance','UARTtx', 'af']
uartrx_list = []  # ['PIN','instance','UARTrx', 'af']
uartcts_list = []  # ['PIN','instance','UARTcts', 'af']
uartrts_list = []  # ['PIN','instance','UARTrts', 'af']
spimosi_list = []  # ['PIN','instance','SPIMOSI', 'sort name', 'af']
spimiso_list = []  # ['PIN','instance','SPIMISO', 'sort name', 'af']
spissel_list = []  # ['PIN','instance','SPISSEL', 'sort name', 'af']
spisclk_list = []  # ['PIN','instance','SPISCLK', 'sort name', 'af']
cantd_list = []  # ['PIN','instance','CANTD', 'af']
canrd_list = []  # ['PIN','instance','CANRD', 'af']
eth_list = []  # ['PIN','instance','ETH', 'af']
xspidata0_list = []  # ['PIN','instance','XSPIDATA0', 'af']
xspidata1_list = []  # ['PIN','instance','XSPIDATA1', 'af']
xspidata2_list = []  # ['PIN','instance','XSPIDATA2', 'af']
xspidata3_list = []  # ['PIN','instance','XSPIDATA3', 'af']
ospidata4_list = []  # ['PIN','instance','OSPIDATA4', 'af']
ospidata5_list = []  # ['PIN','instance','OSPIDATA5', 'af']
ospidata6_list = []  # ['PIN','instance','OSPIDATA6', 'af']
ospidata7_list = []  # ['PIN','instance','OSPIDATA7', 'af']
xspisclk_list = []  # ['PIN','instance','XSPISCLK', 'af']
xspissel_list = []  # ['PIN','instance','XSPISSEL', 'af']
syswkup_list = []  # ['PIN', 'signal']
usb_list = []  # ['PIN','instance','USB', 'af']
usb_otgfs_list = []  # ['PIN','instance','USB', 'af']
usb_otghs_list = []  # ['PIN','instance','USB', 'af']
sdxcmd_list = []  # ['PIN','instance','SDX_CMD', 'af']
sdxck_list = []  # ['PIN','instance','SDX_CK', 'af']
sdxd0_list = []  # ['PIN','instance','SDX_D0', 'af']
sdxd1_list = []  # ['PIN','instance','SDX_D1', 'af']
sdxd2_list = []  # ['PIN','instance','SDX_D2', 'af']
sdxd3_list = []  # ['PIN','instance','SDX_D3', 'af']
sdxd4_list = []  # ['PIN','instance','SDX_D4', 'af']
sdxd5_list = []  # ['PIN','instance','SDX_D5', 'af']
sdxd6_list = []  # ['PIN','instance','SDX_D6', 'af']
sdxd7_list = []  # ['PIN','instance','SDX_D7', 'af']
sdmmcckin_list = []  # ['PIN','instance','SDMMC_CKIN', 'af']
sdmmccdir_list = []  # ['PIN','instance','SDMMC_CDIR', 'af']
sdmmcd0dir_list = []  # ['PIN','instance','SDMMC_D0DIR', 'af']
sdmmcd123dir_list = []  # ['PIN','instance','SDMMC_D123DIR', 'af']

# IP information
gpiofile = ""
tim_inst_list = []  # TIMx instance
usb_inst = {"usb": "", "otg_fs": "", "otg_hs": ""}
mcu_family = ""
mcu_refnames = (
    []
)  # list of mcu_refname corresponding to the pinout file (after expansion if needed)
# Ignored mcu_refnames are those which are not present in the CMSIS device header files,
# and thus cannot be parsed to extract flash and ram information.
# key: series, value: list of mcu_refnames ignored for this series
ignored_mcu_refnames = {}
mcu_info = {}  # dict with key as mcu_refname and value as dict with keys 'flash', 'ram'
# Cube information
product_line_dict = {}
svd_dict = {}  # 'name':'svd file'

# format
# Peripheral
start_elem_fmt = "  {{{:{width}}"
end_array_fmt = """  {{NC,{0:{w1}}NP,{0:{w2}}0}}
}};
#endif
"""

year = datetime.datetime.now().year

# Choice is based on the fact Tone and Servo do not need output nor compare
# capabilities, and thus select timer instance which have the less outputs/compare
# capabilities:
# - TIM6/TIM7/TIM18 because they have no output and no compare capabilities
# - TIM10/TIM11/TIM13/TIM14 only 1 compare channel no complementary
# - TIM16/TIM17 generally only 1 compare channel (with complementary)
# - TIM9/TIM12/TIM21/TIM22 2 compare channels (no complementary)
# - TIM15  generally 2 compare channel (with potentially complementary)
# - TIM3/TIM4/TIM19 up to 4 channels
# - TIM2/TIM5 (most of the time) the only 32bit timer. Could be reserved
# for further 32bit support
# - TIM1/TIM8/TIM20 they are the most advanced/complete timers

tim_inst_order = [
    "TIM6",
    "TIM7",
    "TIM18",
    "TIM10",
    "TIM11",
    "TIM13",
    "TIM14",
    "TIM16",
    "TIM17",
    "TIM9",
    "TIM12",
    "TIM21",
    "TIM22",
    "TIM15",
    "TIM3",
    "TIM4",
    "TIM19",
    "TIM2",
    "TIM5",
    "TIM1",
    "TIM8",
    "TIM20",
]


def update_file(filePath, compile_pattern, subs):
    with open(filePath, "r+", newline="\n") as file:
        fileContents = file.read()
        fileContents = compile_pattern.sub(subs, fileContents)
        file.seek(0)
        file.truncate()
        file.write(fileContents)


def expand_mcu_refname(mcu_filename: str):
    global mcu_refnames
    del mcu_refnames[:]

    # Expand mcu_refnames from the mcu filename using the pinout_name_regex
    ref = pinout_name_regex.search(mcu_filename)
    if ref:
        if ref.group(1).startswith("("):
            first_refs = ref.group(1).removeprefix("(").removesuffix(")").split("-")
        else:
            first_refs = [ref.group(1)]
        if ref.group(2).startswith("("):
            second_refs = ref.group(2).removeprefix("(").removesuffix(")").split("-")
        else:
            second_refs = [ref.group(2)]
        third_ref = ref.group(3)

        if ref.group(4).startswith("("):
            flash_refs = ref.group(4).removeprefix("(").removesuffix(")").split("-")
        else:
            flash_refs = [ref.group(4)]
        package_ref = ref.group(5)
        if ref.group(6) and ref.group(6).startswith("("):
            suffix_refs = (
                ref.group(6)
                .removeprefix("(")
                .removesuffix(")")
                .removesuffix("_")
                .split("-")
            )
        else:
            suffix_refs = [ref.group(6)] if ref.group(6) else [""]
        # Combine the refs to generate the mcu_refnames
        mcu_refnames = [
            f"{mcu_family}{first_ref}{second_ref}{third_ref}{flash_ref}{package_ref}{suffix_ref}"
            for first_ref in first_refs
            for second_ref in second_refs
            for flash_ref in flash_refs
            for suffix_ref in suffix_refs
        ]
    else:
        print(
            f"Error parsing mcu filename {mcu_filename} with regex {pinout_name_regex.pattern}"
        )
        sys.exit(1)


def get_mcu_info():
    series_len = len(mcu_family) + 4
    # Open the pdsc file corresponding to the series
    pdsc_filename = f"STMicroelectronics.stm32{series.lower()}{nx}_dfp.pdsc"
    pdsc_filepath = (
        repo_local_path
        / f"STM32Cube{series}"
        / f"stm32{series.lower()}{nx}_dfp"
        / pdsc_filename
    )
    if not pdsc_filepath.exists():
        print(f"Error: pdsc file {pdsc_filepath} not found.")
        sys.exit(1)
    xml_pdsc = parse(str(pdsc_filepath))

    # Extract the flash, ram and svd information for each mcu_refname
    for mcu_refname in mcu_refnames:
        dname = mcu_refname[:series_len].upper()
        devices = xml_pdsc.getElementsByTagName("device")
        device = next((d for d in devices if d.getAttribute("Dname") == dname), None)
        if device is None:
            if series not in ignored_mcu_refnames:
                ignored_mcu_refnames[series] = []
            ignored_mcu_refnames[series].append(mcu_refname)
            continue
        # extract from:
        # <algorithm name="Flash/STM32C5[34]x.xldr" start="0x08000000" size="0x20000" RAMstart="0x20000000" RAMsize="0x10000" default="1"/>
        # Check if algorithm element exists
        algorithm_elements = device.getElementsByTagName("algorithm")
        if not algorithm_elements:
            if series not in ignored_mcu_refnames:
                ignored_mcu_refnames[series] = []
            ignored_mcu_refnames[series].append(mcu_refname)
            continue
        algorithm = algorithm_elements[0]
        flash_size = int(algorithm.getAttribute("size"), 16)
        ram_size = int(algorithm.getAttribute("RAMsize"), 16)
        mcu_info[mcu_refname] = {
            "flash": flash_size,
            "ram": ram_size,
        }
        # Get svd from:
        # <debug svd="SVD/STM32C531.svd" __ap="1"/>
        # Check if debug element exists
        debug_elements = device.getElementsByTagName("debug")
        if debug_elements:
            debug = device.getElementsByTagName("debug")[0]
            svd = debug.getAttribute("svd")
        else:
            svd = ""
        svd_dict[mcu_refname] = svd.removeprefix("SVD/")
    xml_pdsc.unlink()


# mcu file parsing
def parse_mcu_pinout():
    # Get all pins
    del tim_inst_list[:]
    usb_inst["usb"] = ""
    usb_inst["otg_fs"] = ""
    usb_inst["otg_hs"] = ""
    die_pads = mcu_pinout["die_pads"]
    for key, value in die_pads.items():
        if "port" and "index" in value:
            store_pin(f"P{value['port']}_{value['index']}", key, io_list)
    # print(f"Total number of pins: {len(io_list)}")
    # print(io_list)
    # Manage signal names and store them in the right list
    signals = mcu_pinout["signals"]
    # Search for each signal:
    # ADC, DAC, I2C, I3C, TIM, U(S)ART, LPUART, SPI, QUADSPI, OCTOSPI,
    # CAN, ETH, SDIO, SDMMC, PWR_WKUP and USB signals
    for value in signals:
        signal_name = value["name"]
        instance = value["instance"]
        # Format pin from PYn to PY_n
        # Extract the pin name from the die_pad using the pinregex
        pin_match = re.match(pinregex, value["die_pad"])
        if pin_match:
            pin = pin_match.group(0)
        else:
            pin = value["die_pad"]
        pin = re.sub(r"(\w)(\d+)", r"\1_\2", pin)
        if instance.startswith("ADC"):
            store_adc(pin, instance, signal_name)
        elif instance.startswith("DAC"):
            store_dac(pin, instance, signal_name)
        else:
            # Manage instance
            if (
                "function" in value
                and "type" in value["function"]
                and value["function"]["type"] == "alternate"
            ):
                # Extract the AF number from the function id using the afnum_regex
                af_match = afnum_regex.search(value["function"]["id"])
                if af_match:
                    af = f"HAL_GPIO_AF_{af_match.group(1)}"
                else:
                    af = ""
            if instance.startswith("I2C"):
                store_i2c(pin, instance, signal_name, af)
            elif instance.startswith("I3C"):
                store_i3c(pin, instance, signal_name, af)
            elif instance.startswith("TIM"):
                tim_inst_list.append(instance)
                store_tim(pin, instance, signal_name, af)
            elif re.match("^(LPU|US|U)ART", instance) is not None:
                store_uart(pin, instance, signal_name, af)
            elif "SPI" in instance:
                if "QUADSPI" in instance or "OCTOSPI" in instance:
                    store_xspi(pin, instance, signal_name, af)
                else:
                    store_spi(pin, instance, signal_name, af)
            elif "CAN" in instance:
                store_can(pin, instance, signal_name, af)
            elif "ETH" in instance:
                store_eth(pin, instance, signal_name, af)
            elif "SDMMC" in instance or "SDIO" in instance:
                store_sdx(pin, instance, signal_name, af)
            elif "WKUP" in signal_name or "PWR" in signal_name:
                store_sys(pin, signal_name)
            elif "USB" in signal_name:
                if "OTG" in instance:
                    if "FS" in instance:
                        usb_inst["otg_fs"] = instance
                    elif "HS" in instance:
                        usb_inst["otg_hs"] = instance
                else:
                    usb_inst["usb"] = instance
                store_usb(pin, instance, signal_name, af)
    return True


# Storage
# Store pin I/O
def store_pin(pin, name, dest_list):
    if pin in [p[0] for p in dest_list]:
        return
    p = [pin, name]
    if p not in dest_list:
        dest_list.append(p)


# Store ADC list
def store_adc(pin, instance, signal):
    adclist.append([pin, instance, signal])


# Store DAC list
def store_dac(pin, instance, signal):
    daclist.append([pin, instance, signal])


# Store I2C list
def store_i2c(pin, instance, signal, af):
    # is it SDA or SCL ?
    if "_SCL" in signal:
        i2cscl_list.append([pin, instance, signal, af])
    if "_SDA" in signal:
        i2csda_list.append([pin, instance, signal, af])


# Store I3C list
def store_i3c(pin, instance, signal, af):
    # is it SDA or SCL ?
    if "_SCL" in signal:
        i3cscl_list.append([pin, instance, signal, af])
    if "_SDA" in signal:
        i3csda_list.append([pin, instance, signal, af])


# Store timers
def store_tim(pin, instance, signal, af):
    if "_CH" in signal:
        tim_list.append([pin, instance, signal, af])


# Store Uart pins
def store_uart(pin, instance, signal, af):
    if "_TX" in signal:
        uarttx_list.append([pin, instance, signal, af])
    if "_RX" in signal:
        uartrx_list.append([pin, instance, signal, af])
    if "_CTS" in signal:
        uartcts_list.append([pin, instance, signal, af])
    if "_RTS" in signal:
        uartrts_list.append([pin, instance, signal, af])


# Store SPI pins
def store_spi(pin, instance, signal, af):
    if re.search("[-_]MISO", signal):
        spimiso_list.append([pin, instance, signal, signal.removeprefix("DEBUG_"), af])
    if re.search("[-_]MOSI", signal):
        spimosi_list.append([pin, instance, signal, signal.removeprefix("DEBUG_"), af])
    if re.search("[-_]SCK", signal):
        spisclk_list.append([pin, instance, signal, signal.removeprefix("DEBUG_"), af])
    if re.search("[-_]NSS", signal):
        spissel_list.append([pin, instance, signal, signal.removeprefix("DEBUG_"), af])


# Store CAN pins
def store_can(pin, instance, signal, af):
    if "_RX" in signal:
        canrd_list.append([pin, instance, signal, af])
    if "_TX" in signal:
        cantd_list.append([pin, instance, signal, af])


# Store ETH list
def store_eth(pin, name, signal, af):
    eth_list.append([pin, name, signal, af])


# Store O/QSPI pins
def store_xspi(pin, name, signal, af):
    if "_IO0" in signal:
        xspidata0_list.append([pin, name, signal, af])
    elif "_IO1" in signal:
        xspidata1_list.append([pin, name, signal, af])
    elif "_IO2" in signal:
        xspidata2_list.append([pin, name, signal, af])
    elif "_IO3" in signal:
        xspidata3_list.append([pin, name, signal, af])
    elif "_IO4" in signal:
        ospidata4_list.append([pin, name, signal, af])
    elif "_IO5" in signal:
        ospidata5_list.append([pin, name, signal, af])
    elif "_IO6" in signal:
        ospidata6_list.append([pin, name, signal, af])
    elif "_IO7" in signal:
        ospidata7_list.append([pin, name, signal, af])
    elif "_CLK" in signal:
        xspisclk_list.append([pin, name, signal, af])
    elif "_NCS" in signal:
        xspissel_list.append([pin, name, signal, af])


# Store SYS pins
def store_sys(pin, signal):
    if "_WKUP" in signal and not any(pin.replace("_C", "") in i for i in syswkup_list):
        signal = signal.replace("PWR", "SYS")
        syswkup_list.append([pin, signal])


# Store USB pins
def store_usb(pin, instance, signal, af):
    if "OTG" not in signal:
        usb_list.append([pin, instance, signal, af])
    if signal.startswith("USB_OTG_FS"):
        usb_otgfs_list.append([pin, instance, signal, af])
    if signal.startswith("USB_OTG_HS"):
        usb_otghs_list.append([pin, instance, signal, af])


# Store SD(IO/MMC) pins
def store_sdx(pin, instance, signal, af):
    if signal.endswith("_D0"):
        sdxd0_list.append([pin, instance, signal, af])
    elif signal.endswith("_D1"):
        sdxd1_list.append([pin, instance, signal, af])
    elif signal.endswith("_D2"):
        sdxd2_list.append([pin, instance, signal, af])
    elif signal.endswith("_D3"):
        sdxd3_list.append([pin, instance, signal, af])
    elif signal.endswith("_D4"):
        sdxd4_list.append([pin, instance, signal, af])
    elif signal.endswith("_D5"):
        sdxd5_list.append([pin, instance, signal, af])
    elif signal.endswith("_D6"):
        sdxd6_list.append([pin, instance, signal, af])
    elif signal.endswith("_D7"):
        sdxd7_list.append([pin, instance, signal, af])
    elif signal.endswith("_CMD"):
        sdxcmd_list.append([pin, instance, signal, af])
    elif signal.endswith("_CK"):
        sdxck_list.append([pin, instance, signal, af])
    elif signal.endswith("_CKIN"):
        sdmmcckin_list.append([pin, instance, signal, af])
    elif signal.endswith("_CDIR"):
        sdmmccdir_list.append([pin, instance, signal, af])
    elif signal.endswith("_D0DIR"):
        sdmmcd0dir_list.append([pin, instance, signal, af])
    elif signal.endswith("_D123DIR"):
        sdmmcd123dir_list.append([pin, instance, signal, af])


# PeripheralPins.cpp generation
def adc_pinmap():
    adc_pins_list = []
    winst = []
    wpin = []
    default_mode = "STM_MODE_ANALOG"
    for p in adclist:
        # inst
        inst = p[1]
        winst.append(len(inst))
        wpin.append(len(p[0]))
        negative = re.search(r"IN[N|M]", p[2])
        if negative:
            # Negative input analog channels
            inv = "1"
        else:
            # Positive input analog channels
            inv = "0"
        # chan
        chan = re.sub(r"^V?IN[N|P|M]?|\D*$", "", p[2].split("_")[1])
        if p[2].endswith("b"):
            mode = "STM_MODE_ANALOG_ADC_CHANNEL_BANK_B"
        else:
            mode = default_mode
        adc_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": "LL_GPIO_PULL_NO",
                "af": "0",
                "chan": chan,
                "inv": inv,
                "cmt": p[2],
            }
        )
    return dict(
        name="ADC",
        hal="ADC",
        aname="ADC",
        data="ext",
        wpin=max(wpin) + 1,
        winst=max(winst) + 1,
        list=adc_pins_list,
    )


def dac_pinmap():
    dac_pins_list = []
    winst = [0]
    wpin = [0]
    mode = "STM_MODE_ANALOG"
    for p in daclist:
        inst = p[1]
        chan = p[2][8]
        winst.append(len(inst))
        wpin.append(len(p[0]))
        dac_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": "LL_GPIO_PULL_NO",
                "af": "0",
                "chan": chan,
                "inv": "0",
                "cmt": p[2],
            }
        )
    return dict(
        name="DAC",
        hal="DAC",
        aname="DAC",
        data="ext",
        wpin=max(wpin) + 1,
        winst=max(winst),
        list=dac_pins_list,
    )


def i2c_pinmap(lst):
    i2c_pins_list = []
    winst = [0]
    wpin = [0]
    mode = "STM_MODE_AF_OD"
    if lst == i2csda_list:
        aname = "I2C_SDA"
    else:
        aname = "I2C_SCL"
    for p in lst:
        inst = p[1]
        winst.append(len(inst))
        wpin.append(len(p[0]))
        i2c_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": "LL_GPIO_PULL_NO",
                "af": p[3],
            }
        )
    return dict(
        name="I2C",
        hal="I2C",
        aname=aname,
        data="",
        wpin=max(wpin) + 1,
        winst=max(winst) + 1,
        list=i2c_pins_list,
    )


def i3c_pinmap(lst):
    i3c_pins_list = []
    winst = [0]
    wpin = [0]
    mode = "STM_MODE_AF_PP"
    if lst == i3csda_list:
        aname = "I3C_SDA"
    else:
        aname = "I3C_SCL"
    for p in lst:
        inst = p[1]
        winst.append(len(inst))
        wpin.append(len(p[0]))
        i3c_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": "LL_GPIO_PULL_NO",
                "af": p[3],
            }
        )
    return dict(
        name="I3C",
        hal="I3C",
        aname=aname,
        data="",
        wpin=max(wpin) + 1,
        winst=max(winst) + 1,
        list=i3c_pins_list,
    )


def tim_pinmap():
    tim_pins_list = []
    winst = []
    wpin = []
    mode = "STM_MODE_AF_PP"
    for p in tim_list:
        # 2nd element is the TIM signal
        a = p[2].split("_")
        inst = a[0]
        if not inst[-1].isdigit():
            inst += "1"
        winst.append(len(inst))
        wpin.append(len(p[0]))
        chan = a[1].replace("CH", "")
        if chan.endswith("N"):
            inv = "1"
            chan = chan.strip("N")
        else:
            inv = "0"
        tim_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": "LL_GPIO_PULL_UP",
                "af": p[3],
                "chan": chan,
                "inv": inv,
                "cmt": p[2],
            }
        )
    return dict(
        name="TIM",
        hal="TIM",
        aname="TIM",
        data="ext",
        wpin=max(wpin) + 1,
        winst=max(winst) + 1,
        list=tim_pins_list,
    )


def uart_pinmap(lst):
    uart_pins_list = []
    winst = []
    wpin = []
    mode = "STM_MODE_AF_PP"
    if lst == uarttx_list:
        aname = "UART_TX"
    elif lst == uartrx_list:
        aname = "UART_RX"
    elif lst == uartrts_list:
        aname = "UART_RTS"
    else:
        aname = "UART_CTS"
    for p in lst:
        # 2nd element is the UART_XX signal
        inst = p[2].split("_")[0]
        winst.append(len(inst))
        wpin.append(len(p[0]))
        if "STM32F1" in mcu_family and lst == uartrx_list:
            mode = "STM_MODE_INPUT"
        else:
            mode = "STM_MODE_AF_PP"
        uart_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": "LL_GPIO_PULL_UP",
                "af": p[3],
            }
        )
    return dict(
        name="UART",
        hal="UART",
        aname=aname,
        data="",
        wpin=max(wpin) + 1,
        winst=max(winst) + 1,
        list=uart_pins_list,
    )


def spi_pinmap(lst):
    spi_pins_list = []
    winst = []
    wpin = []
    sp = re.compile(r"-|_")
    if lst == spimosi_list:
        aname = "SPI_MOSI"
    elif lst == spimiso_list:
        aname = "SPI_MISO"
    elif lst == spisclk_list:
        aname = "SPI_SCLK"
    else:
        aname = "SPI_SSEL"
    for p in lst:
        # 2nd element is the SPI_XXXX signal
        # but using 3rd which contains the stripped one
        # used to properly sort them
        inst = sp.split(p[3])[0]
        winst.append(len(inst))
        wpin.append(len(p[0]))
        spi_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": "STM_MODE_AF_PP",
                "pull": "LL_GPIO_PULL_UP" if inst != "SUBGHZSPI" else "LL_GPIO_PULL_NO",
                "af": p[4],
            }
        )
    return dict(
        name="SPI",
        hal="SPI",
        aname=aname,
        data="",
        wpin=max(wpin) + 1,
        winst=max(winst) + 1,
        list=spi_pins_list,
    )


def can_pinmap(lst):
    can_pins_list = []
    winst = [0]
    wpin = [0]
    if canrd_list and "FDCAN" in canrd_list[0][2]:
        name = "FDCAN"
    else:
        name = "CAN"
    if lst == canrd_list:
        aname = "CAN_RD"
    else:
        aname = "CAN_TD"
    for p in lst:
        # 2nd element is the (FD)CAN_XX signal
        inst = p[2].split("_")[0]
        if not inst[-1].isdigit():
            inst += "1"
        winst.append(len(inst))
        wpin.append(len(p[0]))
        if "STM32F1" in mcu_family and lst == canrd_list:
            mode = "STM_MODE_INPUT"
        else:
            mode = "STM_MODE_AF_PP"
        can_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": "LL_GPIO_PULL_NO",
                "af": p[3],
            }
        )
    return dict(
        name=name,
        hal=name,
        aname=aname,
        data="",
        wpin=max(wpin) + 1,
        winst=max(winst) + 1,
        list=can_pins_list,
    )


def eth_pinmap():
    eth_pins_list = []
    seen_pins = {}
    wpin = [0]
    inst = "ETH"
    for p in eth_list:
        pin = re.sub(r"_ALT\d+$", "", p[0])
        key = (pin, p[1], p[3])
        if key in seen_pins:
            entry = eth_pins_list[seen_pins[key]]
            if p[2] not in entry["cmt"].split(" | "):
                entry["cmt"] += " | " + p[2]
            continue
        # Note: Some pins are duplicated with only a different signal
        # Now considered as an ALTX pins even ifsame AF
        wpin.append(len(p[0]))
        eth_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": "STM_MODE_AF_PP",
                "pull": "LL_GPIO_PULL_UP",
                "af": p[3],
                "cmt": p[2],
            }
        )
        seen_pins[key] = len(eth_pins_list) - 1
    return dict(
        name="ETHERNET",
        hal="ETH",
        aname="Ethernet",
        data="",
        wpin=max(wpin) + 1,
        winst=4,
        list=eth_pins_list,
    )


def xspi_pinmap(lst):
    xspi_pins_list = []
    winst = [0]
    wpin = [0]
    name = "QUADSPI"
    hal = "QSPI"
    ospi_regex = r"OCTOSPI(?:M_P)?(\d).*"

    if xspidata0_list and "OCTOSPI" in xspidata0_list[0][2]:
        name = "OCTOSPI"
        hal = "OSPI"
    if lst == xspidata0_list:
        aname = f"{name}_DATA0"
    elif lst == xspidata1_list:
        aname = f"{name}_DATA1"
    elif lst == xspidata2_list:
        aname = f"{name}_DATA2"
    elif lst == xspidata3_list:
        aname = f"{name}_DATA3"
    elif lst == ospidata4_list:
        aname = f"{name}_DATA4"
    elif lst == ospidata5_list:
        aname = f"{name}_DATA5"
    elif lst == ospidata6_list:
        aname = f"{name}_DATA6"
    elif lst == ospidata7_list:
        aname = f"{name}_DATA7"
    elif lst == xspisclk_list:
        aname = f"{name}_SCLK"
    else:
        aname = f"{name}_SSEL"
    for p in lst:
        # 2nd element is the XXXXSPI_YYYY signal
        instm = re.match(ospi_regex, p[2])
        if instm:
            if "1" in instm.group(1):
                inst = "OCTOSPI1"
            elif "2" in instm.group(1):
                inst = "OCTOSPI2"
        else:
            inst = "QUADSPI"
        winst.append(len(inst))
        wpin.append(len(p[0]))
        xspi_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": "STM_MODE_AF_PP",
                "pull": "LL_GPIO_PULL_UP",
                "af": p[3],
                "cmt": p[2],
            }
        )
    return dict(
        name=name,
        hal=hal,
        aname=aname,
        data="",
        wpin=max(wpin) + 1,
        winst=max(winst) + 1,
        list=xspi_pins_list,
    )


def usb_pinmap(lst):
    usb_pins_list = []
    wpin = [0]

    if lst == usb_otgfs_list:
        inst = usb_inst["otg_fs"]
        pin_groups = [(lst, 0)]
    elif lst == usb_otghs_list:
        inst = usb_inst["otg_hs"]
        sof_pins = [p for p in lst if "SOF" in p[2]]
        fs_pins = [p for p in lst if "SOF" not in p[2] and "ULPI" not in p[2]]
        ulpi_pins = [p for p in lst if "ULPI" in p[2]]
        pin_groups = [(sof_pins, 0)]
        if fs_pins:
            pin_groups.append((fs_pins, 1))
        if ulpi_pins:
            pin_groups.append((ulpi_pins, 2 if fs_pins else 0))
    else:
        inst = usb_inst["usb"]
        pin_groups = [(lst, 0)]

    for pins, group_marker in pin_groups:
        for pin_index, p in enumerate(pins):
            hsinfs = group_marker if pin_index == 0 else 3

            # 2nd element is the USB_XXXX signal
            if not p[2].startswith("USB_D") and "VBUS" not in p[2]:
                if "ID" not in p[2]:
                    mode = "STM_MODE_AF_PP"
                    pull = "LL_GPIO_PULL_UP"
                else:
                    # ID pin: AF_PP + PULLUP
                    mode = "STM_MODE_AF_OD"
                    pull = "LL_GPIO_PULL_UP"
            else:
                # USB_DM/DP and VBUS: INPUT/AF + NOPULL
                if p[2].startswith("USB_D") and "NONE" not in p[3]:
                    mode = "STM_MODE_AF_PP"
                else:
                    mode = "STM_MODE_INPUT"
                pull = "LL_GPIO_PULL_NO"
            wpin.append(len(p[0]))
            usb_pins_list.append(
                {
                    "hsinfs": hsinfs,
                    "pin": p[0],
                    "inst": inst,
                    "mode": mode,
                    "pull": pull,
                    "af": p[3],
                    "cmt": p[2],
                }
            )
    return dict(
        name="USB",
        hal=["PCD", "HCD"],
        aname=inst,
        data="",
        hsinfs=any(marker == 1 for _, marker in pin_groups),
        wpin=max(wpin) + 1,
        winst=len(inst) + 1,
        list=usb_pins_list,
    )


def sdx_pinmap(lst):
    sdx_pins_list = []
    winst = [0]
    wpin = [0]
    mode = "STM_MODE_AF_PP"
    if lst == sdxd0_list:
        aname = "SD_DATA0"
    elif lst == sdxd1_list:
        aname = "SD_DATA1"
    elif lst == sdxd2_list:
        aname = "SD_DATA2"
    elif lst == sdxd3_list:
        aname = "SD_DATA3"
    elif lst == sdxd4_list:
        aname = "SD_DATA4"
    elif lst == sdxd5_list:
        aname = "SD_DATA5"
    elif lst == sdxd6_list:
        aname = "SD_DATA6"
    elif lst == sdxd7_list:
        aname = "SD_DATA7"
    elif lst == sdxcmd_list:
        aname = "SD_CMD"
    elif lst == sdxck_list:
        aname = "SD_CK"
    elif lst == sdmmcckin_list:
        aname = "SD_CKIN"
    elif lst == sdmmccdir_list:
        aname = "SD_CDIR"
    elif lst == sdmmcd0dir_list:
        aname = "SD_D0DIR"
    elif lst == sdmmcd123dir_list:
        aname = "SD_D123DIR"
    for p in lst:
        # 2nd element is the SD signal
        a = p[2].split("_")
        inst = a[0]
        if a[1].startswith("C") or a[1].endswith("DIR"):
            pull = "LL_GPIO_PULL_NO"
        else:
            pull = "LL_GPIO_PULL_UP"
        winst.append(len(inst))
        wpin.append(len(p[0]))
        sdx_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": pull,
                "af": p[3],
                "cmt": p[2],
            }
        )
    return dict(
        name="SD",
        hal="SD",
        aname=aname,
        data="",
        wpin=max(wpin) + 1,
        winst=max(winst) + 1,
        list=sdx_pins_list,
    )


def print_peripheral():
    # Print specific PinNames in header file
    periph_c_template = j2_env.get_template(
        periph_c_filename,
    )

    if usb_list:
        usb_pinmmap = [usb_pinmap(usb_list)]
    elif usb_otgfs_list:
        usb_pinmmap = (usb_pinmap(usb_otgfs_list), usb_pinmap(usb_otghs_list))
    else:
        usb_pinmmap = [usb_pinmap(usb_otghs_list)]

    periph_c_file.write(
        periph_c_template.render(
            year=year,
            mcu_file=mcu_file.name,
            db_release="",
            peripherals_list=(
                [adc_pinmap()],
                [dac_pinmap()],
                (i2c_pinmap(i2csda_list), i2c_pinmap(i2cscl_list)),
                (i3c_pinmap(i3csda_list), i3c_pinmap(i3cscl_list)),
                [tim_pinmap()],
                (
                    uart_pinmap(uarttx_list),
                    uart_pinmap(uartrx_list),
                    uart_pinmap(uartrts_list),
                    uart_pinmap(uartcts_list),
                ),
                (
                    spi_pinmap(spimosi_list),
                    spi_pinmap(spimiso_list),
                    spi_pinmap(spisclk_list),
                    spi_pinmap(spissel_list),
                ),
                (can_pinmap(canrd_list), can_pinmap(cantd_list)),
                [eth_pinmap()],
                (
                    xspi_pinmap(xspidata0_list),
                    xspi_pinmap(xspidata1_list),
                    xspi_pinmap(xspidata2_list),
                    xspi_pinmap(xspidata3_list),
                    xspi_pinmap(ospidata4_list),
                    xspi_pinmap(ospidata5_list),
                    xspi_pinmap(ospidata6_list),
                    xspi_pinmap(ospidata7_list),
                    xspi_pinmap(xspisclk_list),
                    xspi_pinmap(xspissel_list),
                ),
                usb_pinmmap,
                (
                    sdx_pinmap(sdxcmd_list),
                    sdx_pinmap(sdxck_list),
                    sdx_pinmap(sdxd0_list),
                    sdx_pinmap(sdxd1_list),
                    sdx_pinmap(sdxd2_list),
                    sdx_pinmap(sdxd3_list),
                    sdx_pinmap(sdxd4_list),
                    sdx_pinmap(sdxd5_list),
                    sdx_pinmap(sdxd6_list),
                    sdx_pinmap(sdxd7_list),
                    sdx_pinmap(sdmmcckin_list),
                    sdx_pinmap(sdmmccdir_list),
                    sdx_pinmap(sdmmcd0dir_list),
                    sdx_pinmap(sdmmcd123dir_list),
                ),
            ),
            halv2=True,
        )
    )


# PinNamesVar.h generation
def manage_syswkup():
    if len(syswkup_list) != 0:
        # Find the max range of SYS_WKUP.
        # Ensure it is compatible with the current maximum range
        # used by STM32LowPower.
        max_range = syswkup_list[-1][1].replace("SYS_WKUP", "")
        max_range = int(max_range) if max_range else 8
        # F446 start from 0
        base_index = 1
        if syswkup_list[0][1].replace("SYS_WKUP", "") == "0":
            base_index = 0
            max_range += 1
        # Ensure the max_range is at least 8
        # as some mcu PWR_WAKEUP_PINx while not SYS_WKUPx
        if max_range < 8:
            max_range = 8
        syswkup_pins_list = [[] for _ in range(max_range)]
        for p in syswkup_list:
            num = p[1].replace("SYS_WKUP", "")
            num = int(num) if num else 1
            if base_index == 1:
                num -= 1
                cmt = ""
            else:
                cmt = f" /* {p[1]} */"
            syswkup_pins_list[num].append([p[0], cmt])
    else:
        syswkup_pins_list = []
    return syswkup_pins_list


def print_pinamevar():
    # First check core version and search PWR_WAKEUP_*
    syswkup_type = "PIN"

    # Print specific PinNames in header file
    pinvar_h_template = j2_env.get_template(pinvar_h_filename)

    dualpad_pins_list = []
    for p in dualpad_list:
        dualpad_pins_list.append({"name": p[0], "base": p[0].split("_C")[0]})

    remap_pins_list = []
    for p in remap_list:
        remap_pins_list.append({"name": p[0], "base": p[0].split("_R")[0]})

    alt_pins_list = []
    waltpin = [0]
    for p in alt_list:
        if "_ALT" in p[0]:
            waltpin.append(len(p[0]))
            alt_pins_list.append(
                {"name": p[0], "base": p[0].split("_A")[0], "num": p[0].split("_")[-1]}
            )

    syswkup_pins_list = manage_syswkup()

    usb_pins_list = []
    wusbpin = [0]
    if usb_list or usb_otgfs_list or usb_otghs_list:
        for p in usb_list + usb_otgfs_list + usb_otghs_list:
            wusbpin.append(len(p[2]))
            usb_pins_list.append({"name": p[2], "pn": p[0]})
    sorted_usb_pins_list = sorted(usb_pins_list, key=lambda i: i["name"])

    pinvar_h_file.write(
        pinvar_h_template.render(
            dualpad_pins_list=dualpad_pins_list,
            remap_pins_list=remap_pins_list,
            waltpin=max(waltpin),
            alt_pins_list=alt_pins_list,
            syswkup_type=syswkup_type,
            syswkup_pins_list=syswkup_pins_list,
            wusbpin=max(wusbpin),
            usb_pins_list=sorted_usb_pins_list,
        )
    )
    alt_syswkup_list = []
    for idx, syswkup_list in enumerate(syswkup_pins_list, start=1):
        if len(syswkup_list) > 1:
            for idx2, _lst in enumerate(syswkup_list[1:], start=1):
                alt_syswkup_list.append(f"{idx}_{idx2}")
    return alt_syswkup_list


# Variant files generation
def spi_pins_variant():
    ss_pin = ss1_pin = ss2_pin = ss3_pin = mosi_pin = miso_pin = sck_pin = (
        "PNUM_NOT_DEFINED"
    )

    # Iterate to find match instance if any
    for mosi in spimosi_list:
        mosi_inst = mosi[1]
        for miso in spimiso_list:
            miso_inst = miso[1]
            if mosi_inst == miso_inst:
                for sck in spisclk_list:
                    sck_inst = sck[1]
                    if mosi_inst == sck_inst:
                        miso_pin = miso[0]
                        mosi_pin = mosi[0]
                        sck_pin = sck[0]
                        break
                else:
                    continue
                break
        else:
            continue

        # Try to find hw ssel
        for ss in spissel_list:
            ss_inst = ss[1]
            if mosi_inst == ss_inst:
                if ss_pin == "PNUM_NOT_DEFINED":
                    ss_pin = ss[0]
                elif ss1_pin == "PNUM_NOT_DEFINED":
                    ss1_pin = ss[0]
                elif ss2_pin == "PNUM_NOT_DEFINED":
                    ss2_pin = ss[0]
                elif ss3_pin == "PNUM_NOT_DEFINED":
                    ss3_pin = ss[0]
                    break
        break
    else:
        print("No SPI found!")
    return dict(
        ss=ss_pin.replace("_", "", 1) if ss_pin != "PNUM_NOT_DEFINED" else ss_pin,
        ss1=ss1_pin.replace("_", "", 1) if ss1_pin != "PNUM_NOT_DEFINED" else ss1_pin,
        ss2=ss2_pin.replace("_", "", 1) if ss2_pin != "PNUM_NOT_DEFINED" else ss2_pin,
        ss3=ss3_pin.replace("_", "", 1) if ss3_pin != "PNUM_NOT_DEFINED" else ss3_pin,
        mosi=(
            mosi_pin.replace("_", "", 1) if mosi_pin != "PNUM_NOT_DEFINED" else mosi_pin
        ),
        miso=(
            miso_pin.replace("_", "", 1) if miso_pin != "PNUM_NOT_DEFINED" else miso_pin
        ),
        sck=sck_pin.replace("_", "", 1) if sck_pin != "PNUM_NOT_DEFINED" else sck_pin,
    )


def i2c_pins_variant():
    sda_pin = scl_pin = "PNUM_NOT_DEFINED"
    # Iterate to find match instance if any
    for sda in i2csda_list:
        sda_inst = sda[1]
        for scl in i2cscl_list:
            scl_inst = scl[1]
            if sda_inst == scl_inst:
                sda_pin = sda[0]
                scl_pin = scl[0]
                break
        else:
            continue
        break
    else:
        print("No I2C found!")
    return dict(
        sda=sda_pin.replace("_", "", 1) if sda_pin != "PNUM_NOT_DEFINED" else sda_pin,
        scl=scl_pin.replace("_", "", 1) if scl_pin != "PNUM_NOT_DEFINED" else scl_pin,
    )


def i3c_pins_variant():
    sda_pin = scl_pin = "PNUM_NOT_DEFINED"
    # Iterate to find match instance if any
    for sda in i3csda_list:
        sda_inst = sda[1]
        for scl in i3cscl_list:
            scl_inst = scl[1]
            if sda_inst == scl_inst:
                sda_pin = sda[0]
                scl_pin = scl[0]
                break
        else:
            continue
        break
    else:
        print("No I3C found!")
    return dict(
        sda=sda_pin.replace("_", "", 1) if sda_pin != "PNUM_NOT_DEFINED" else sda_pin,
        scl=scl_pin.replace("_", "", 1) if scl_pin != "PNUM_NOT_DEFINED" else scl_pin,
    )


def serial_pins_variant():
    # Manage (LP)U(S)ART pins
    if uarttx_list:
        # Default if no rx pin
        serialtx_pin = uarttx_list[0]
        serial_inst = uarttx_list[0]
        # Half duplex
        serialrx_pin = serialtx_pin
        if uartrx_list:
            # Iterate to find match instance if any
            for uarttx in uarttx_list:
                serialtx_inst = uarttx[1]
                for uartrx in uartrx_list:
                    serialrx_inst = uartrx[1]
                    if serialtx_inst == serialrx_inst:
                        serialtx_pin = uarttx[0]
                        serialrx_pin = uartrx[0]
                        serial_inst = serialtx_inst
                        break
                else:
                    continue
                break
        end_num_regex = r".*(\d+)$"
        serialnum = re.match(end_num_regex, serial_inst)
        if serialnum:
            serialnum = serialnum.group(1)
            if serial_inst.startswith("LP"):
                serialnum = f"10{serialnum}"
        else:
            print("No serial instance number found!")
            serialnum = "-1"
    else:
        serialtx_pin = "PNUM_NOT_DEFINED"
        serialnum = "-1"
        print("No serial found!")
    return dict(
        instance=serialnum,
        rx=(
            serialrx_pin.replace("_", "", 1)
            if serialrx_pin != "PNUM_NOT_DEFINED"
            else serialrx_pin
        ),
        tx=(
            serialtx_pin.replace("_", "", 1)
            if serialtx_pin != "PNUM_NOT_DEFINED"
            else serialtx_pin
        ),
    )


def timer_variant():
    tone = servo = "TIMx"
    if tim_inst_list:
        for pref in tim_inst_order:
            if pref in tim_inst_list:
                if tone == "TIMx":
                    tone = pref
                elif servo == "TIMx":
                    servo = pref
                    break
        else:
            print("Not all TIM instance found!")
    return dict(tone=tone, servo=servo)


def sdmmc_signals():
    sdmmcNA_list = []
    # Check if SDMMC instance
    if sdxd0_list and "SDMMC" in sdxd0_list[0][2]:
        if not sdmmcckin_list:
            sdmmcNA_list.append("SDMMC_CKIN_NA")
        if not sdmmccdir_list:
            sdmmcNA_list.append("SDMMC_CDIR_NA")
        if not sdmmcd0dir_list:
            sdmmcNA_list.append("SDMMC_D0DIR_NA")
        if not sdmmcd123dir_list:
            sdmmcNA_list.append("SDMMC_D123DIR_NA")
    return sdmmcNA_list


def print_variant(generic_list, alt_syswkup_list):
    variant_h_template = j2_env.get_template(variant_h_filename)
    variant_cpp_template = j2_env.get_template(variant_cpp_filename)

    # Default pins definition
    num_digital_pins = len(io_list) + len(dualpad_list) + len(remap_list)
    num_dualpad_pins = len(dualpad_list)
    num_remap_pins = len(remap_list)

    # SPI definition
    spi_pins = spi_pins_variant()

    # I2C definition
    i2c_pins = i2c_pins_variant()

    # I3C definition if any
    if i3csda_list and i3cscl_list:
        i3c_pins = i3c_pins_variant()
    else:
        i3c_pins = None

    # Serial definition
    serial = serial_pins_variant()

    # Timers definition
    timer = timer_variant()

    # SDMMC signals definition
    sdmmcNA_list = sdmmc_signals()

    # Manage all pins number, PinName and analog pins
    analog_index = 0
    pins_number_list = []
    analog_pins_list = []
    pinnames_list = []
    idx_sum = len(io_list)
    for idx, io in enumerate(io_list):
        pyn = io[0].replace("_", "", 1)
        if [item for item in adclist if item[0] == io[0]]:
            ax = f"A{analog_index}"
            pins_number_list.append({"name": pyn, "val": f"PIN_{ax}"})
            pinnames_list.append({"name": io[0], "ax": analog_index})
            analog_pins_list.append({"val": idx, "ax": ax, "pyn": pyn})
            analog_index += 1
        else:
            pins_number_list.append({"name": pyn, "val": idx})
            pinnames_list.append({"name": io[0], "ax": -1})

    for idx, io in enumerate(dualpad_list):
        pyn = io[0].replace("_", "", 1)
        if [item for item in adclist if item[0] == io[0]]:
            ax = f"A{analog_index}"
            pins_number_list.append({"name": pyn, "val": f"PIN_{ax}"})
            pinnames_list.append({"name": io[0], "ax": analog_index})
            analog_pins_list.append({"val": idx + idx_sum, "ax": ax, "pyn": pyn})
            analog_index += 1
        else:
            pins_number_list.append({"name": pyn, "val": idx + idx_sum})
            pinnames_list.append({"name": io[0], "ax": -1})
    idx_sum += len(dualpad_list)
    for idx, io in enumerate(remap_list):
        pyn = io[0].replace("_", "", 1)
        if [item for item in adclist if item[0] == io[0]]:
            ax = f"A{analog_index}"
            pins_number_list.append({"name": pyn, "val": f"PIN_{ax}"})
            pinnames_list.append({"name": io[0], "ax": analog_index})
            analog_pins_list.append({"val": idx + idx_sum, "ax": ax, "pyn": pyn})
            analog_index += 1
        else:
            pins_number_list.append({"name": pyn, "val": idx + idx_sum})
            pinnames_list.append({"name": io[0], "ax": -1})
    alt_pins_list = []
    waltpin = [0]
    for p in alt_list:
        if "_ALT" in p[0]:
            pyn = p[0].replace("_", "", 1)
            waltpin.append(len(pyn))
            alt_pins_list.append(
                {"name": pyn, "base": pyn.split("_A")[0], "num": pyn.split("_")[-1]}
            )

    # Define extra HAL modules
    hal_modules_list = []
    if daclist:
        hal_modules_list.append("DAC")
    if eth_list:
        hal_modules_list.append("ETH")
    if i3csda_list and i3cscl_list:
        hal_modules_list.append("I3C")
    if xspidata0_list:
        if "OCTOSPI" in xspidata0_list[0][2]:
            hal_modules_list.append("OSPI")
        else:
            hal_modules_list.append("QSPI")
    if sdxcmd_list:
        hal_modules_list.append("SD")

    variant_h_file.write(
        variant_h_template.render(
            year=year,
            pins_number_list=pins_number_list,
            alt_pins_list=alt_pins_list,
            alt_syswkup_list=alt_syswkup_list,
            waltpin=max(waltpin),
            num_digital_pins=num_digital_pins,
            num_dualpad_pins=num_dualpad_pins,
            num_remap_pins=num_remap_pins,
            num_analog_inputs=len(analog_pins_list),
            spi_pins=spi_pins,
            i2c_pins=i2c_pins,
            i3c_pins=i3c_pins,
            timer=timer,
            serial=serial,
            hal_modules_list=hal_modules_list,
            alias_list=[],
            sdmmcNA_list=sdmmcNA_list,
            halv2=True,
        )
    )

    variant_cpp_file.write(
        variant_cpp_template.render(
            year=year,
            generic_list=generic_list,
            pinnames_list=pinnames_list,
            analog_pins_list=analog_pins_list,
        )
    )


def search_product_line(valueline: str, extra: str) -> str:
    product_line = ""
    product_line_list = product_line_dict[mcu_family]
    for idx_pline, pline in enumerate(product_line_list):
        vline = valueline
        product_line = pline
        # Remove the 'x' character from pline and
        # the one at same index in the vline
        while 1:
            idx = pline.find("x")
            if idx > 0:
                pline = pline.replace("x", "", 1)
                vline = vline[:idx] + vline[idx + 1 :]
            else:
                break
        if pline >= vline:
            if (
                extra
                and len(product_line_list) > idx_pline + 1
                and product_line_list[idx_pline + 1] == (product_line + extra)
            ):
                # Look for the next product line if contains the extra
                product_line = product_line_list[idx_pline + 1]
            break
    else:
        # In case of CMSIS device does not exist
        product_line = ""
    return product_line


def search_svdfile(mcu_name):
    svd_file = svd_dict.get(mcu_name, "")
    return svd_file


def print_boards_entry():
    boards_entry_template = j2_env.get_template(boards_entry_filename)

    # Parse only one time the CMSIS startup file
    if mcu_family not in product_line_dict:
        # Search the product line
        CMSIS_startup_file_path = (
            system_path
            / "Drivers"
            / "CMSIS"
            / "Device"
            / "ST"
            / mcu_family_dir
            / "Source"
        )
        startup_files = sorted(
            [s.name for s in CMSIS_startup_file_path.glob("startup_*.c")]
        )

        for idx, s in enumerate(startup_files):
            # Remove "startup_" and file extension
            product_line = re.split("_|\\.", s)[1]
            startup_files[idx] = product_line.upper().replace("X", "x")
        product_line_dict[mcu_family] = startup_files

    # Only one item in the list as we are in the context of one MCU
    generic_list = []
    valueline = mcu_refname
    generic_list.append(
        {
            "name": mcu_refname.replace("STM32", ""),
            "board": mcu_refname.replace("STM32", "").upper(),
            "flash": mcu_info[mcu_refname]["flash"],
            "ram": mcu_info[mcu_refname]["ram"],
            "svd": search_svdfile(mcu_refname),
        }
    )
    subp = pl_regex.search(valueline)
    product_line = search_product_line(
        package_regex.sub(r"", valueline),
        subp.group(1) if subp and subp.group(1) is not None else "",
    )

    gen_entry = mcu_family.replace("STM32", "Gen")

    boards_entry_file.write(
        boards_entry_template.render(
            generic_list=generic_list,
            gen_entry=gen_entry,
            mcu_dir=mcu_refname.replace("STM32", ""),
            mcu_family_dir=mcu_family_dir,
            product_line=product_line,
        )
    )
    return generic_list


def print_general_clock(generic_list):
    generic_clock_template = j2_env.get_template(generic_clock_filename)
    generic_clock_file.write(
        generic_clock_template.render(
            year=year,
            generic_list=generic_list,
        )
    )


# List management
tokenize = re.compile(r"(\d+)|(\D+)").findall


def natural_sortkey(list_2_elem):
    return tuple(int(num) if num else alpha for num, alpha in tokenize(list_2_elem[0]))


def natural_sortkey2(list_2_elem):
    return tuple(int(num) if num else alpha for num, alpha in tokenize(list_2_elem[2]))


def natural_sortkey3(list_2_elem):
    return tuple(int(num) if num else alpha for num, alpha in tokenize(list_2_elem[3]))


def sort_my_lists():
    io_list.sort(key=natural_sortkey)
    dualpad_list.sort(key=natural_sortkey)
    remap_list.sort(key=natural_sortkey)
    adclist.sort(key=natural_sortkey)
    daclist.sort(key=natural_sortkey)
    i2cscl_list.sort(key=natural_sortkey)
    i2csda_list.sort(key=natural_sortkey)
    i3cscl_list.sort(key=natural_sortkey)
    i3csda_list.sort(key=natural_sortkey)
    tim_list.sort(key=natural_sortkey2)
    tim_list.sort(key=natural_sortkey)
    uarttx_list.sort(key=natural_sortkey)
    uartrx_list.sort(key=natural_sortkey)
    uartcts_list.sort(key=natural_sortkey)
    uartrts_list.sort(key=natural_sortkey)
    spimosi_list.sort(key=natural_sortkey3)
    spimosi_list.sort(key=natural_sortkey)
    spimiso_list.sort(key=natural_sortkey3)
    spimiso_list.sort(key=natural_sortkey)
    spissel_list.sort(key=natural_sortkey3)
    spissel_list.sort(key=natural_sortkey)
    spisclk_list.sort(key=natural_sortkey3)
    spisclk_list.sort(key=natural_sortkey)
    cantd_list.sort(key=natural_sortkey)
    canrd_list.sort(key=natural_sortkey)
    eth_list.sort(key=natural_sortkey)
    xspidata0_list.sort(key=natural_sortkey)
    xspidata1_list.sort(key=natural_sortkey)
    xspidata2_list.sort(key=natural_sortkey)
    xspidata3_list.sort(key=natural_sortkey)
    ospidata4_list.sort(key=natural_sortkey)
    ospidata5_list.sort(key=natural_sortkey)
    ospidata6_list.sort(key=natural_sortkey)
    ospidata7_list.sort(key=natural_sortkey)
    xspisclk_list.sort(key=natural_sortkey)
    xspissel_list.sort(key=natural_sortkey)
    syswkup_list.sort(key=natural_sortkey)
    usb_list.sort(key=natural_sortkey)
    usb_otgfs_list.sort(key=natural_sortkey)
    usb_otghs_list.sort(key=natural_sortkey)
    sdxcmd_list.sort(key=natural_sortkey)
    sdxck_list.sort(key=natural_sortkey)
    sdxd0_list.sort(key=natural_sortkey)
    sdxd1_list.sort(key=natural_sortkey)
    sdxd2_list.sort(key=natural_sortkey)
    sdxd3_list.sort(key=natural_sortkey)
    sdxd4_list.sort(key=natural_sortkey)
    sdxd5_list.sort(key=natural_sortkey)
    sdxd6_list.sort(key=natural_sortkey)
    sdxd7_list.sort(key=natural_sortkey)
    sdmmcckin_list.sort(key=natural_sortkey)
    sdmmccdir_list.sort(key=natural_sortkey)
    sdmmcd0dir_list.sort(key=natural_sortkey)
    sdmmcd123dir_list.sort(key=natural_sortkey)


def clean_all_lists():
    del io_list[:]
    del alt_list[:]
    del dualpad_list[:]
    del remap_list[:]
    del adclist[:]
    del daclist[:]
    del i2cscl_list[:]
    del i2csda_list[:]
    del i3cscl_list[:]
    del i3csda_list[:]
    del tim_list[:]
    del uarttx_list[:]
    del uartrx_list[:]
    del uartcts_list[:]
    del uartrts_list[:]
    del spimosi_list[:]
    del spimiso_list[:]
    del spissel_list[:]
    del spisclk_list[:]
    del cantd_list[:]
    del canrd_list[:]
    del eth_list[:]
    del xspidata0_list[:]
    del xspidata1_list[:]
    del xspidata2_list[:]
    del xspidata3_list[:]
    del ospidata4_list[:]
    del ospidata5_list[:]
    del ospidata6_list[:]
    del ospidata7_list[:]
    del xspisclk_list[:]
    del xspissel_list[:]
    del syswkup_list[:]
    del usb_list[:]
    del usb_otgfs_list[:]
    del usb_otghs_list[:]
    del sdxcmd_list[:]
    del sdxck_list[:]
    del sdxd0_list[:]
    del sdxd1_list[:]
    del sdxd2_list[:]
    del sdxd3_list[:]
    del sdxd4_list[:]
    del sdxd5_list[:]
    del sdxd6_list[:]
    del sdxd7_list[:]
    del sdmmcckin_list[:]
    del sdmmccdir_list[:]
    del sdmmcd0dir_list[:]
    del sdmmcd123dir_list[:]


def manage_alternate():
    sort_my_lists()

    update_alternate(adclist)
    update_alternate(daclist)
    update_alternate(i2cscl_list)
    update_alternate(i2csda_list)
    update_alternate(i3cscl_list)
    update_alternate(i3csda_list)
    update_alternate(tim_list)
    update_alternate(uarttx_list)
    update_alternate(uartrx_list)
    update_alternate(uartcts_list)
    update_alternate(uartrts_list)
    update_alternate(spimosi_list)
    update_alternate(spimiso_list)
    update_alternate(spissel_list)
    update_alternate(spisclk_list)
    update_alternate(cantd_list)
    update_alternate(canrd_list)
    update_alternate(eth_list)
    update_alternate(xspidata0_list)
    update_alternate(xspidata1_list)
    update_alternate(xspidata2_list)
    update_alternate(xspidata3_list)
    update_alternate(ospidata4_list)
    update_alternate(ospidata5_list)
    update_alternate(ospidata6_list)
    update_alternate(ospidata7_list)
    update_alternate(xspisclk_list)
    update_alternate(xspissel_list)
    update_alternate(syswkup_list)
    update_alternate(usb_list)
    update_alternate(usb_otgfs_list)
    update_alternate_usb_otg_hs()
    update_alternate(sdxcmd_list)
    update_alternate(sdxck_list)
    update_alternate(sdxd0_list)
    update_alternate(sdxd1_list)
    update_alternate(sdxd2_list)
    update_alternate(sdxd3_list)
    update_alternate(sdxd4_list)
    update_alternate(sdxd5_list)
    update_alternate(sdxd6_list)
    update_alternate(sdxd7_list)
    update_alternate(sdmmcckin_list)
    update_alternate(sdmmccdir_list)
    update_alternate(sdmmcd0dir_list)
    update_alternate(sdmmcd123dir_list)

    alt_list.sort(key=natural_sortkey)


def update_alternate(lst):
    prev_p = ""
    alt_index = 1
    for index, p in enumerate(lst):
        if p[0] == prev_p:
            p[0] += "_ALT%d" % alt_index
            lst[index] = p
            store_pin(p[0], p[1], alt_list)
            alt_index += 1
        else:
            prev_p = p[0]
            alt_index = 1


def update_alternate_usb_otg_hs():
    prev_p = ""
    alt_index = 1
    for nb in range(2):
        for index, p in enumerate(usb_otghs_list):
            if nb == 0:
                if "ULPI" in p[2]:
                    continue
            else:
                if "ULPI" not in p[2]:
                    continue
            if p[0] == prev_p:
                p[0] += "_ALT%d" % alt_index
                usb_otghs_list[index] = p
                store_pin(p[0], p[1], alt_list)
                alt_index += 1
            else:
                prev_p = p[0]
                alt_index = 1


def keyflash(x):
    return x[0]


def group_by_flash(glist, index_mcu_base):
    expanded_dir_list = []
    group_flash_list = []
    new_mcu_dirname = ""

    base_name = glist[0][:index_mcu_base]
    # Expand all mcu flash to ease aggregation
    # Strip basename
    for dir_name in glist:
        subf = flash_group_regex.search(dir_name)
        if subf:
            for flash in subf.group(2).split("-"):
                expanded_dir_list.append(flash + subf.group(3))
        else:
            expanded_dir_list.append(dir_name[index_mcu_base:])
    # Remove duplicate
    expanded_dir_list = list(dict.fromkeys(expanded_dir_list))
    expanded_dir_list.sort()
    group_flash_list = [list(g) for _, g in groupby(expanded_dir_list, keyflash)]
    packages_per_flash = OrderedDict()
    for gflash in group_flash_list:
        packages_list = []
        flash = gflash[0][0]
        for info in gflash:
            packages_list.append(info[1:])

        if packages_list in packages_per_flash.values():
            key = list(packages_per_flash.keys())[
                list(packages_per_flash.values()).index(packages_list)
            ]
            # Merge key
            if key:
                packages_per_flash[f"{key}-{flash}"] = packages_per_flash.pop(key)
        else:
            packages_per_flash[flash] = packages_list

    for index, key in enumerate(packages_per_flash):
        key_package_list = packages_per_flash[key]
        new_mcu_dirname += ("_" if index != 0 else "") + base_name
        if len(key) == 1:
            new_mcu_dirname += key
        else:
            new_mcu_dirname += f"({key})"
        # Handle package with AGNPQSXZ
        # One case not manage: [Tx, TxX, Yx]
        # Assuming it is not an issue to have non existing mcu
        # Ease parsing and shorten directory name
        package_list = []
        ext_list = []
        for ppe in key_package_list:
            sub = mcu_PE_regex.search(ppe)
            if not sub:
                print(f"Package: {base_name}, ppe: {ppe} not recognized")
                exit(1)
            else:
                package_list.append(sub.group(1))
                # Assert
                if sub.group(2) != "x":
                    print(
                        f"Package: {base_name}, ppe: {ppe} contains {sub.group(2)} instead of 'x'"
                    )
                    exit(1)
                if sub.group(3):
                    ext_list.append(sub.group(3))
        # Count each subpart
        pcounter = Counter(package_list)
        ecounter = Counter(ext_list)
        if len(pcounter) == 1:
            new_mcu_dirname += package_list[0]
        else:
            new_mcu_dirname += f"({'-'.join(k for k in sorted(pcounter))})"
        if len(ecounter):
            new_mcu_dirname += "x"
            if (len(ecounter) == 1) and (
                sum(pcounter.values()) == sum(ecounter.values())
            ):
                # new_mcu_dirname += next(iter(ecounter))
                new_mcu_dirname += ext_list[0]
            else:
                new_mcu_dirname += f"({'-'.join(k for k in sorted(ecounter))})"
        del package_list[:]
        del ext_list[:]

    del group_flash_list[:]
    del expanded_dir_list[:]
    return new_mcu_dirname


def merge_dir(out_temp_path, group_mcu_dir, mcu_family_name, pinout_json, variant_exp):
    dirname_list = []
    new_mcu_dirname = ""
    # Working mcu directory
    mcu_dir = group_mcu_dir[0]
    # Merge if needed
    if len(group_mcu_dir) != 1:
        # Handle mcu name length dynamically
        # Add num for extra information line, #pin and flash
        nx = stm32_dict[mcu_family_name.removeprefix("STM32")]
        index_mcu_base = len(mcu_family_name.removeprefix("STM32").removesuffix(nx)) + (
            3 if len(nx) == 2 else 2
        )
        # Extract only dir name
        for dir_name in group_mcu_dir:
            dirname_list.append(dir_name.stem)

        # using lambda + itertools.groupby() + split()
        # group by mcu base name
        group_base_list = [
            list(g) for _, g in groupby(dirname_list, lambda x: x[0:index_mcu_base])
        ]

        group_flash_list = []
        group_package_list = []
        for index, glist in enumerate(group_base_list):
            # Only one mcu
            if len(glist) == 1:
                new_mcu_dirname += f"{'_' if index != 0 else ''}{glist[0].strip('x')}"
            else:
                # Group using flash info
                gbf = group_by_flash(glist, index_mcu_base)
                new_mcu_dirname += f"{'_' if index != 0 else ''}{gbf}"
        del group_package_list[:]
        del group_flash_list[:]
        del group_base_list[:]
        del dirname_list[:]

        new_mcu_dir = out_temp_path / f"{mcu_family_name}{nx}" / new_mcu_dirname

        board_entry = ""
        with open(mcu_dir / boards_entry_filename) as fp:
            board_entry = fp.read()
        # Handle files
        # Skip first dir
        for dir_name in group_mcu_dir[1:]:
            # Save board entry
            skip = False
            with open(dir_name / boards_entry_filename) as fp:
                for _index, line in enumerate(fp):
                    # Skip until next empty line (included)
                    if skip:
                        if line == "\n":
                            skip = False
                        continue
                    if line != "\n" and line in board_entry:
                        skip = True
                        continue
                    board_entry += line
            # Delete directory
            for filepath in dir_name.glob("*.*"):
                filepath.unlink()
            dir_name.rmdir()

        # Rename it
        # With python 3.8 and above: mcu_dir = mcu_dir.replace(new_mcu_dir)
        mcu_dir.replace(new_mcu_dir)
        mcu_dir = new_mcu_dir

        # Update files
        if pinout_json:
            pinout_json.sort()
            pinout_json = list(OrderedDict.fromkeys(pinout_json))
            new_line_c = pinout_json.pop(0)
            for index, jsonf in enumerate(pinout_json, 1):
                if index % 2 == 0:
                    new_line_c += f"\n * {jsonf}"
                else:
                    new_line_c += f", {jsonf}"

            update_file(mcu_dir / periph_c_filename, pinout_json_regex, new_line_c)

        variant_exp.sort()
        variant_exp = list(OrderedDict.fromkeys(variant_exp))
        new_line_c = variant_exp[0]
        new_line_h = f"{variant_exp.pop(0)}"
        for index, pre in enumerate(variant_exp, 1):
            if index % 2 == 0:
                new_line_c += f" ||\\\n    {pre}"
                new_line_h += f" &&\\\n    !{pre}"
            else:
                new_line_c += f" || {pre}"
                new_line_h += f" && !{pre}"
        update_file(mcu_dir / variant_cpp_filename, update_regex, new_line_c)
        update_file(mcu_dir / generic_clock_filename, update_regex, new_line_c)
        update_file(mcu_dir / variant_h_filename, update_regex, new_line_h)

        # Dump new board_entry file
        with open(mcu_dir / boards_entry_filename, "w", newline="\n") as fp:
            fp.write(board_entry)

        update_file(
            mcu_dir / boards_entry_filename,
            board_entry_regex,
            rf"\g<1>{mcu_dir.name}",
        )
    else:
        if mcu_dir.stem.endswith("x"):
            # Rename it
            new_mcu_dir = mcu_dir.parent / mcu_dir.stem.strip("x")
            # With python 3.8 and above: mcu_dir = mcu_dir.replace(new_mcu_dir)
            mcu_dir.replace(new_mcu_dir)
            mcu_dir = new_mcu_dir
            update_file(
                mcu_dir / boards_entry_filename,
                board_entry_regex,
                rf"\g<1>{mcu_dir.name}",
            )
    return mcu_dir


# Aggregating all generated files
def aggregate_dir():
    # Get mcu_family directories
    out_temp_path = tmp_dir

    group_mcu_dir = []
    mcu_dir1_files_list = []
    mcu_dir2_files_list = []

    # Compare per family
    for mcu_family_name in aggregate_series_list:
        nx = stm32_dict[mcu_family_name.removeprefix("STM32")]
        mcu_family_path = out_temp_path / f"{mcu_family_name}{nx}"
        out_family_path = root_dir / "variants" / mcu_family_path.name
        # Get all mcu_dir
        mcu_dirs = sorted(mcu_family_path.glob("*/"))
        # Get original directory list of current series STM32YYxx
        mcu_out_dirs_ori = sorted(out_family_path.glob("*/**"))
        mcu_out_dirs_up = []
        # Group mcu directories when only expressions and json file name are different
        while mcu_dirs:
            # Pop first item
            group_mcu_dir = [mcu_dirs.pop(0)]
            index = 0
            mcu_dir = group_mcu_dir[0]
            mcu_dir1_files_list = [
                mcu_dir / periph_c_filename,
                mcu_dir / pinvar_h_filename,
                mcu_dir / variant_cpp_filename,
                mcu_dir / variant_h_filename,
            ]
            pinout_json = []
            variant_exp = []
            # Compare the first directory to all other directories
            while mcu_dirs and index < len(mcu_dirs):
                # Compare all the variant files except the generic_boards.txt
                mcu_dir2_files_list = [
                    mcu_dirs[index] / periph_c_filename,
                    mcu_dirs[index] / pinvar_h_filename,
                    mcu_dirs[index] / variant_cpp_filename,
                    mcu_dirs[index] / variant_h_filename,
                ]
                # Iterate over each variant files
                pinout_json_tmp = []
                variant_exp_tmp = []
                for index2, fname in enumerate(mcu_dir1_files_list):
                    with open(fname, "r") as f1, open(
                        mcu_dir2_files_list[index2], "r"
                    ) as f2:
                        diff = set(f1).symmetric_difference(f2)
                        diff.discard("\n")
                        if not diff or len(diff) == 2:
                            if index2 == 0:
                                for line in diff:
                                    pinout_json_tmp += pinout_json_regex.findall(line)
                            elif index2 == 2:
                                for line in diff:
                                    variant_exp_tmp += variant_regex.findall(line)
                            continue
                        else:
                            # Not the same directory compare with the next one
                            index += 1
                            break
                # All files compared and matched
                else:
                    # Concatenate lists without duplicate
                    uniq_pinout_json = set(pinout_json_tmp) - set(pinout_json)
                    pinout_json = pinout_json + list(uniq_pinout_json)
                    uniq_variant_exp = set(variant_exp_tmp) - set(variant_exp)
                    variant_exp = variant_exp + list(uniq_variant_exp)
                    # Matched files append to the group list
                    group_mcu_dir.append(mcu_dirs.pop(index))
                    del pinout_json_tmp[:]
                    del variant_exp_tmp[:]
                del mcu_dir2_files_list[:]

            # Merge directories name and contents if needed
            mcu_dir = merge_dir(
                out_temp_path, group_mcu_dir, mcu_family_name, pinout_json, variant_exp
            )
            # Move to variants/ folder
            out_path = out_family_path / mcu_dir.stem
            generic_clock_filepath = out_path / generic_clock_filename
            out_path.mkdir(parents=True, exist_ok=True)
            for fname in mcu_dir.glob("*.*"):
                if (
                    fname.name == generic_clock_filename
                    and generic_clock_filepath.exists()
                ):
                    fname.unlink()
                else:
                    fname.replace(out_path / fname.name)
            # Append updated directory to the list of current series STM32YYxx
            mcu_out_dirs_up.append(out_path)
            del group_mcu_dir[:]
            del mcu_dir1_files_list[:]
        mcu_out_dirs_up.sort()
        new_dirs = set(mcu_out_dirs_up) - set(mcu_out_dirs_ori)
        if new_dirs:
            nb_new = len(new_dirs)
            dir_str = "directories" if nb_new > 1 else "directory"
            print(f"\nNew {dir_str} for {mcu_family_path.name}:\n")
            for d in new_dirs:
                print(f"  - {d.name}")
            print("\n  --> Please, check if it is a new directory or a renamed one.")
        old_dirs = set(mcu_out_dirs_ori) - set(mcu_out_dirs_up)
        if old_dirs:
            nb_old = len(old_dirs)
            dir_str = "Directories" if nb_old > 1 else "Directory"
            print(f"\n{dir_str} not updated for {mcu_family_path.name}:\n")
            for d in old_dirs:
                # Check if ldsript.ld file exists in the folder
                if not (d / "ldscript.ld").exists():
                    deleteFolder(d)
                    print(f"  - {d.name} (deleted)")
                else:
                    print(f"  - {d.name}")
            print("""
  --> For each directory not deleted, it requires manual update as it was renamed:
    - Find new directory name.
    - Move custom boards definition files, if any.
    - Move linker script(s).
    - Copy 'SystemClock_Config(void)' function to the new generic clock config file.
  --> Then remove it and update old path in boards.txt
     (for custom board(s) as well as generic ones).
""")
        del mcu_out_dirs_ori[:]
        del mcu_out_dirs_up[:]


# Config management
def checkConfig():
    global repo_local_path
    if config_filename.is_file():
        try:
            with open(config_filename, "r") as config_file:
                path_config = json.load(config_file)
            if "REPOV2_LOCAL_PATH" not in path_config:
                path_config["REPOV2_LOCAL_PATH"] = str(repo_local_path)
                defaultConfig(config_filename, path_config)
            else:
                conf = path_config["REPOV2_LOCAL_PATH"]
                if conf != "":
                    repo_local_path = Path(conf)
        except IOError:
            print(f"Failed to open {config_filename}")
    else:
        defaultConfig(config_filename, {"REPOV2_LOCAL_PATH": str(repo_local_path)})


# main
tmp_dir = script_path / "variants"
root_dir = script_path.parents[1]
system_path = root_dir / "system"
templates_dir = script_path / "templates"
mcu_family_dir = ""
filtered_series = ""
periph_c_filename = "PeripheralPins.c"
pinvar_h_filename = "PinNamesVar.h"
config_filename = script_path / "update_config.json"
variant_h_filename = "variant_generic.h"
variant_cpp_filename = "variant_generic.cpp"
boards_entry_filename = "boards_entry.txt"
generic_clock_filename = "generic_clock.c"
repo_local_path = script_path / "repo"
nx = "xx"
checkConfig()

# By default, generate for all mcu json pinout files description
parser = argparse.ArgumentParser(
    description=textwrap.dedent(f"""
By default, generates:
 - {periph_c_filename},
 - {pinvar_h_filename},
 - {variant_cpp_filename},
 - {variant_h_filename},
 - {boards_entry_filename}
 - {generic_clock_filename}
for all json pinout files available in supported series.
"""),
    epilog=textwrap.dedent("""\
After files generation, review them carefully and please report any issue to GitHub:
\thttps://github.com/stm32duino/Arduino_Core_STM32/issues
"""),
    formatter_class=RawTextHelpFormatter,
)
group = parser.add_mutually_exclusive_group()
group.add_argument(
    "-l",
    "--list",
    help="list available json pinout files",
    action="store_true",
)

group.add_argument(
    "-s",
    "--series",
    metavar="pattern",
    help="Generate all files for specified STM32 series(s) pattern.",
)
args = parser.parse_args()

# Create the jinja2 environment.
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)

# Get all STM32 series v2 supported by the core
stm32_dict = loadSTM32Series(script_path, False, True)
stm32_list = sorted([f"{stm32}" for stm32 in stm32_dict.keys()])
if args.series:
    useries = args.series.upper()
    if useries not in stm32_list:
        print(f"{useries} is not supported yet by the core.")
        sys.exit(1)
    # Manage only the requested series
    stm32_list = [useries]
if not stm32_list:
    print("No STM32 series found!")
    sys.exit(1)

for series in stm32_list:
    nx = stm32_dict[series]
    dir_pinout = (
        repo_local_path
        / f"STM32Cube{series}"
        / f"stm32{series.lower()}{nx}_dfp"
        / "Descriptors"
        / "pinout"
    )
    # Get all json files
    pinout_dict[series] = sorted(dir_pinout.glob("STM32*_pinout.json"))

if args.list:
    print("Available json pinout files per series:")
    for series, files in pinout_dict.items():
        print(f"{series}:")
        for f in files:
            print(f"  {f.name}")
    quit()

# Clean temporary dir
deleteFolder(tmp_dir)

pl_regex = re.compile(r"([AQ])$")
package_regex = re.compile(r"[\w][\w]([ANPQSXZ])?$")
flash_group_regex = re.compile(r"(.*)\((.*)\)(.*)")
pinregex = r"^(P[A-Z][0-9][0-5]?)"
afnum_regex = re.compile(r"AF(\d+)")
# Parse each json pinout file and generate corresponding files
for series, files in pinout_dict.items():
    mcu_family = f"STM32{series}"
    nx = stm32_dict[series]
    mcu_family_dir = f"{mcu_family}{nx}"
    # Used after removing STM32{series}
    pinout_name_regex = re.compile(
        rf"^STM32{series}(\w|\(\w-\w\))(\w|\(\w-\w\))(\w)(\w|\(\w-\w-?\w?\))(\wx)(.*)_pinout$"
    )
    for mcu_file in files:
        # Multiple refnames per pinout file
        expand_mcu_refname(mcu_file.stem)
        # Get mcu info for each refname
        get_mcu_info()
        # Open input file
        try:
            with open(mcu_file, "r") as pinout_file:
                mcu_pinout = json.load(pinout_file)
        except IOError:
            print(f"Failed to open {mcu_file}")
            continue
        if parse_mcu_pinout() is False:
            continue
        manage_alternate()

        # Add mcu family to the list of directory to aggregate
        if mcu_family not in aggregate_series_list:
            aggregate_series_list.append(mcu_family)

        print(f"Generating files for '{mcu_file.name}'...")

        for mcu_refname in mcu_refnames:
            # Check if the mcu_refname is in the ignored list for the current series
            if (
                series in ignored_mcu_refnames
                and mcu_refname in ignored_mcu_refnames[series]
            ):
                # print(f"Skipping '{mcu_refname}' as it is in the ignored list for {series}.")
                continue
            out_temp_path = tmp_dir / mcu_family_dir / mcu_refname.replace("STM32", "")
            periph_c_filepath = out_temp_path / periph_c_filename
            pinvar_h_filepath = out_temp_path / pinvar_h_filename
            variant_cpp_filepath = out_temp_path / variant_cpp_filename
            variant_h_filepath = out_temp_path / variant_h_filename
            boards_entry_filepath = out_temp_path / boards_entry_filename
            generic_clock_filepath = out_temp_path / generic_clock_filename
            out_temp_path.mkdir(parents=True, exist_ok=True)
            with open(boards_entry_filepath, "w", newline="\n") as boards_entry_file:
                generic_list = print_boards_entry()
            with open(generic_clock_filepath, "w", newline="\n") as generic_clock_file:
                print_general_clock(generic_list)
            with open(periph_c_filepath, "w", newline="\n") as periph_c_file:
                print_peripheral()
            with open(pinvar_h_filepath, "w", newline="\n") as pinvar_h_file:
                alt_syswkup_list = print_pinamevar()
            with open(
                variant_cpp_filepath, "w", newline="\n"
            ) as variant_cpp_file, open(
                variant_h_filepath, "w", newline="\n"
            ) as variant_h_file:
                print_variant(generic_list, alt_syswkup_list)
            del alt_syswkup_list[:]
            del generic_list[:]
            sum_io = len(io_list) + len(alt_list) + len(dualpad_list) + len(remap_list)
        print(f"* Total I/O pins found: {sum_io}")
        print(f"   - {len(io_list)} I/O pins")
        if len(dualpad_list):
            print(f"   - {len(dualpad_list)} dual pad")
        if len(remap_list):
            print(f"   - {len(remap_list)} remap pins")
        print(f"   - {len(alt_list)} ALT I/O pins")

        # for io in io_list:
        #     print(io[0] + ", " + io[1])
        clean_all_lists()

    # Print mcu_refnames for debug
    # print(f"mcu_refnames for {mcu_file.name}: {mcu_refnames}")
    # Print mcu_info for debug
    # print(f"mcu_info for {mcu_file.name}: {mcu_info}")
    # Print ignored mcu_refnames for debug
    # print(f"Ignored mcu_refnames: {ignored_mcu_refnames}")

print("Aggregating all generated files...")
pinout_json_regex = re.compile(r"\S+\.json")
variant_regex = re.compile(r"defined\(ARDUINO_GENERIC_[^\s&|]*\)")
update_regex = re.compile(r"defined\(ARDUINO_GENERIC_.+\)")
board_entry_regex = re.compile(r"(Gen.+\..+variant=STM32[^x]+xx?/)\S+")
#                              P     T      E
mcu_PE_regex = re.compile(r"([\w])([\w])([AGJNPQSUXZ])?$")
aggregate_dir()

# Clean temporary dir
deleteFolder(tmp_dir)
