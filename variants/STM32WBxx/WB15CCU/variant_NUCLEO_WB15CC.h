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
#define PB7                     0
#define PB6                     1
#define PB0                     2
#define PA12                    3
#define PB1                     4
#define PA11                    5
#define PA8                     PIN_A6
#define PE4                     7
#define PB5                     8
#define PA15                    9
#define PB2                     10
#define PA7                     PIN_A7
#define PB4                     12
#define PA5                     PIN_A8
#define PB9                     14
#define PB8                     15
#define PA4                     PIN_A0
#define PA6                     PIN_A1
#define PA1                     PIN_A2
#define PA0                     PIN_A3
#define PA2                     PIN_A4
#define PA3                     PIN_A5
// ST Morpho
// CN7 Left Side
#define PH3                     22     // BOOT0
#define PA13                    23     // SWDIO
#define PA14                    24     // SWDCLK
#define PC14                    25     // OSC32_IN
#define PC15                    26     // OSC32_OUT
// CN10 Right side
#define PA9                     PIN_A9
#define PA10                    28
#define PB3                     29

#define NUM_DIGITAL_PINS        30
#define NUM_ANALOG_INPUTS       10

// On-board LED pin number
#define LED1                    PB5
#define LED2                    PB0
#define LED3                    PB1
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED1
#endif
#define LED_BLUE                LED1
#define LED_GREEN               LED2
#define LED_RED                 LED3

// On-board user button
#define B1_BTN                  PA0
#define B2_BTN                  PE4
#define B3_BTN                  PA6
#ifndef USER_BTN
  #define USER_BTN              B1_BTN
#endif

// Timer Definitions
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM2
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM1
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1 //Connected to ST-Link
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

// Only 128k provided for cpu1, so defined the FLASH_PAGE_NUMBER
// for EEPROM emulation to the last 128k pages.
#define FLASH_PAGE_NUMBER       63

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
  #define SERIAL_PORT_HARDWARE  Serial1
#endif
