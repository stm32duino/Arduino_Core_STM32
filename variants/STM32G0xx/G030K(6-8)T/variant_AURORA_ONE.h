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
#define PA10                    0
#define PA9                     1
#define PA6                     PIN_A6
#define PA7                     PIN_A7
#define PA8                     4
#define PC6                     5
#define PA11                    PIN_A10
#define PA12                    PIN_A11
#define PB2                     PIN_A12
#define PB1                     PIN_A9
#define PB0                     PIN_A8
#define PB5                     11
#define PB4                     12
#define PB3                     13      // LED
#define PB7                     PIN_A13
#define PB6                     15
#define PB9                     16
#define PB8                     17
#define PA15                    18
#define PA14                    PIN_A14 // SWD / BOOT0
#define PA13                    PIN_A15 // SWD
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA2                     PIN_A2
#define PA3                     PIN_A3
#define PA4                     PIN_A4
#define PA5                     PIN_A5
#define PA9_R                   27
#define PA10_R                  28
// #define PC14                    29      // OSC32IN
// #define PC15                    30      // OSC32OUT

// Alternate pins number
#define PA6_ALT1                (PA6 | ALT1)
#define PA7_ALT1                (PA7 | ALT1)
#define PA7_ALT2                (PA7 | ALT2)
#define PA7_ALT3                (PA7 | ALT3)
#define PB0_ALT1                (PB0 | ALT1)
#define PB1_ALT1                (PB1 | ALT1)
#define PB1_ALT2                (PB1 | ALT2)
#define PB6_ALT1                (PB6 | ALT1)

#define NUM_DIGITAL_PINS        29
#define NUM_REMAP_PINS          2
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PB3
#endif
#define LED_GREEN               LED_BUILTIN

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PA8
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM14
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM16
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  2 //Connected to Aurora Connect Lite
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
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
  #define SERIAL_PORT_HARDWARE  Serial2
#endif
