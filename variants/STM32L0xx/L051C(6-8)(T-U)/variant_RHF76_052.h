/*
 *******************************************************************************
 * Copyright (c) 2019-2021, STMicroelectronics
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
 *        STM32 pins number
 *----------------------------------------------------------------------------*/
#define PA1                     0
#define PA2                     1
#define PA4                     2
#define PA5                     3
#define PA6                     4
#define PA7                     5
#define PB0                     6
#define PB1                     7
#define PB2                     8
#define PB4                     9
#define PB5                     10
#define PB10                    11
#define PB11                    12
#define PC0                     13
#define PB6                     14 // TX Module LoRa
#define PB7                     15 // RX
#define PA9                     16 // TX Boot
#define PA10                    17 // RX Boot

// Alternate pins number
#define PA2_ALT1                (PA2 | ALT1)
#define PA3_ALT1                (PA3 | ALT1)

#define NUM_DIGITAL_PINS        18

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PB4
#endif

#define LED_GREEN               LED_BUILTIN

// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA7
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PA6
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PA5
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PB7
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PB6
#endif

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
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR     Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE    Serial1
  #endif
#endif
