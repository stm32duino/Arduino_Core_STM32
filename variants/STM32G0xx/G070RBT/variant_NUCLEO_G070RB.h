/*
 *******************************************************************************
 * Copyright (c) 2022, STMicroelectronics
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
#define PC5                     PIN_A10
#define PC4                     PIN_A11
#define PA10                    2
#define PB3                     3
#define PB5                     4
#define PB4                     5
#define PB14                    6
#define PA8                     7
#define PA9                     8
#define PC7                     9
#define PB0                     PIN_A12
#define PA7                     PIN_A6
#define PA6                     PIN_A7
#define PA5                     PIN_A13 // LED
#define PB9                     14
#define PB8                     15
// ST Morpho
// CN7 Left Side
#define PC10                    16
#define PC12                    17
#define PA14                    18 // SWD
#define PD0                     19
#define PD3                     20
#define PA13                    21 // SWD
#define PD4                     22
#define PA15                    23
#define PB7                     24
#define PC13                    25
#define PC14                    26
#define PC15                    27
#define PF0                     28
#define PF1                     29
#define PC2                     30
#define PC3                     31
// CN7 Right Side
#define PC11                    32
#define PD2                     33
#define PD1                     34
#define PD5                     35
// CN10 Left Side
#define PC9                     36
// CN10 Right side
#define PC8                     37
#define PC6                     38
#define PA3                     PIN_A14
#define PD6                     40
#define PA11                    41
#define PA12                    42
#define PC1                     43
#define PC0                     44
#define PB2                     PIN_A8
#define PB6                     46
#define PB15                    47
#define PB10                    PIN_A9
#define PB13                    49
#define PA2                     PIN_A15
#define PD8                     51
#define PD9                     52
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA4                     PIN_A2
#define PB1                     PIN_A3
#define PB11                    PIN_A4
#define PB12                    PIN_A5
#define PF2                     59
#define PA9_R                   60
#define PA10_R                  61

// Alternate pins number
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB6_ALT1                (PB6  | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

#define NUM_DIGITAL_PINS        62
#define NUM_REMAP_PINS          2
#define NUM_ANALOG_INPUTS       16

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
  #define SERIAL_UART_INSTANCE  2 //Connected to ST-Link
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
  #define SERIAL_PORT_MONITOR   Serial
  #define SERIAL_PORT_HARDWARE  Serial2
#endif
