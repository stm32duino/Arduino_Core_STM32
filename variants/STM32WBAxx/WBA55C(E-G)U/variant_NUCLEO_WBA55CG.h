/*
 *******************************************************************************
 * Copyright (c) 2023, STMicroelectronics
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
#define PB5                     1
#define PB7                     2  // B2
#define PB6                     3  // B3
#define PA11                    4
#define PB14                    5
#define PB0                     6
#define PB9                     PIN_A6
#define PB15                    8
#define PA9                     9  // LED2 (default not connected SB28 off)
#define PA12                    10
#define PA15                    11
#define PB3                     12
#define PB4                     13 // LED1
#define PB1                     14
#define PB2                     15

#define PA7                     PIN_A0
#define PA6                     PIN_A1
#define PA2                     PIN_A2
#define PA1                     PIN_A3
#define PA5                     PIN_A4
#define PA0                     PIN_A5

#define PB8                     22 // LED3
#define PC13                    23 // B1
#define PB12                    24 // VCP1_TX
#define PA8                     25 // VCP1_RX
#define PC15                    26 // OSC32_IN
#define PC14                    27 // OSC32_OUT
#define PA14                    28 // SWCLK
#define PA13                    29 // SWDIO
#define PH3                     30 // BOOT0

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA1_ALT2                (PA1  | ALT2)
#define PA2_ALT1                (PA2  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB2_ALT1                (PB2  | ALT1)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB15_ALT1               (PB15 | ALT1)

#define NUM_DIGITAL_PINS        31
#define NUM_ANALOG_INPUTS       7

// On-board LED pin number
#define LED1                    PB4
#define LED2                    PA9
#define LED3                    PB8
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED1
#endif
#define LED_BLUE                LED1
#define LED_GREEN               LED2
#define LED_RED                 LED3

// On-board user button
#define B1_BTN                  PC13
#define B2_BTN                  PB6
#define B3_BTN                  PB7
#ifndef USER_BTN
  #define USER_BTN              B1_BTN
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
  #define PIN_SERIAL_RX         PA8
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PB12
#endif

// Alternate SYS_WKUP definition
#define PWR_WAKEUP_PIN1_1
#define PWR_WAKEUP_PIN3_1
#define PWR_WAKEUP_PIN4_1
#define PWR_WAKEUP_PIN6_1
#define PWR_WAKEUP_PIN7_1
#define PWR_WAKEUP_PIN8_1

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
