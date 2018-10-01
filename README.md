# Arduino core support for STM32 based boards
[![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
[![GitHub commits](https://img.shields.io/github/commits-since/stm32duino/Arduino_Core_STM32/1.3.0.svg)](https://github.com/stm32duino/Arduino_Core_STM32/compare/1.3.0...master)
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
### Current release
  * STM32F0
    * [Nucleo F030R8](http://www.st.com/en/evaluation-tools/nucleo-f030r8.html)
    * [Nucleo F091RC](http://www.st.com/en/evaluation-tools/nucleo-f091rc.html)
    * [32F0308DISCOVERY](http://www.st.com/en/evaluation-tools/32f0308discovery.html)

  * STM32F1
    * BluePill F103C8 (Basic support, no USB)
    * MapleMini F103CB (Basic support, no USB)
    * [Nucleo F103RB](http://www.st.com/en/evaluation-tools/nucleo-f103rb.html)
    * [STM32VLDISCOVERY](https://community.st.com/external-link.jspa?url=http%3A%2F%2Fwww.st.com%2Fen%2Fevaluation-tools%2Fstm32vldiscovery.html)

  * STM32F2
    * [Nucleo F207ZG](http://www.st.com/en/evaluation-tools/nucleo-f207zg.html)

  * STM32F3
    * [Nucleo F302R8](http://www.st.com/en/evaluation-tools/nucleo-f302r8.html)
    * [Nucleo F303K8](http://www.st.com/en/evaluation-tools/nucleo-f303k8.html)
    * [Nucleo F303RE](http://www.st.com/en/evaluation-tools/nucleo-f303re.html)
 
  * STM32F4
    * [Nucleo F401RE](http://www.st.com/en/evaluation-tools/nucleo-f401re.html)
    * [Nucleo F411RE](http://www.st.com/en/evaluation-tools/nucleo-f411re.html)
    * [Nucleo F429ZI](http://www.st.com/en/evaluation-tools/nucleo-f429zi.html)
    * [Nucleo F446RE](http://www.st.com/en/evaluation-tools/nucleo-f446re.html)
    * [STM32F407G-DISC1](http://www.st.com/en/evaluation-tools/stm32f4discovery.html)

  * STM32F7
    * [STM32F746G-DISCOVERY](http://www.st.com/en/evaluation-tools/32f746gdiscovery.html)

  * STM32L0
    * [Nucleo L031K6](http://www.st.com/en/evaluation-tools/nucleo-l031k6.html)
    * [Nucleo L053R8](http://www.st.com/en/evaluation-tools/nucleo-l053r8.html)
    * [B-L072Z-LRWAN1](http://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html)

  * STM32L1
    * [Nucleo L152RE](http://www.st.com/en/evaluation-tools/nucleo-l152re.html)

  * STM32L4
    * [Nucleo L432KC](http://www.st.com/en/evaluation-tools/nucleo-l432kc.html)
    * [Nucleo L476RG](http://www.st.com/en/evaluation-tools/nucleo-l476rg.html)
    * [Nucleo L496ZG](http://www.st.com/en/evaluation-tools/nucleo-l496zg.html)
    * [Nucleo L496ZG-P](http://www.st.com/en/evaluation-tools/nucleo-l496zg-p.html)
    * [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html)

### Next release
  * STM32F4
    * [Black F407VET6](http://wiki.stm32duino.com/index.php?title=STM32F407#.22Black_VET6.22_STM32F407VET6_Variant)
    * [Blue F407VET6 Mini](http://wiki.stm32duino.com/index.php?title=Vcc-gnd.com_STM32F407VET6_Mini)

  * STM32F7
    * [Nucleo F767ZI](http://www.st.com/en/evaluation-tools/nucleo-f767zi.html)
    * [RemRam v1](https://github.com/hasenbanck/remram)

  * STM32L0
    * [Nucleo L073RZ](http://www.st.com/en/evaluation-tools/nucleo-l073rz.html)
    * [RAK811 LoRa Tracker](https://www.rakwireless.com/en/) (Basic support)

  * STM32L4
    * [Nucleo L4R5ZI](http://www.st.com/en/evaluation-tools/nucleo-l4r5zi.html)
    * [Nucleo L4R5ZI-P](http://www.st.com/en/evaluation-tools/nucleo-l4r5zi-p.html)



## Troubleshooting

If you have any issue, you could [file an issue on Github](https://github.com/stm32duino/Arduino_Core_STM32/issues/new).

Or submit a topic on the [stm32duino forum](http://stm32duino.com):

 * questions on the [STM32 Core](http://stm32duino.com/viewforum.php?f=48)

 * bugs/enhancements on the [STM core: Bugs and enhancements](http://stm32duino.com/viewforum.php?f=49)
