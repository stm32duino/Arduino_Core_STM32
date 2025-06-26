/*
 *******************************************************************************
 * Copyright (c) 2025, STMicroelectronics
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
// Arduino UNO V3
// CN8
#define PB5                     PIN_A3  // Q4 Not connected by default (SB31 OFF)
#define PB4                     1       // A5 / Not connected by default (SB29 OFF)
#define PB14                    2       // Not connected by default (SB36 OFF)
#define PB3                     PIN_A0  // Not connected by default (SB24 OFF)
#define PA11                    4       // Not connected by default (SB44 OFF)
#define PB7                     5       // Not connected by default (SB42 OFF)
#define PB6                     6       // Not connected by default (SB40 OFF)
#define PA8                     7       // Not connected by default (SB39 OFF)
// CN6
#define PB15                    8
#define PA0                     9       // Not connected by default (SB12 OFF)
#define PA9                     10      // SB47 ON
// 11 is PA11                  (4)      // SB43 ON
// 12 is PA8                   (7)      // SB41 ON
// 13 is PB3                   (3)      // SB14 ON
// 14 is PB7                   (5)      // SB34 ON
// 15 is PB6                   (6)      // SB32 ON
// CN7
// Analog pins A0 to A5 silkscreened
// None connected by default moreover some of assigned pins are not supported
// as the N channel of the ADC is not supportedby the core
#define PB2                     16      // A1 / Not connected by default (SB13 OFF)
#define PB1                     PIN_A2  // Not connected by default (SB10 OFF)
#define PB0                     18      // A3 / Not connected by default (SB8 OFF)
// ST Morpho
// CN3 Left Side
#define PA10                    19
#define PA2                     20
#define PA3                     PIN_A1
#define PB12                    22
#define PB13                    23
#define PA1                     24

// Alternate pins number
#define PA2_ALT1                (PA2 | ALT1)
#define PA3_ALT1                (PA3 | ALT1)
#define PA9_ALT1                (PA9 | ALT1)
#define PB3_ALT1                (PB3 | ALT1)
#define PB4_ALT1                (PB4 | ALT1)
#define PB6_ALT1                (PB6 | ALT1)

#define NUM_DIGITAL_PINS        25
#define NUM_ANALOG_INPUTS       4

// On-board LED pin number
#define LED_BLUE                PB1
#define LED_LD1                 LED_BLUE
#define LED_GREEN               PB4
#define LED_LD2                 LED_GREEN
#define LED_RED                 PB2
#define LED_LD3                 LED_RED
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_BLUE
#endif

// On-board user button
#define USER_B1                 PA0
#define USER_B2                 PB5
#define USER_B3                 PB14
#ifndef USER_BTN
  #define USER_BTN              USER_B1
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM16
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM17
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PB0
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA1
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
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
#endif
