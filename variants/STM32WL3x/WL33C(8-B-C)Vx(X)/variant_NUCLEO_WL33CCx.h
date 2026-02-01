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
#define PB7                     0
#define PB6                     1
#define PA9                     2
#define PA0                     3
#define PA8                     4
#define PA13                    5
#define PA12                    6
#define PA4                     7
#define PA5                     8
#define PA14                    9
#define PB10                    10
#define PB9                     11
#define PB8                     12
#define PB11                    13
#define PA7                     14
#define PA6                     15
#define PB0                     16
#define PB1                     PIN_A0
#define PB2                     18
#define PB3                     PIN_A1
#define PB14                    20
#define PB5                     PIN_A2
#define PA1                     22     // VCP RX
#define PA15                    23     // VCP TX
#define PB4                     24     // LD2
#define PB15                    25     // LD3
#define PA2                     26     // SWDIO
#define PA3                     27     // SWCLK
#define PA10                    28     // BOOT0
#define PA11                    29
#define PB12                    30     // OSC_32_OUT
#define PB13                    31     // OSC_32_IN


// Alternate pins number
#define PA2_ALT1                (PA2 | ALT1)
#define PA3_ALT1                (PA3 | ALT1)

#define NUM_DIGITAL_PINS        32
#define NUM_ANALOG_INPUTS       3

// On-board LED pin number
#define LED_BLUE                PA14
#define LED_LD1                 LED_BLUE
#define LED_GREEN               PB4
#define LED_LD2                 LED_GREEN
#define LED_RED                 PB5
#define LED_LD3                 LED_RED
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_BLUE
#endif

// On-board user button
#define USER_B1                 PA0
#define USER_B2                 PB11
#define USER_B3                 PB15
#ifndef USER_BTN
  #define USER_BTN              USER_B1
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM16
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM2
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA15
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA1
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif

// Alternate SYS_WKUP definition
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
