/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#pragma once

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

#define PB0                     0
#define PB1                     1
#define PA8                     PIN_A8
#define PA9                     PIN_A9
#define PA10                    4
#define PA15                    5
#define PE4                     6
#define PB2                     7
#define PB5                     8
#define PB3                     9
#define PB4                     10
#define PB9                     11
#define PB8                     12
#define PB7                     13
#define PB6                     14
#define PH3                     15     // BOOT0 / USR BTN

#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA2                     PIN_A2
#define PA3                     PIN_A3
#define PA4                     PIN_A4
#define PA5                     PIN_A5
#define PA6                     PIN_A6
#define PA7                     PIN_A7 // VBAT sense

// Alternate pins number
#define PA7_ALT1                (PA7 | ALT1)
#define PB8_ALT1                (PB8 | ALT1)
#define PB9_ALT1                (PB9 | ALT1)

#define NUM_DIGITAL_PINS        24
#define NUM_ANALOG_INPUTS       10

// On-board LED pin number
#define LED                     PE4
#define LED1                    LED
#define LED_BUILTIN             LED

// On-board user button
// Note: use '_BTN' for SW1 and SW2 as they are register name of M24SR64-Y
#define SW1_BTN                 PH3
#define USER_BTN                SW1_BTN

// SPI Definitions
#define PIN_SPI_SS              PB2
#define PIN_SPI_SS1             PA15
#define PIN_SPI_SS2             PA4
#define PIN_SPI_SS3             PE4
#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PB3

// I2C Definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
#define TIMER_TONE              TIM16
#define TIMER_SERVO             TIM17

// UART Definitions
#define SERIAL_UART_INSTANCE    1

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PB7
#define PIN_SERIAL_TX           PB6

/* Extra HAL configuration */
#define PREFETCH_ENABLE         1U

// Only 512k provided for cpu1, so defined the FLASH_PAGE_NUMBER
// for EEPROM emulation to the last 512k pages.
#define FLASH_PAGE_NUMBER       127

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
  // These serial port names are intended to allow libraries and architecture-neutral
  // sketches to automatically default to the correct port name for a particular type
  // of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
  // the first hardware serial port whose RX/TX pins are not dedicated to another use.
  //
  // SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
  //
  // SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
  //
  // SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
  //
  // SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
  //
  // SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
  //                            pins are NOT connected to anything by default.
  #define SERIAL_PORT_MONITOR   Serial
  #define SERIAL_PORT_HARDWARE  Serial1
#endif
