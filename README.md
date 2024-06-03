# Arduino core support for STM32 based boards
[![forums](https://img.shields.io/badge/join-the%20forums-blue.svg)](https://www.stm32duino.com/)
[![wiki](https://img.shields.io/badge/browse-the%20wiki-orange.svg)](https://github.com/stm32duino/Arduino_Core_STM32/wiki)
[![STM32 Core Continuous Integration](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/Arduino-build.yml/badge.svg?branch=main)](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/Arduino-build.yml )
[![Arduino lint status](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/arduino-lint.yml)
[![codespell](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/CodeSpell.yml/badge.svg)](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/CodeSpell.yml)
[![CMake](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/Cmake.yml/badge.svg)](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/Cmake.yml)


[![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
![GitHub All Releases](https://img.shields.io/github/downloads/stm32duino/Arduino_Core_STM32/total.svg?label=downloads%20since%201.4.0)
[![GitHub commits since latest release](https://img.shields.io/github/commits-since/stm32duino/Arduino_Core_STM32/latest/main)](https://github.com/stm32duino/Arduino_Core_STM32/compare/2.7.1...main)


* [Introduction](https://github.com/stm32duino/Arduino_Core_STM32#Introduction)<br>
* [Getting Started](https://github.com/stm32duino/Arduino_Core_STM32#getting-started)<br>
* [Supported boards](https://github.com/stm32duino/Arduino_Core_STM32#supported-boards)<br>
* [Troubleshooting](https://github.com/stm32duino/Arduino_Core_STM32#troubleshooting)<br>
* [Wiki](https://github.com/stm32duino/Arduino_Core_STM32/wiki/)

## Introduction

This repo adds the support of STM32 MCU in Arduino IDE.<br>

This porting is based on:
* [STM32Cube MCU Packages](https://www.st.com/en/embedded-software/stm32cube-mcu-packages.html) including:
    * The HAL hardware abstraction layer, enabling portability between different STM32 devices via standardized API calls
    * The Low-Layer (LL) APIs, a light-weight, optimized, expert oriented set of APIs designed for both performance and runtime efficiency
    * CMSIS device definition for STM32
* [CMSIS](https://developer.arm.com/embedded/cmsis): Cortex Microcontroller Software Interface Standard (CMSIS) is a vendor-independent hardware abstraction layer for the Cortex®-M processor series and defines generic tool interfaces. It has been packaged as a module for Arduino IDE: https://github.com/stm32duino/ArduinoModule-CMSIS
* [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm): Arm Embedded GCC compiler, libraries and other GNU tools necessary for bare-metal software development on devices based on the Arm Cortex-M. Packages are provided thanks [The xPack GNU Arm Embedded GCC](https://xpack.github.io/arm-none-eabi-gcc/): https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack
## Getting Started

This repo is available as a package usable with [Arduino Boards Manager](https://www.arduino.cc/en/guide/cores).

Add this link in the "*Additional Boards Managers URLs*" field:

https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json

**Warning**:
* Default branch has changed to *main*.
* Since core release 2.0.0 this link has changed.

For full instructions on using the "**Boards Manager**", see the [Getting Started](https://github.com/stm32duino/Arduino_Core_STM32/wiki/Getting-Started) page.

Advanced user can use the repository to benefit from the latest development. See the [Using git repository](https://github.com/stm32duino/Arduino_Core_STM32/wiki/Using-git-repository) page.

User can add a STM32 based board following this [wiki](https://github.com/stm32duino/Arduino_Core_STM32/wiki/Add-a-new-variant-(board)).

## Supported boards

 - [Nucleo 144 boards](#nucleo-144-boards)
 - [Nucleo 64 boards](#nucleo-64-boards)
 - [Nucleo 32 boards](#nucleo-32-boards)
 - [Discovery boards](#discovery-boards)
 - [Eval boards](#eval-boards)
 - [STM32MP1 series coprocessor boards](#stm32mp1-series-coprocessor-boards)
 - [Generic STM32C0 boards](#generic-stm32c0-boards)
 - [Generic STM32F0 boards](#generic-stm32f0-boards)
 - [Generic STM32F1 boards](#generic-stm32f1-boards)
 - [Generic STM32F2 boards](#generic-stm32f2-boards)
 - [Generic STM32F3 boards](#generic-stm32f3-boards)
 - [Generic STM32F4 boards](#generic-stm32f4-boards)
 - [Generic STM32F7 boards](#generic-stm32f7-boards)
 - [Generic STM32G0 boards](#generic-stm32g0-boards)
 - [Generic STM32G4 boards](#generic-stm32g4-boards)
 - [Generic STM32H5 boards](#generic-stm32h5-boards)
 - [Generic STM32H7 boards](#generic-stm32h7-boards)
 - [Generic STM32L0 boards](#generic-stm32l0-boards)
 - [Generic STM32L1 boards](#generic-stm32l1-boards)
 - [Generic STM32L4 boards](#generic-stm32l4-boards)
 - [Generic STM32L5 boards](#generic-stm32l5-boards)
 - [Generic STM32U5 boards](#generic-stm32u5-boards)
 - [Generic STM32WB boards](#generic-stm32wb-boards)
 - [Generic STM32WBA boards](#generic-stm32wba-boards)
 - [Generic STM32WL boards](#generic-stm32wl-boards)
 - [3D printer boards](#3d-printer-boards)
 - [Blues Wireless boards](#blues-wireless-boards)
 - [Elecgator boards](#elecgator-boards)
 - [Electronic Speed Controller boards](#electronic-speed-controller-boards)
 - [Garatronic/McHobby boards](#garatronicmchobby-boards)
 - [Generic flight controllers](#generic-flight-controllers)
 - [IoT continuum boards](#iot-continuum-boards)
 - [LoRa boards](#lora-boards)
 - [Midatronics boards](#midatronics-boards)
 - [SparkFun boards](#sparkfun-boards)
 - [ELV Boards](#elv-boards)

**Note about Status**:
  - :green_heart: board support is available since the specified release version.
  - :yellow_heart: board support is available in the main branch and will be available in the specified release version.

### [Nucleo 144](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-nucleo-boards.html) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F207ZG | [Nucleo F207ZG](http://www.st.com/en/evaluation-tools/nucleo-f207zg.html) | *0.2.0* |  |
| :green_heart:  | STM32F412ZG | [Nucleo F412ZG](http://www.st.com/en/evaluation-tools/nucleo-f412zg.html) | *2.6.0* |  |
| :green_heart:  | STM32F413ZH | [Nucleo F413ZH](http://www.st.com/en/evaluation-tools/nucleo-f413zh.html) | *2.4.0* |  |
| :green_heart:  | STM32F429ZI | [Nucleo F429ZI](http://www.st.com/en/evaluation-tools/nucleo-f429zi.html) | *0.1.0* |  |
| :yellow_heart:  | STM32F439ZI | [Nucleo F439ZI](http://www.st.com/en/evaluation-tools/nucleo-f439zi.html) | **2.8.0** |  |
| :green_heart:  | STM32F446ZE | [Nucleo F446ZE](http://www.st.com/en/evaluation-tools/nucleo-f446ze.html) | *2.7.0* |  |
| :green_heart:  | STM32F722ZE | [Nucleo F722ZE](http://www.st.com/en/evaluation-tools/nucleo-f722ze.html) | *2.4.0* |  |
| :green_heart:  | STM32F767ZI | [Nucleo F767ZI](http://www.st.com/en/evaluation-tools/nucleo-f767zi.html) | *1.4.0* |  |
| :green_heart:  | STM32F746ZG | [Nucleo F746ZG](https://www.st.com/en/evaluation-tools/nucleo-f746zg.html) | *1.9.0* |  |
| :green_heart:  | STM32F756ZG | [Nucleo F756ZG](https://www.st.com/en/evaluation-tools/nucleo-f756zg.html) | *1.9.0* |  |
| :green_heart:  | STM32H563ZI | [Nucleo H563ZI](https://www.st.com/en/evaluation-tools/nucleo-h563zi.html) | *2.6.0* |  |
| :green_heart:  | STM32H723ZG | [Nucleo H723ZG](https://www.st.com/en/evaluation-tools/nucleo-h723zg.html) | *2.4.0* |  |
| :green_heart:  | STM32H743ZI | [Nucleo H743ZI(2)](https://www.st.com/en/evaluation-tools/nucleo-h743zi.html) | *1.5.0* | Nucleo H743ZI2 since 1.6.0 |
| :green_heart:  | STM32H753ZI | [Nucleo H753ZI](https://www.st.com/en/evaluation-tools/nucleo-h753zi.html) | *2.7.0* |  |
| :green_heart:  | STM32L496ZG | [Nucleo L496ZG](http://www.st.com/en/evaluation-tools/nucleo-l496zg.html) | *1.3.0* |  |
| :green_heart:  | STM32L496ZG-P | [Nucleo L496ZG-P](http://www.st.com/en/evaluation-tools/nucleo-l496zg-p.html) | *1.3.0* |  |
| :green_heart:  | STM32L4R5ZI | [Nucleo L4R5ZI](http://www.st.com/en/evaluation-tools/nucleo-l4r5zi.html) | *1.4.0* |  |
| :green_heart:  | STM32L4R5ZI-P | [Nucleo L4R5ZI-P](http://www.st.com/en/evaluation-tools/nucleo-l4r5zi-p.html) | *1.4.0* |  |
| :green_heart: | STM32L552ZE-Q | [Nucleo L552ZE-Q](https://www.st.com/en/evaluation-tools/nucleo-l552ze-q.html) | *2.0.0* |  |
| :green_heart:  | STM32U575ZI-Q | [NUCLEO-U575ZI-Q](https://www.st.com/en/evaluation-tools/nucleo-u575zi-q.html) | *2.1.0* |  |

### [Nucleo 64](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-nucleo-boards.html) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32C031C6 | [Nucleo C031C6](https://www.st.com/en/evaluation-tools/nucleo-c031c6.html) | *2.5.0* |  |
| :green_heart:  | STM32F030R8 | [Nucleo F030R8](http://www.st.com/en/evaluation-tools/nucleo-f030r8.html) | *0.2.0* |  |
| :green_heart:  | STM32F070RB | [Nucleo F070RB](http://www.st.com/en/evaluation-tools/nucleo-f070rb.html) | *2.0.0* |  |
| :green_heart:  | STM32F072RB | [Nucleo F072RB](http://www.st.com/en/evaluation-tools/nucleo-f072rb.html) | *1.9.0* |  |
| :green_heart:  | STM32F091RC | [Nucleo F091RC](http://www.st.com/en/evaluation-tools/nucleo-f091rc.html) | *0.1.0* |  |
| :green_heart:  | STM32F103RB | [Nucleo F103RB](http://www.st.com/en/evaluation-tools/nucleo-f103rb.html) | *0.2.0* |  |
| :green_heart:  | STM32F302R8 | [Nucleo F302R8](http://www.st.com/en/evaluation-tools/nucleo-f302r8.html) | *1.1.0* |  |
| :green_heart:  | STM32F303RE | [Nucleo F303RE](http://www.st.com/en/evaluation-tools/nucleo-f303re.html) | *0.1.0* |  |
| :green_heart:  | STM32F401RE | [Nucleo F401RE](http://www.st.com/en/evaluation-tools/nucleo-f401re.html) | *0.2.1* |  |
| :green_heart:  | STM32F411RE | [Nucleo F411RE](http://www.st.com/en/evaluation-tools/nucleo-f411re.html) | *0.2.1* |  |
| :green_heart:  | STM32F446RE | [Nucleo F446RE](http://www.st.com/en/evaluation-tools/nucleo-f446re.html) | *1.1.1* |  |
| :green_heart:  | STM32G070RB | [Nucleo G070RB](https://www.st.com/en/evaluation-tools/nucleo-g070rb.html) | *2.3.0* |  |
| :green_heart:  | STM32G071RB | [Nucleo G071RB](https://www.st.com/en/evaluation-tools/nucleo-g071rb.html) | *1.6.0* |  |
| :green_heart:  | STM32G0B1RE | [Nucleo G0B1RE](https://www.st.com/en/evaluation-tools/nucleo-g0b1re.html) | *2.1.0* |  |
| :green_heart:  | STM32G431RB | [Nucleo G431RB](https://www.st.com/en/evaluation-tools/nucleo-g431rb.html) | *1.7.0* |  |
| :green_heart:  | STM32G474RE | [Nucleo G474RE](https://www.st.com/en/evaluation-tools/nucleo-g474re.html) | *1.7.0* |  |
| :green_heart:  | STM32H503RB | [Nucleo H503RB](https://www.st.com/en/evaluation-tools/nucleo-h503rb.html) | *2.7.0* |  |
| :green_heart:  | STM32L010RB | [Nucleo L010RB](https://www.st.com/en/evaluation-tools/nucleo-l010rb.html) | *2.1.0* |  |
| :green_heart:  | STM32L053R8 | [Nucleo L053R8](http://www.st.com/en/evaluation-tools/nucleo-l053r8.html) | *0.1.0* |  |
| :green_heart:  | STM32L073RZ | [Nucleo L073RZ](http://www.st.com/en/evaluation-tools/nucleo-l073rz.html) | *1.4.0* |  |
| :green_heart:  | STM32L152RE | [Nucleo L152RE](http://www.st.com/en/evaluation-tools/nucleo-l152re.html) | *1.0.0* |  |
| :green_heart:  | STM32L433RC-P | [Nucleo L433RC-P](https://www.st.com/en/evaluation-tools/nucleo-l433rc-p.html) | *1.9.0* |  |
| :green_heart:  | STM32L452RE | [Nucleo L452RE](http://www.st.com/en/evaluation-tools/nucleo-l452re.html) | *1.5.0* |  |
| :green_heart:  | STM32L452RE-P | [Nucleo L452RE-P](http://www.st.com/en/evaluation-tools/nucleo-l452re-p.html) | *1.8.0* |  |
| :green_heart:  | STM32L476RG | [Nucleo L476RG](http://www.st.com/en/evaluation-tools/nucleo-l476rg.html) | *0.1.0* |  |
| :green_heart:  | STM32WB15CCU | [Nucleo-WB15CC](https://www.st.com/en/evaluation-tools/nucleo-wb15cc.html) | *2.5.0* |  |
| :yellow_heart: | STM32WBA55CGU | Nucleo-WBA55CG | **2.8.0** |  |
| :green_heart:  | STM32WB55RG | [P-Nucleo-WB55RG](https://www.st.com/en/evaluation-tools/p-nucleo-wb55.html) | *1.6.0* | BLE support with [STM32duinoBLE](https://github.com/stm32duino/STM32duinoBLE) |
| :green_heart:  | STM32WB55CG | [P-Nucleo-WB55 USB Dongle](https://www.st.com/en/evaluation-tools/p-nucleo-wb55.html) | *2.5.0* | BLE support with [STM32duinoBLE](https://github.com/stm32duino/STM32duinoBLE) |
| :green_heart:  | STM32WL55JC | [Nucleo WL55JC1](https://www.st.com/en/evaluation-tools/nucleo-wl55jc.html) | *2.1.0* | LoRa support not available |


### [Nucleo 32](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-nucleo-boards.html) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F031K6T | [Nucleo F031K6](https://www.st.com/en/evaluation-tools/nucleo-f031k6.html) | *1.9.0* |  |
| :green_heart:  | STM32F042K6T | [Nucleo F042K6](https://www.st.com/en/evaluation-tools/nucleo-f042k6.html) | *2.1.0* |  |
| :green_heart:  | STM32F303K8 | [Nucleo F303K8](http://www.st.com/en/evaluation-tools/nucleo-f303k8.html) | *1.1.0* |  |
| :green_heart: | STM32G031K8 | [Nucleo G031K8](https://www.st.com/en/evaluation-tools/nucleo-g031k8.html) | *2.0.0* |
| :green_heart:  | STM32G431KB | [Nucleo G431KB](https://www.st.com/en/evaluation-tools/nucleo-g431kb.html) | *1.7.0* |  |
| :green_heart:  | STM32L031K6 | [Nucleo L031K6](http://www.st.com/en/evaluation-tools/nucleo-l031k6.html) | *1.1.1* |  |
| :green_heart:  | STM32L412KB | [Nucleo L412KB](http://www.st.com/en/evaluation-tools/nucleo-l412kb.html) | *1.5.0* |  |
| :green_heart:  | STM32L432KC | [Nucleo L432KC](http://www.st.com/en/evaluation-tools/nucleo-l432kc.html) | *0.2.0* |  |

### [Discovery](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-discovery-kits.html) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32C011F6 | [STM32C0116-DK](https://www.st.com/en/evaluation-tools/stm32c0116-dk.html) | *2.6.0* |  |
| :green_heart: | STM32C031C6 | [STM32C0316-DK](https://www.st.com/en/evaluation-tools/stm32c0316-dk.html) | *2.5.0* |  |
| :green_heart:  | STM32F030R8 | [32F0308DISCOVERY](http://www.st.com/en/evaluation-tools/32f0308discovery.html) | *1.3.0* |  |
| :green_heart:  | STM32F072RB | [32F072BDISCOVERY](https://www.st.com/en/evaluation-tools/32f072bdiscovery.html) | *1.5.0* |  |
| :green_heart:  | STM32F100RB | [STM32VLDISCOVERY](https://www.st.com/en/evaluation-tools/stm32vldiscovery.html) | 0.2.1 |  |
| :green_heart:  | STM32F303VC | [STM32F3DISCOVERY](https://www.st.com/en/evaluation-tools/stm32f3discovery.html) | *2.0.0* |  |
| :green_heart:  | STM32F407VG | [STM32F407G-DISC1](http://www.st.com/en/evaluation-tools/stm32f4discovery.html) | *0.1.0* |  |
| :green_heart:  | STM32F413ZH | [32F413HDISCOVERY](https://www.st.com/en/evaluation-tools/32f413hdiscovery.html) | *1.9.0* |  |
| :green_heart:  | STM32F746NG | [STM32F746G-DISCOVERY](http://www.st.com/en/evaluation-tools/32f746gdiscovery.html) | *0.1.0* |  |
| :green_heart:  | STM32G031J6 | [STM32G0316-DISCO](https://www.st.com/en/evaluation-tools/stm32g0316-disco.html) | *1.9.0* |  |
| :green_heart:  | STM32G431CB | [B-G431B-ESC1](https://www.st.com/en/evaluation-tools/b-g431b-esc1.html) | *2.0.0* |  |
| :green_heart:  | STM32H573IIKxQ | [STM32H573I-DK](https://www.st.com/en/evaluation-tools/stm32h573i-dk.html) | *2.6.0* |  |
| :green_heart:  | STM32H747XIHx | [STM32H747I-DISCO](https://www.st.com/en/evaluation-tools/stm32h747i-disco.html) | *2.7.0* |  |
| :green_heart:  | STM32L4S5VI | [B-L4S5I-IOT01A](https://www.st.com/en/evaluation-tools/b-l4s5i-iot01a.html) | *2.0.0* | |
| :green_heart: | STM32U585AIIxQ | [B-U585I-IOT02A](https://www.st.com/en/evaluation-tools/b-u585i-iot02a.html) | *2.1.0* |  |
| :green_heart: | STM32WB5MMG | [STM32WB5MM-DK](https://www.st.com/en/evaluation-tools/stm32wb5mm-dk.html) | *2.1.0* |  |

### [Eval](https://www.st.com/en/evaluation-tools/stm32-eval-boards.html) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32L4R9ZI | [STEVAL-MKSBOX1V1 (SensorTile.box)](https://www.st.com/en/evaluation-tools/steval-mksbox1v1.html) | *1.7.0* |  |
| :green_heart:  | STM32U585AIIxQ | [STEVAL-MKBOXPRO (SensorTile.box Pro)](https://www.st.com/en/evaluation-tools/steval-mkboxpro.html) | *2.6.0* |  |

### [STM32MP1 series coprocessor](https://www.st.com/content/st_com/en/products/microcontrollers-microprocessors/stm32-arm-cortex-mpus/stm32mp1-series.html) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32MP157A | [STM32MP157A-DK1](https://www.st.com/en/evaluation-tools/stm32mp157a-dk1.html) | *1.8.0* | See [the documentation](https://github.com/stm32duino/Arduino_Core_STM32/tree/main/variants/STM32MP1xx/MP153AAC_MP153CAC_MP153DAC_MP153FAC_MP157AAC_MP157CAC_MP157DAC_MP157FAC/README.md) to use this board|
| :green_heart:  | STM32MP157C | [STM32MP157C-DK2](https://www.st.com/en/evaluation-tools/stm32mp157c-dk2.html) | *1.8.0* | See [the documentation](https://github.com/stm32duino/Arduino_Core_STM32/tree/main/variants/STM32MP1xx/MP153AAC_MP153CAC_MP153DAC_MP153FAC_MP157AAC_MP157CAC_MP157DAC_MP157FAC/README.md) to use this board|

### Generic STM32C0 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32C011D6 | Generic Board | *2.6.0* |  |
| :green_heart: | STM32C011F4<br>STM32C011F6 | Generic Board | *2.6.0* |  |
| :yellow_heart: | STM32C011J4<br>STM32C011J6 | Generic Board | **2.8.0** |  |
| :green_heart: | STM32C031C4<br>STM32C031C6 | Generic Board | *2.5.0* |  |
| :green_heart: | STM32C031F4<br>STM32C031F6 | Generic Board | *2.6.0* |  |

### Generic STM32F0 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F030C6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F030F4 | [STM32F030F4 Demo board](https://stm32-base.org/boards/STM32F030F4P6-STM32F030-DEMO-BOARD-V1.1) | *1.5.0* |  |
| :green_heart:  | STM32F030K6 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32F030C8 | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F030F4 | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F030R8 | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F031C4<br>STM32F031C6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F031E6<br>STM32F038E6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F031F4<br>STM32F031F6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F031G4<br>STM32F031G6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F031K4<br>STM32F031K6 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32F031K6T | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F038C6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F038F6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F038G6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F038K6 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32F042C4<br>STM32F042C6 | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F042F4<br>STM32F042F6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F042G4<br>STM32F042G6 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32F042K4T<br>STM32F042K6T | Generic Board | **2.0.1** |  |
| :green_heart:  | STM32F042T6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F048G6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F048T6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F051C4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F051K4 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32F051K6U<br>STM32F051K8U | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F051R4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F051T8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F058C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F058R8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F058T8 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32F070CB | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F070RB | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F071C8<br>STM32F071CB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F071RB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F071V8<br>STM32F071VB | Generic Board | *2.4.0* |  |
| :green_heart: | STM32F072C8<br>STM32F072CB | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F072R8<br>STM32F072RB | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F071C8<br>STM32F071CB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F072V8<br>STM32F072VB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F078CB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F078RB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F078VB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F091CB<br>STM32F091CC | Generic Board | *2.4.0* |  |
| :green_heart: | STM32F091RB<br>STM32F091RC | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F091VB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F091VC | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F098CC | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F098RC | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F098VC | Generic Board | *2.4.0* |  |

### Generic STM32F1 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32F100C4<br>STM32F100C6 | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F100C8<br>STM32F100CB | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F100R4<br>STM32F100R6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F100V8<br>STM32F100VB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F100ZC<br>STM32F100ZD<br>STM32F100ZT | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F101C4<br>STM32F101C6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F101R4<br>STM32F101R6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F101T4<br>STM32F101T6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F101V8<br>STM32F101VB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F101ZC<br>STM32F101ZD<br>STM32F101ZE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F103C6<br>STM32F103C8<br>STM32F103CB | [Blue Pill](https://stm32-base.org/boards/STM32F103C8T6-Blue-Pill) | *1.2.0* | USB CDC support since *1.5.0*<br> Maple bootloaders support since *1.6.0* |
| :green_heart:  | STM32F103C8<br>STM32F103CB | [Black Pill](https://stm32-base.org/boards/STM32F103C8T6-Black-Pill) | *1.5.0* |  |
| :green_heart:  | STM32F103C4<br>STM32F103C6<br>STM32F103C8<br>STM32F103CB | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F103R8<br>STM32F103RB<br>STM32F103RC<br>STM32F103RE | [Blue Button F103Rx](https://stm32-base.org/boards/STM32F103RET6-Generic-Board) | *1.9.0* |  |
| :green_heart:  | STM32F103R6<br>STM32F103R8<br>STM32F103RB<br>STM32F103RC<br>STM32F103RD<br>STM32F103RE<br>STM32F103RF<br>STM32F103RG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F103T4<br>STM32F103T6<br>STM32F103T8<br>STM32F103TB | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F103V8<br>STM32F103VB<br>STM32F103VC<br>STM32F103VD<br>STM32F103VE<br>STM32F103VF<br>STM32F103VG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F103ZC<br>STM32F103ZD<br>STM32F103ZE<br>STM32F103ZF<br>STM32F103ZG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F103TB | HY-TinySTM103T | *1.5.0* | [More info](https://www.hotmcu.com/stm32f103tb-arm-cortex-m3-development-board-p-222.html) |
| :green_heart:  | STM32F103CB | Maple Mini | *1.2.0* | [More info](https://www.leaflabs.com/maple)<br>USB CDC support since *1.5.0*<br>Maple bootloaders support since *1.6.0* |
| :green_heart:  | STM32F103ZE | [vcc-gnd.com](https://stm32-base.org/boards/STM32F103ZET6-VCC-GND-XLarge) | *1.9.0* |  |
| :green_heart:  | STM32F103ZE | vcc-gnd.com Mini | *1.9.0* |  |

### Generic STM32F2 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F205RB<br>STM32F205RC<br>STM32F205RE<br>STM32F205RF | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F205VB<br>STM32F205VC<br>STM32F205VE<br>STM32F205VF<br>STM32F205VG | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F205ZC<br>STM32F205ZE<br>STM32F205ZF<br>STM32F205ZG | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F207IC<br>STM32F207IE<br>STM32F207IF<br>STM32F207IG | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F207VC<br>STM32F207VE<br>STM32F207VF<br>STM32F207VG | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F207ZC<br>STM32F207ZE<br>STM32F207ZF<br>STM32F207ZG | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F215RE<br>STM32F215RG | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F215VE<br>STM32F215VG | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F215ZE<br>STM32F215ZG | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F217IE<br>STM32F217IG | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F217VE<br>STM32F217VG | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F217ZE<br>STM32F217ZG | Generic Board | *2.0.0* |  |

### Generic STM32F3 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F301C6<br>STM32F301C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F301K6<br>STM32F301K8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F301R6<br>STM32F301R8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F302R6<br>STM32F302R8 | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F303C6<br>STM32F303C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F303CB<br>STM32F303CC | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F303CC | [RobotDyn Black Pill](https://stm32-base.org/boards/STM32F303CCT6-RobotDyn-Black-Pill) | *1.6.1* | |
| :green_heart:  | STM32F303K6<br>STM32F303K8 | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F303R6<br>STM32F303R8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F303RD<br>STM32F303RE | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F303RB<br>STM32F303RC | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F303RC | [OLIMEXINO-STM32F3](https://www.olimex.com/Products/Duino/STM32/OLIMEXINO-STM32F3/) | *2.0.0* | |
| :green_heart:  | STM32F303VBT<br>STM32F303VCT | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F318C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F318K8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F328C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F334C4<br>STM32F334C6<br>STM32F334C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F334K4<br>STM32F334K6<br>STM32F334K8 | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F334R6<br>STM32F334R8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F358CC | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F358RC | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F358VC | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F378CC | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F378RC | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F378VC | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F398VE | Generic Board | *2.4.0* |  |

### Generic STM32F4 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F405RG | [Adafruit Feather STM32F405 Express](https://www.adafruit.com/product/4382) | *1.8.0* |  |
| :green_heart:  | STM32F401CC | [WeAct Black Pill](https://stm32-base.org/boards/STM32F401CCU6-WeAct-Black-Pill-V1.2) | *1.7.0* | [More info](https://github.com/WeActStudio/WeActStudio.MiniSTM32F4x1) |
| :green_heart:  | STM32F401CE | [WeAct Black Pill](https://stm32-base.org/boards/STM32F401CEU6-WeAct-Black-Pill-V3.0) | *2.4.0* | [More info](https://github.com/WeActStudio/WeActStudio.MiniSTM32F4x1) |
| :green_heart:  | STM32F411CE | [WeAct Black Pill](https://stm32-base.org/boards/STM32F411CEU6-WeAct-Black-Pill-V2.0) | *1.9.0* | [More info](https://github.com/WeActStudio/WeActStudio.MiniSTM32F4x1) |
| :green_heart:  | STM32F407VE<br>STM32F407VG | [STM32 F4VE / Black F407VET6](https://stm32-base.org/boards/STM32F407VET6-STM32-F4VE-V2.0) | *1.4.0* | STM32F407VG support since *1.5.0* |
| :green_heart:  | STM32F407ZE<br>STM32F407ZG | Black F407ZE / Black F407ZG | *1.5.0* |  |
| :green_heart: | STM32F407ZG | vcc-gnd.com Mini | **2.0.0** |  |
| :green_heart:  | STM32F407VE | [vcc-gnd.com Mini](https://stm32-base.org/boards/STM32F407VET6-VCC-GND-Small) | *1.4.0* |  |
| :green_heart:  | STM32F401RC | [STM32F Core Board](https://stm32-base.org/boards/STM32F401RCT6-STM32F-Core-Board) | *1.7.0* |  |
| :green_heart:  | STM32F407VG | [DIYMORE STM32F407VGT](https://stm32-base.org/boards/STM32F407VGT6-diymore) | *1.5.0* |  |
| :green_heart:  | STM32F407VE | [FK407M1](https://stm32-base.org/boards/STM32F407VET6-FK407M1-V1.0) | *1.5.0* |  |
| :green_heart:  | STM32F401CB<br>STM32F401CC<br>STM32F401CD<br>STM32F401CE | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F401RB<br>STM32F401RC<br>STM32F401RD<br>STM32F401RE | Generic Board | *1.8.0* |  |
| :green_heart:  | STM32F401VB<br>STM32F401VC<br>STM32F401VD<br>STM32F401VE | Generic Board | **2.0.0** |  |
| :green_heart:  | STM32F405RG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F407VE<br>STM32F407VG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F407ZE<br>STM32F407ZG | Generic Board | **2.0.0** |  |
| :green_heart:  | STM32F410C8<br>STM32F410CB | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F410R8<br>STM32F410RB | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F410T8<br>STM32F410TB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32F411CC<br>STM32F411CE | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F411RC<br>STM32F411RE | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F412CE<br>STM32F412CG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F412RE<br>STM32F412RG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F412ZE<br>STM32F412ZG | Generic Board | *2.6.0* |  |
| :green_heart:  | STM32F413CG<br>STM32F413CH | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F413RG<br>STM32F413RH | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F413ZG<br>STM32F413ZH | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32F415RG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F417VE<br>STM32F417VG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F417ZE<br>STM32F417ZG | Generic Board | **2.0.0** |  |
| :green_heart:  | STM32F423CH | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F423RH | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F423ZH | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F427ZG<br>STM32F427ZI | Generic Board | **2.0.0** |  |
| :green_heart: | STM32F429ZE<br>STM32F429ZG<br>STM32F429ZI | Generic Board | **2.0.0** |
| :green_heart: | STM32F437ZG<br>STM32F437ZI | Generic Board | **2.0.0** |
| :green_heart: | STM32F439ZG<br>STM32F439ZI | Generic Board | **2.0.0** |
| :green_heart:  | STM32F446RC<br>STM32F446RE | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F446ZC<br>STM32F446ZE | Generic Board | *2.7.0* |  |
| :green_heart: | STM32F446VC<br>STM32F446VE | Generic Board | **2.0.0** |
| :green_heart:  | STM32F411CE | [ThunderPack v1.1+](https://github.com/jgillick/ThunderPack) | *1.9.0* |  |

### Generic STM32F7 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32F722RC<br>STM32F722RE | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32F722ZC<br>STM32F722ZE | Generic Board | *2.4.0* |  |
| :green_heart: | STM32F723IC<br>STM32F723IE | Generic Board | *2.7.0* |  |
| :green_heart: | STM32F730I8K | Generic Board | *2.7.0* |  |
| :green_heart: | STM32F730R8 | Generic Board | *2.3.0* |  |
| :green_heart: | STM32F732RE | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32F732ZE | Generic Board | *2.4.0* |  |
| :green_heart: | STM32F733IE<br> | Generic Board | *2.7.0* |  |
| :green_heart: | STM32F745ZE<br>STM32F745ZG | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F746BE<br>STM32F746BG<br>STM32F746NE<br>STM32F746NG | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F746ZE<br>STM32F746ZG | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F750N8 | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F750Z8 | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F756BG<br>STM32F756NG | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F756ZG | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F765IGK<br>STM32F765IIK<br>STM32F765IGT<br>STM32F765IIT | Generic Board | *2.3.0* |  |
| :green_heart: | STM32F765VG<br>STM32F765VI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F765ZG<br>STM32F765ZI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F767IGK<br>STM32F767IIK<br>STM32F767IGT<br>STM32F767IIT | Generic Board | *2.3.0* |  |
| :green_heart: | STM32F767VG<br>STM32F767VI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F767ZG<br>STM32F767ZI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F777IIK<br>STM32F777IIT | Generic Board | *2.3.0* |  |
| :green_heart: | STM32F777VI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32F777ZI | Generic Board | *2.0.0* |  |

### Generic STM32G0 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32G030C6<br>STM32G030C8 | Generic Board | *2.2.0* |
| :green_heart: | STM32G030F6<br>STM32G030F6 | Generic Board | *2.2.0* |
| :green_heart: | STM32G030K8 | Aurora One | *2.0.0* |
| :green_heart: | STM32G071CB | [AGAFIA SG0](https://www.sigmaic.com) | *2.3.0* |
| :green_heart:  | STM32G030J6 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G030K6<br>STM32G030K8 | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32G031C4<br>STM32G031C6<br>STM32G031C8 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G031F4<br>STM32G031F6<br>STM32G031F8 | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32G031G4<br>STM32G031G6<br>STM32G031G8 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G031J4<br>STM32G031J6 | Generic Board | *2.0.0* |  |
| :green_heart: | STM32G031K4<br>STM32G031K6<br>STM32G031K8 | Generic Board | *2.0.0* |  |
| :green_heart: | STM32G031Y8 | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32G041C6<br>STM32G041C8 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G041F6<br>STM32G041F8 | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32G041G6<br>STM32G041G8 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G041J6 | Generic Board | *2.0.0* |  |
| :green_heart: | STM32G041K6<br>STM32G041K8 | Generic Board | *2.0.0* |  |
| :green_heart: | STM32G041Y8 | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32G050C6<br>STM32G050C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G050F6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G050K6<br>STM32G050K8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G051C6<br>STM32G051C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G051F6<br>STM32G051F8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G051G6<br>STM32G051G8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G051K6<br>STM32G051K8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G061C6<br>STM32G061C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G061F6<br>STM32G061F8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G061G6<br>STM32G061G8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G061K6<br>STM32G061K8 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G070CB | Generic Board | *2.3.0* |  |
| :green_heart: | STM32G070KB | Generic Board | *2.3.0* |  |
| :green_heart: | STM32G070RB | Generic Board | *2.3.0* |  |
| :green_heart: | STM32G071C6<br>STM32G071C8<br>STM32G071CB | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32G071EB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G071G6<br>STM32G071G8<br>STM32G071GB | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G071G8UxN | Generic Board | *2.3.0* |  |
| :green_heart: | STM32G071GBUxN | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32G071K6<br>STM32G071K8<br>STM32G071KB | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G071R6<br>STM32G071R8<br>STM32G071RB | Generic Board | *2.0.0* |  |
| :green_heart: | STM32G081CBT<br>STM32G081CBU | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32G081EB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G081GB | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G081GBUxN | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32G081KB | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G081RB | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32G0B0CE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0B0RE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0B0VE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0B1CB<br>STM32G0B1CC<br>STM32G0B1CE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0B1KB<br>STM32G0B1KC<br>STM32G0B1KE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0B1MB<br>STM32G0B1MC<br>STM32G0B1ME | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0B1NE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0B1VB<br>STM32G0B1VC<br>STM32G0B1VE | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G0B1RB<br>STM32G0B1RC<br>STM32G0B1RE | Generic Board | *2.1.0* |  |
| :green_heart:  | STM32G0C1CC<br>STM32G0C1CE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0C1KB<br>STM32G0C1KC<br>STM32G0C1KE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0C1MC<br>STM32G0C1ME | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0C1NE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G0C1VC<br>STM32G0C1VE | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G0C1RB<br>STM32G0C1RE | Generic Board | *2.1.0* |  |

### Generic STM32G4 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32G431C6<br>STM32G431C8<br>STM32G431CB | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G431C6U<br>STM32G431C8U<br>STM32G431CBU | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32G431M6<br>STM32G431M8<br>STM32G431MB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G431V6<br>STM32G431V8<br>STM32G431VB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G441CB | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G441CBU | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32G441MB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G441VB | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G431K6<br>STM32G431K8<br>STM32G431KB | Generic Board | *2.0.0* |  |
| :green_heart: | STM32G441KB | Generic Board | *2.0.0* |  |
| :green_heart: | STM32G431R6<br>STM32G431R8<br>STM32G431RB | Generic Board | *2.0.0* |  |
| :green_heart: | STM32G441RB  | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32G471CC<br>STM32G471CE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G471MC<br>STM32G471ME | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G471QC<br>STM32G471QE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G471RC<br>STM32G471RE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G471VC<br>STM32G471VE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G473CB<br>STM32G473CC<br>STM32G473CE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G473MB<br>STM32G473MC<br>STM32G473ME | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G473PB<br>STM32G473PC<br>STM32G473PE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G473QB<br>STM32G473QC<br>STM32G473QE | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G473RB<br>STM32G473RC<br>STM32G473RE | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32G473VB<br>STM32G473VC<br>STM32G473VE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G474CB<br>STM32G474CC<br>STM32G474CE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G474MB<br>STM32G474MC<br>STM32G474ME | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G474PB<br>STM32G474PC<br>STM32G474PE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G474QB<br>STM32G474QC<br>STM32G474QE | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G474RB<br>STM32G474RC<br>STM32G474RE | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32G474VB<br>STM32G474VC<br>STM32G474VE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G483CE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G483ME | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G483PE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G483QE | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G483RE | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32G483VE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G484CE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G484ME | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G484PE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G484QE | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G484RE | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32G484VE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G491CC<br>STM32G491CE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G491KC<br>STM32G491KE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G491MC<br>STM32G491ME | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G491RC<br>STM32G491RE | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32G491VC<br>STM32G491VE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G4A1CE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G4A1KE | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32G4A1ME | Generic Board | *2.4.0* |  |
| :green_heart: | STM32G4A1RE | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32G4A1VE | Generic Board | *2.4.0* |  |

### Generic STM32H5 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32H503RB | Generic Board | *2.7.0* |  |
| :green_heart:  | STM32H563IIKxQ | Generic Board | *2.6.0* |  |
| :green_heart:  | STM32H563ZG<br>STM32H563ZI | Generic Board | *2.6.0* |  |
| :green_heart:  | STM32H573IIKxQ | Generic Board | *2.6.0* |  |
| :green_heart:  | STM32H573ZI | Generic Board | *2.6.0* |  |

### Generic STM32H7 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32H723ZE<br>STM32H723ZG | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32H730ZBT | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32H733ZGT | Generic Board | *2.4.0* |  |
| :green_heart: | STM32H742IG<br>STM32H742II | Generic Board | *2.1.0* |  |
| :green_heart: | STM32H742VG<br>STM32H742VI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H742XG<br>STM32H742XI | Generic Board | *2.7.0* |  |
| :green_heart: | STM32H742ZG<br>STM32H742ZI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H743IG<br>STM32H743II | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H743VG<br>STM32H743VI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H743VI | [DevEBox H743VIT6](https://github.com/mcauser/MCUDEV_DEVEBOX_H7XX_M) | *2.2.0* | |
| :green_heart: | STM32H743VI | [WeAct MiniSTM32H743VIT6](https://github.com/WeActStudio/MiniSTM32H7xx) | *2.2.0* | [More info](https://github.com/stm32duino/Arduino_Core_STM32/pull/1552) |
| :green_heart: | STM32H743XG<br>STM32H743XI | Generic Board | *2.7.0* |  |
| :green_heart: | STM32H743ZG<br>STM32H743ZI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H745XG<br>STM32H745XI | Generic Board | *2.7.0* |  |
| :green_heart: | STM32H747AG<br>STM32H747AI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H747IG<br>STM32H747II | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H747XG<br>STM32H747XI | Generic Board | *2.7.0* |  |
| :green_heart: | STM32H750ZB | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H750IB<br>STM32H750II | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H750IB | [Daisy](https://www.electro-smith.com/daisy/daisy) | *1.9.0* |  |
| :green_heart: | STM32H750IB | [Daisy Patch SM](https://www.electro-smith.com/daisy/patch-sm) | *2.2.0* |  |
| :green_heart: | STM32H750IB | [Daisy Petal SM](https://www.electro-smith.com) | *2.2.0* |  |
| :green_heart: | STM32H750VB | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H750VB | [DevEBox H750VBT6](https://github.com/mcauser/MCUDEV_DEVEBOX_H7XX_M) | *2.2.0* | |
| :green_heart: | STM32H750VB | [WeAct MiniSTM32H750VBT6](https://github.com/WeActStudio/MiniSTM32H7xx) | *2.2.0* | [More info](https://github.com/stm32duino/Arduino_Core_STM32/pull/1552) |
| :green_heart: | STM32H750XB | Generic Board | *2.7.0* |  |
| :green_heart: | STM32H753VI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H753XI | Generic Board | *2.7.0* |  |
| :green_heart: | STM32H753ZI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H755XI | Generic Board | *2.7.0* |  |
| :green_heart: | STM32H757AI | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H757II | Generic Board | *2.0.0* |  |
| :green_heart: | STM32H757XI | Generic Board | *2.7.0* |  |
| :yellow_heart: | STM32H7B0VBTX | Generic Board | *2.7.0* |  |
| :yellow_heart: | STM32H7B0VBTX | Generic Board | *2.7.0* |  |

### Generic STM32L0 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32L010C6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L010F4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L010R8 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L010RB | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L011D3<br>STM32L011D4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L011E3<br>STM32L011E4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L011F3<br>STM32L011F4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L011G3<br>STM32L011G4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L011K3<br>STM32L011K4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L021F4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L021D4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L021F4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L021G4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L021K4 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L031C4<br>STM32L031C6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L031E4<br>STM32L031E6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L031F4<br>STM32L031F6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L031G4<br>STM32L031G6 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L031K4T<br>STM32L031K6T | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L041C4<br>STM32L041C6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L041E6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L041F6 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L041G6 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L041K6T | Generic Board | *2.0.0* |  |
| :green_heart: | STM32L051C6<br>STM32L051C8 | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L052C6<br>STM32L052C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L052K6<br>STM32L052K8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L052R6<br>STM32L052R8 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L052R6T<br>STM32L052R8T | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L052T6<br>STM32L052T8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L053C6<br>STM32L053C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L053R6<br>STM32L053R8 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L053R6T<br>STM32L053R8T | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L062C8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L062K8 | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L063C8 | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L063R8T | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L072CB<br>STM32L072CZ | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L072CBY<br>STM32L072CZE<br>STM32L072CZY | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L072KB<br>STM32L072KZ | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L072KBT<br>STM32L072KZT | Generic Board | *2.0.0* |  |
| :green_heart: | STM32L072KZT | [ThunderPack v1.0](https://github.com/jgillick/ThunderPack) | *1.8.0* |  |
| :green_heart: | STM32L072RBT | [PX-HER0](https://piconomix.com/) | *1.8.0* |  |
| :green_heart:  | STM32L072RB<br>STM32L072RZ | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L072RBT<br>STM32L072RZT | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L072V8<br>STM32L072VB<br>STM32L072VZ | Generic Board | *2.4.0* |
| :green_heart:  | STM32L073CB<br>STM32L073CZ | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L073CZY | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L073RB<br>STM32L073RZ | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L073RBT<br>STM32L073RZT | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L073V8<br>STM32L073VB<br>STM32L073VZ | Generic Board | *2.4.0* |
| :green_heart:  | STM32L082CZ | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L082CZY | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L082KB<br>STM32L082KZ | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L082KBT<br>STM32L082KZT | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L083CB | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L083CZ | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L083RB | Generic Board | *2.4.0* |  |
| :green_heart: | STM32L083RBT<br>STM32L083RZT | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L083RZ | Generic Board | *2.4.0* |  |
| :green_heart:  | STM32L083V8<br>STM32L083VB<br>STM32L083VZ | Generic Board | *2.4.0* |

### Generic STM32L1 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32L100C6<br>STM32L100C6-A | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L151C6<br>STM32L151C8<br>STM32L151CB | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L151C6-A<br>STM32L151C8-A<br>STM32L151CB-A | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L152C6<br>STM32L152C8<br>STM32L152CB | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L152C6-A<br>STM32L152C8-A<br>STM32L152CB-A | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L151RE | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L151ZD | Generic Board | *2.6.0* |  |
| :green_heart:  | STM32L152RE | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L152ZD | Generic Board | *2.6.0* |  |
| :green_heart:  | STM32L162RE | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L162ZD | Generic Board | *2.6.0* |  |

### Generic STM32L4 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32L412K8<br>STM32L412KB<br>STM32L422KB | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L431RB<br>STM32L431RC | Generic Board | *2.3.0* |  |
| :green_heart:  | STM32L432KB<br>STM32L432KC<br>STM32L442KC | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L433CBT<br>STM32L433CCT | Generic Board | *2.1.0* |  |
| :green_heart:  | STM32L433CBU<br>STM32L433CCU | Generic Board | *2.1.0* |  |
| :green_heart:  | STM32L443CC<br>STM32L443CC | Generic Board | *2.1.0* |  |
| :green_heart:  | STM32L433RC<br>STM32L443RC<br>STM32L433RB | Generic Board | *2.6.0* |  |
| :green_heart:  | STM32L433RC-P | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L452RC<br>STM32L452RE<br>STM32L462RE | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L452RE | [Leafony AP03](https://docs.leafony.com/en/docs/leaf/processor/ap03) | *2.4.0* |
| :green_heart:  | STM32L452RE-P | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L475VC<br>STM32L475VE<br>STM32L475VG | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L476VC<br>STM32L476VE<br>STM32L476VG | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L476RC<br>STM32L476RE<br>STM32L476RG | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L486VG | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L496ZE<br>STM32L496ZG | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L496ZG-P | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4A6ZG | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4A6ZG-P | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4R5VG<br>STM32L4R5VI | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4R5ZGTx<br>STM32L4R5ZITx | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4R5ZGYx<br>STM32L4R5ZIYx | Generic Board | *2.1.0* |  |
| :green_heart:  | STM32L4R5ZI-P | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4R7VITx | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4R7ZITx | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4R9ZGJx<br>STM32L4R9ZIJx | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4R9ZGYx<br>STM32L4R9ZIYx | Generic Board | *2.1.0* |  |
| :green_heart:  | STM32L4S5VI | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4S5ZITx | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4S5ZIYx | Generic Board | *2.1.0* |  |
| :green_heart:  | STM32L4S7VI | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4S7ZITx | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4S9ZIJx | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L4S9ZIYx | Generic Board | *2.1.0* |  |

### Generic STM32L5 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32L552ZC-Q<br>STM32L552ZE-Q | Generic Board | *2.0.0* |  |
| :green_heart:  | STM32L562ZE-Q | Generic Board | *2.0.0* |  |

### Generic STM32U5 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32U575AGIxQ<br>STM32U575AIIxQ | Generic Board | *2.1.0* |  |
| :green_heart:  | STM32U575CGx<br>STM32U575CIx | Generic Board | *2.7.0* |  |
| :green_heart:  | STM32U575ZGTxQ<br>STM32U575ZITxQ | Generic Board | *2.1.0* |  |
| :green_heart:  | STM32U585AIIxQ | Generic Board | *2.1.0* |  |
| :green_heart:  | STM32U585CIx | Generic Board | *2.7.0* |  |
| :green_heart:  | STM32U585ZITxQ | Generic Board | *2.1.0* |  |

### Generic STM32WB boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32WB15CCU | Generic Board | *2.5.0* |  |
| :green_heart: | STM32WB55CC<br>STM32WB55CE<br>STM32WB55CG | Generic Board | *2.0.0* |  |
| :green_heart: | STM32WB5MMG | Generic Board | *2.1.0* |  |
| :green_heart: | STM32WB55RC<br>STM32WB55RE<br>STM32WB55RG | Generic Board | *2.0.0* |  |

### Generic STM32WBA boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :yellow_heart: | STM32WBA55CEU<br>STM32WBA55CGU | Generic Board | **2.8.0** |  |

### Generic STM32WL boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32WL55CC | [Generic Node Sensor Edition](https://www.genericnode.com/docs/sensor-edition) (GNSE) by TTI | *2.1.0* | [GNSE GitHub](https://github.com/TheThingsIndustries/generic-node-se) |
| :green_heart: | STM32WL54CC<br>STM32WL55CC | Generic Board | *2.1.0* |  |
| :green_heart: | STM32WL55JC<br>STM32WL55JC | Generic Board | *2.1.0* |  |
| :green_heart: | STM32WLE4C8<br>STM32WLE4CB<br>STM32WLE4CC | Generic Board | *2.1.0* |  |
| :green_heart: | STM32WLE4J8<br>STM32WLE4JB<br>STM32WLE4JC | Generic Board | *2.1.0* |  |
| :green_heart: | STM32WLE5C8<br>STM32WLE5CB<br>STM32WLE5CC | Generic Board | *2.1.0* |  |
| :green_heart: | STM32WLE5J8<br>STM32WLE5JB<br>STM32WLE5JC | Generic Board | *2.1.0* |  |

### 3D printer boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F407VE | [ARMED V1](https://github.com/ktand/Armed) | *1.5.0* |  |
| :green_heart:  | STM32F030   | [EExtruder F030 V1](https://github.com/ghent360/PrntrBoard/tree/tmc2130-redesign/EExtruder) | *1.5.0* | Small companion board for Prntr Board V1 |
| :green_heart:  | STM32F103C8 | [Malyan M200 V1](http://malyansys.com/product/m200-v1/) | *1.5.0* |  |
| :green_heart:  | STM32F070C8 | [Malyan M200 V2](http://malyansys.com/product/m200-v2/) | *1.5.0* |  |
| :green_heart:  | STM32F070C8 | [Malyan M300](http://malyansys.com/product/m300/) | *1.8.0* |  |
| :green_heart:  | STM32F407VE | [Prntr Board V1](https://github.com/ghent360/PrntrBoard) | *1.5.0* |  |
| :green_heart:  | STM32F407VE | [Prntr Board V2](https://github.com/ghent360/PrntrBoardV2) | *1.8.0* |  |
| :green_heart:  | STM32F765VI | [RemRam v1](https://github.com/hasenbanck/remram) | *1.4.0* |  |
| :green_heart:  | STM32F446VE | [RUMBA32](https://github.com/Aus3D/RUMBA32) | *1.5.0* |  |
| :green_heart:  | STM32F401VE | [STEVAL-3DP001V1](https://www.st.com/en/evaluation-tools/steval-3dp001v1.html) | *1.6.0* |  |
| :green_heart:  | STM32F446RE | [VAkE v1.0](https://www.facebook.com/pages/category/Product-Service/VAkE-Board-2290066274575218/) | *1.6.0* |  |
| :green_heart:  | STM32F446VE | [FYSETC_S6](https://wiki.fysetc.com/FYSETC_S6/) | *1.9.0* | |
| :green_heart:  | STM32G0B1CB | [BTT EBB42 CAN V1.1](https://github.com/bigtreetech/EBB/tree/master/EBB%20CAN%20V1.1%20(STM32G0B1)/EBB42%20CAN%20V1.1) | *2.4.0* |  |

### [Blues Wireless](https://blues.io/) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32L4R5ZIYx | [Swan R5](https://blues.io/products/swan) | *2.1.0* |  |

### [Elecgator](https://www.elecgator.com/) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F746ZET | [EtherCATduino](https://www.elecgator.com/products/info/EtherCATduino) | *2.1.0* |  |

### Electronic Speed Controller boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F051K6U | Wraith V1 ESC | *1.8.0* |  |
| :green_heart:  | STM32F103RCT | [STorM32 V1.31 RC](http://www.olliw.eu/storm32bgc-wiki/STorM32_Boards#STorM32-BGC_v1.3) | *2.1.0* |  |

### [Garatronic](https://www.garatronic.fr)/[McHobby](https://shop.mchobby.be) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F072RB | [PYBStick 26 Duino](https://shop.mchobby.be/fr/compatibles-arduino/1851-pybstick-duino-arduino-uniquement-3232100018518-garatronic.html) | *1.9.0* | [More info](https://github.com/mchobby/pyboard-driver/tree/master/PYBStick) |
| :green_heart:  | STM32F401CE | [PYBStick 26 Lite](https://shop.mchobby.be/fr/micropython/1830-pybstick-lite-26-micropython-et-arduino-3232100018303-garatronic.html) | *1.9.0* | [More info](https://github.com/mchobby/pyboard-driver/tree/master/PYBStick) |
| :green_heart:  | STM32F411RE | [PYBStick 26 Standard](https://shop.mchobby.be/fr/micropython/1844-pybstick-standard-26-micropython-et-arduino-3232100018440-garatronic.html) | *1.9.0* | [More info](https://github.com/mchobby/pyboard-driver/tree/master/PYBStick) |
| :green_heart:  | STM32F412RE | [PYBStick 26 Pro](https://shop.mchobby.be/fr/micropython/1850-pybstick-pro-26-micropython-et-arduino-3232100018501-garatronic.html) | *1.9.0* | [More info](https://github.com/mchobby/pyboard-driver/tree/master/PYBStick) |

### Generic flight controllers

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F103CB | Afro Flight Rev5 (8/12MHz) | *1.7.0* |  |
| :green_heart:  | STM32F303CC | [Sparky V1](https://github.com/TauLabs/TauLabs/wiki/Sparky) | *1.6.0* |  |

### [IoT continuum](https://iotjourney.orange.com/fr-FR) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32U585CIU6 | [IoT continuum DevKit Board - STM32U585CIU6](https://iotjourney.orange.com/en/iotcontinuum/kits) | *2.7.0* |  |

### LoRa boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32L073RZ | [AcSIP S76S](https://www.acsip.com.tw) | *2.3.0* |  |
| :green_heart:  | STM32F072C8<br>STM32F072CB | [Elektor LoRa Node](https://github.com/ElektorLabs/180516-Elektor_LoRa_Node) | *1.8.0* | [More info](https://www.elektormagazine.com/labs/lorawan-node-experimental-platform) |
| :green_heart:  | STM32WLE5JC | [LoRa-E5 mini](https://wiki.seeedstudio.com/LoRa_E5_mini/) | *2.6.0* |  |
| :green_heart:  | STM32WLE5CC | [RAK3172 Module](https://github.com/RAKWireless/rakwireless-docs/tree/master/docs/Product-Categories/WisDuo/RAK3172-Module) | *2.6.0* |  |
| :green_heart:  | STM32L151CB | [RAK811 LoRa Tracker](https://www.rakwireless.com/en/) | *1.4.0* | [Wiki](https://github.com/stm32duino/Arduino_Core_STM32/wiki/Connectivities#lora) |
| :green_heart:  | STM32L051C8 | [RHF76-052](https://lora-alliance.org/lora_products/rhf76-052/) | *1.7.0* | Basic support |

### Midatronics boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32WB55CE | SharkyMKR | *1.7.0* |  |

### [SparkFun](https://www.sparkfun.com/) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32F405RG | [SparkFun MicroMod Processor Board - STM32F405](https://www.sparkfun.com/products/21326) | *2.6.0* |  |
| :green_heart: | STM32WB5MMG | [SparkFun MicroMod Processor Board - STM32WB5MMG](https://www.sparkfun.com/products/21438) | *2.6.0* |  |

### [ELV Boards](https://de.elv.com/lorawan)

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :yellow_heart:  | STM32WLE5JB | ELV-BM-TRX1 | **2.8.0** |  |

## Next release

See [milestones](https://github.com/stm32duino/Arduino_Core_STM32/milestones) to have an overview of the next release content.

## Troubleshooting

For question, support, ...,  you could submit a topic on the [stm32duino forum](http://stm32duino.com).

If you have any issue, you could [file an issue on GitHub](https://github.com/stm32duino/Arduino_Core_STM32/issues/new).

In any case, it always fine to search if your issue was not already existing before submit a new one.
