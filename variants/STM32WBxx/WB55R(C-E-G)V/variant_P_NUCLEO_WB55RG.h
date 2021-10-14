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
 *        STM32 pins number
 *----------------------------------------------------------------------------*/
#define PA3                     PIN_A6
#define PA2                     PIN_A7
#define PC6                     2
#define PA10                    3
#define PC10                    4
#define PA15                    5
#define PA8                     PIN_A8
#define PC13                    7
#define PC12                    8
#define PA9                     PIN_A9
#define PA4                     PIN_A10 // PB10 (SB41 !SB42)
#define PA7                     PIN_A11
#define PA6                     PIN_A12
#define PA5                     PIN_A13
#define PB9                     14
#define PB8                     15
// ST Morpho
// CN7 Left Side
#define PB11                    16
#define PC5                     PIN_A14
#define PA13                    18      // SWD
#define PA14                    19      // SWD
#define PC14                    20
#define PC15                    21
// CN7 Right Side
#define PB2                     22
#define PE4                     23
// CN10 Left Side
#define PC4                     PIN_A15 // SW1
// CN10 Right side
#define PB4                     25
#define PB7                     26
#define PA12                    27
#define PA11                    28
#define PB12                    29
#define PB0                     30      // LED2
#define PB1                     31      // LED3
#define PB15                    32      // PB4 (SB7 !SB9 !SB10) or PA9 (!SB7 !SB9 SB10)
#define PB14                    33
#define PB13                    34      // PB3 (!SB12 SB13)
#define PB6                     35
#define PD0                     36      // SW2
#define PD1                     37      // SW3
#define PB3                     38
#define PC0                     PIN_A0
#define PC1                     PIN_A1
#define PA1                     PIN_A2
#define PA0                     PIN_A3
#define PC3                     PIN_A4
#define PC2                     PIN_A5
// Not on connectors
#define PB5                     45      // LED1
#define PB10                    46
#define PC11                    47
#define PH3                     48      // BOOT0

// Alternate pins number
#define PA7_ALT1                (PA7 | ALT1)
#define PB8_ALT1                (PB8 | ALT1)
#define PB9_ALT1                (PB9 | ALT1)

#define NUM_DIGITAL_PINS        49
#define NUM_ANALOG_INPUTS       16

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
// Note: use '_BTN' for SW1 and SW2 as they are register name of M24SR64-Y
#define SW1_BTN                 PC4 // PC13 (!SB47 SB48)
#define SW2_BTN                 PD0
#define SW3_BTN                 PD1
#ifndef USER_BTN
  #define USER_BTN              SW1_BTN
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
  #define SERIAL_UART_INSTANCE  1 //Connected to ST-Link
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PB7
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PB6
#endif

// Only 512k provided for cpu1, so defined the FLASH_PAGE_NUMBER
// for EEPROM emulation to the last 512k pages.
#define FLASH_PAGE_NUMBER       127

// Extra HAL modules
#if !defined(HAL_QSPI_MODULE_DISABLED)
  #define HAL_QSPI_MODULE_ENABLED
#endif

/* backward compatibility */
#define ARDUINO_PNUCLEO_WB55RG

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
