# Arduino core support for STM32 based boards
[![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
[![GitHub commits](https://img.shields.io/github/commits-since/stm32duino/Arduino_Core_STM32/1.5.0.svg)](https://github.com/stm32duino/Arduino_Core_STM32/compare/1.5.0...master)
[![Build Status](https://travis-ci.com/stm32duino/Arduino_Core_STM32.svg?branch=master)](https://travis-ci.com/stm32duino/Arduino_Core_STM32)

* [Introduction](https://github.com/stm32duino/Arduino_Core_STM32#Introduction)<br>
* [Getting Started](https://github.com/stm32duino/Arduino_Core_STM32#getting-started)<br>
* [Boards available](https://github.com/stm32duino/Arduino_Core_STM32#boards-available)<br>
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
* [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm): Arm Embedded GCC compiler, libraries and other GNU tools necessary for bare-metal software development on devices based on the Arm Cortex-M. Packages are provided thanks: https://github.com/stm32duino/arm-none-eabi-gcc


## Getting Started

This repo is available as a package usable with [Arduino Boards Manager](https://www.arduino.cc/en/guide/cores).

Use this link in the "*Additional Boards Managers URLs*" field:

https://github.com/stm32duino/BoardManagerFiles/raw/master/STM32/package_stm_index.json


For full instructions on using the "**Boards Manager**", see the [Getting Started](https://github.com/stm32duino/wiki/wiki/Getting-Started) page.

Advanced user can use the repository to benefit from the latest development. See the [Using git repository](https://github.com/stm32duino/wiki/wiki/Using-git-repository) page.

User can add a STM32 based board following this [wiki](https://github.com/stm32duino/wiki/wiki/Add-a-new-variant-(board)).

## Boards available

| Status | [Nucleo 144](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-nucleo-boards.html) | Release | Comment |
| :---: | --- | :---: | :--- |
| :green_heart: | [Nucleo F207ZG](http://www.st.com/en/evaluation-tools/nucleo-f207zg.html) | *0.2.0* |  |
| :green_heart: | [Nucleo F429ZI](http://www.st.com/en/evaluation-tools/nucleo-f429zi.html) | *0.1.0* |  |
| :green_heart: | [Nucleo F767ZI](http://www.st.com/en/evaluation-tools/nucleo-f767zi.html) | *1.4.0* |  |
| :green_heart: | [Nucleo L496ZG](http://www.st.com/en/evaluation-tools/nucleo-l496zg.html) | *1.3.0* |  |
| :green_heart: | [Nucleo L496ZG-P](http://www.st.com/en/evaluation-tools/nucleo-l496zg-p.html) | *1.3.0* |  |
| :green_heart: | [Nucleo L4R5ZI](http://www.st.com/en/evaluation-tools/nucleo-l4r5zi.html) | *1.4.0* |  |
| :green_heart: | [Nucleo L4R5ZI-P](http://www.st.com/en/evaluation-tools/nucleo-l4r5zi-p.html) | *1.4.0* |  |
| :green_heart: | [Nucleo H743ZI](https://www.st.com/en/evaluation-tools/nucleo-h743zi.html) | *1.5.0* |  |

| Status | [Nucleo 64](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-nucleo-boards.html) | Release | Comment |
| :---: | --- | :---: | :--- |
| :green_heart: | [Nucleo F030R8](http://www.st.com/en/evaluation-tools/nucleo-f030r8.html) | *0.2.0* |  |
| :green_heart: | [Nucleo F091RC](http://www.st.com/en/evaluation-tools/nucleo-f091rc.html) | *0.1.0* |  |
| :green_heart: | [Nucleo F103RB](http://www.st.com/en/evaluation-tools/nucleo-f103rb.html) | *0.2.0* |  |
| :green_heart: | [Nucleo F302R8](http://www.st.com/en/evaluation-tools/nucleo-f302r8.html) | *1.1.0* |  |
| :green_heart: | [Nucleo F303RE](http://www.st.com/en/evaluation-tools/nucleo-f303re.html) | *0.1.0* |  |
| :green_heart: | [Nucleo F401RE](http://www.st.com/en/evaluation-tools/nucleo-f401re.html) | *0.2.1* |  |
| :green_heart: | [Nucleo F411RE](http://www.st.com/en/evaluation-tools/nucleo-f411re.html) | *0.2.1* |  |
| :green_heart: | [Nucleo F446RE](http://www.st.com/en/evaluation-tools/nucleo-f446re.html) | *1.1.1* |  |
| :green_heart: | [Nucleo L053R8](http://www.st.com/en/evaluation-tools/nucleo-l053r8.html) | *0.1.0* |  |
| :green_heart: | [Nucleo L073RZ](http://www.st.com/en/evaluation-tools/nucleo-l073rz.html) | *1.4.0* |  |
| :green_heart: | [Nucleo L152RE](http://www.st.com/en/evaluation-tools/nucleo-l152re.html) | *1.0.0* |  |
| :green_heart: | [Nucleo L452RE](http://www.st.com/en/evaluation-tools/nucleo-l452re.html) | *1.5.0* |  |
| :green_heart: | [Nucleo L476RG](http://www.st.com/en/evaluation-tools/nucleo-l476rg.html) | *0.1.0* |  |

| Status | [Nucleo 32](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-nucleo-boards.html) | Release | Comment |
| :---: | --- | :---: | :--- |
| :green_heart: | [Nucleo F303K8](http://www.st.com/en/evaluation-tools/nucleo-f303k8.html) | *1.1.0* |  |
| :green_heart: | [Nucleo L031K6](http://www.st.com/en/evaluation-tools/nucleo-l031k6.html) | *1.1.1* |  |
| :green_heart: | [Nucleo L412KB](http://www.st.com/en/evaluation-tools/nucleo-l412kb.html) | *1.5.0* |  |
| :green_heart: | [Nucleo L432KC](http://www.st.com/en/evaluation-tools/nucleo-l432kc.html) | *0.2.0* |  |

| Status | [Discovery](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-discovery-kits.html) | Release | Comment |
| :---: | --- | :---: | :--- |
| :green_heart: | [32F0308DISCOVERY](http://www.st.com/en/evaluation-tools/32f0308discovery.html) | *1.3.0* |  |
| :green_heart: | [32F072BDISCOVERY](https://www.st.com/en/evaluation-tools/32f072bdiscovery.html) | *1.5.0* |  |
| :green_heart: | [STM32VLDISCOVERY](https://community.st.com/external-link.jspa?url=http%3A%2F%2Fwww.st.com%2Fen%2Fevaluation-tools%2Fstm32vldiscovery.html) | 0.2.1 |  |
| :green_heart: | [STM32F407G-DISC1](http://www.st.com/en/evaluation-tools/stm32f4discovery.html) | *0.1.0* |  |
| :green_heart: | [STM32F746G-DISCOVERY](http://www.st.com/en/evaluation-tools/32f746gdiscovery.html) | *0.1.0* |  |
| :green_heart: | [B-L072Z-LRWAN1](http://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html) | *1.1.0* |  |
| :green_heart: | [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) | *1.0.1* |  |

| Status | Generic STM32F0xx | Release | Comment |
| :---: | --- | :---: | :--- |
| :green_heart: | STM32F030F4 Demo board | *1.5.0* |  |

| Status | Generic STM32F1xx | Release | Comment |
| :---: | --- | :---: | :--- |
| :green_heart: | BluePill F103C(6-8-B) | *1.2.0* | USB CDC support in *1.5.0* |
| :green_heart: | BlackPill F103C(8-B) | *1.5.0* |  |
| :green_heart: | MapleMini F103CB | *1.2.0* | USB CDC support in *1.5.0* |
| :green_heart: | HY-TinySTM103T | *1.5.0* |  |

| Status | Generic STM32F4xx | Release | Comment |
| :---: | --- | :---: | :--- |
| :green_heart: | [Black F407VET6](http://wiki.stm32duino.com/index.php?title=STM32F407#.22Black_VET6.22_STM32F407VET6_Variant) | *1.4.0* | VG/ZE/ZG in *1.5.0* |
| :green_heart: | [Blue F407VET6 Mini](http://wiki.stm32duino.com/index.php?title=Vcc-gnd.com_STM32F407VET6_Mini) | *1.4.0* |  |
| :green_heart: | DIYMROE STM32F407VGT | *1.5.0* |  |
| :green_heart: | FK407M1 | *1.5.0* |  |

| Status | 3D printer boards | Release | Comment |
| :---: | --- | :---: | :--- |
| :green_heart: | [ARMED V1](https://github.com/ktand/Armed) | *1.5.0* |  |
| :green_heart: | [EExtruder F030 V1](https://github.com/ghent360/PrntrBoard/tree/tmc2130-redesign/EExtruder) | *1.5.0* | Small companion board for Prntr Board V1 |
| :green_heart: | Malyan M200 V1 | *1.5.0* |  |
| :green_heart: | Malyan M200 V2 | *1.5.0* |  |
| :green_heart: | [Prntr Board V1](https://github.com/ghent360/PrntrBoard) | *1.5.0* |  |
| :green_heart: | [RemRam v1](https://github.com/hasenbanck/remram) | *1.4.0* |  |
| :green_heart: | [RUMBA32](https://github.com/Aus3D/RUMBA32) | *1.5.0* |  |

| Status | RAK Wireless | Release | Comment |
| :---: | --- | :---: | :--- |
| :green_heart: | [RAK811 LoRa Tracker](https://www.rakwireless.com/en/) | *1.4.0* | Basic support |

## Next release

  See [milestones](https://github.com/stm32duino/Arduino_Core_STM32/milestones) to have an overview of the next release content.

## Troubleshooting

If you have any issue, you could [file an issue on Github](https://github.com/stm32duino/Arduino_Core_STM32/issues/new).

Or submit a topic on the [stm32duino forum](http://stm32duino.com):

 * questions on the [STM32 Core](http://stm32duino.com/viewforum.php?f=48)

 * bugs/enhancements on the [STM core: Bugs and enhancements](http://stm32duino.com/viewforum.php?f=49)
