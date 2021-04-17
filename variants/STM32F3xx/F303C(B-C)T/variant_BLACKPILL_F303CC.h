/*
 *******************************************************************************
 * Copyright (c) 2018-2021, STMicroelectronics
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
// USB connector on the top, MCU side
// Left Side
#define PB9                     0
#define PB8                     1
#define PB7                     2
#define PB6                     3
#define PB5                     4
#define PB4                     5
#define PB3                     6
#define PA15                    7
#define PA12                    8  // USB_DP
#define PA11                    9  // USB_DM
#define PA10                    10
#define PA9                     11
#define PA8                     12
#define PB15                    PIN_A14
#define PB14                    PIN_A13
#define PB13                    PIN_A12
#define PB12                    PIN_A11
// Right side
#define PC13                    17 // LED
#define PC14                    18
#define PC15                    19
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA2                     PIN_A2
#define PA3                     PIN_A3
#define PA4                     PIN_A4
#define PA5                     PIN_A5
#define PA6                     PIN_A6
#define PA7                     PIN_A7
#define PB0                     PIN_A8
#define PB1                     PIN_A9
#define PB10                    30
#define PB11                    31
// Other
#define PB2                     PIN_A10 // BOOT1
#define PA13                    33  // SWDIO
#define PA14                    34  // SWCLK
#define PF0                     35  // OSC IN
#define PF1                     36  // OSC OUT

// Alternate pins number
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
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)

#define NUM_DIGITAL_PINS        37
#define NUM_ANALOG_INPUTS       15

// On-board LED pin number
#define LED_BLUE                PC13
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_BLUE
#endif

// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
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

// I2C Definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB6
#endif

// Timer Definitions
// Use TIM6 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM2
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
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
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
  #ifndef SERIAL_PORT_USBVIRTUAL
    #define SERIAL_PORT_USBVIRTUAL  SerialUSB
  #endif
#endif
