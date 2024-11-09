/*
 *******************************************************************************
 * Copyright (c) 2024, STMicroelectronics
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
#define PB7                     0
#define PB6                     1
#define PA10                    2
#define PC7                     3
#define PB5                     4
#define PB4                     5
#define PC8                     6
#define PA8                     PIN_A6
#define PA9                     8
#define PB3                     9
#define PA15                    10
#define PA7                     PIN_A7
#define PA6                     PIN_A8
#define PA5                     PIN_A9  // LED1
#define PB9                     14
#define PB8                     15
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA4                     PIN_A2
#define PB0                     PIN_A3
#define PC4                     PIN_A4
#define PC5                     PIN_A5
// ST Morpho
// CN7 Left Side
#define PC10                    22
#define PC12                    23
#define PD4                     24
#define PD0                     25
#define PD3                     26
#define PA13                    27      // SWD
#define PA14                    28      // SWD
#define PC6                     29
#define PC2                     30
#define PC13                    31      // USER_BTN
#define PC14                    32      // OSCX_IN
#define PC15                    33      // OSCX_OUT
#define PF0                     34      // OSC_IN
#define PF1                     35      // OSC_OUT
#define PF3                     36      // VBAT
#define PB2                     PIN_A10
#define PB11                    PIN_A11
// CN7 Right Side
#define PC11                    39
#define PD2                     40
#define PD1                     41
#define PF2                     42      // NRST
#define PD5                     43
// CN10 Left Side
#define PC3                     44
// CN10 Right side
#define PC9                     45      // LED2
#define PC1                     46
#define PA3                     47      // RX
#define PD6                     48
#define PA12                    49      // USB_DP
#define PA11                    50      // USB_DM
#define PB12                    PIN_A12
#define PA2                     52      // TX
#define PC0                     53      // USB_SENSE
#define PB1                     PIN_A13
#define PB15                    55
#define PB14                    56
#define PB13                    57
#define PB10                    PIN_A14
#define PD8                     59
#define PD9                     60

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA0_ALT2                (PA0  | ALT2)
#define PA1_ALT1                (PA1  | ALT1)
#define PA1_ALT2                (PA1  | ALT2)
#define PA2_ALT1                (PA2  | ALT1)
#define PA2_ALT2                (PA2  | ALT2)
#define PA3_ALT1                (PA3  | ALT1)
#define PA3_ALT2                (PA3  | ALT2)
#define PA4_ALT1                (PA4  | ALT1)
#define PA4_ALT2                (PA4  | ALT2)
#define PA5_ALT1                (PA5  | ALT1)
#define PA5_ALT2                (PA5  | ALT2)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA8_ALT1                (PA8  | ALT1)
#define PA8_ALT2                (PA8  | ALT2)
#define PA8_ALT3                (PA8  | ALT3)
#define PA8_ALT4                (PA8  | ALT4)
#define PA8_ALT5                (PA8  | ALT5)
#define PA9_ALT1                (PA9  | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB1_ALT3                (PB1  | ALT3)
#define PB3_ALT1                (PB3  | ALT1)
#define PB3_ALT2                (PB3  | ALT2)
#define PB5_ALT1                (PB5  | ALT1)
#define PB6_ALT1                (PB6  | ALT1)
#define PB6_ALT2                (PB6  | ALT2)
#define PB6_ALT3                (PB6  | ALT3)
#define PB6_ALT4                (PB6  | ALT4)
#define PB6_ALT5                (PB6  | ALT5)
#define PB7_ALT1                (PB7  | ALT1)
#define PB7_ALT2                (PB7  | ALT2)
#define PB7_ALT3                (PB7  | ALT3)
#define PB7_ALT4                (PB7  | ALT4)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC14_ALT1               (PC14 | ALT1)

#define NUM_DIGITAL_PINS        61
#define NUM_ANALOG_INPUTS       15

// On-board LED pin number
#define LED1                    PA5
#define LED2                    PC9
#define LED_GREEN               LED1
#define LED_BLUE                LED2
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
  #define TIMER_TONE            TIM14
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM16
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  2
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA3
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA2
#endif

#define HSE_VALUE               (8000000U)  /*!< Value of the External oscillator in Hz */

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
