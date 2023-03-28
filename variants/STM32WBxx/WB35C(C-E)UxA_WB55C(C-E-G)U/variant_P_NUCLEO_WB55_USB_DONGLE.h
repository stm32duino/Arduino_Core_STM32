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
// CN1
#define PA13                    0      // SWDIO
#define PA14                    1      // SWCLK
#define PB3                     2      // SWO
#define PB2                     3      // SPI1 NSS
#define PA5                     PIN_A0 // SPI1 SCK
#define PA6                     PIN_A1 // SPI1 MISO
#define PA7                     PIN_A2 // SPI1 MOSI
// CN2
#define PB8                     7      // I2C1 SCL
#define PB9                     8      // I2C1 SDA
#define PA0                     PIN_A3 // WKUP
#define PA2                     PIN_A4 // LPUART1 TX
#define PA3                     PIN_A5 // LPUART1 RX
#define PB6                     12
#define PA9                     PIN_A6 // SB2 close/SB6 open (default)
#define PA8                     PIN_A7
#define PA1                     PIN_A8
// Same position than PA9 on CN2
#define PB7                     16     // SB2 open/SB6 close
// Specific
#define PC14                    17     // OSC32-IN
#define PC15                    18     // OSC32-OUT
#define PH3                     19     // BOOT0
#define PA4                     20     // LED1 BLUE
#define PB0                     21     // LED2 GREEN
#define PB1                     22     // LED3 RED
#define PA10                    23     // USER_BTN
#define PA11                    24     // USB_DM
#define PA12                    25     // USB_DP

// Not connected
// PA15
// PB4
// PB5
// PE4

// Alternate pins number
#define PA7_ALT1                (PA7 | ALT1)
#define PB8_ALT1                (PB8 | ALT1)
#define PB9_ALT1                (PB9 | ALT1)

#define NUM_DIGITAL_PINS        26
#define NUM_ANALOG_INPUTS       9

// On-board LED pin number
#define LED1                    PA4
#define LED2                    PB0
#define LED3                    PB1
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED1
#endif
#define LED_BLUE                LED1
#define LED_GREEN               LED2
#define LED_RED                 LED3

// On-board user button
// Note: use '_BTN' for SW1 as it is a register name of M24SR64-Y
#define SW1_BTN                 PA10
#ifndef USER_BTN
  #define USER_BTN              SW1_BTN
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PB2
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PB6
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PA8
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3           PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA7
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PA6
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PA5
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB9
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB8
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
  #define SERIAL_UART_INSTANCE  101
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA3
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA2
#endif

// Extra HAL modules
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
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
#endif
