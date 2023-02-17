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

#define PA10                    0
#define PA9                     1
#define PA12                    2
#define PB0                     3
#define PB7                     4 // RX, SDA
#define PB6                     5 // TX, SCL
#define PB1                     6
#define PF0                     7
#define PF1                     8
#define PA8                     9
#define PA11                    10
#define PB5                     11
#define PB4                     12 // LED_BLUE
#define PB3                     13 // LED_GREEN
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA3                     PIN_A2
#define PA4                     PIN_A3
#define PA5                     PIN_A4
#define PA6                     PIN_A5
#define PA7                     PIN_A6
#define PA2                     21 // RC Input
#define PA15                    22 // LED_RED
// Pins not defined
// PA13, PA14, PB2, PB8

// Alternate pins number
#define PA2_ALT1                (PA2 | ALT1)
#define PA3_ALT1                (PA3 | ALT1)
#define PA6_ALT1                (PA6 | ALT1)
#define PA7_ALT1                (PA7 | ALT1)
#define PA7_ALT2                (PA7 | ALT2)
#define PA7_ALT3                (PA7 | ALT3)
#define PB0_ALT1                (PB0 | ALT1)
#define PB1_ALT1                (PB1 | ALT1)
#define PB1_ALT2                (PB1 | ALT2)

#define NUM_DIGITAL_PINS        23
#define NUM_ANALOG_INPUTS       7

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PB3
#endif
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PB4
#define LED_RED                 PA15

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// I2C Definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB6
#endif

// Timer Definitions
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM6
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  2
#endif

// Serial Pin Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PB7
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PB6
#endif

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
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
  #define SERIAL_PORT_HARDWARE  Serial
#endif
