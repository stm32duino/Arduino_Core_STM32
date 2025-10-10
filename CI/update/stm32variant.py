import argparse
import json
import re
import subprocess
import sys
import textwrap
from argparse import RawTextHelpFormatter
from collections import Counter
from collections import OrderedDict
from itertools import groupby
from jinja2 import Environment, FileSystemLoader
from pathlib import Path
from xml.dom.minidom import parse, Node

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils import (
    defaultConfig,
    deleteFolder,
    execute_cmd,
    getRepoBranchName,
    genSTM32Dict,
)

stm32_list = []  # series
stm32_dict = OrderedDict()  # key: serie, value: nx
ignored_stm32_list = []  # series
aggregate_serie_list = []  # series
mcu_list = []  # 'name'
io_list = []  # 'PIN','name'
alt_list = []  # 'PIN','name'
dualpad_list = []  # 'PIN','name'
remap_list = []  # 'PIN','name'
adclist = []  # ['PIN','name','ADCSignal']
daclist = []  # ['PIN','name','DACSignal']
i2cscl_list = []  # ['PIN','name','I2CSCLSignal', ['af']]
i2csda_list = []  # ['PIN','name','I2CSDASignal', ['af']
i3cscl_list = []  # ['PIN','name','I3CSCLSignal', ['af']]
i3csda_list = []  # ['PIN','name','I3CSDASignal', ['af']
tim_list = []  # ['PIN','name','TIMSignal', ['af']]
uarttx_list = []  # ['PIN','name','UARTtx', ['af']]
uartrx_list = []  # ['PIN','name','UARTrx', ['af']]
uartcts_list = []  # ['PIN','name','UARTcts', ['af']]
uartrts_list = []  # ['PIN','name','UARTrts', ['af']]
spimosi_list = []  # ['PIN','name','SPIMOSI', 'sort name', ['af']]
spimiso_list = []  # ['PIN','name','SPIMISO', 'sort name', ['af']]
spissel_list = []  # ['PIN','name','SPISSEL', 'sort name', ['af']]
spisclk_list = []  # ['PIN','name','SPISCLK', 'sort name', ['af']]
cantd_list = []  # ['PIN','name','CANTD', ['af']]
canrd_list = []  # ['PIN','name','CANRD', ['af']]
eth_list = []  # ['PIN','name','ETH', ['af']]
xspidata0_list = []  # ['PIN','name','XSPIDATA0', ['af']]
xspidata1_list = []  # ['PIN','name','XSPIDATA1', ['af']]
xspidata2_list = []  # ['PIN','name','XSPIDATA2', ['af']]
xspidata3_list = []  # ['PIN','name','XSPIDATA3', ['af']]
ospidata4_list = []  # ['PIN','name','OSPIDATA4', ['af']]
ospidata5_list = []  # ['PIN','name','OSPIDATA5', ['af']]
ospidata6_list = []  # ['PIN','name','OSPIDATA6', ['af']]
ospidata7_list = []  # ['PIN','name','OSPIDATA7', ['af']]
xspisclk_list = []  # ['PIN','name','XSPISCLK', ['af']]
xspissel_list = []  # ['PIN','name','XSPISSEL', ['af']]
syswkup_list = []  # ['PIN','name','SYSWKUP']
usb_list = []  # ['PIN','name','USB', ['af']]
usb_otgfs_list = []  # ['PIN','name','USB', ['af']]
usb_otghs_list = []  # ['PIN','name','USB', ['af']]
sdxcmd_list = []  # ['PIN','name','SDX_CMD', ['af']]
sdxck_list = []  # ['PIN','name','SDX_CK', ['af']]
sdxd0_list = []  # ['PIN','name','SDX_D0', ['af']]
sdxd1_list = []  # ['PIN','name','SDX_D1', ['af']]
sdxd2_list = []  # ['PIN','name','SDX_D2', ['af']]
sdxd3_list = []  # ['PIN','name','SDX_D3', ['af']]
sdxd4_list = []  # ['PIN','name','SDX_D4', ['af']]
sdxd5_list = []  # ['PIN','name','SDX_D5', ['af']]
sdxd6_list = []  # ['PIN','name','SDX_D6', ['af']]
sdxd7_list = []  # ['PIN','name','SDX_D7', ['af']]
sdmmcckin_list = []  # ['PIN','name','SDMMC_CKIN', ['af']]
sdmmccdir_list = []  # ['PIN','name','SDMMC_CDIR', ['af']]
sdmmcd0dir_list = []  # ['PIN','name','SDMMC_D0DIR', ['af']]
sdmmcd123dir_list = []  # ['PIN','name','SDMMC_D123DIR', ['af']]

# IP information
gpiofile = ""
tim_inst_list = []  # TIMx instance
usb_inst = {"usb": "", "otg_fs": "", "otg_hs": ""}
mcu_family = ""
mcu_refname = ""
mcu_core = []
mcu_flash = []
mcu_ram = []
legacy_hal = {
    "CAN": ["F0", "F1", "F2", "F3", "F4", "F7", "L4"],
    "ETH": ["F4", "F7", "H7"],
}
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


# mcu file parsing
def parse_mcu_file():
    global gpiofile
    global mcu_family
    global mcu_refname
    global mcu_core

    tim_regex = r"^(TIM\d+)$"
    usb_regex = r"^(USB(?!PD|_HOST|_DEVICE|X).*)$"
    gpiofile = ""
    del tim_inst_list[:]
    del mcu_ram[:]
    del mcu_flash[:]
    del mcu_core[:]
    usb_inst["usb"] = ""
    usb_inst["otg_fs"] = ""
    usb_inst["otg_hs"] = ""

    mcu_node = xml_mcu.getElementsByTagName("Mcu")[0]
    mcu_family = mcu_node.attributes["Family"].value
    # Check if FwLibrary is present in the attributes
    if "FwLibrary" in mcu_node.attributes:
        mcu_family = mcu_node.attributes["FwLibrary"].value
        # split using '_' and kept the lasy part
        mcu_family = f"STM32{mcu_family.split('_')[-1]}"

    if mcu_family.endswith("+"):
        mcu_family = mcu_family[:-1]

    # Generate only for specified pattern series or supported one
    # Check if mcu_family is supported by the core
    if (
        mcu_family not in stm32_list
        or args.serie
        and serie_pattern.search(mcu_family) is None
    ):
        if mcu_family not in ignored_stm32_list and mcu_family not in stm32_list:
            ignored_stm32_list.append(mcu_family)
        xml_mcu.unlink()
        return False

    mcu_refname = mcu_node.attributes["RefName"].value
    core_node = mcu_node.getElementsByTagName("Core")
    for f in core_node:
        # Strip last non digit characters and extract the number
        arm_core_ = re.sub(r"^A[Rr][Mm] Cortex-", "", f.firstChild.nodeValue).strip("+")
        mcu_core_family = re.sub(r"\d+$", "", arm_core_)
        mcu_core_digit = int(re.sub(r"^[ARM]", "", arm_core_))
        mcu_core.append([mcu_core_family, mcu_core_digit])

    ram_node = mcu_node.getElementsByTagName("Ram")
    for f in ram_node:
        mcu_ram.append(int(f.firstChild.nodeValue) * 1024)
    flash_node = mcu_node.getElementsByTagName("Flash")
    for f in flash_node:
        mcu_flash.append(int(f.firstChild.nodeValue) * 1024)

    itemlist = xml_mcu.getElementsByTagName("IP")
    for s in itemlist:
        inst = re.match(tim_regex, s.attributes["InstanceName"].value)
        if inst:
            # Collect all TIMx instance
            tim_inst_list.append(inst.group(1))
        else:
            inst = re.match(usb_regex, s.attributes["InstanceName"].value)
            if inst:
                if "OTG" in inst.group(1):
                    if "FS" in inst.group(1):
                        usb_inst["otg_fs"] = inst.group(1)
                    else:
                        if inst.group(1).endswith("HS1"):
                            usb_inst["otg_hs"] = inst.group(1)[:-1]
                        else:
                            usb_inst["otg_hs"] = inst.group(1)
                else:
                    usb_inst["usb"] = inst.group(1)
            else:
                if gpiofile == "" and s.attributes["Name"].value == "GPIO":
                    gpiofile = s.attributes["Version"].value
    return True


def get_gpio_af_num(pintofind, iptofind):
    if "STM32F1" in mcu_family:
        return get_gpio_af_numF1(pintofind, iptofind)
    # DBG print ('pin to find ' + pintofind)
    i = 0
    mygpioaf = ""
    for n in xml_gpio.documentElement.childNodes:
        i += 1
        j = 0
        if n.nodeType != Node.ELEMENT_NODE:
            continue
        for firstlevel in n.attributes.items():
            # if 'PB7' in firstlevel:
            if pintofind != firstlevel[1]:
                continue
            # DBG print (i , firstlevel)
            # n = pin node found
            for m in n.childNodes:
                j += 1
                k = 0
                if m.nodeType != Node.ELEMENT_NODE:
                    continue
                for secondlevel in m.attributes.items():
                    k += 1
                    # if 'I2C1_SDA' in secondlevel:
                    if iptofind not in secondlevel:
                        continue
                    # DBG print (i, j,  m.attributes.items())
                    # m = IP node found
                    for p in m.childNodes:
                        if p.nodeType != Node.ELEMENT_NODE:
                            continue
                        # p node of 'Specific parameter'
                        # DBG print (i,j,k,p.attributes.items())
                        for myc in p.childNodes:
                            # DBG print (myc)
                            if myc.nodeType != Node.ELEMENT_NODE:
                                continue
                            # myc = node of ALTERNATE
                            for mygpioaflist in myc.childNodes:
                                if mygpioaflist.data not in mygpioaf:
                                    if mygpioaf != "":
                                        mygpioaf += " "
                                    mygpioaf += mygpioaflist.data
                                # print (mygpioaf)
    if mygpioaf == "":
        mygpioaf = "GPIO_AF_NONE"
    return mygpioaf


def get_gpio_af_numF1_default(pintofind, iptofind):
    # Default AFIO to disable some remapping, used when:
    # <RemapBlock Name="TIM2_REMAP0" DefaultRemap="true" />
    # is present in xml file
    default_afio_f1 = {
        "PA0": {"TIM2": "AFIO_TIM2_DISABLE", "USART2": "AFIO_USART2_DISABLE"},
        "PA1": {"TIM2": "AFIO_TIM2_DISABLE", "USART2": "AFIO_USART2_DISABLE"},
        "PA2": {
            "TIM2": "AFIO_TIM2_DISABLE",
            "TIM9": "AFIO_TIM9_DISABLE",
            "TIM15": "AFIO_TIM15_DISABLE",
            "USART2": "AFIO_USART2_DISABLE",
        },
        "PA3": {
            "TIM2": "AFIO_TIM2_DISABLE",
            "TIM9": "AFIO_TIM9_DISABLE",
            "TIM15": "AFIO_TIM15_DISABLE",
            "USART2": "AFIO_USART2_DISABLE",
        },
        "PA4": {"SPI1": "AFIO_SPI1_DISABLE", "USART2": "AFIO_USART2_DISABLE"},
        "PA5": {"SPI1": "AFIO_SPI1_DISABLE"},
        "PA6": {
            "SPI1": "AFIO_SPI1_DISABLE",
            "TIM3": "AFIO_TIM3_DISABLE",
            "TIM13": "AFIO_TIM13_DISABLE",
        },
        "PA7": {
            "ETH": "AFIO_ETH_DISABLE",
            "SPI1": "AFIO_SPI1_DISABLE",
            "TIM3": "AFIO_TIM3_DISABLE",
            "TIM14": "AFIO_TIM14_DISABLE",
        },
        "PA8": {"TIM1": "AFIO_TIM1_DISABLE"},
        "PA9": {"TIM1": "AFIO_TIM1_DISABLE", "USART1": "AFIO_USART1_DISABLE"},
        "PA10": {"TIM1": "AFIO_TIM1_DISABLE", "USART1": "AFIO_USART1_DISABLE"},
        "PA11": {"CAN1": "AFIO_CAN1_1", "TIM1": "AFIO_TIM1_DISABLE"},
        "PA12": {"CAN1": "AFIO_CAN1_1", "TIM1": "AFIO_TIM1_DISABLE"},
        "PA15": {
            "SPI3": (
                "AFIO_SPI3_DISABLE"
                if re.match("STM32F10[57]", mcu_refname)
                else "AFIO_NONE"
            )
        },
        "PB0": {"ETH": "AFIO_ETH_DISABLE", "TIM3": "AFIO_TIM3_DISABLE"},
        "PB1": {"ETH": "AFIO_ETH_DISABLE", "TIM3": "AFIO_TIM3_DISABLE"},
        "PB3": {
            "SPI3": (
                "AFIO_SPI3_DISABLE"
                if re.match("STM32F10[57]", mcu_refname)
                else "AFIO_NONE"
            )
        },
        "PB4": {
            "SPI3": (
                "AFIO_SPI3_DISABLE"
                if re.match("STM32F10[57]", mcu_refname)
                else "AFIO_NONE"
            )
        },
        "PB5": {
            "SPI3": (
                "AFIO_SPI3_DISABLE"
                if re.match("STM32F10[57]", mcu_refname)
                else "AFIO_NONE"
            )
        },
        "PB6": {"I2C1": "AFIO_I2C1_DISABLE", "TIM4": "AFIO_TIM4_DISABLE"},
        "PB7": {"I2C1": "AFIO_I2C1_DISABLE", "TIM4": "AFIO_TIM4_DISABLE"},
        "PB8": {
            "TIM4": "AFIO_TIM4_DISABLE",
            "TIM10": "AFIO_TIM10_DISABLE",
            "TIM16": "AFIO_TIM16_DISABLE",
        },
        "PB9": {
            "TIM4": "AFIO_TIM4_DISABLE",
            "TIM11": "AFIO_TIM11_DISABLE",
            "TIM17": "AFIO_TIM17_DISABLE",
        },
        "PB12": {
            "CAN2": "AFIO_CAN2_DISABLE",
            "TIM1": "AFIO_TIM1_DISABLE",
            "USART3": "AFIO_USART3_DISABLE",
        },
        "PB13": {
            "CAN2": "AFIO_CAN2_DISABLE",
            "TIM1": "AFIO_TIM1_DISABLE",
            "USART3": "AFIO_USART3_DISABLE",
        },
        "PB14": {"TIM1": "AFIO_TIM1_DISABLE"},
        "PB15": {"TIM1": "AFIO_TIM1_DISABLE"},
        "PC4": {"ETH": "AFIO_ETH_DISABLE", "TIM12": "AFIO_TIM12_DISABLE"},
        "PC5": {"ETH": "AFIO_ETH_DISABLE", "TIM12": "AFIO_TIM12_DISABLE"},
        "PC8": {"TIM13": "AFIO_TIM13_DISABLE"},
        "PC9": {"TIM14": "AFIO_TIM14_DISABLE"},
        "PC10": {"USART3": "AFIO_USART3_DISABLE"},
        "PC11": {"USART3": "AFIO_USART3_DISABLE"},
        "PC12": {"USART3": "AFIO_USART3_DISABLE"},
    }

    # return "AFIO_" + iptofind .split("_")[0] + "_DISABLE"
    ip = iptofind.split("_")[0]
    afio_default = "AFIO_NONE"
    if pintofind in default_afio_f1 and ip in default_afio_f1[pintofind]:
        afio_default = default_afio_f1[pintofind][ip]
    return afio_default


def get_gpio_af_numF1(pintofind, iptofind):
    #  print ('pin to find ' + pintofind + ' ip to find ' + iptofind)
    i = 0
    mygpioaf = ""
    for n in xml_gpio.documentElement.childNodes:
        i += 1
        j = 0
        if n.nodeType != Node.ELEMENT_NODE:
            continue
        for firstlevel in n.attributes.items():
            # print ('firstlevel ' , firstlevel)
            #                if 'PB7' in firstlevel:
            if pintofind != firstlevel[1]:
                continue
            # print ('firstlevel ' , i , firstlevel)
            # n = pin node found
            for m in n.childNodes:
                j += 1
                k = 0
                if m.nodeType != Node.ELEMENT_NODE:
                    continue
                for secondlevel in m.attributes.items():
                    # print ('secondlevel ' , i, j, k , secondlevel)
                    k += 1
                    # if 'I2C1_SDA' in secondlevel:
                    if iptofind not in secondlevel:
                        continue
                    # m = IP node found
                    # print (i, j,  m.attributes.items())
                    for p in m.childNodes:
                        # p node 'RemapBlock'
                        if (
                            p.nodeType == Node.ELEMENT_NODE
                            and p.hasChildNodes() is False
                        ):
                            mygpioaf += (
                                " " if mygpioaf != "" else ""
                            ) + get_gpio_af_numF1_default(pintofind, iptofind)
                        else:
                            for s in p.childNodes:
                                if s.nodeType != Node.ELEMENT_NODE:
                                    continue
                                # s node 'Specific parameter'
                                # print (i,j,k,p.attributes.items())
                                for myc in s.childNodes:
                                    # DBG print (myc)
                                    if myc.nodeType != Node.ELEMENT_NODE:
                                        continue
                                    # myc = AF value
                                    for mygpioaflist in myc.childNodes:
                                        if mygpioaf != "":
                                            mygpioaf += " "
                                        mygpioaf += mygpioaflist.data.replace(
                                            "__HAL_", ""
                                        ).replace("_REMAP", "")
                                        # print mygpioaf
    if mygpioaf == "":
        mygpioaf = get_gpio_af_numF1_default(pintofind, iptofind)
    return mygpioaf


# Storage
# Store pin I/O
def store_pin(pin, name, dest_list):
    if pin in [p[0] for p in dest_list]:
        return
    p = [pin, name]
    if p not in dest_list:
        dest_list.append(p)


# Store ADC list
def store_adc(pin, name, signal):
    # Skip Negative input analog channels (INN, INM)
    # Differential is currently not managed
    # And skip PGA
    if "IN" in signal:
        skip_signal = re.search(r"IN[N|M]|PGA", signal)
        if not skip_signal:
            adclist.append([pin, name, signal])


# Store DAC list
def store_dac(pin, name, signal):
    daclist.append([pin, name, signal])


# Store I2C list
def store_i2c(pin, name, signal):
    # is it SDA or SCL ?
    if "_SCL" in signal:
        i2cscl_list.append([pin, name, signal])
    if "_SDA" in signal:
        i2csda_list.append([pin, name, signal])


# Store I3C list
def store_i3c(pin, name, signal):
    # is it SDA or SCL ?
    if "_SCL" in signal:
        i3cscl_list.append([pin, name, signal])
    if "_SDA" in signal:
        i3csda_list.append([pin, name, signal])


# Store timers
def store_tim(pin, name, signal):
    if "_CH" in signal:
        tim_list.append([pin, name, signal])


# Store Uart pins
def store_uart(pin, name, signal):
    if "_TX" in signal:
        uarttx_list.append([pin, name, signal])
    if "_RX" in signal:
        uartrx_list.append([pin, name, signal])
    if "_CTS" in signal:
        uartcts_list.append([pin, name, signal])
    if "_RTS" in signal:
        uartrts_list.append([pin, name, signal])


# Store SPI pins
def store_spi(pin, name, signal):
    if re.search("[-_]MISO", signal):
        spimiso_list.append([pin, name, signal, signal.removeprefix("DEBUG_")])
    if re.search("[-_]MOSI", signal):
        spimosi_list.append([pin, name, signal, signal.removeprefix("DEBUG_")])
    if re.search("[-_]SCK", signal):
        spisclk_list.append([pin, name, signal, signal.removeprefix("DEBUG_")])
    if re.search("[-_]NSS", signal):
        spissel_list.append([pin, name, signal, signal.removeprefix("DEBUG_")])


# Store CAN pins
def store_can(pin, name, signal):
    if "_RX" in signal:
        canrd_list.append([pin, name, signal])
    if "_TX" in signal:
        cantd_list.append([pin, name, signal])


# Store ETH list
def store_eth(pin, name, signal):
    eth_list.append([pin, name, signal])


# Store O/QSPI pins
def store_xspi(pin, name, signal):
    if "_IO0" in signal:
        xspidata0_list.append([pin, name, signal])
    elif "_IO1" in signal:
        xspidata1_list.append([pin, name, signal])
    elif "_IO2" in signal:
        xspidata2_list.append([pin, name, signal])
    elif "_IO3" in signal:
        xspidata3_list.append([pin, name, signal])
    elif "_IO4" in signal:
        ospidata4_list.append([pin, name, signal])
    elif "_IO5" in signal:
        ospidata5_list.append([pin, name, signal])
    elif "_IO6" in signal:
        ospidata6_list.append([pin, name, signal])
    elif "_IO7" in signal:
        ospidata7_list.append([pin, name, signal])
    elif "_CLK" in signal:
        xspisclk_list.append([pin, name, signal])
    elif "_NCS" in signal:
        xspissel_list.append([pin, name, signal])


# Store SYS pins
def store_sys(pin, name, signal):
    if "_WKUP" in signal and not any(pin.replace("_C", "") in i for i in syswkup_list):
        signal = signal.replace("PWR", "SYS")
        syswkup_list.append([pin, name, signal])


# Store USB pins
def store_usb(pin, name, signal):
    if "OTG" not in signal:
        usb_list.append([pin, name, signal])
    if signal.startswith("USB_OTG_FS"):
        usb_otgfs_list.append([pin, name, signal])
    if signal.startswith("USB_OTG_HS"):
        usb_otghs_list.append([pin, name, signal])


# Store SD(IO/MMC) pins
def store_sdx(pin, name, signal):
    if signal.endswith("_D0"):
        sdxd0_list.append([pin, name, signal])
    elif signal.endswith("_D1"):
        sdxd1_list.append([pin, name, signal])
    elif signal.endswith("_D2"):
        sdxd2_list.append([pin, name, signal])
    elif signal.endswith("_D3"):
        sdxd3_list.append([pin, name, signal])
    elif signal.endswith("_D4"):
        sdxd4_list.append([pin, name, signal])
    elif signal.endswith("_D5"):
        sdxd5_list.append([pin, name, signal])
    elif signal.endswith("_D6"):
        sdxd6_list.append([pin, name, signal])
    elif signal.endswith("_D7"):
        sdxd7_list.append([pin, name, signal])
    elif signal.endswith("_CMD"):
        sdxcmd_list.append([pin, name, signal])
    elif signal.endswith("_CK"):
        sdxck_list.append([pin, name, signal])
    elif signal.endswith("_CKIN"):
        sdmmcckin_list.append([pin, name, signal])
    elif signal.endswith("_CDIR"):
        sdmmccdir_list.append([pin, name, signal])
    elif signal.endswith("_D0DIR"):
        sdmmcd0dir_list.append([pin, name, signal])
    elif signal.endswith("_D123DIR"):
        sdmmcd123dir_list.append([pin, name, signal])


# PeripheralPins.cpp generation
def adc_pinmap():
    adc_pins_list = []
    winst = []
    wpin = []
    # For STM32L47xxx/48xxx, it is necessary to configure
    # the GPIOx_ASCR register
    if re.match("STM32L4[78]+", mcu_refname):
        default_mode = "STM_MODE_ANALOG_ADC_CONTROL"
    else:
        default_mode = "STM_MODE_ANALOG"
    for p in adclist:
        # inst
        a = p[2].split("_")
        inst = a[0]
        if not inst[-1].isdigit():
            inst += "1"  # single ADC for this product
        winst.append(len(inst))
        wpin.append(len(p[0]))
        negative = re.search(r"IN[N|M]", a[1])
        if negative:
            # Negative input analog channels
            inv = "1"
        else:
            # Positive input analog channels
            inv = "0"
        # chan
        chan = re.sub(r"^V?IN[N|P|M]?|\D*$", "", a[1])
        if a[1].endswith("b"):
            mode = "STM_MODE_ANALOG_ADC_CHANNEL_BANK_B"
        else:
            mode = default_mode
        adc_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": "GPIO_NOPULL",
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
        # 2nd element is the DAC signal
        if p[2][3] == "_":  # 1 DAC in this chip
            inst = "1"
            chan = p[2][7]
        else:
            inst = p[2][3]
            chan = p[2][8]
        winst.append(len(inst))
        wpin.append(len(p[0]))
        dac_pins_list.append(
            {
                "pin": p[0],
                "inst": "DAC" + inst,
                "mode": mode,
                "pull": "GPIO_NOPULL",
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
        winst=max(winst) + 4,
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
        # 2nd element is the I2C XXX signal
        b = p[2].split("_")[0]
        inst = b[: len(b) - 1] + b[len(b) - 1]
        winst.append(len(inst))
        wpin.append(len(p[0]))
        i2c_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": "GPIO_NOPULL",
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
    mode = "STM_MODE_AF_OD"
    if lst == i3csda_list:
        aname = "I3C_SDA"
    else:
        aname = "I3C_SCL"
    for p in lst:
        # 2nd element is the I3C XXX signal
        b = p[2].split("_")[0]
        inst = b[: len(b) - 1] + b[len(b) - 1]
        winst.append(len(inst))
        wpin.append(len(p[0]))
        i3c_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": mode,
                "pull": "GPIO_NOPULL",
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
                "pull": "GPIO_PULLUP",
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
                "pull": "GPIO_PULLUP",
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
                "pull": "GPIO_PULLUP" if inst != "SUBGHZSPI" else "GPIO_NOPULL",
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
                "pull": "GPIO_NOPULL",
                "af": p[3],
            }
        )
    return dict(
        name=name,
        hal=(
            ["CAN", "CAN_LEGACY"]
            if name != "FDCAN" and any(mcu in mcu_family for mcu in legacy_hal["CAN"])
            else name
        ),
        aname=aname,
        data="",
        wpin=max(wpin) + 1,
        winst=max(winst) + 1,
        list=can_pins_list,
    )


def eth_pinmap():
    eth_pins_list = []
    wpin = [0]
    inst = "ETH"
    for p in eth_list:
        # Note: Some pins are duplicated with only a different signal
        # Now considered as an ALTX pins even ifsame AF
        wpin.append(len(p[0]))
        eth_pins_list.append(
            {
                "pin": p[0],
                "inst": inst,
                "mode": "STM_MODE_AF_PP",
                "pull": "GPIO_PULLUP",
                "af": p[3],
                "cmt": p[2],
            }
        )
    return dict(
        name="ETHERNET",
        hal=(
            ["ETH", "ETH_LEGACY"]
            if any(mcu in mcu_family for mcu in legacy_hal["ETH"])
            else "ETH"
        ),
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
                "pull": "GPIO_PULLUP",
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
    use_hs_in_fs = False
    nb_loop = 1

    if lst == usb_otgfs_list:
        inst = usb_inst["otg_fs"]
    elif lst == usb_otghs_list:
        inst = usb_inst["otg_hs"]
        nb_loop = 2
    else:
        inst = usb_inst["usb"]
    for nb in range(nb_loop):
        for p in lst:
            hsinfs = 0
            if lst == usb_otghs_list:
                hsinfs = 3
                if nb == 0:
                    if "ULPI" in p[2]:
                        continue
                    elif not use_hs_in_fs:
                        hsinfs = 1
                        use_hs_in_fs = True
                else:
                    if "ULPI" not in p[2]:
                        continue
                    elif use_hs_in_fs:
                        hsinfs = 2
                        use_hs_in_fs = False

            # 2nd element is the USB_XXXX signal
            if not p[2].startswith("USB_D") and "VBUS" not in p[2]:
                if "ID" not in p[2]:
                    mode = "STM_MODE_AF_PP"
                    pull = "GPIO_PULLUP"
                else:
                    # ID pin: AF_PP + PULLUP
                    mode = "STM_MODE_AF_OD"
                    pull = "GPIO_PULLUP"
            else:
                # USB_DM/DP and VBUS: INPUT/AF + NOPULL
                if p[2].startswith("USB_D") and "NONE" not in p[3]:
                    mode = "STM_MODE_AF_PP"
                else:
                    mode = "STM_MODE_INPUT"
                pull = "GPIO_NOPULL"
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
            pull = "GPIO_NOPULL"
        else:
            pull = "GPIO_PULLUP"
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
            mcu_file=mcu_file.name,
            db_release=db_release,
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
        )
    )


# PinNamesVar.h generation
def manage_syswkup():
    if len(syswkup_list) != 0:
        # Find the max range of SYS_WKUP.
        # Ensure it is compatible with the current maximum range
        # used by STM32LowPower.
        max_range = syswkup_list[-1][2].replace("SYS_WKUP", "")
        max_range = int(max_range) if max_range else 8
        # F446 start from 0
        base_index = 1
        if syswkup_list[0][2].replace("SYS_WKUP", "") == "0":
            base_index = 0
            max_range += 1
        # Ensure the max_range is at least 8
        # as some mcu PWR_WAKEUP_PINx while not SYS_WKUPx
        if max_range < 8:
            max_range = 8
        syswkup_pins_list = [[] for _ in range(max_range)]
        for p in syswkup_list:
            num = p[2].replace("SYS_WKUP", "")
            num = int(num) if num else 1
            if base_index == 1:
                num -= 1
                cmt = ""
            else:
                cmt = f" /* {p[2]} */"
            syswkup_pins_list[num].append([p[0], cmt])
    else:
        syswkup_pins_list = []
    return syswkup_pins_list


def print_pinamevar():
    # First check core version and search PWR_WAKEUP_*
    syswkup_type = "PIN"
    if "STM32WB0" in mcu_family:
        syswkup_type = "PINNAME"
    if mcu_core[0][1] == 33:
        # Search in stm32{series}xx_hal_pwr.h WR_WAKEUP_
        pwr_header_file_path = (
            system_path
            / "Drivers"
            / f"{mcu_family}{nx}_HAL_Driver"
            / "Inc"
            / f"stm32{mcu_family.replace('STM32', '').lower()}{nx}_hal_pwr.h"
        )
        if not (pwr_header_file_path).exists():
            print(f"Error: {pwr_header_file_path} not found!")
            exit(1)
        else:
            with open(pwr_header_file_path, "r") as pwr_header_file:
                for line in pwr_header_file:
                    if "PWR_WAKEUP_LINE" in line:
                        syswkup_type = "LINE"
                        break

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
        mosi_inst = mosi[2].split("_", 1)[0]
        for miso in spimiso_list:
            miso_inst = miso[2].split("_", 1)[0]
            if mosi_inst == miso_inst:
                for sck in spisclk_list:
                    sck_inst = sck[2].split("_", 1)[0]
                    if mosi_inst == sck_inst:
                        miso_pin = miso[0].replace("_", "", 1)
                        mosi_pin = mosi[0].replace("_", "", 1)
                        sck_pin = sck[0].replace("_", "", 1)
                        break
                else:
                    continue
                break
        else:
            continue

        # Try to find hw ssel
        for ss in spissel_list:
            ss_inst = ss[2].split("_", 1)[0]
            if mosi_inst == ss_inst:
                if ss_pin == "PNUM_NOT_DEFINED":
                    ss_pin = ss[0].replace("_", "", 1)
                elif ss1_pin == "PNUM_NOT_DEFINED":
                    ss1_pin = ss[0].replace("_", "", 1)
                elif ss2_pin == "PNUM_NOT_DEFINED":
                    ss2_pin = ss[0].replace("_", "", 1)
                elif ss3_pin == "PNUM_NOT_DEFINED":
                    ss3_pin = ss[0].replace("_", "", 1)
                    break
        break
    else:
        print("No SPI found!")
    return dict(
        ss=ss_pin,
        ss1=ss1_pin,
        ss2=ss2_pin,
        ss3=ss3_pin,
        mosi=mosi_pin,
        miso=miso_pin,
        sck=sck_pin,
    )


def i2c_pins_variant():
    sda_pin = scl_pin = "PNUM_NOT_DEFINED"
    # Iterate to find match instance if any
    for sda in i2csda_list:
        sda_inst = sda[2].split("_", 1)[0]
        for scl in i2cscl_list:
            scl_inst = scl[2].split("_", 1)[0]
            if sda_inst == scl_inst:
                sda_pin = sda[0].replace("_", "", 1)
                scl_pin = scl[0].replace("_", "", 1)
                break
        else:
            continue
        break
    else:
        print("No I2C found!")
    return dict(sda=sda_pin, scl=scl_pin)


def serial_pins_variant():
    # Manage (LP)U(S)ART pins
    if uarttx_list:
        # Default if no rx pin
        serialtx_pin = uarttx_list[0][0].replace("_", "")
        serial_inst = uarttx_list[0][2].split("_", 1)[0]
        # Half duplex
        serialrx_pin = serialtx_pin
        if uartrx_list:
            # Iterate to find match instance if any
            for uarttx in uarttx_list:
                serialtx_inst = uarttx[2].split("_", 1)[0]
                for uartrx in uartrx_list:
                    serialrx_inst = uartrx[2].split("_", 1)[0]
                    if serialtx_inst == serialrx_inst:
                        serialtx_pin = uarttx[0].replace("_", "", 1)
                        serialrx_pin = uartrx[0].replace("_", "", 1)
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
    return dict(instance=serialnum, rx=serialrx_pin, tx=serialtx_pin)


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


def alias_definition():
    # alias for STM32WL
    alias_list = []
    if mcu_family == "STM32WL":
        mosi = [
            mosi[0].replace("_", "", 1)
            for mosi in spimosi_list
            if "SUBGHZSPI" in mosi[2]
        ]
        miso = [
            miso[0].replace("_", "", 1)
            for miso in spimiso_list
            if "SUBGHZSPI" in miso[2]
        ]
        sck = [
            sck[0].replace("_", "", 1) for sck in spisclk_list if "SUBGHZSPI" in sck[2]
        ]
        ssel = [
            ssel[0].replace("_", "", 1)
            for ssel in spissel_list
            if "SUBGHZSPI" in ssel[2]
        ]
        if mosi and miso and sck and ssel:
            alias_list.append(("DEBUG_SUBGHZSPI_MOSI", mosi[0]))
            alias_list.append(("DEBUG_SUBGHZSPI_MISO", miso[0]))
            alias_list.append(("DEBUG_SUBGHZSPI_SCLK", sck[0]))
            alias_list.append(("DEBUG_SUBGHZSPI_SS", ssel[0]))
    return alias_list


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

    # Serial definition
    serial = serial_pins_variant()

    # Timers definition
    timer = timer_variant()

    # Alias to ease some usage
    alias_list = alias_definition()

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
    if xspidata0_list:
        if "OCTOSPI" in xspidata0_list[0][2]:
            hal_modules_list.append("OSPI")
        else:
            hal_modules_list.append("QSPI")
    if sdxcmd_list:
        hal_modules_list.append("SD")

    variant_h_file.write(
        variant_h_template.render(
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
            timer=timer,
            serial=serial,
            hal_modules_list=hal_modules_list,
            alias_list=alias_list,
            sdmmcNA_list=sdmmcNA_list,
        )
    )

    variant_cpp_file.write(
        variant_cpp_template.render(
            generic_list=generic_list,
            pinnames_list=pinnames_list,
            analog_pins_list=analog_pins_list,
        )
    )


def search_product_line(valueline: str, extra: str) -> str:
    product_line = ""
    product_line_list = product_line_dict[mcu_family]
    if not valueline.startswith("STM32MP1"):
        for idx_pline, pline in enumerate(product_line_list):
            vline = valueline
            product_line = pline
            if vline.startswith("STM32WB0") or vline.startswith("STM32WL3"):
                pline = pline + "xx"
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
    else:
        # previous
        # Unfortunately, MP1 does not follows the same naming rules
        for pline in product_line_dict[mcu_family]:
            vline = valueline
            product_line = pline
            # Remove the 'x' character from pline and
            # the one at same index in the vline
            while 1:
                idx = pline.find("x")
                if idx > 0:
                    pline = pline.replace("x", "", 1)
                    if "STM32MP15xx" != vline:
                        vline = vline[:idx] + vline[idx + 1 :]
                else:
                    break
            if pline >= vline and pline[:10] == vline[:10]:
                break
        else:
            # In case of CMSIS device does not exist
            product_line = "STM32MP15xx"
    return product_line


def parse_stm32targets():
    global svd_dict
    xml_stm32targets = parse(str(stm32targets_file))
    mcu_nodes = xml_stm32targets.getElementsByTagName("mcu")
    for mcu_node in mcu_nodes:
        mcu_node_name = mcu_node.getElementsByTagName("name")[0].firstChild.data
        cpus_node_name = mcu_node.getElementsByTagName("cpus")
        cpu_node_name = cpus_node_name[0].getElementsByTagName("cpu")
        svd_node = cpu_node_name[0].getElementsByTagName("svd")
        svd_file = svd_node[0].getElementsByTagName("name")[0].firstChild.data
        svd_dict[mcu_node_name] = svd_file
    xml_stm32targets.unlink()


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
            / "Templates"
            / "gcc"
        )
        startup_files = sorted(
            [s.name for s in CMSIS_startup_file_path.glob("startup_*.s")]
        )

        for idx, s in enumerate(startup_files):
            # Remove "startup_" and file extension
            product_line = re.split("_|\\.", s)[1]
            if product_line.startswith("stm32mp15") and not product_line.endswith("xx"):
                product_line += "xx"
            startup_files[idx] = product_line.upper().replace("X", "x")
        product_line_dict[mcu_family] = startup_files

    # Search if several flash size
    # Also used to manage define name (ARDUINO_GENERIC_*)
    subf = flash_group_regex.search(mcu_refname.replace("STM32", ""))
    generic_list = []
    if subf:
        valueline = re.sub(r"\([\s\S]*\)", "x", mcu_refname)
        for index, flash in enumerate(subf.group(2).split("-")):
            if len(mcu_ram) == index:
                mcu_ram.append(mcu_ram[0])
            gen_name = subf.group(1) + flash + subf.group(3)
            generic_list.append(
                {
                    "name": gen_name,
                    "board": gen_name.upper(),
                    "flash": mcu_flash[index],
                    "ram": mcu_ram[index],
                    "svd": search_svdfile(f"STM32{gen_name}"),
                }
            )
        # Search product line for last flash size
        # Keep the AQ if any
        subp = pl_regex.search(subf.group(3))
        product_line = search_product_line(
            "STM32"
            + subf.group(1)
            + subf.group(2).split("-")[-1]
            + package_regex.sub(r"", subf.group(3)),
            subp.group(1) if subp and subp.group(1) is not None else "",
        )
    else:
        valueline = mcu_refname
        generic_list.append(
            {
                "name": mcu_refname.replace("STM32", ""),
                "board": mcu_refname.replace("STM32", "").upper(),
                "flash": mcu_flash[0],
                "ram": mcu_ram[0],
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
    syswkup_list.sort(key=natural_sortkey2)
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


def manage_af_and_alternate():
    add_af(i2cscl_list)
    add_af(i2csda_list)
    add_af(i3cscl_list)
    add_af(i3csda_list)
    add_af(tim_list)
    add_af(uarttx_list)
    add_af(uarttx_list)
    add_af(uartrx_list)
    add_af(uartcts_list)
    add_af(uartrts_list)
    add_af(spimosi_list)
    add_af(spimiso_list)
    add_af(spissel_list)
    add_af(spisclk_list)
    add_af(cantd_list)
    add_af(canrd_list)
    add_af(eth_list)
    add_af(xspidata0_list)
    add_af(xspidata1_list)
    add_af(xspidata2_list)
    add_af(xspidata3_list)
    add_af(ospidata4_list)
    add_af(ospidata5_list)
    add_af(ospidata6_list)
    add_af(ospidata7_list)
    add_af(xspisclk_list)
    add_af(xspissel_list)
    add_af(usb_list)
    add_af(usb_otgfs_list)
    add_af(usb_otghs_list)
    add_af(sdxcmd_list)
    add_af(sdxck_list)
    add_af(sdxd0_list)
    add_af(sdxd1_list)
    add_af(sdxd2_list)
    add_af(sdxd3_list)
    add_af(sdxd4_list)
    add_af(sdxd5_list)
    add_af(sdxd6_list)
    add_af(sdxd7_list)
    add_af(sdmmcckin_list)
    add_af(sdmmccdir_list)
    add_af(sdmmcd0dir_list)
    add_af(sdmmcd123dir_list)

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


def add_af(lst):
    duplicate_pin = []
    for index, p in enumerate(lst):
        result = get_gpio_af_num(p[1], p[2]).split(" ")
        if len(result) > 1:
            for af in result[1:]:
                # Duplicate pin (F1)
                # Shallow copy
                duplicate_pin.append(p.copy())
                duplicate_pin[-1].append(af)
        lst[index].append(result[0])
    if len(duplicate_pin):
        lst.extend(duplicate_pin)


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


def parse_pins():
    print(" * Getting pins per Ips...")
    pinregex = r"^(P[A-Z][0-9][0-5]?[_]?[C]?)|^(ANA[0-9])"
    itemlist = xml_mcu.getElementsByTagName("Pin")
    for s in itemlist:
        m = re.match(pinregex, s.attributes["Name"].value)
        if m:
            if m.group(1) is not None:
                # pin formatted P<port>_<number>: PF_O
                pin = m.group(0)[:2] + "_" + m.group(0)[2:]
            else:
                # pin formatted ANA_<number>: ANA_1
                pin = m.group(0)[:3] + "_" + m.group(0)[3:]
            name = s.attributes["Name"].value.strip()  # full name: "PF0 / OSC_IN"
            if s.attributes["Type"].value in ["I/O", "MonoIO"]:
                if pin.endswith("_C"):
                    store_pin(pin, name, dualpad_list)
                elif (
                    "Variant" in s.attributes
                    and "REMAP" in s.attributes["Variant"].value
                ):
                    pin += "_R"
                    store_pin(pin, name, remap_list)
                else:
                    store_pin(pin, name, io_list)
            else:
                continue
            siglist = s.getElementsByTagName("Signal")
            for a in siglist:
                sig = a.attributes["Name"].value.strip()
                if sig.startswith("ADC"):
                    store_adc(pin, name, sig)
                elif all(["DAC" in sig, "_OUT" in sig]):
                    store_dac(pin, name, sig)
                elif re.match("^I2C", sig) is not None:  # ignore FMPI2C
                    store_i2c(pin, name, sig)
                elif re.match("^I3C", sig) is not None:
                    store_i3c(pin, name, sig)
                elif re.match("^TIM", sig) is not None:  # ignore HRTIM
                    store_tim(pin, name, sig)
                elif re.match("^(LPU|US|U)ART", sig) is not None:
                    store_uart(pin, name, sig)
                elif "SPI" in sig:
                    if "QUADSPI" in sig or "OCTOSPI" in sig:
                        store_xspi(pin, name, sig)
                    else:
                        store_spi(pin, name, sig)
                elif "CAN" in sig:
                    store_can(pin, name, sig)
                elif "ETH" in sig:
                    store_eth(pin, name, sig)
                elif "SYS_" in sig or "PWR_" in sig:
                    store_sys(pin, name, sig)
                elif "USB" in sig:
                    store_usb(pin, name, sig)
                elif re.match("^SD(IO|MMC)", sig) is not None:
                    store_sdx(pin, name, sig)
    del itemlist[:]


def keyflash(x):
    return x[0]


def group_by_flash(group_base_list, glist, index_mcu_base):
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
                print(f"Package of {base_name}, ppe {ppe} info not recognized")
                exit(1)
            else:
                package_list.append(sub.group(1))
                # Assert
                if sub.group(2) != "x":
                    print(
                        f"Package of {base_name}, ppe {ppe} info contains {sub.group(2)} instead of 'x'"
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


def merge_dir(out_temp_path, group_mcu_dir, mcu_family, periph_xml, variant_exp):
    dirname_list = []
    new_mcu_dirname = ""
    # Working mcu directory
    mcu_dir = group_mcu_dir[0]
    # Merge if needed
    if len(group_mcu_dir) != 1:
        # Handle mcu name length dynamically
        # Add num for extra information line, #pin and flash
        index_mcu_base = len(mcu_family.name.removeprefix("STM32").removesuffix(nx)) + (
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
                gbf = group_by_flash(group_base_list, glist, index_mcu_base)
                new_mcu_dirname += f"{'_' if index != 0 else ''}{gbf}"
        del group_package_list[:]
        del group_flash_list[:]
        del group_base_list[:]
        del dirname_list[:]

        new_mcu_dir = out_temp_path / mcu_family.name / new_mcu_dirname

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
        periph_xml.sort()
        periph_xml = list(OrderedDict.fromkeys(periph_xml))
        new_line_c = periph_xml.pop(0)
        for index, xml in enumerate(periph_xml, 1):
            if index % 2 == 0:
                new_line_c += f"\n * {xml}"
            else:
                new_line_c += f", {xml}"

        update_file(mcu_dir / periph_c_filename, periperalpins_regex, new_line_c)

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
    for mcu_family_name in aggregate_serie_list:
        mcu_family = out_temp_path / f"{mcu_family_name}{nx}"
        out_family_path = root_dir / "variants" / mcu_family.name
        # Get all mcu_dir
        mcu_dirs = sorted(mcu_family.glob("*/"))
        # Get original directory list of current serie STM32YYxx
        mcu_out_dirs_ori = sorted(out_family_path.glob("*/**"))
        mcu_out_dirs_up = []
        # Group mcu directories when only expressions and xml file name are different
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
            periph_xml = []
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
                periph_xml_tmp = []
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
                                    periph_xml_tmp += periperalpins_regex.findall(line)
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
                    uniq_periph_xml = set(periph_xml_tmp) - set(periph_xml)
                    periph_xml = periph_xml + list(uniq_periph_xml)
                    uniq_variant_exp = set(variant_exp_tmp) - set(variant_exp)
                    variant_exp = variant_exp + list(uniq_variant_exp)
                    # Matched files append to the group list
                    group_mcu_dir.append(mcu_dirs.pop(index))
                    del periph_xml_tmp[:]
                    del variant_exp_tmp[:]
                del mcu_dir2_files_list[:]

            # Merge directories name and contents if needed
            mcu_dir = merge_dir(
                out_temp_path, group_mcu_dir, mcu_family, periph_xml, variant_exp
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
            # Append updated directory to the list of current serie STM32YYxx
            mcu_out_dirs_up.append(out_path)
            del group_mcu_dir[:]
            del mcu_dir1_files_list[:]
        mcu_out_dirs_up.sort()
        new_dirs = set(mcu_out_dirs_up) - set(mcu_out_dirs_ori)
        if new_dirs:
            nb_new = len(new_dirs)
            dir_str = "directories" if nb_new > 1 else "directory"
            print(f"\nNew {dir_str} for {mcu_family.name}:\n")
            for d in new_dirs:
                print(f"  - {d.name}")
            print("\n  --> Please, check if it is a new directory or a renamed one.")
        old_dirs = set(mcu_out_dirs_ori) - set(mcu_out_dirs_up)
        if old_dirs:
            nb_old = len(old_dirs)
            dir_str = "Directories" if nb_old > 1 else "Directory"
            print(f"\n{dir_str} not updated for {mcu_family.name}:\n")
            for d in old_dirs:
                # Check if ldsript.ld file exists in the folder
                if not (d / "ldscript.ld").exists():
                    deleteFolder(d)
                    print(f"  - {d.name} (deleted)")
                else:
                    print(f"  - {d.name}")
            print(
                """
  --> For each directory not deleted, it requires manual update as it was renamed:
    - Find new directory name.
    - Move custom boards definition files, if any.
    - Move linker script(s).
    - Copy 'SystemClock_Config(void)' function to the new generic clock config file.
  --> Then remove it and update old path in boards.txt
     (for custom board(s) as well as generic ones).
"""
            )
        del mcu_out_dirs_ori[:]
        del mcu_out_dirs_up[:]


def default_cubemxdir():
    global cubemxdir
    if sys.platform.startswith("win32"):
        print("Platform is Windows")
        cubemxdir = Path(r"C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeMX")
    elif sys.platform.startswith("linux"):
        print("Platform is Linux")
        cubemxdir = Path.home() / "STM32CubeMX"
    elif sys.platform.startswith("darwin"):
        print("Platform is Mac OSX")
        cubemxdir = Path(
            "/Applications/STMicroelectronics/STM32CubeMX.app/Contents/Resources"
        )
    else:
        print("Platform unknown")
        cubemxdir = "<Set CubeMX install directory>"


# Config management
def checkConfig():
    global cubemxdir
    global repo_local_path
    global repo_path
    global cubeclt_mcu_path
    default_cubemxdir()
    if config_filename.is_file():
        try:
            # config_file = open(config_filename, "r")
            # path_config = json.load(config_file)
            # config_file.close()
            with open(config_filename, "r") as config_file:
                path_config = json.load(config_file)
            if "REPO_LOCAL_PATH" not in path_config:
                path_config["REPO_LOCAL_PATH"] = str(repo_local_path)
                defaultConfig(config_filename, path_config)
            else:
                conf = path_config["REPO_LOCAL_PATH"]
                if conf != "":
                    repo_local_path = Path(conf)
                    repo_path = repo_local_path / repo_name

            if "CUBEMX_DIRECTORY" not in path_config:
                path_config["CUBEMX_DIRECTORY"] = str(cubemxdir)
                defaultConfig(config_filename, path_config)
            else:
                cubemxdir = Path(path_config["CUBEMX_DIRECTORY"])
            if "STM32CUBECLT_PATH" not in path_config:
                path_config["STM32CUBECLT_PATH"] = str(
                    "Path to STM32CubeCLT installation directory"
                )
                defaultConfig(config_filename, path_config)
            else:
                cubeclt_path = Path(path_config["STM32CUBECLT_PATH"])
            if not cubeclt_path.is_dir():
                print(f"{cubeclt_path} does not exist!")
                exit(1)
            else:
                cubeclt_mcu_path = cubeclt_path / "STM32target-mcu"
                if not cubeclt_mcu_path.is_dir():
                    print(f"{cubeclt_mcu_path} does not exist!")
                    exit(1)
        except IOError:
            print(f"Failed to open {config_filename}")
    else:
        defaultConfig(
            config_filename,
            {
                "CUBEMX_DIRECTORY": str(cubemxdir),
                "REPO_LOCAL_PATH": str(repo_local_path),
            },
        )


def manage_repo():
    global db_release
    repo_local_path.mkdir(parents=True, exist_ok=True)

    if not args.skip:
        print(f"Updating {repo_name}...")
        if repo_path.is_dir():
            rname, bname = getRepoBranchName(repo_path)

            # Get new tags from the remote
            git_cmds = [
                ["git", "-C", repo_path, "clean", "-fdx"],
                ["git", "-C", repo_path, "fetch"],
                [
                    "git",
                    "-C",
                    repo_path,
                    "reset",
                    "--hard",
                    f"{rname}/{bname}",
                ],
            ]
        else:
            # Clone it as it does not exists yet
            git_cmds = [["git", "-C", repo_local_path, "clone", gh_url]]

        for cmd in git_cmds:
            execute_cmd(cmd, None)
    if repo_path.is_dir():
        # Get tag
        sha1_id = execute_cmd(
            ["git", "-C", repo_path, "rev-list", "--tags", "--max-count=1"], None
        )
        version_tag = execute_cmd(
            ["git", "-C", repo_path, "describe", "--tags", sha1_id], None
        )
        execute_cmd(
            ["git", "-C", repo_path, "checkout", version_tag],
            subprocess.DEVNULL,
        )
        db_release = version_tag
        return True
    return False


# main
tmp_dir = script_path / "variants"
root_dir = script_path.parents[1]
system_path = root_dir / "system"
templates_dir = script_path / "templates"
mcu_family_dir = ""
filtered_serie = ""
periph_c_filename = "PeripheralPins.c"
pinvar_h_filename = "PinNamesVar.h"
config_filename = script_path / "update_config.json"
variant_h_filename = "variant_generic.h"
variant_cpp_filename = "variant_generic.cpp"
boards_entry_filename = "boards_entry.txt"
generic_clock_filename = "generic_clock.c"
repo_local_path = script_path / "repo"
cubemxdir = Path()
cubeclt_mcu_path = Path()
gh_url = "https://github.com/STMicroelectronics/STM32_open_pin_data"
repo_name = gh_url.rsplit("/", 1)[-1]
repo_path = repo_local_path / repo_name
db_release = "Unknown"
nx = "xx"
checkConfig()

# By default, generate for all mcu xml files description
parser = argparse.ArgumentParser(
    description=textwrap.dedent(
        f"""
By default, generates:
 - {periph_c_filename},
 - {pinvar_h_filename},
 - {variant_cpp_filename},
 - {variant_h_filename},
 - {boards_entry_filename}
 - {generic_clock_filename}
for all xml files description available in STM32CubeMX internal database.
Internal database path must be defined in {config_filename}.
It can be the one from STM32CubeMX directory if defined:
\t{cubemxdir}
or the one from GitHub:
\t{gh_url}

"""
    ),
    epilog=textwrap.dedent(
        """\
After files generation, review them carefully and please report any issue to GitHub:
\thttps://github.com/stm32duino/Arduino_Core_STM32/issues
"""
    ),
    formatter_class=RawTextHelpFormatter,
)
group = parser.add_mutually_exclusive_group()
group.add_argument(
    "-l",
    "--list",
    help="list available xml files description in database.",
    action="store_true",
)

group.add_argument(
    "-s",
    "--serie",
    metavar="pattern",
    help="Generate all files for specified STM32 serie(s) pattern.",
)

parser.add_argument(
    "-c",
    "--cube",
    help=textwrap.dedent(
        f"""\
Use STM32CubeMX internal database. Default use GitHub {repo_name} repository.
"""
    ),
    action="store_true",
)
parser.add_argument(
    "--skip",
    help=f"Skip {repo_name} clone/fetch",
    action="store_true",
)
args = parser.parse_args()

# Using GitHub repo is the preferred way, CubeMX used as a fallback
fallback = False
if not args.cube:
    if manage_repo():
        dirMCU = repo_path / "mcu"
        dirIP = dirMCU / "IP"
        print("Using GitHub repository database")
    else:
        fallback = True
if fallback or args.cube:
    if not (cubemxdir.is_dir()):
        print(
            f"""
Cube Mx seems not to be installed or not at the specified location.

Please check the value set for 'CUBEMX_DIRECTORY' in '{config_filename}' file."""
        )
        quit()

    dirMCU = cubemxdir / "db" / "mcu"
    dirIP = dirMCU / "IP"
    print("Using STM32CubeMX internal database")
    version_file = cubemxdir / "db" / "package.xml"
    if version_file.is_file():
        xml_file = parse(str(version_file))
        PackDescription_item = xml_file.getElementsByTagName("PackDescription")
        for item in PackDescription_item:
            db_release = item.attributes["Release"].value
        xml_file.unlink()

# Process DB release
release_regex = r".*(\d+\.\d+\.\d+)$"
release_match = re.match(release_regex, db_release)
if release_match:
    db_release = release_match.group(1)
print(f"CubeMX DB release {db_release}\n")

# Open stm32targets.xml to get svd file
stm32targets_file = cubeclt_mcu_path / "stm32targets.xml"
if stm32targets_file.is_file():
    parse_stm32targets()
else:
    print(f"{stm32targets_file} does not exits!")
    exit(1)

if args.serie:
    serie = args.serie.upper()
    serie_pattern = re.compile(rf"STM32({serie})$", re.IGNORECASE)
# Get all xml files
mcu_list = sorted(dirMCU.glob("STM32*.xml"))

if args.list:
    print("Available xml files description:")
    for f in mcu_list:
        print(f.name)
    quit()
stm32_dict = genSTM32Dict(system_path / "Drivers")
stm32_list = sorted([f"STM32{stm32}" for stm32 in stm32_dict.keys()])

if not stm32_list:
    print(f"No STM32 series found in {system_path}/Drivers")
    quit()

# Create the jinja2 environment.
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)

# Clean temporary dir
deleteFolder(tmp_dir)

pl_regex = re.compile(r"([AQ])$")
package_regex = re.compile(r"[\w][\w]([ANPQSXZ])?$")
flash_group_regex = re.compile(r"(.*)\((.*)\)(.*)")

for mcu_file in mcu_list:
    # Open input file
    xml_mcu = parse(str(mcu_file))
    if parse_mcu_file() is False:
        continue

    # Add mcu family to the list of directory to aggregate
    if mcu_family not in aggregate_serie_list:
        aggregate_serie_list.append(mcu_family)
    nx = stm32_dict[mcu_family.removeprefix("STM32")]

    print(f"Generating files for '{mcu_file.name}'...")
    if not gpiofile:
        print("Could not find GPIO file")
        quit()
    xml_gpio = parse(str(dirIP / f"GPIO-{gpiofile}_Modes.xml"))

    mcu_family_dir = f"{mcu_family}{nx}"
    out_temp_path = tmp_dir / mcu_family_dir / mcu_file.stem.replace("STM32", "")
    periph_c_filepath = out_temp_path / periph_c_filename
    pinvar_h_filepath = out_temp_path / pinvar_h_filename
    variant_cpp_filepath = out_temp_path / variant_cpp_filename
    variant_h_filepath = out_temp_path / variant_h_filename
    boards_entry_filepath = out_temp_path / boards_entry_filename
    generic_clock_filepath = out_temp_path / generic_clock_filename
    out_temp_path.mkdir(parents=True, exist_ok=True)

    parse_pins()
    manage_af_and_alternate()

    with open(boards_entry_filepath, "w", newline="\n") as boards_entry_file:
        generic_list = print_boards_entry()
    with open(generic_clock_filepath, "w", newline="\n") as generic_clock_file:
        print_general_clock(generic_list)
    with open(periph_c_filepath, "w", newline="\n") as periph_c_file:
        print_peripheral()
    with open(pinvar_h_filepath, "w", newline="\n") as pinvar_h_file:
        alt_syswkup_list = print_pinamevar()
    with open(variant_cpp_filepath, "w", newline="\n") as variant_cpp_file, open(
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

    xml_mcu.unlink()
    xml_gpio.unlink()

print("Aggregating all generated files...")
periperalpins_regex = re.compile(r"\S+\.xml")
variant_regex = re.compile(r"defined\(ARDUINO_GENERIC_[^\s&|]*\)")
update_regex = re.compile(r"defined\(ARDUINO_GENERIC_.+\)")
board_entry_regex = re.compile(r"(Gen.+\..+variant=STM32[^x]+xx?/)\S+")
#                              P     T      E
mcu_PE_regex = re.compile(r"([\w])([\w])([AGNPQSXZ])?$")
aggregate_dir()

# Clean temporary dir
deleteFolder(tmp_dir)

# Display ignored families
if ignored_stm32_list:
    print("\nIgnored families:")
    for family in ignored_stm32_list:
        print(f"  - {family}")
    print("To be supported, series must first be supported by the core.")
