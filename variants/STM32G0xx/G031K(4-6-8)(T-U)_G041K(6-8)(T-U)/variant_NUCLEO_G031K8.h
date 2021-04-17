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
#define PB7                     PIN_A8
#define PB6                     1
#define PA15                    2
#define PB1                     PIN_A9
#define PA10                    4
#define PA9                     5
#define PB0                     PIN_A10
#define PB2                     PIN_A11
#define PB8                     8
#define PA8                     9
#define PB9                     10
#define PB5                     11
#define PB4                     12
#define PB3                     13
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA4                     PIN_A2
#define PA5                     PIN_A3
#define PA12                    PIN_A4
#define PA11                    PIN_A5
#define PA6                     PIN_A6
#define PA7                     PIN_A7
#define PA9_R                   22
#define PA10_R                  23
#define PC6                     24  // LED
#define PA2                     25  // STLink Tx
#define PA3                     26  // STLink Rx
#define PA13                    27  // SWDIO
#define PA14                    28  // SWCLK/BOOT0
#define PC14                    29  // OSC32 IN
#define PC15                    30  // OSC32 OUT
#define PF2                     31  // NRST or USER Button

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
#define PB3_ALT1                (PB3 | ALT1)
#define PB6_ALT1                (PB6 | ALT1)
#define PC6_ALT1                (PC6 | ALT1)

#define NUM_DIGITAL_PINS        32
#define NUM_REMAP_PINS          2
#define NUM_ANALOG_INPUTS       12

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PC6
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PF2
#endif

// I2C Definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PA10
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PA9
#endif

// Timer Definitions
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM14
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM16
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  101 //Connected to ST-Link
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA3
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA2
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
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_HARDWARE    Serial
#endif
