/*
 *******************************************************************************
 * Copyright (c) 2017-2021, STMicroelectronics
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

#define PA0                     0 // LED 1
#define PA1                     1 // LED 2
#define PA2                     2 // LED 3
#define PA3                     3 // LED 4
#define PA4                     PIN_A0
#define PA5                     PIN_A1
#define PA6                     PIN_A2
#define PA7                     PIN_A3
#define PA8                     8
#define PA9                     9
#define PA10                    10
#define PB6                     11 // TX
#define PB7                     12 // RX
#define PB8                     13
#define PB4                     14 // User button

#define PA11                    17 // USB_D-
#define PA12                    18 // USB_D+
#define PA13                    19 // SWD
#define PA14                    20 // SWD

// Alternate pins number
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA14_ALT1               (PA14 | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)

#define NUM_DIGITAL_PINS        21
#define NUM_ANALOG_INPUTS       4

// On-board LED pin number
#define LED_GREEN               PA0
#define LED_1                   PA0
#define LED_2                   PA1
#define LED_3                   PA2
#define LED_4                   PA3
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PB4
#endif

// Timer Definitions
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for 'Serial' instance
// Mandatory for Firmata
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
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR     Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE    Serial
  #endif
#endif
