/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
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
#define PB15                    0
#define PB14                    1
#define PA10                    2
#define PB3                     3
#define PB5                     4
#define PB4                     5
#define PB10                    6
#define PA8                     7
#define PC7                     8
#define PC6                     9
#define PC9                     10
#define PA7                     PIN_A11
#define PA6                     PIN_A12
#define PA5                     PIN_A13
#define PB7                     14
#define PB6                     15
// CN7 odd pins
#define PC10                    16
#define PC12                    17
// PA13 and PA14 are shared with SWD signals connected to STLINK-V3EC.
// It is not recommended to use them as I/O pins.
// By default, they are used as SWD signals (SB40 and SB41 ON).
#define PA13                    18
#define PA14                    19
#define PA15                    20
#define PC13                    21
#define PC14                    22
#define PC15                    23
#define PH0                     24
#define PH1                     25
#define PC2                     PIN_A6
#define PC3                     PIN_A7
// CN7 even pins
#define PC11                    28
#define PD2                     29
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA2                     PIN_A2
#define PB0                     PIN_A3
#define PC1                     PIN_A4
#define PC0                     PIN_A5
// CN10 odd pins are D0-D15
// CN10 even pins
#define PC8                     36
#define PC5                     PIN_A8
#define PA12                    38
#define PA11                    39
#define PB12                    40
#define PB2                     41
#define PB1                     PIN_A9
// 43 is PB15                   (0)
// 44 is PB14                   (1)
#define PB13                    45
#define PC4                     PIN_A10
#define PB8                     47
// Other
#define PA3                     PIN_A14
#define PA4                     PIN_A15
#define PA9                     50  // USB_VBUS

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA0_ALT2                (PA0  | ALT2)
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA4_ALT1                (PA4  | ALT1)
#define PA5_ALT1                (PA5  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA8_ALT1                (PA8  | ALT1)
#define PA8_ALT2                (PA8  | ALT2)
#define PA9_ALT1                (PA9  | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PA11_ALT1               (PA11 | ALT1)
#define PA12_ALT1               (PA12 | ALT1)
#define PA13_ALT1               (PA13 | ALT1)
#define PA14_ALT1               (PA14 | ALT1)
#define PA14_ALT2               (PA14 | ALT2)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB2_ALT1                (PB2  | ALT1)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB4_ALT2                (PB4  | ALT2)
#define PB5_ALT1                (PB5  | ALT1)
#define PB6_ALT1                (PB6  | ALT1)
#define PB6_ALT2                (PB6  | ALT2)
#define PB7_ALT1                (PB7  | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC1_ALT1                (PC1  | ALT1)
#define PC2_ALT1                (PC2  | ALT1)
#define PC3_ALT1                (PC3  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC12_ALT1               (PC12 | ALT1)

#define NUM_DIGITAL_PINS        51
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#define LED_GREEN               PA5
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

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
  #define SERIAL_UART_INSTANCE  3
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA_3_ALT1
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA4
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif

// Value of the External oscillator in Hz
#define HSE_VALUE               24000000UL

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
