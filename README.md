# Arduino core support for STM32L082-based boards

This repository is MCCI's version of [Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32), adapted for the STM32L082. The BSP here targets the STM32L082 as used in the Murata CMWX1ZZABZ LoRa&reg; module, as further in the MCCI Catena&reg; LoRaWAN&reg; technology boards. Several of these boards are closely compatible with the Adafruit Feather M0 LoRa. See [Supported Boards and CPUs](#supported-boards-and-cpus) for more info.

For general information, please check the stm32duino [README.md](https://github.com/stm32duino/Arduino_Core_STM32#arduino-core-support-for-stm32-based-boards), especially the [Getting Started](https://github.com/stm32duino/Arduino_Core_STM32#getting-started) section.

[![GitHub release](https://img.shields.io/github/release/mcci-catena/Arduino_Core_STM32.svg)](https://github.com/mcci-catena/Arduino_Core_STM32/releases/latest) [![GitHub commits](https://img.shields.io/github/commits-since/mcci-catena/Arduino_Core_STM32/latest.svg)](https://github.com/mcci-catena/Arduino_Core_STM32/compare/v2.5.0...master)

**Contents:**
<!-- markdownlint-disable MD033 -->
<!-- markdownlint-capture -->
<!-- markdownlint-disable -->
<!-- TOC depthFrom:2 updateOnSave:true -->

- [Getting Started](#getting-started)
- [Features](#features)
- [Supported Boards and CPUs](#supported-boards-and-cpus)
	- [Catena 461x Series](#catena-461x-series)
		- [Sensors on Catena 4612, 4617, and 4618](#sensors-on-catena-4612-4617-and-4618)
	- [Catena 4630 Features](#catena-4630-features)
	- [Catena 4801 Features](#catena-4801-features)
- [Troubleshooting](#troubleshooting)
- [Installing a Development Copy of this BSP](#installing-a-development-copy-of-this-bsp)
- [Release History](#release-history)
- [Notes and Acknowledgements](#notes-and-acknowledgements)
- [Support Open-Source Software, Hardware, and Community IoT](#support-open-source-software-hardware-and-community-iot)

<!-- /TOC -->
<!-- markdownlint-restore -->
<!-- Due to a bug in Markdown TOC, the table is formatted incorrectly if tab indentation is set other than 4. Due to another bug, this comment must be *after* the TOC entry. -->

## Getting Started

This repository is available as a package usable with the [Arduino Boards Manager](https://www.arduino.cc/en/guide/cores).  Add this URL to _"Additional Boards Manager URLs"_ under `File>Preferences`:

`https://github.com/mcci-catena/arduino-boards/raw/master/BoardManagerFiles/package_mcci_index.json`

For full instructions on using the "**Boards Manager**", see  [Installing the MCCI Catena BSP](https://github.com/mcci-catena/arduino-boards#installing-the-mcci-catena-bsp).

## Features

The Arduino IDE allows you to select the following items.

- **LoRaWAN Region**: when using the Arduino LMIC, you can select North America, Europ, Australia, Asia, Japan, or India as your target region.
- **Optimization**: choose smallest, fast, faster, fastest, or debug.
- **Serial interface**: Select "USB Serial", "Generic Serial" or "No Serial".
- **System clock**: Select "32 MHz (most power)", "24 MHz", "16 MHz", "4.194 MHz (no USB)" or "2.097 MHz (no USB, least power)". If "2.097 MHz (no USB, least power)" or "4.194 MHz (no USB)" is selected, then you cannot use "USB Serial" for serial interface.
- **Upload method**: select Mass Storage, DFU, or STLink. DFU works well, but requires use of the boot jumper to select DFU mode, and a little driver wrangling on Windows.

## Supported Boards and CPUs

| Board | CPU/SOC/Module | Section | Comment |
|:-----:|:--------------:|:-------:|---------|
| MCCI Catena 4551 | Murata CMWX1ZZABZ module, STM32L082 | [461x](#catena-461x-series) | Obsolete |
| MCCI Catena 4610 | Murata CMWX1ZZABZ module, STM32L082 | [461x](#catena-461x-series) | LiPo battery |
| MCCI Catena 4611 | Murata CMWX1ZZABZ module, STM32L082 | [461x](#catena-461x-series) | Special order only |
| MCCI Catena 4612 | Murata CMWX1ZZABZ module, STM32L082 | [461x](#catena-461x-series) | Primary battery, BME280 |
| MCCI Catena 4617 | Murata CMWX1ZZABZ module, STM32L082 | [461x](#catena-461x-series) | Primary battery, HS3001 |
| MCCI Catena 4618 | Murata CMWX1ZZABZ module, STM32L082 | [461x](#catena-461x-series) | Primary battery, SHT31-DIS-F |
| MCCI Catena 4630 | Murata CMWX1ZZABZ module, STM32L082 | [4630](#catena-4630-features) | LiPo battery,ZMOD4410, PMS7003 |
| MCCI Catena 4801 | Murata CMWX1ZZABZ module, STM32L082 | [4801](#catena-4801-features) | Primary battery, Modbus |

### Catena 461x Series

| Feature | 4551 | 4610 | 4611 | 4612 / 4617 / 4618 |
|---------|------|------|------|------|
| TCXO control | Always on (power consumption issue) | Controlled by code | Controlled by code | Controlled by code | Controlled by code | Controlled by code |
| Battery type | Primary (non-rechargeable) reference is 2x AAA cells | Secondary (LiPo rechargeable), compatible with Adafruit | Feather batteries | Primary (non-rechargeable) reference is 2x AAA cells | Primary (non-rechargeable) reference is 2x AAA cells |
| System voltage | 3.3V | 3.3V | 3.3V | 2.2V to 3.3V, depending on whether boost regulator is enabled. |
| Regulator control | EN pin on Feather disables VDD altogether | No boost regulator; EN disables VDD altogether. | EN pin on JP2-3 shuts down boost regulator | EN output from CPU controls boost regulator. 4612/4617/4618 normally run with boost regulator off for lower power. |
| High-side switch for external sensors | No switch, screw terminal power is from VDD (3.3V) | High-side switch allows software to turn off power to the external sensor screw terminals | High-side switch allows software to turn off power to the external sensor screw terminals | High-side switch allows software to turn off power to the external sensor screw terminals |
| Feather electrical compatibility  | Good, except for different battery system | Very good | Very good | Good physical compatibility but the varying VDD may be an issue |
| Feather physical compatibility | Yes | Yes | Yes | Yes |
| USB | Supported | Supported | Supported | Supported | Supported | Supported |
| Sensors | BME280, Si1123 | BME280, Si1113 | BME280, Si1113 | See [Catena 4612/7/8 Sensors](#sensors-on-catena-4612-4617-and-4618), below |
| Screw terminals for external sensors | 2x4 pin | 2x4 pin | 2x4 pin | 2x4 pin | 2x4 pin | 2x4 pin |
| Boot mode enable | Jumper | Dedicated switch | Jumper | Jumper |

#### Sensors on Catena 4612, 4617, and 4618

All three boards incorporate a Silicon Labs Si1133 ambient light sensor. They differ in the environmental sensor.

Board | Sensor | Temperature | Humidity | Barometric Pressure | Comments
:----:|:------:|:-----------:|:--------:|:-------------------:|:----------
4612  | BME280 | Yes | Yes | Yes | Not suitable for outdoor applications or high-humidity environments.
4617  | HS3001 | Yes | Yes | **No** | Suitable for general-purpose use.
4618  | SHT31-DIS-F | Yes | Yes | **No** | Sensor protected by an IP66 PTFE membrane, best for outdoor deployments.

### Catena 4630 Features

The 4630 is a Feather-compatible board designed for field air-quality monitoring.

| Feature | 4630 |
|---------|------|
| TCXO Control | Controlled by code |
| Battery type | LiPo with on-board charger |
| System voltage | 3.3V, plus programmable 5V regulator for PMS7003 PM2.5 sensor support. |
| Regulator control | No boost regulator for 3.3V; EN disables VDD altogether. D12 controls 5V boost regulator for PMS7003. |
| High-side switch for power for external sensors | No |
| Screw terminals for external sensors | None |
| Feather electrical compatibilty | Yes |
| Feather physical compatibility | Yes |
| USB | Yes, DFU download, runtime data, and charging |
| Sensors | ZMOD4410 VOC sensor; BME280 temperature/pressure/humidity |
| External interfaces | TTL Serial, dedicated cable for connecting to PMS7003 PM2.5 sensor |

### Catena 4801 Features

The 4801 is a dedicated board for remote Modbus applications, using the Murata module.

| Feature | 4801 |
|---------|------|
| TCXO Control | Controlled by code |
| Battery type | Primary battery, boost regulator (but can tolerate up to 3.7V battery) |
| System voltage | 2.2V to 3.3V, depending on whether boost regulator is enabled. |
| Regulator control | EN output from CPU controls boost regulator, and 4801 normally runs with boost regulator off for lower power. |
| High-side switch for power for external sensors | Yes |
| Screw terminals for external sensors | 1x4 pin |
| Feather physical compatibility | No |
| USB | Not supported |
| Sensors | none |
| External interfaces | Modbus, TTL serial |

## Troubleshooting

If you have any issue, you may [file an issue on Github](https://github.com/mcci-catena/Arduino_Core_STM32/issues/new).  You may also submit a support request on the [MCCI support forum](http://portal.mcci.com).

## Installing a Development Copy of this BSP

If you want to develop and test changes to this package, we suggest the following.

1. Install the current release from the standard location using the Arduino `Tools>Boards>Boards Manager...` menu. This installs tools and so forth.
2. Select a board supported by this package.
3. Create an empty sketch with Arduino `File>New`, and check that you can build.
4. Close the Arduino IDE.
5. Clone this repo to a convenient spot on your computer.
6. Open a command window and go to the Arduino board installation directory. It will be one of the following.

   | System | Location |
   |:------:|:---------|
   | Windows 7 through 10 | <code>c:\Users\\<em><strong>username</strong></em>\AppData\Local\Arduino15</code>. If you're using git bash, you can also use `~/AppData/Local/Arduino15` |
   | macOS | <code>~/Library/Arduino15</code> |
   | Linux | <code>~/.arduino15</code> |

7. From this location, change directory to `packages/mcci/stm32`.
8. Look at the direcory contents with `ls`. You'll see a directory named like a version number, for example `1.0.8`.
9. Move the directory you just found away from the `stm32` directory. It's convenient to have it around, so we sugest not delete it.
10. Create a symbolic link to the sandbox you created in step (3) above. On macOS and Linux, this is done using the `ln -s` command. On Windows 10, this is done with the `mklink /d` command. (On older versions of Windows, unless you're very experienced, you might want to use a Linux VM in VirtualBox -- we can't advise on the best way to do this.)
11. Open the Arduino IDE.
12. Use the menu `File>New` to create an empty sketch (or reuse the sketch from step 3).
13. Make sure the board you want to develop for is selected in `Tools>Boards`.
14. Make changes and build.

Remember to restart the IDE whenever you change `platform.txt`, `boards.txt` or `programmers.txt`.

## Release History

- [v2.5.0](https://github.com/mcci-catena/Arduino_Core_STM32/releases/tag/v2.5.0) enables the crystal controlled LSE clock, and uses it to run the RTC. Code was substantially refactored to move common code to common directories. Bug fixes.

- [v2.4.0](https://github.com/mcci-catena/Arduino_Core_STM32/releases/tag/v2.4.0) Added support for new boards: 4617, 4618 and 4630. Serial interface configuration in `boards.template` has been updated with new option to use both USB Serial and Hardware Serial at same time.

- [v2.3.0](https://github.com/mcci-catena/Arduino_Core_STM32/releases/tag/v2.3.0) corrects the handling of clocking in the various SLEEP/STOP/SSTANDBY modes. It also ensures that `.RamFunc` code is properly placed in RAM (initialzed when statics are initialized).

- [v2.2.1](https://github.com/mcci-catena/Arduino_Core_STM32/releases/tag/v2.2.1) fixed the version number in `platform.txt`, and sets GPIO to reset state when deinitializing SPI, I2C and UARTs.

- [v2.2.0](https://github.com/mcci-catena/Arduino_Core_STM32/releases/tag/v2.2.0) increases the serial buffer size to 256 and adds low-power changes for the Catena 4801.

- [v2.1.0](https://github.com/mcci-catena/Arduino_Core_STM32/releases/tag/v2.1.0) fixed the device ID register offset, and improved sleep mode power.

- [v2.0.0](https://github.com/mcci-catena/Arduino_Core_STM32/releases/tag/v2.0.0) is a major release. It improves wakeup support and power management, and simplifies some of the menus. New boards: 4610 and 4801. The template system was enhanced. USB manufacturer string is no longer "unknown". Changed hardware serial default baud rate to 115,200 from 9600. Moved USB clock control to USB module. Enhanced begin()/end() for USB and I2C to start/stop clocks. (This is a major bump beause the baud rate change may be a breaking change.)

- [v1.1.2](https://github.com/mcci-catena/Arduino_Core_STM32/releases/tag/v1.1.2) added 4611, 4612 support, and templating for generating boards.txt.

## Notes and Acknowledgements

MCCI and MCCI Catena are registered trademarks of MCCI Corporation. ChaeHee Won, Sungjoon Park, and Terry Moore of MCCI maintain this BSP.

LoRa is a registered trademark of the LoRa Alliance. LoRaWAN is a registered trademark of the LoRa Alliance.

All other trademarks are the property of their respective owners.

## Support Open-Source Software, Hardware, and Community IoT

Everyone at MCCI invests time and resources providing this open-source code and open-source hardware. MCCI is also the principal corporate sponsor of [The Things Network New York](https://thethings.nyc) and [Ithaca](https://ttni.tech). Please support our work by purchasing products from MCCI! Visit our on-line store at [store.mcci.com](https://store.mcci.com).
