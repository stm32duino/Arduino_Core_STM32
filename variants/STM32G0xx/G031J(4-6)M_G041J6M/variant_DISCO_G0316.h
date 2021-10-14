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
 *        STM32 pins number
 *----------------------------------------------------------------------------*/
#define PA0                     PIN_A0 // package pin number 4
#define PA1                     PIN_A1 // package pin number 4
#define PA2                     PIN_A2 // package pin number 4
#define PA8                     3      // package pin number 5
#define PA9_R                   4      // package pin number 5 - shared with PA11
#define PA10_R                  5      // package pin number 6 - shared with PA12
#define PA11                    PIN_A3 // package pin number 5
#define PA12                    PIN_A4 // package pin number 6 - LED
#define PA13                    PIN_A5 // package pin number 7 - SWDIO
#define PA14                    PIN_A6 // package pin number 8 - SWCLK - BOOT0
#define PA15                    10     // package pin number 8

#define PB0                     PIN_A7 // package pin number 5
#define PB1                     PIN_A8 // package pin number 5
#define PB5                     13     // package pin number 8
#define PB6                     14     // package pin number 8
#define PB7                     PIN_A9 // package pin number 1
#define PB8                     16     // package pin number 1
#define PB9                     17     // package pin number 1

#define PC14                    18     // package pin number 1

#define PF2                     19     // package pin number 4

// Alternate pins number
#define PA2_ALT1                (PA2 | ALT1)
#define PB0_ALT1                (PB0 | ALT1)
#define PB1_ALT1                (PB1 | ALT1)
#define PB1_ALT2                (PB1 | ALT2)
#define PB6_ALT1                (PB6 | ALT1)

#define NUM_DIGITAL_PINS        20
#define NUM_REMAP_PINS          2
#define NUM_ANALOG_INPUTS       10

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PA12
#endif
#define LED_GREEN               LED_BUILTIN

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PF2
#endif

// Below SPI and I2C definitions already done in the core
// Could be redefined here if differs from the default one
// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA13
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA12
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PA11
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PA1
#endif

// I2C Definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB6
#endif

// Timer Definitions
// Use TIM14/TIM16/TIM17 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM14
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM16
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for generic 'Serial' instance
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
  #define SERIAL_PORT_MONITOR   Serial
#endif
