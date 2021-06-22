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
#define PB0                     PIN_A8
#define PB7                     4
#define PB6                     5
#define PB1                     PIN_A9
#define PC14                    7  // By default, SB6 open PF0/PC14 not connected to D7
#define PC15                    8  // By default, SB8 open PF1/PC15 not connected to D8
#define PA8                     9
#define PA11                    10
#define PB5                     11
#define PB4                     12
#define PB3                     13 // LED
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA3                     PIN_A2
#define PA4                     PIN_A3
#define PA5                     PIN_A4
#define PA6                     PIN_A5
#define PA7                     PIN_A6
#define PA2                     PIN_A7 // SB2 ON STLink Tx
#define PA15                    22 // STLink Rx
// PA13, PA14 and PH3 not available

// Alternate pins number
#define PA1_ALT1                (PA1 | ALT1)
#define PA2_ALT1                (PA2 | ALT1)
#define PA3_ALT1                (PA3 | ALT1)
#define PA4_ALT1                (PA4 | ALT1)
#define PA5_ALT1                (PA5 | ALT1)
#define PA6_ALT1                (PA6 | ALT1)
#define PA7_ALT1                (PA7 | ALT1)
#define PB0_ALT1                (PB0 | ALT1)
#define PB1_ALT1                (PB1 | ALT1)

#define NUM_DIGITAL_PINS        23
#define NUM_ANALOG_INPUTS       10

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN             PB3
#endif
#ifndef LED_GREEN
  #define LED_GREEN               LED_BUILTIN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN                PA8
#endif

// I2C Definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA            PB7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL            PB6
#endif

// Timer Definitions
// Use TIM6 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE              TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO             TIM16
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE    2 //Connected to ST-Link
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX           PA15
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX           PA_2_ALT1
#endif

// Extra HAL modules
#if !defined(HAL_QSPI_MODULE_DISABLED)
  #define HAL_QSPI_MODULE_ENABLED
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
