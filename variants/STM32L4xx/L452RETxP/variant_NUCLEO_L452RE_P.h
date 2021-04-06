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
#define PB3                     3
#define PB5                     4
#define PA15                    5
#define PB10                    6
#define PC7                     7
#define PB6                     8
#define PA8                     9
#define PA11                    10
#define PB15                    11
#define PB14                    12
#define PB13                    13 // LED
#define PB7                     14
#define PB8                     15
// ST Morpho
// CN5 Left Side
#define PC10                    16
#define PC12                    17
#define PB12                    18
#define PA13                    19 // SWD
#define PA14                    20 // SWD
#define PC13                    21
#define PC14                    22
#define PC15                    23
#define PH0                     24
#define PH1                     25
#define PB4                     26
#define PB9                     27
// CN5 Right Side
#define PC11                    28
// CN6 Left Side
#define PC9                     29
// CN6 Right side
#define PC8                     30
#define PC6                     31
#define PB0                     PIN_A10
#define PB11                    33
#define PB2                     34
#define PB1                     PIN_A11
#define PA7                     PIN_A9
#define PA6                     PIN_A8
#define PA5                     PIN_A7
#define PA4                     PIN_A6
#define PC4                     PIN_A12
#define PA3                     41
#define PA2                     42
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PC3                     PIN_A2
#define PC2                     PIN_A3
#define PC1                     PIN_A4
#define PC0                     PIN_A5
#define PH3                     49 // BOOT0

// Alternate pins number
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA4_ALT1                (PA4  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PB6_ALT1                (PB6  | ALT1)
#define PB7_ALT1                (PB7  | ALT1)
#define PB10_ALT1               (PB10 | ALT1)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PC0_ALT1                (PC0  | ALT1)
#define PC1_ALT1                (PC1  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

#define NUM_DIGITAL_PINS        50
#define NUM_ANALOG_INPUTS       13

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN             PB13
#endif
#ifndef LED_GREEN
  #define LED_GREEN               LED_BUILTIN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN                PC13
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
  #define SERIAL_UART_INSTANCE    101 //Connected to ST-Link
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA3
#define PIN_SERIAL_TX           PA2

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
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
  #define SERIAL_PORT_MONITOR   Serial
  #define SERIAL_PORT_HARDWARE  Serial
#endif
