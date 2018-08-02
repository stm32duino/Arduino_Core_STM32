# Arduino core support for STM32L082-based boards

This repository is MCCI's version of https://github.com/stm32duino/Arduino_Core_STM32, adapted for the STM32L082. The BSP here targets the STM32L082 as used in the Murata CMWX1ZZABZ LoRa&reg; module, as further in the MCCI Catena&reg; LoRaWAN&trade; boards. The pinouts, etc., are therefore chosen to make the Catena 4551 closely compatible with the Adafruit Feather M0 LoRa.

For general information, please check the stm32duino [README.md](https://github.com/stm32duino/Arduino_Core_STM32#arduino-core-support-for-stm32-based-boards), especially the [Getting Started](https://github.com/stm32duino/Arduino_Core_STM32#getting-started) section.

<!-- TOC depthFrom:2 updateOnSave:true -->

- [Latest release](#latest-release)
- [Getting Started](#getting-started)
- [Supported Boards and CPUs](#supported-boards-and-cpus)
- [Troubleshooting](#troubleshooting)
- [Developing](#developing)
- [Notes and Acknowledgements](#notes-and-acknowledgements)
- [Support Open-Source Software, Hardware, and Community IoT!](#support-open-source-software-hardware-and-community-iot)

<!-- /TOC -->

## Latest release

[![GitHub release](https://img.shields.io/github/release/mcci-catena/Arduino_Core_STM32.svg)](https://github.com/mcci-catena/Arduino_Core_STM32/releases/latest) [![GitHub commits](https://img.shields.io/github/commits-since/mcci-catena/Arduino_Core_STM32/latest.svg)](https://github.com/mcci-catena/Arduino_Core_STM32/compare/v1.1.0...master)

## Getting Started

This repository is available as a package usable with the [Arduino Boards Manager](https://www.arduino.cc/en/guide/cores).  Add this URL to _"Additional Boards Manager URLs"_ under `File>Preferences`:

`https://github.com/mcci-catena/arduino-boards/raw/master/BoardManagerFiles/package_mcci_index.json`

For full instructions on using the "**Boards Manager**", see  [Installing the MCCI Catena BSP](https://github.com/mcci-catena/arduino-boards#installing-the-mcci-catena-bsp).

## Supported Boards and CPUs

| Board | CPU/SOC | Comment |
|-------|:-------:|---------|
| MCCI Catena 4551 | STM32L082 | This board uses a Murata CMWX1ZZABZ module, containing the STM32L082 CPU |

## Troubleshooting

If you have any issue, you may [file an issue on Github](https://github.com/mcci-catena/Arduino_Core_STM32/issues/new).  You may also submit a support request on the [MCCI support forum](http://portal.mcci.com).

## Developing

If you want to develop and test changes to this package, we suggest the following.

1. Install the current release from the standard location using the Arduino `Tools>Boards>Boards Manager...` menu. This installs tools and so forth.
2. Select a board supported by this package.
3. Create an empty sketch with Arduino `File>New`, and check that you can build.
4. Close the Arduino IDE.
5. Clone this repo to a convenient spot on your computer.
6. Open a command window and go to the Arduino board installation directory. It will be one of the following.

   | System | Location |
   |:------:|:---------|
   | Windows 7 through 10 | <code>c:\Users\\<em><strong>username</strong></em>\AppData\Local\Arduino15</code>. If you're using git bash, you can also use `~/Documents/Arduino15` |
   | macOS | <code>~/Library/Arduino15</code> |
   | Linux | <code>~/.arduino15</code> |

4. From this location, change directory to `packages/mcci/stm32`.
5. Look at the direcory contents with `ls`. You'll see a directory named like a version number, for example `1.0.8`.
5. Move the directory you just found away from the `stm32` directory. It's convenient to have it around, so we sugest not delete it.
6. Create a symbolic link to the sandbox you created in step (3) above. On macOS and Linux, this is done using the `ln -s` command. On Windows 10, this is done with the `mklink /d` command. (On older versions of Windows, unless you're very experienced, you might want to use a Linux VM in VirtualBox -- we can't advise on the best way to do this.)
7. Open the Arduino IDE.
8. Use the menu `File>New` to create an empty sketch (or reuse the sketch from step 3).
9. Make sure the board you want to develop for is selected in `Tools>Boards`.
10. Make changes and build.

Remember to restart the IDE whenever you change `platform.txt`, `boards.txt` or `programmers.txt`.

## Notes and Acknowledgements

MCCI and MCCI Catena are registered trademarks of MCCI Corporation.

LoRa is a registered trademark of the LoRa Alliance. LoRaWAN is a trademark of the LoRa Alliance.

All other trademarks are the property of their respective owners.

## Support Open-Source Software, Hardware, and Community IoT!

Everyone at MCCI invests time and resources providing this open-source code and open-source hardware. MCCI is also the principal corporate sponsor of [The Things Network New York](https://thethings.nyc) and [Ithaca](https://ttni.tech). Please support our work by purchasing products from MCCI! Visit our on-line store at [store.mcci.com](https://store.mcci.com).
