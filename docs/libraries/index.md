

# Libraries

This page lists libraries included with the STM32 core, STM32duino libraries,
expansion-board libraries, and selected libraries from Arduino. Compatibility
depends on the library, board, and STM32 device, so check each library's
requirements and examples before use. Install libraries through the Arduino
Library Manager when available; see each library's documentation for required
dependencies and board-specific setup.
See [additional libraries and compatibility](additional-libraries.md) for
Arduino libraries, community-tested libraries, and compatibility guidance.

> [!WARNING]
> Some Arduino shields route SPI through an ICSP connector, which may not be
> present on an STM32 board. Check the board pinout and connect MISO, MOSI, and
> SCK to the appropriate pins when needed.

> [!NOTE]
> All STM32duino libraries are available through the "_**Library Manager**_"
> or have a look hereafter to see which one is available:
>
> * http://www.arduinolibraries.info/architectures/stm32

## Built-in (delivered with the core package)

* CMSIS_DSP: see the [CMSIS-DSP reference](built-in/CMSIS-DSP-library.md) and the usage example [here](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/libraries/CMSIS_DSP/examples/arm_sin_cos_example_f32/arm_sin_cos_example_f32.ino)
* EEPROM: follow the official [EEPROM](https://docs.arduino.cc/learn/built-in-libraries/eeprom/) API, see also the [EEPROM emulation reference](built-in/EEPROM-library.md)
* IWatchdog: see [here](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/libraries/IWatchdog/README.md)
* Servo: follow the official [Servo](https://docs.arduino.cc/libraries/servo/) API, see also the [Servo reference](built-in/Servo-library.md)
* SoftwareSerial: follow the official [SoftwareSerial](https://docs.arduino.cc/learn/built-in-libraries/software-serial/) API.<br>
  It uses an **hardware timer**. Interrupt is triggered at a `frequency = Baudrate * OVERSAMPLE` (by default _3*baudrate_) to handle RX as well as TX transmissions.
  This impacts CPU load specially at high baudrate.
* SPI: follow the official [SPI](https://docs.arduino.cc/language-reference/en/functions/communication/SPI/) API, see also the [STM32 SPI reference](built-in/SPI-library.md)
* Wire (I2C): follow the official [Wire](https://docs.arduino.cc/language-reference/en/functions/communication/Wire/) API, see also the [STM32 I2C reference](built-in/I2C-library.md)

## STM32-specific libraries

<!-- BEGIN GENERATED STM32duino library list -->

This list is generated from public STM32duino repositories that contain a `library.properties` file.

### Communication

* [STM32duino ISM43362-M3G-L44](https://github.com/stm32duino/WiFi-ISM43362-M3G-L44): This library includes drivers for Inventek Systems WiFi device named ISM43362-M3G-L44.
* [STM32duino LwIP](https://github.com/stm32duino/LwIP): A Lightweight TCP/IP stack
* [STM32duino M24SR64-Y](https://github.com/stm32duino/M24SR64-Y): This library includes drivers for ST's M24SR64-Y NFC/RFID tag.
* [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL): Allows controlling the ST NFC card reader components based on RFAL
* [STM32duino S2-LP](https://github.com/stm32duino/S2-LP): This library includes drivers for ST S2-LP sub-1GHz transceiver.
* [STM32duino SPBTLE-RF](https://github.com/stm32duino/SPBTLE-RF): This library includes drivers for ST's BlueNRG/BlueNRG-MS Bluetooth Low Energy device.
* [STM32duino ST25DV](https://github.com/stm32duino/ST25DV): Allows controlling the NFC ST25DV
* [STM32duino ST25R200](https://github.com/stm32duino/ST25R200): Allows controlling the ST ST25R100 and ST25R200 components
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL)
* [STM32duino ST25R3911B](https://github.com/stm32duino/ST25R3911B): Allows controlling the ST ST25R3911B component
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL)
* [STM32duino ST25R3916](https://github.com/stm32duino/ST25R3916): Allows controlling the ST ST25R3916 and ST25R3916B components
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL)
* [STM32duino ST25R500](https://github.com/stm32duino/ST25R500): Allows controlling the ST ST25R300 and ST25R500 components
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL)
* [STM32duino ST25R95](https://github.com/stm32duino/ST25R95): Allows controlling the ST ST25R95 component
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL)
* [STM32duino STM32Ethernet](https://github.com/stm32duino/STM32Ethernet): Enables network connection (local and Internet) using the STM32 Board.
    * Depends on: [STM32duino LwIP](https://github.com/stm32duino/LwIP)
* [STM32duinoBLE](https://github.com/stm32duino/STM32duinoBLE): Fork of ArduinoBLE library to add the support of STM32WB, SPBTLE-RF, SPBTLE-1S, BLUENRG-M2SP, BLUENRG-LP and BLUENRG-M0 BLE modules.
* [STM32duinoLoRaWAN](https://github.com/stm32duino/STM32LoRaWAN): Support library for STM32WL microcontrollers featuring a sub-GHz radio based-on Semtech SX126x
    * Depends on: [STM32duino RTC](https://github.com/stm32duino/STM32RTC)

### Data Storage

* [FatFs](https://github.com/stm32duino/FatFs): FAT file system based on open-source FatFS solution.
* [STM32duino M95640-R](https://github.com/stm32duino/M95640-R): This library includes drivers for ST M95640-R EEPROM.
* [STM32duino MX25R6435F](https://github.com/stm32duino/MX25R6435F): Quad-SPI NOR Flash memory library.
* [STM32duino STM32SD](https://github.com/stm32duino/STM32SD): Enables reading and writing on SD card using SD card slot connected to the SDIO/SDMMC-hardware of the STM32 MCU. For slots connected to SPI-hardware use the standard Arduino SD library.
    * Depends on: [FatFs](https://github.com/stm32duino/FatFs)

### Device Control

* [STM32duino Low Power](https://github.com/stm32duino/STM32LowPower): Power save primitives features for STM32 boards
    * Depends on: [STM32duino RTC](https://github.com/stm32duino/STM32RTC)
* [STM32duino Proximity Gesture](https://github.com/stm32duino/Proximity_Gesture): Allows performing simple gestures detection using proximity sensors
* [STM32duino VL53L0X](https://github.com/stm32duino/VL53L0X): Allows controlling the VL53L0X (Time-of-Flight and gesture detection sensor)
* [STM32duino VL53L1](https://github.com/stm32duino/VL53L1): Allows controlling the VL53L1 (Time-of-Flight)
* [STM32duino VL53L1X](https://github.com/stm32duino/VL53L1X): Allows controlling the VL53L1X (Time-of-Flight and gesture detection sensor)
* [STM32duino VL53L3CX](https://github.com/stm32duino/VL53L3CX): Allows controlling the VL53L3CX (Time-of-Flight ranging sensor with multi target detection)
* [STM32duino VL53L4CD](https://github.com/stm32duino/VL53L4CD): Allows controlling the VL53L4CD (Time-of-Flight)
* [STM32duino VL53L4CX](https://github.com/stm32duino/VL53L4CX): Allows controlling the VL53L4CX (Time-of-Flight ranging sensor with multi target detection)
* [STM32duino VL53L4ED](https://github.com/stm32duino/VL53L4ED): Allows controlling the VL53L4ED (Time-of-Flight)
* [STM32duino VL53L5CX](https://github.com/stm32duino/VL53L5CX): Allows controlling the VL53L5CX (Time-of-Flight 8x8 multizone ranging sensor with wide field view)
* [STM32duino VL53L7CH](https://github.com/stm32duino/VL53L7CH): Allows controlling the VL53L7CH (Time-of-Flight 8x8 multizone ranging sensor with wide field view)
* [STM32duino VL53L7CX](https://github.com/stm32duino/VL53L7CX): Allows controlling the VL53L7CX (Time-of-Flight 8x8 multizone ranging sensor with wide field view)
* [STM32duino VL53L8CH](https://github.com/stm32duino/VL53L8CH): Allows controlling the VL53L8CH (Time-of-Flight 8x8 multizone ranging sensor with wide field view)
* [STM32duino VL53L8CX](https://github.com/stm32duino/VL53L8CX): Allows controlling the VL53L8CX (Time-of-Flight 8x8 multizone ranging sensor with wide field view)
* [STM32duino VL6180](https://github.com/stm32duino/VL6180): Allows controlling the VL6180 (proximity sensor)
* [STM32duino VL6180X](https://github.com/stm32duino/VL6180X): Allows controlling the VL6180X (proximity and ambient light sensing (ALS) sensor)

### Other

* [STM32duino Examples](https://github.com/stm32duino/STM32Examples): Provides several examples for the Arduino core for STM32 MCUs.
* [STM32duino FP_Examples](https://github.com/stm32duino/FP_Examples): Provides several Function Packs that combine the usage of several X-NUCLEO boards
    * Depends on: [STM32duino LSM6DSL](https://github.com/stm32duino/LSM6DSL), [STM32duino LSM303AGR](https://github.com/stm32duino/LSM303AGR), [STM32duino LPS22HB](https://github.com/stm32duino/LPS22HB), [STM32duino VL6180X](https://github.com/stm32duino/VL6180X), [STM32duino VL53L0X](https://github.com/stm32duino/VL53L0X), [STM32duino VL53L1X](https://github.com/stm32duino/VL53L1X), [STM32duino Proximity Gesture](https://github.com/stm32duino/Proximity_Gesture), [STM32duino X-NUCLEO-6180XA1](https://github.com/stm32duino/X-NUCLEO-6180XA1), [STM32duino X-NUCLEO-53L0A1](https://github.com/stm32duino/X-NUCLEO-53L0A1), [STM32duino X-NUCLEO-53L1A1](https://github.com/stm32duino/X-NUCLEO-53L1A1), [STM32duino SPBTLE-RF](https://github.com/stm32duino/SPBTLE-RF), [STM32duino X-NUCLEO-IHM02A1](https://github.com/stm32duino/X-NUCLEO-IHM02A1), [STM32duino X-NUCLEO-LED61A1](https://github.com/stm32duino/X-NUCLEO-LED61A1), [STM32duino LPS25HB](https://github.com/stm32duino/LPS25HB), [STM32duino LSM6DS3](https://github.com/stm32duino/LSM6DS3), [STM32duino LSM6DSO](https://github.com/stm32duino/LSM6DSO), [STM32duino LIS2DW12](https://github.com/stm32duino/LIS2DW12), [STM32duino LIS2MDL](https://github.com/stm32duino/LIS2MDL), [STM32duino HTS221](https://github.com/stm32duino/HTS221), [STM32duino LPS22HH](https://github.com/stm32duino/LPS22HH), [STM32duino STTS751](https://github.com/stm32duino/STTS751), [STM32duino S2-LP](https://github.com/stm32duino/S2-LP), [STM32duino M95640-R](https://github.com/stm32duino/M95640-R), [STM32duino X-NUCLEO-IKS02A1 Audio](https://github.com/stm32duino/X-NUCLEO-IKS02A1-Audio), [STM32duinoBLE](https://github.com/stm32duino/STM32duinoBLE), [STM32duino MotionFX](https://github.com/stm32duino/MotionFX)

### Sensors

* [STM32duino ASM330LHH](https://github.com/stm32duino/ASM330LHH): Automotive inertial measurement unit.
* [STM32duino HTS221](https://github.com/stm32duino/HTS221): Capacitive digital sensor for relative humidity and temperature.
* [STM32duino IIS2DLPC](https://github.com/stm32duino/IIS2DLPC): High Performance Ultra Low Power 3D accelerometer.
* [STM32duino IIS2DULPX](https://github.com/stm32duino/IIS2DULPX): Ultra Low Power inertial measurement unit.
* [STM32duino IIS2MDC](https://github.com/stm32duino/IIS2MDC): Ultra Low Power 3D magnetometer.
* [STM32duino ILPS22QS](https://github.com/stm32duino/ILPS22QS): Nano pressure sensor.
* [STM32duino ISM330DHCX](https://github.com/stm32duino/ISM330DHCX): High-Performance 3D digital accelerometer and 3D digital gyroscope.
* [STM32duino ISM330DLC](https://github.com/stm32duino/ISM330DLC): 3D accelerometer and 3D gyroscope.
* [STM32duino ISM330IS](https://github.com/stm32duino/ISM330IS): Ultra Low Power inertial measurement unit.
* [STM32duino ISM6HG256X](https://github.com/stm32duino/ISM6HG256X): Intelligent IMU with simultaneous low-g and high-g acceleration detection.
* [STM32duino LIS2DU12](https://github.com/stm32duino/LIS2DU12): Ultra Low Power 3D accelerometer.
* [STM32duino LIS2DUXS12](https://github.com/stm32duino/LIS2DUXS12): Ultra Low Power 3D accelerometer.
* [STM32duino LIS2DW12](https://github.com/stm32duino/LIS2DW12): Ultra Low Power 3D accelerometer.
* [STM32duino LIS2MDL](https://github.com/stm32duino/LIS2MDL): Ultra Low Power 3D magnetometer.
* [STM32duino LIS3DHH](https://github.com/stm32duino/LIS3DHH): Ultra High Resolution 3D accelerometer.
* [STM32duino LIS3MDL](https://github.com/stm32duino/LIS3MDL): High-performance 3D magnetometer.
* [STM32duino LPS22DF](https://github.com/stm32duino/LPS22DF): Nano pressure sensor.
* [STM32duino LPS22HB](https://github.com/stm32duino/LPS22HB): 260-1260 hPa absolute digital output barometer.
* [STM32duino LPS22HH](https://github.com/stm32duino/LPS22HH): Nano pressure sensor.
* [STM32duino LPS25HB](https://github.com/stm32duino/LPS25HB): 260-1260 hPa absolute digital output barometer.
* [STM32duino LSM303AGR](https://github.com/stm32duino/LSM303AGR): 3D accelerometer and 3D magnetometer.
* [STM32duino LSM6DS0](https://github.com/stm32duino/LSM6DS0): 3D accelerometer and 3D gyroscope.
* [STM32duino LSM6DS3](https://github.com/stm32duino/LSM6DS3): 3D accelerometer and 3D gyroscope.
* [STM32duino LSM6DSL](https://github.com/stm32duino/LSM6DSL): 3D accelerometer and 3D gyroscope.
* [STM32duino LSM6DSO](https://github.com/stm32duino/LSM6DSO): Ultra Low Power inertial measurement unit.
* [STM32duino LSM6DSO16IS](https://github.com/stm32duino/LSM6DSO16IS): Ultra Low Power inertial measurement unit.
* [STM32duino LSM6DSO32](https://github.com/stm32duino/LSM6DSO32): Ultra Low Power inertial measurement unit.
* [STM32duino LSM6DSOSensorHub](https://github.com/stm32duino/LSM6DSOSensorHub): Sensor Hub manager for LSM6DSO sensor master
    * Depends on: [STM32duino LSM6DSO](https://github.com/stm32duino/LSM6DSO), [STM32duino LIS2DW12](https://github.com/stm32duino/LIS2DW12), [STM32duino LIS2MDL](https://github.com/stm32duino/LIS2MDL), [STM32duino HTS221](https://github.com/stm32duino/HTS221), [STM32duino LPS22HH](https://github.com/stm32duino/LPS22HH), [STM32duino STTS751](https://github.com/stm32duino/STTS751)
* [STM32duino LSM6DSOX](https://github.com/stm32duino/LSM6DSOX): Ultra Low Power inertial measurement unit.
* [STM32duino LSM6DSR](https://github.com/stm32duino/LSM6DSR): iNEMO inertial measurement unit.
* [STM32duino LSM6DSV16BX](https://github.com/stm32duino/LSM6DSV16BX): Ultra Low Power inertial measurement unit.
* [STM32duino LSM6DSV16BX TDM](https://github.com/stm32duino/LSM6DSV16BX-TDM): TDM for LSM6DSV16BX.
    * Depends on: [STM32duino LSM6DSV16BX](https://github.com/stm32duino/LSM6DSV16BX)
* [STM32duino LSM6DSV16X](https://github.com/stm32duino/LSM6DSV16X): Ultra Low Power inertial measurement unit.
* [STM32duino MotionFX](https://github.com/stm32duino/MotionFX): Allows to run Sensor Fusion algorithms with ST MEMS sensors on STM32 boards
    * Depends on: [STM32duino LSM6DSO](https://github.com/stm32duino/LSM6DSO), [STM32duino LIS2MDL](https://github.com/stm32duino/LIS2MDL), [STM32duino LSM6DSL](https://github.com/stm32duino/LSM6DSL), [STM32duino LSM303AGR](https://github.com/stm32duino/LSM303AGR), [STM32duino ISM330DHCX](https://github.com/stm32duino/ISM330DHCX), [STM32duino IIS2MDC](https://github.com/stm32duino/IIS2MDC)
* [STM32duino SHT40-AD1B](https://github.com/stm32duino/SHT40-AD1B): Capacitive digital sensor for relative humidity and temperature.
* [STM32duino STEVAL-MKBOXPRO-Audio](https://github.com/stm32duino/STEVAL-MKBOXPRO-Audio): PCM recording using digital microphone MP23DB01HP on STEVAL-MKBOXPRO.
* [STM32duino STEVAL-MKBOXPRO-Examples](https://github.com/stm32duino/STEVAL-MKBOXPRO-Examples): Examples to use MEMS sensors and NFC tag on STEVAL board
    * Depends on: [STM32duino LIS2DU12](https://github.com/stm32duino/LIS2DU12), [STM32duino LSM6DSV16X](https://github.com/stm32duino/LSM6DSV16X), [STM32duino LPS22DF](https://github.com/stm32duino/LPS22DF), [STM32duino LIS2MDL](https://github.com/stm32duino/LIS2MDL), [STM32duino STTS22H](https://github.com/stm32duino/STTS22H), [STM32duino STEVAL-MKBOXPRO-Audio](https://github.com/stm32duino/STEVAL-MKBOXPRO-Audio), [STM32duino ST25DV](https://github.com/stm32duino/ST25DV)
* [STM32duino STTS22H](https://github.com/stm32duino/STTS22H): digital temperature sensor.
* [STM32duino STTS751](https://github.com/stm32duino/STTS751): digital temperature sensor.

### Timing

* [STM32duino FreeRTOS](https://github.com/stm32duino/STM32FreeRTOS): Real Time Operating System implemented for STM32
* [STM32duino RTC](https://github.com/stm32duino/STM32RTC): Allows to use the RTC functionalities of STM32 based boards.

## Expansion boards

* [STM32duino I-NUCLEO-LRWAN1](https://github.com/stm32duino/I-NUCLEO-LRWAN1): This library provides the LoRa® driver for the expansion board I-NUCLEO-LRWAN1.
* [STM32duino X-NUCLEO-53L0A1](https://github.com/stm32duino/X-NUCLEO-53L0A1): Allows controlling the VL53L0X sensors on board of X-NUCLEO-53L0A1
    * Depends on: [STM32duino VL53L0X](https://github.com/stm32duino/VL53L0X), [STM32duino Proximity Gesture](https://github.com/stm32duino/Proximity_Gesture)
* [STM32duino X-NUCLEO-53L1A1](https://github.com/stm32duino/X-NUCLEO-53L1A1): Allows controlling the VL53L1X sensors on board of X-NUCLEO-53L1A1
    * Depends on: [STM32duino VL53L1X](https://github.com/stm32duino/VL53L1X), [STM32duino Proximity Gesture](https://github.com/stm32duino/Proximity_Gesture)
* [STM32duino X-NUCLEO-53L1A2](https://github.com/stm32duino/X-NUCLEO-53L1A2): Allows controlling the VL53L1 sensors on board of X-NUCLEO-53L1A2
    * Depends on: [STM32duino VL53L1](https://github.com/stm32duino/VL53L1)
* [STM32duino X-NUCLEO-53L3A2](https://github.com/stm32duino/X-NUCLEO-53L3A2): Allows controlling the VL53L3CX sensors on board of X-NUCLEO-53L3A2
    * Depends on: [STM32duino VL53L3CX](https://github.com/stm32duino/VL53L3CX)
* [STM32duino X-NUCLEO-53L4A1](https://github.com/stm32duino/X-NUCLEO-53L4A1): Allows controlling the VL53L4CD sensors on board of X-NUCLEO-53L4A1
    * Depends on: [STM32duino VL53L4CD](https://github.com/stm32duino/VL53L4CD)
* [STM32duino X-NUCLEO-53L4A2](https://github.com/stm32duino/X-NUCLEO-53L4A2): Allows controlling the VL53L4CX sensors on board of X-NUCLEO-53L4A2
    * Depends on: [STM32duino VL53L4CX](https://github.com/stm32duino/VL53L4CX)
* [STM32duino X-NUCLEO-53L4A3](https://github.com/stm32duino/X-NUCLEO-53L4A3): Allows controlling the VL53L4ED sensors on board of X-NUCLEO-53L4A3
    * Depends on: [STM32duino VL53L4ED](https://github.com/stm32duino/VL53L4ED)
* [STM32duino X-NUCLEO-53L5A1](https://github.com/stm32duino/X-NUCLEO-53L5A1): Allows controlling the VL53L5CX sensors on board of X-NUCLEO-53L5A1
    * Depends on: [STM32duino VL53L5CX](https://github.com/stm32duino/VL53L5CX)
* [STM32duino X-NUCLEO-53L7A1](https://github.com/stm32duino/X-NUCLEO-53L7A1): Allows controlling the VL53L7CX sensors on board of X-NUCLEO-53L7A1
    * Depends on: [STM32duino VL53L7CX](https://github.com/stm32duino/VL53L7CX)
* [STM32duino X-NUCLEO-53L8A1](https://github.com/stm32duino/X-NUCLEO-53L8A1): Allows controlling the VL53L8CX sensors on board of X-NUCLEO-53L8A1
    * Depends on: [STM32duino VL53L8CX](https://github.com/stm32duino/VL53L8CX)
* [STM32duino X-NUCLEO-6180A1](https://github.com/stm32duino/X-NUCLEO-6180A1): Allows controlling the VL6180 sensors on board of X-NUCLEO-6180A1
    * Depends on: [STM32duino VL6180](https://github.com/stm32duino/VL6180)
* [STM32duino X-NUCLEO-6180XA1](https://github.com/stm32duino/X-NUCLEO-6180XA1): Allows controlling the VL6180X sensors on board of X-NUCLEO-6180XA1
    * Depends on: [STM32duino VL6180X](https://github.com/stm32duino/VL6180X), [STM32duino Proximity Gesture](https://github.com/stm32duino/Proximity_Gesture)
* [STM32duino X-NUCLEO-GNSS1A1](https://github.com/stm32duino/X-NUCLEO-GNSS1A1): Allows controlling the X-NUCLEO-GNSS1A1 (GNSS expansion board based on Teseo LIV3F)
    * Depends on: `MicroNMEA`
* [STM32duino X-NUCLEO-IDB05A1](https://github.com/stm32duino/X-NUCLEO-IDB05A1): Allows controlling the ST X-NUCLEO-IDB05A1 expansion board
    * Depends on: [STM32duino SPBTLE-RF](https://github.com/stm32duino/SPBTLE-RF)
* [STM32duino X-NUCLEO-IHM01A1](https://github.com/stm32duino/X-NUCLEO-IHM01A1): Allows controlling the ST X-NUCLEO-IHM01A1 expansion board
* [STM32duino X-NUCLEO-IHM02A1](https://github.com/stm32duino/X-NUCLEO-IHM02A1): Allows controlling the ST X-NUCLEO-IHM02A1 expansion board
* [STM32duino X-NUCLEO-IHM04A1](https://github.com/stm32duino/X-NUCLEO-IHM04A1): Allows controlling the ST X-NUCLEO-IHM04A1 expansion board
* [STM32duino X-NUCLEO-IHM05A1](https://github.com/stm32duino/X-NUCLEO-IHM05A1): Allows controlling the ST X-NUCLEO-IHM05A1 expansion board
* [STM32duino X-NUCLEO-IHM12A1](https://github.com/stm32duino/X-NUCLEO-IHM12A1): Allows controlling the ST X-NUCLEO-IHM12A1 expansion board
* [STM32duino X-NUCLEO-IHM15A1](https://github.com/stm32duino/X-NUCLEO-IHM15A1): Allows controlling the ST X-NUCLEO-IHM15A1 expansion board
* [STM32duino X-NUCLEO-IKA01A1](https://github.com/stm32duino/X-NUCLEO-IKA01A1): Allows controlling the ST Microelectronics X-NUCLEO-IKA01A1 Expansion Board
* [STM32duino X-NUCLEO-IKS01A1](https://github.com/stm32duino/X-NUCLEO-IKS01A1): Allows controlling the ST X-NUCLEO-IKS01A1 expansion board
    * Depends on: [STM32duino LSM6DS0](https://github.com/stm32duino/LSM6DS0), [STM32duino LSM6DS3](https://github.com/stm32duino/LSM6DS3), [STM32duino LIS3MDL](https://github.com/stm32duino/LIS3MDL), [STM32duino HTS221](https://github.com/stm32duino/HTS221), [STM32duino LPS25HB](https://github.com/stm32duino/LPS25HB)
* [STM32duino X-NUCLEO-IKS01A2](https://github.com/stm32duino/X-NUCLEO-IKS01A2): Allows controlling the ST X-NUCLEO-IKS01A2 expansion board
    * Depends on: [STM32duino LSM6DSL](https://github.com/stm32duino/LSM6DSL), [STM32duino LSM303AGR](https://github.com/stm32duino/LSM303AGR), [STM32duino HTS221](https://github.com/stm32duino/HTS221), [STM32duino LPS22HB](https://github.com/stm32duino/LPS22HB)
* [STM32duino X-NUCLEO-IKS01A3](https://github.com/stm32duino/X-NUCLEO-IKS01A3): Allows controlling the ST X-NUCLEO-IKS01A3 expansion board
    * Depends on: [STM32duino LSM6DSO](https://github.com/stm32duino/LSM6DSO), [STM32duino LIS2DW12](https://github.com/stm32duino/LIS2DW12), [STM32duino LIS2MDL](https://github.com/stm32duino/LIS2MDL), [STM32duino HTS221](https://github.com/stm32duino/HTS221), [STM32duino LPS22HH](https://github.com/stm32duino/LPS22HH), [STM32duino STTS751](https://github.com/stm32duino/STTS751), [STM32duino LSM6DSOX](https://github.com/stm32duino/LSM6DSOX)
* [STM32duino X-NUCLEO-IKS02A1](https://github.com/stm32duino/X-NUCLEO-IKS02A1): Allows controlling the ST X-NUCLEO-IKS02A1 expansion board
    * Depends on: [STM32duino ISM330DHCX](https://github.com/stm32duino/ISM330DHCX), [STM32duino IIS2DLPC](https://github.com/stm32duino/IIS2DLPC), [STM32duino IIS2MDC](https://github.com/stm32duino/IIS2MDC), [STM32duino X-NUCLEO-IKS02A1 Audio](https://github.com/stm32duino/X-NUCLEO-IKS02A1-Audio)
* [STM32duino X-NUCLEO-IKS02A1 Audio](https://github.com/stm32duino/X-NUCLEO-IKS02A1-Audio): Digital microphone IMP34DT05.
* [STM32duino X-NUCLEO-IKS4A1](https://github.com/stm32duino/X-NUCLEO-IKS4A1): Allows controlling the ST X-NUCLEO-IKS4A1 expansion board
    * Depends on: [STM32duino LSM6DSV16X](https://github.com/stm32duino/LSM6DSV16X), [STM32duino LIS2DUXS12](https://github.com/stm32duino/LIS2DUXS12), [STM32duino LSM6DSO16IS](https://github.com/stm32duino/LSM6DSO16IS), [STM32duino LIS2MDL](https://github.com/stm32duino/LIS2MDL), [STM32duino SHT40-AD1B](https://github.com/stm32duino/SHT40-AD1B), [STM32duino LPS22DF](https://github.com/stm32duino/LPS22DF), [STM32duino STTS22H](https://github.com/stm32duino/STTS22H)
* [STM32duino X-NUCLEO-IKS5A1](https://github.com/stm32duino/X-NUCLEO-IKS5A1): Allows controlling the ST X-NUCLEO-IKS5A1 expansion board
    * Depends on: [STM32duino ISM6HG256X](https://github.com/stm32duino/ISM6HG256X), [STM32duino IIS2DULPX](https://github.com/stm32duino/IIS2DULPX), [STM32duino ISM330IS](https://github.com/stm32duino/ISM330IS), [STM32duino IIS2MDC](https://github.com/stm32duino/IIS2MDC), [STM32duino ILPS22QS](https://github.com/stm32duino/ILPS22QS)
* [STM32duino X-NUCLEO-IPS02A1](https://github.com/stm32duino/X-NUCLEO-IPS02A1): Allows controlling the ST X-NUCLEO-IPS02A1 expansion board
* [STM32duino X-NUCLEO-LED61A1](https://github.com/stm32duino/X-NUCLEO-LED61A1): Allows controlling the ST Microelectronics X-NUCLEO-LED61A1 Expansion Board
* [STM32duino X-NUCLEO-NFC01A1](https://github.com/stm32duino/X-NUCLEO-NFC01A1): Allows controlling the ST X-NUCLEO-NFC01A1 expansion board
    * Depends on: [STM32duino M24SR64-Y](https://github.com/stm32duino/M24SR64-Y)
* [STM32duino X-NUCLEO-NFC03A1](https://github.com/stm32duino/X-NUCLEO-NFC03A1): Allows controlling the ST X-NUCLEO-NFC03A1 expansion board
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL), [STM32duino ST25R95](https://github.com/stm32duino/ST25R95)
* [STM32duino X-NUCLEO-NFC04A1](https://github.com/stm32duino/X-NUCLEO-NFC04A1): Allows controlling the ST X-NUCLEO-NFC04A1 expansion board
    * Depends on: [STM32duino ST25DV](https://github.com/stm32duino/ST25DV)
* [STM32duino X-NUCLEO-NFC05A1](https://github.com/stm32duino/X-NUCLEO-NFC05A1): Allows controlling the ST X-NUCLEO-NFC05A1 expansion board
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL), [STM32duino ST25R3911B](https://github.com/stm32duino/ST25R3911B)
* [STM32duino X-NUCLEO-NFC06A1](https://github.com/stm32duino/X-NUCLEO-NFC06A1): Allows controlling the ST X-NUCLEO-NFC06A1 expansion board
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL), [STM32duino ST25R3916](https://github.com/stm32duino/ST25R3916)
* [STM32duino X-NUCLEO-NFC07A1](https://github.com/stm32duino/X-NUCLEO-NFC07A1): Allows controlling the ST X-NUCLEO-NFC07A1 expansion board
    * Depends on: [STM32duino ST25DV](https://github.com/stm32duino/ST25DV)
* [STM32duino X-NUCLEO-NFC08A1](https://github.com/stm32duino/X-NUCLEO-NFC08A1): Allows controlling the ST X-NUCLEO-NFC08A1 expansion board
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL), [STM32duino ST25R3916](https://github.com/stm32duino/ST25R3916)
* [STM32duino X-NUCLEO-NFC09A1](https://github.com/stm32duino/X-NUCLEO-NFC09A1): Allows controlling the ST X-NUCLEO-NFC09A1 expansion board
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL), [STM32duino ST25R200](https://github.com/stm32duino/ST25R200)
* [STM32duino X-NUCLEO-NFC10A1](https://github.com/stm32duino/X-NUCLEO-NFC10A1): Allows controlling the ST X-NUCLEO-NFC10A1 expansion board
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL), [STM32duino ST25R200](https://github.com/stm32duino/ST25R200)
* [STM32duino X-NUCLEO-NFC12A1](https://github.com/stm32duino/X-NUCLEO-NFC12A1): Allows controlling the ST X-NUCLEO-NFC12A1 expansion board
    * Depends on: [STM32duino NFC-RFAL](https://github.com/stm32duino/NFC-RFAL), [STM32duino ST25R500](https://github.com/stm32duino/ST25R500)
* [STM32duino X-NUCLEO-S2868A1](https://github.com/stm32duino/X-NUCLEO-S2868A1): Allows controlling the S2-LP radio on board of X-NUCLEO-S2868A1
    * Depends on: [STM32duino S2-LP](https://github.com/stm32duino/S2-LP), [STM32duino M95640-R](https://github.com/stm32duino/M95640-R)
* [STM32duino X-NUCLEO-S2868A2](https://github.com/stm32duino/X-NUCLEO-S2868A2): Allows controlling the S2-LP radio on board of X-NUCLEO-S2868A2
    * Depends on: [STM32duino S2-LP](https://github.com/stm32duino/S2-LP), [STM32duino M95640-R](https://github.com/stm32duino/M95640-R)
* [STM32duino X-NUCLEO-S2915A1](https://github.com/stm32duino/X-NUCLEO-S2915A1): Allows controlling the S2-LP radio on board of X-NUCLEO-S2915A1
    * Depends on: [STM32duino S2-LP](https://github.com/stm32duino/S2-LP), [STM32duino M95640-R](https://github.com/stm32duino/M95640-R)

<!-- END GENERATED STM32duino library list -->

See the [additional libraries and compatibility](additional-libraries.md) page for more information.
