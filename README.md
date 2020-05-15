# Arduino core support for STM32 based boards
[![forums](https://img.shields.io/badge/join-the%20forums-blue.svg)](https://www.stm32duino.com/)
[![wiki](https://img.shields.io/badge/browse-the%20wiki-orange.svg)](https://github.com/stm32duino/wiki/wiki)
![STM32 Core Continuous Integration](https://github.com/stm32duino/Arduino_Core_STM32/workflows/STM32%20Core%20Continuous%20Integration/badge.svg?branch=master)

[![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
![GitHub All Releases](https://img.shields.io/github/downloads/stm32duino/Arduino_Core_STM32/total.svg?label=downloads%20since%201.4.0)
[![GitHub commits](https://img.shields.io/github/commits-since/stm32duino/Arduino_Core_STM32/1.8.0.svg)](https://github.com/stm32duino/Arduino_Core_STM32/compare/1.9.0...master)
<!-- [![Build Status](https://travis-ci.com/stm32duino/Arduino_Core_STM32.svg?branch=master)](https://travis-ci.com/stm32duino/Arduino_Core_STM32) -->

* [Introduction](https://github.com/stm32duino/Arduino_Core_STM32#Introduction)<br>
* [Getting Started](https://github.com/stm32duino/Arduino_Core_STM32#getting-started)<br>
* [Supported boards](https://github.com/stm32duino/Arduino_Core_STM32#supported-boards)<br>
* [Troubleshooting](https://github.com/stm32duino/Arduino_Core_STM32#troubleshooting)<br>
* [Wiki](https://github.com/stm32duino/wiki/wiki/)

## Introduction

This repo adds the support of STM32 MCU in Arduino IDE.<br>

This porting is based on:
* [STM32Cube MCU Packages](https://www.st.com/en/embedded-software/stm32cube-mcu-packages.html) including:
    * The HAL hardware abstraction layer, enabling portability between different STM32 devices via standardized API calls
    * The Low-Layer (LL) APIs, a light-weight, optimized, expert oriented set of APIs designed for both performance and runtime efficiency
    * CMSIS device defintion for STM32
* [CMSIS](https://developer.arm.com/embedded/cmsis): Cortex Microcontroller Software Interface Standard (CMSIS) is a vendor-independent hardware abstraction layer for the Cortex®-M processor series and defines generic tool interfaces. It has been packaged as a module for Arduino IDE: https://github.com/stm32duino/ArduinoModule-CMSIS
* [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm): Arm Embedded GCC compiler, libraries and other GNU tools necessary for bare-metal software development on devices based on the Arm Cortex-M. Packages are provided thanks [The xPack GNU Arm Embedded GCC](https://xpack.github.io/arm-none-eabi-gcc/): https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack

## Getting Started

This repo is available as a package usable with [Arduino Boards Manager](https://www.arduino.cc/en/guide/cores).

Use this link in the "*Additional Boards Managers URLs*" field:

https://github.com/stm32duino/BoardManagerFiles/raw/master/STM32/package_stm_index.json


For full instructions on using the "**Boards Manager**", see the [Getting Started](https://github.com/stm32duino/wiki/wiki/Getting-Started) page.

Advanced user can use the repository to benefit from the latest development. See the [Using git repository](https://github.com/stm32duino/wiki/wiki/Using-git-repository) page.

User can add a STM32 based board following this [wiki](https://github.com/stm32duino/wiki/wiki/Add-a-new-variant-(board)).

## Supported boards

 - [Nucleo 144 boards](#nucleo-144-boards)
 - [Nucleo 64 boards](#nucleo-64-boards)
 - [Nucleo 32 boards](#nucleo-32-boards)
 - [Discovery boards](#discovery-boards)
 - [Eval boards](#eval-boards)
 - [STM32MP1 series coprocessor boards](#stm32mp1-series-coprocessor-boards)
 - [Generic STM32F0 boards](#generic-stm32f0-boards)
 - [Generic STM32F1 boards](#generic-stm32f1-boards)
 - [Generic STM32F3 boards](#generic-stm32f3-boards)
 - [Generic STM32F4 boards](#generic-stm32f4-boards)
 - [Generic STM32H7 boards](#generic-stm32h7-boards)
 - [Generic STM32L0 boards](#generic-stm32l0-boards)
 - [3D printer boards](#3d-printer-boards)
 - [LoRa boards](#lora-boards)
 - [Electronic Speed Controller boards](#electronic-speed-controller-boards)
 - [Generic flight controllers](#generic-flight-controllers)
 - [Garatronics boards](#Garatronic/McHobby-boards)
 - [Midatronics boards](#midatronics-boards)


### [Nucleo 144](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-nucleo-boards.html)

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F207ZG | [Nucleo F207ZG](http://www.st.com/en/evaluation-tools/nucleo-f207zg.html) | *0.2.0* |  |
| :green_heart:  | STM32F429ZI | [Nucleo F429ZI](http://www.st.com/en/evaluation-tools/nucleo-f429zi.html) | *0.1.0* |  |
| :green_heart:  | STM32F767ZI | [Nucleo F767ZI](http://www.st.com/en/evaluation-tools/nucleo-f767zi.html) | *1.4.0* |  |
| :green_heart:  | STM32F746ZG | [Nucleo F746ZG](https://www.st.com/en/evaluation-tools/nucleo-f746zg.html) | *1.9.0* |  |
| :green_heart:  | STM32F756ZG | [Nucleo F756ZG](https://www.st.com/en/evaluation-tools/nucleo-f756zg.html) | *1.9.0* |  |
| :green_heart:  | STM32L496ZG | [Nucleo L496ZG](http://www.st.com/en/evaluation-tools/nucleo-l496zg.html) | *1.3.0* |  |
| :green_heart:  | STM32L496ZG-P | [Nucleo L496ZG-P](http://www.st.com/en/evaluation-tools/nucleo-l496zg-p.html) | *1.3.0* |  |
| :green_heart:  | STM32L4R5ZI | [Nucleo L4R5ZI](http://www.st.com/en/evaluation-tools/nucleo-l4r5zi.html) | *1.4.0* |  |
| :green_heart:  | STM32L4R5ZI-P | [Nucleo L4R5ZI-P](http://www.st.com/en/evaluation-tools/nucleo-l4r5zi-p.html) | *1.4.0* |  |
| :green_heart:  | STM32H743ZI | [Nucleo H743ZI(2)](https://www.st.com/en/evaluation-tools/nucleo-h743zi.html) | *1.5.0* | Nucleo H743ZI2 since 1.6.0 |

### [Nucleo 64](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-nucleo-boards.html)

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F030R8 | [Nucleo F030R8](http://www.st.com/en/evaluation-tools/nucleo-f030r8.html) | *0.2.0* |  |
| :green_heart:  | STM32F072RB | [Nucleo F072RB](http://www.st.com/en/evaluation-tools/nucleo-f072rb.html) | *1.9.0* |  |
| :green_heart:  | STM32F091RC | [Nucleo F091RC](http://www.st.com/en/evaluation-tools/nucleo-f091rc.html) | *0.1.0* |  |
| :green_heart:  | STM32F103RB | [Nucleo F103RB](http://www.st.com/en/evaluation-tools/nucleo-f103rb.html) | *0.2.0* |  |
| :green_heart:  | STM32F302R8 | [Nucleo F302R8](http://www.st.com/en/evaluation-tools/nucleo-f302r8.html) | *1.1.0* |  |
| :green_heart:  | STM32F303RE | [Nucleo F303RE](http://www.st.com/en/evaluation-tools/nucleo-f303re.html) | *0.1.0* |  |
| :green_heart:  | STM32F401RE | [Nucleo F401RE](http://www.st.com/en/evaluation-tools/nucleo-f401re.html) | *0.2.1* |  |
| :green_heart:  | STM32F411RE | [Nucleo F411RE](http://www.st.com/en/evaluation-tools/nucleo-f411re.html) | *0.2.1* |  |
| :green_heart:  | STM32F446RE | [Nucleo F446RE](http://www.st.com/en/evaluation-tools/nucleo-f446re.html) | *1.1.1* |  |
| :green_heart:  | STM32G071RB | [Nucleo G071RB](https://www.st.com/en/evaluation-tools/nucleo-g071rb.html) | *1.6.0* |  |
| :green_heart:  | STM32G431RB | [Nucleo G431RB](https://www.st.com/en/evaluation-tools/nucleo-g431rb.html) | *1.7.0* |  |
| :green_heart:  | STM32G474RE | [Nucleo G474RE](https://www.st.com/en/evaluation-tools/nucleo-g474re.html) | *1.7.0* |  |
| :green_heart:  | STM32L053R8 | [Nucleo L053R8](http://www.st.com/en/evaluation-tools/nucleo-l053r8.html) | *0.1.0* |  |
| :green_heart:  | STM32L073RZ | [Nucleo L073RZ](http://www.st.com/en/evaluation-tools/nucleo-l073rz.html) | *1.4.0* |  |
| :green_heart:  | STM32L152RE | [Nucleo L152RE](http://www.st.com/en/evaluation-tools/nucleo-l152re.html) | *1.0.0* |  |
| :green_heart:  | STM32L433RC-P | [Nucleo L433RC-P](https://www.st.com/en/evaluation-tools/nucleo-l433rc-p.html) | *1.9.0* |  |
| :green_heart:  | STM32L452RE | [Nucleo L452RE](http://www.st.com/en/evaluation-tools/nucleo-l452re.html) | *1.5.0* |  |
| :green_heart:  | STM32L452RE-P | [Nucleo L452RE-P](http://www.st.com/en/evaluation-tools/nucleo-l452re-p.html) | *1.8.0* |  |
| :green_heart:  | STM32L476RG | [Nucleo L476RG](http://www.st.com/en/evaluation-tools/nucleo-l476rg.html) | *0.1.0* |  |
| :green_heart:  | STM32WB55RG<br>STM32WB55CG | [P-Nucleo-WB55RG](https://www.st.com/en/evaluation-tools/p-nucleo-wb55.html) | *1.6.0* | No BLE support |

### [Nucleo 32](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-nucleo-boards.html) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F031K6 | [Nucleo F031K6](https://www.st.com/en/evaluation-tools/nucleo-f031k6.html) | *1.9.0* |  |
| :green_heart:  | STM32F303K8 | [Nucleo F303K8](http://www.st.com/en/evaluation-tools/nucleo-f303k8.html) | *1.1.0* |  |
| :green_heart:  | STM32G431KB | [Nucleo G431KB](https://www.st.com/en/evaluation-tools/nucleo-g431kb.html) | *1.7.0* |  |
| :green_heart:  | STM32L031K6 | [Nucleo L031K6](http://www.st.com/en/evaluation-tools/nucleo-l031k6.html) | *1.1.1* |  |
| :green_heart:  | STM32L412KB | [Nucleo L412KB](http://www.st.com/en/evaluation-tools/nucleo-l412kb.html) | *1.5.0* |  |
| :green_heart:  | STM32L432KC | [Nucleo L432KC](http://www.st.com/en/evaluation-tools/nucleo-l432kc.html) | *0.2.0* |  |

### [Discovery](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-discovery-kits.html) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F030R8 | [32F0308DISCOVERY](http://www.st.com/en/evaluation-tools/32f0308discovery.html) | *1.3.0* |  |
| :green_heart:  | STM32F072RB | [32F072BDISCOVERY](https://www.st.com/en/evaluation-tools/32f072bdiscovery.html) | *1.5.0* |  |
| :green_heart:  | STM32F100RB | [STM32VLDISCOVERY](https://www.st.com/en/evaluation-tools/stm32vldiscovery.html) | 0.2.1 |  |
| :green_heart:  | STM32F407VG | [STM32F407G-DISC1](http://www.st.com/en/evaluation-tools/stm32f4discovery.html) | *0.1.0* |  |
| :green_heart:  | STM32F746NG | [STM32F746G-DISCOVERY](http://www.st.com/en/evaluation-tools/32f746gdiscovery.html) | *0.1.0* |  |
| :green_heart:  | STM32G031J6 | [STM32G0316-DISCO](https://www.st.com/en/evaluation-tools/stm32g0316-disco.html) | *1.9.0* |  |
| :green_heart:  | STM32L072CZ | [B-L072Z-LRWAN1](http://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html) | *1.1.0* |  |
| :green_heart:  | STM32L475VG | [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) | *1.0.1* |  |
| :green_heart:  | STM32F413ZH | [32F413HDISCOVERY](https://www.st.com/en/evaluation-tools/32f413hdiscovery.html) | *1.9.0* |  |

### [Eval](https://www.st.com/en/evaluation-tools/stm32-eval-boards.html) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32L4R9ZI | [STEVAL-MKSBOX1V1 (SensorTile.box)](https://www.st.com/en/evaluation-tools/steval-mksbox1v1.html) | *1.7.0* |  |

### [STM32MP1 series coprocessor](https://www.st.com/content/st_com/en/products/microcontrollers-microprocessors/stm32-arm-cortex-mpus/stm32mp1-series.html) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32MP157A | [STM32MP157A-DK1](https://www.st.com/en/evaluation-tools/stm32mp157a-dk1.html) | *1.8.0* | See [the documentation](https://github.com/stm32duino/Arduino_Core_STM32/tree/master/variants/STM32MP157_DK/README.md) to use this board|
| :green_heart:  | STM32MP157C | [STM32MP157C-DK2](https://www.st.com/en/evaluation-tools/stm32mp157c-dk2.html) | *1.8.0* | See [the documentation](https://github.com/stm32duino/Arduino_Core_STM32/tree/master/variants/STM32MP157_DK/README.md) to use this board|

### Generic STM32F0 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F030F4 | [STM32F030F4 Demo board](https://stm32-base.org/boards/STM32F030F4P6-STM32F030-DEMO-BOARD-V1.1) | *1.5.0* |  |

### Generic STM32F1 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F103C6<br>STM32F103C8<br>STM32F103CB | [Blue Pill](https://stm32-base.org/boards/STM32F103C8T6-Blue-Pill) | *1.2.0* | USB CDC support since *1.5.0*<br> Maple bootloaders support since *1.6.0* |
| :green_heart:  | STM32F103C8<br>STM32F103CB | [Black Pill](https://stm32-base.org/boards/STM32F103C8T6-Black-Pill) | *1.5.0* |  |
| :green_heart:  | STM32F103C4<br>STM32F103C6<br>STM32F103C8<br>STM32F103CB | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F103R6<br>STM32F103R8<br>STM32F103RB<br>STM32F103RC<br>STM32F103RD<br>STM32F103RE<br>STM32F103RF<br>STM32F103RG | [Generic Board](https://stm32-base.org/boards/STM32F103RET6-Generic-Board) | *1.9.0* |  |
| :green_heart:  | STM32F103T4<br>STM32F103T6<br>STM32F103T8<br>STM32F103TB | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F103V8<br>STM32F103VB<br>STM32F103VC<br>STM32F103VD<br>STM32F103VE<br>STM32F103VF<br>STM32F103VG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F103ZC<br>STM32F103ZD<br>STM32F103ZE<br>STM32F103ZF<br>STM32F103ZG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F103TB | HY-TinySTM103T | *1.5.0* | [More info](https://www.hotmcu.com/stm32f103tb-arm-cortex-m3-development-board-p-222.html) |
| :green_heart:  | STM32F103CB | Maple Mini | *1.2.0* | [More info](https://www.leaflabs.com/maple)<br>USB CDC support since *1.5.0*<br>Maple bootloaders support since *1.6.0* |
| :green_heart:  | STM32F103ZE | [vcc-gnd.com](https://stm32-base.org/boards/STM32F103ZET6-VCC-GND-XLarge) | *1.9.0* | [More info](http://www.vcc-gnd.com/rtd/html/STM32/quickref.html#stm32f1) |
| :green_heart:  | STM32F103ZE | vcc-gnd.com Mini | *1.9.0* | [More info](http://www.vcc-gnd.com/rtd/html/STM32/quickref.html#stm32f1) |

### Generic STM32F3 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F303CC | [RobotDyn Black Pill](https://stm32-base.org/boards/STM32F303CCT6-RobotDyn-Black-Pill) | *1.6.1* | [More info](https://robotdyn.com/catalog/development-boards/stm-boards-and-shields.html) |

### Generic STM32F4 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F405RG | [Adafruit Feather STM32F405 Express](https://www.adafruit.com/product/4382) | *1.8.0* |  |
| :green_heart:  | STM32F401CC | [WeAct Black Pill](https://stm32-base.org/boards/STM32F401CCU6-WeAct-Black-Pill-V1.2) | *1.7.0* | [More info](https://github.com/WeActTC/MiniF4-STM32F4x1) |
| :green_heart:  | STM32F411CE | [WeAct Black Pill](https://stm32-base.org/boards/STM32F411CEU6-WeAct-Black-Pill-V2.0) | *1.9.0* | [More info](https://github.com/WeActTC/MiniF4-STM32F4x1) |
| :green_heart:  | STM32F407VE<br>STM32F407VG | [STM32 F4VE / Black F407VET6](https://stm32-base.org/boards/STM32F407VET6-STM32-F4VE-V2.0) | *1.4.0* | STM32F407VG support since *1.5.0* |
| :green_heart:  | STM32F407ZE<br>STM32F407ZG | Black F407ZE / Black F407ZG | *1.5.0* |  |
| :green_heart:  | STM32F407VE | [vcc-gnd.com Mini](https://stm32-base.org/boards/STM32F407VET6-VCC-GND-Small) | *1.4.0* | [More info](http://vcc-gnd.com/rtd/html/STM32/quickref.html#stm32f4) |
| :green_heart:  | STM32F401RC | [STM32F Core Board](https://stm32-base.org/boards/STM32F401RCT6-STM32F-Core-Board) | *1.7.0* |  |
| :green_heart:  | STM32F407VG | [DIYMORE STM32F407VGT](https://stm32-base.org/boards/STM32F407VGT6-diymore) | *1.5.0* |  |
| :green_heart:  | STM32F407VE | [FK407M1](https://stm32-base.org/boards/STM32F407VET6-FK407M1-V1.0) | *1.5.0* |  |
| :green_heart:  | STM32F401CB<br>STM32F401CC<br>STM32F401CD<br>STM32F401CE | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F401RB<br>STM32F401RC<br>STM32F401RD<br>STM32F401RE | Generic Board | *1.8.0* |  |
| :green_heart:  | STM32F405RG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F407VE<br>STM32F407VG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F410C8<br>STM32F410CB | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F410R8<br>STM32F410RB | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F411CC<br>STM32F411CE | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F411RC<br>STM32F411RE | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F412CE<br>STM32F412CG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F412RE<br>STM32F412RG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F413CG<br>STM32F413CH | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F413RG<br>STM32F413RH | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F415RG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F417VE<br>STM32F417VG | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F423CH | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F423RH | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F446RC<br>STM32F446RE | Generic Board | *1.9.0* |  |
| :green_heart:  | STM32F411CE | [ThunderPack v1.1+](https://github.com/jgillick/ThunderPack) | *1.9.0* |  |

### Generic STM32H7 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32H750IB | [Daisy ](https://www.electro-smith.com/daisy/daisy) | *1.9.0* |  |

### Generic STM32L0 boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32L072RB | [PX-HER0](https://piconomix.com/fwlib/_p_i_c_o_n_o_m_i_x__s_t_m32__h_e_r_o__b_o_a_r_d.html) | *1.8.0* |  |
| :green_heart: | STM32L072KZ | [ThunderPack v1.0](https://github.com/jgillick/ThunderPack) | *1.8.0* |  |

### 3D printer boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F407VE | [ARMED V1](https://github.com/ktand/Armed) | *1.5.0* |  |
| :green_heart:  | STM32F030   | [EExtruder F030 V1](https://github.com/ghent360/PrntrBoard/tree/tmc2130-redesign/EExtruder) | *1.5.0* | Small companion board for Prntr Board V1 |
| :green_heart:  | STM32F103C8 | [Malyan M200 V1](http://malyansys.com/product/m200-v1/) | *1.5.0* |  |
| :green_heart:  | STM32F070C8 | [Malyan M200 V2](http://malyansys.com/product/m200-v2/) | *1.5.0* |  |
| :green_heart:  | STM32F070C8 | [Malyan M300](http://malyansys.com/product/m300/) | *1.8.0* |  |
| :green_heart:  | N.A.        | [Prntr Board V1](https://github.com/ghent360/PrntrBoard) | *1.5.0* |  |
| :green_heart:  | N.A.        | [Prntr Board V2](https://github.com/ghent360/PrntrBoardV2) | *1.8.0* |  |
| :green_heart:  | STM32F765VI | [RemRam v1](https://github.com/hasenbanck/remram) | *1.4.0* |  |
| :green_heart:  | STM32F446VE | [RUMBA32](https://github.com/Aus3D/RUMBA32) | *1.5.0* |  |
| :green_heart:  | STM32F401VE | [STEVAL-3DP001V1](https://www.st.com/en/evaluation-tools/steval-3dp001v1.html) | *1.6.0* |  |
| :green_heart:  | STM32F446RE | [VAkE v1.0](https://www.facebook.com/pages/category/Product-Service/VAkE-Board-2290066274575218/) | *1.6.0* |  |
| :green_heart:  | STM32F446VE | [FYSETC_S6](https://wiki.fysetc.com/FYSETC_S6/) | *1.9.0* | |

### LoRa boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F072C8<br>STM32F072CB | [Elektor LoRa Node](https://github.com/ElektorLabs/180516-Elektor_LoRa_Node) | *1.8.0* | [More info](https://www.elektormagazine.com/labs/lorawan-node-experimental-platform) |
| :green_heart:  | STM32L151RB | [RAK811 LoRa Tracker](https://www.rakwireless.com/en/) | *1.4.0* | [Wiki](https://github.com/stm32duino/wiki/wiki/Connectivities#lora) |
| :green_heart:  | STM32L052C8 | [RHF76-052](https://www.ai-thinker.com/) | *1.7.0* | Basic support |

### Electronic Speed Controller boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F051K6 | Wraith V1 ESC | *1.8.0* |  |

### Generic flight controllers

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F103CB | Afro Flight Rev5 (8/12MHz) | *1.7.0* |  |
| :green_heart:  | STM32F303CC | [Sparky V1](https://github.com/TauLabs/TauLabs/wiki/Sparky) | *1.6.0* |  |

### [Garatronic](https://www.garatronic.fr)/[McHobby](https://shop.mchobby.be) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32F072RB | [PYBStick 26 Duino](https://shop.mchobby.be/fr/compatibles-arduino/1851-pybstick-duino-arduino-uniquement-3232100018518-garatronic.html) | *1.9.0* | [More info](https://github.com/mchobby/pyboard-driver/tree/master/PYBStick) |
| :green_heart:  | STM32F401CE | [PYBStick 26 Lite](https://shop.mchobby.be/fr/micropython/1830-pybstick-lite-26-micropython-et-arduino-3232100018303-garatronic.html) | *1.9.0* | [More info](https://github.com/mchobby/pyboard-driver/tree/master/PYBStick) |
| :green_heart:  | STM32F411RE | [PYBStick 26 Standard](https://shop.mchobby.be/fr/micropython/1844-pybstick-standard-26-micropython-et-arduino-3232100018440-garatronic.html) | *1.9.0* | [More info](https://github.com/mchobby/pyboard-driver/tree/master/PYBStick) |
| :green_heart:  | STM32F412RE | [PYBStick 26 Pro](https://shop.mchobby.be/fr/micropython/1850-pybstick-pro-26-micropython-et-arduino-3232100018501-garatronic.html) | *1.9.0* | [More info](https://github.com/mchobby/pyboard-driver/tree/master/PYBStick) |

### [Midatronics](https://midatronics.com/) boards

| Status | Device(s) | Name | Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart:  | STM32WB55CG | [SharkyMKR](https://midatronics.com/shop/development-boards/mkr-sharky-i/) | *1.7.0* |  |

## Next release

See [milestones](https://github.com/stm32duino/Arduino_Core_STM32/milestones) to have an overview of the next release content.

## Troubleshooting

For question, support, ...,  you could submit a topic on the [stm32duino forum](http://stm32duino.com).

If you have any issue, you could [file an issue on Github](https://github.com/stm32duino/Arduino_Core_STM32/issues/new).

In any case, it always fine to search if your issue was not already existing before submit a new one.
