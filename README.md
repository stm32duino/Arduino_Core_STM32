# Arduino core support for STM32 based boards
[![forums](https://img.shields.io/badge/join-the%20forums-blue.svg)](https://www.stm32duino.com/)
[![docs](https://img.shields.io/badge/browse-the%20docs-orange.svg)](https://stm32duino.github.io/latest/)
[![STM32 Core Continuous Integration](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/Arduino-build.yml/badge.svg?branch=main)](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/Arduino-build.yml )
[![Arduino lint status](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/arduino-lint.yml)
[![codespell](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/CodeSpell.yml/badge.svg)](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/CodeSpell.yml)
[![CMake](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/Cmake.yml/badge.svg)](https://github.com/stm32duino/Arduino_Core_STM32/actions/workflows/Cmake.yml)


[![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
![GitHub All Releases](https://img.shields.io/github/downloads/stm32duino/Arduino_Core_STM32/total.svg?label=downloads%20since%201.4.0)
[![GitHub commits since latest release](https://img.shields.io/github/commits-since/stm32duino/Arduino_Core_STM32/latest/main)](https://github.com/stm32duino/Arduino_Core_STM32/compare/3.0.0...main)


* [Introduction](https://github.com/stm32duino/Arduino_Core_STM32#Introduction)<br>
* [Getting Started](https://github.com/stm32duino/Arduino_Core_STM32#getting-started)<br>
* [Supported boards](docs/supported-boards/index.md)<br>
* [Troubleshooting](https://github.com/stm32duino/Arduino_Core_STM32#troubleshooting)<br>
* [Documentation](https://stm32duino.github.io/latest/)

## Introduction

This repo adds the support of STM32 MCU in Arduino IDE 2.x.<br>

This porting is based on:
* [STM32Cube MCU Packages](https://www.st.com/en/embedded-software/stm32cube-mcu-packages.html) including:
    * The HAL hardware abstraction layer, enabling portability between different STM32 devices via standardized API calls
    * The Low-Layer (LL) APIs, a light-weight, optimized, expert oriented set of APIs designed for both performance and runtime efficiency
    * CMSIS device definition for STM32
* [CMSIS](https://developer.arm.com/embedded/cmsis): Cortex Microcontroller Software Interface Standard (CMSIS) is a vendor-independent hardware abstraction layer for the Cortex®-M processor series and defines generic tool interfaces. It has been packaged as a module for Arduino IDE: https://github.com/stm32duino/ArduinoModule-CMSIS
* [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm): Arm Embedded GCC compiler, libraries and other GNU tools necessary for bare-metal software development on devices based on the Arm Cortex-M. Packages are provided thanks [The xPack 3rd Party Development Tools](https://github.com/xpack-dev-tools/):
  * https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack
  * https://github.com/xpack-dev-tools/openocd-xpack

## Getting Started

This repo is available as a package usable with [Arduino Boards Manager](https://docs.arduino.cc/learn/starting-guide/cores/).

Add this link in the "*Additional Boards Managers URLs*" field:

https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json

> [!WARNING]
> Since core release 2.8.0, only Arduino IDE 2 is supported.

For full instructions on using the "**Boards Manager**", see [Getting Started](https://stm32duino.github.io/latest/Getting-Started/).

Advanced users can use the repository to benefit from the latest development. See [Using git repository](https://stm32duino.github.io/latest/development/Using-git-repository/).

Users can add an STM32-based board by following [Add a board variant](https://stm32duino.github.io/latest/development/Add-a-new-variant/).

## Supported boards

See the [supported boards list](docs/supported-boards/index.md).

## Next release

See [milestones](https://github.com/stm32duino/Arduino_Core_STM32/milestones) to have an overview of the next release content.

## Troubleshooting

For question, support, ...,  you could submit a topic on the [stm32duino forum](http://stm32duino.com).

If you have any issue, you could [file an issue on GitHub](https://github.com/stm32duino/Arduino_Core_STM32/issues/new).

In any case, it always fine to search if your issue was not already existing before submit a new one.
