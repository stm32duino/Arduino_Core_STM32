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
 *        Pins
 *----------------------------------------------------------------------------*/
// CN9
#define PC5                     PIN_A12
#define PC4                     PIN_A13
#define PA10                    2
#define PB3                     3
#define PB5                     4
#define PB4                     5
#define PB10                    6
#define PA8                     7
// CN5
#define PA9                     8
#define PC7                     9
#define PB6                     10
#define PA7                     PIN_A18
#define PA6                     PIN_A19
#define PA5                     PIN_A20 // LED
#define PB9                     14
#define PB8                     15
// CN7 Left Side
#define PC10                    16
#define PC12                    17
#define PA13                    18 // SWDIO
#define PA14                    19 // SWCLK
#define PA15                    20
#define PB7                     21
#define PC13                    22
#define PC14                    23
#define PC15                    24
#define PF0                     PIN_A14
#define PF1                     PIN_A15
#define PC2                     PIN_A16
#define PC3                     PIN_A17
// CN7 Right Side
#define PD2                     29
#define PC11                    30
// CN10 Left Side
#define PC9                     31
// CN8
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA4                     PIN_A2
#define PB0                     PIN_A3
#define PC1                     PIN_A4
#define PC0                     PIN_A5
// CN10 Right side
#define PB14                    PIN_A6
#define PB15                    PIN_A7
#define PB1                     PIN_A8
#define PB2                     PIN_A9
#define PB11                    PIN_A10
#define PB12                    PIN_A11
#define PB13                    44
#define PA11                    45
#define PA12                    46
#define PC6                     47
#define PC8                     48
#define PA2                     PIN_A21 // VCP_TX
#define PA3                     PIN_A22 // VCP_RX
//PG10

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA4_ALT1                (PA4  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA9_ALT1                (PA9  | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PA11_ALT1               (PA11 | ALT1)
#define PA11_ALT2               (PA11 | ALT2)
#define PA12_ALT1               (PA12 | ALT1)
#define PA12_ALT2               (PA12 | ALT2)
#define PA13_ALT1               (PA13 | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB4_ALT2                (PB4  | ALT2)
#define PB5_ALT1                (PB5  | ALT1)
#define PB5_ALT2                (PB5  | ALT2)
#define PB6_ALT1                (PB6  | ALT1)
#define PB6_ALT2                (PB6  | ALT2)
#define PB7_ALT1                (PB7  | ALT1)
#define PB7_ALT2                (PB7  | ALT2)
#define PB8_ALT1                (PB8  | ALT1)
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB9_ALT3                (PB9  | ALT3)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC1_ALT1                (PC1  | ALT1)
#define PC2_ALT1                (PC2  | ALT1)
#define PC3_ALT1                (PC3  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PC13_ALT1               (PC13 | ALT1)

// This must be a literal
#define NUM_DIGITAL_PINS        51
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       23

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PA5
#endif
#define LED_GREEN               LED_BUILTIN

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC13
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
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
  #define SERIAL_PORT_HARDWARE  SerialLP1
#endif
