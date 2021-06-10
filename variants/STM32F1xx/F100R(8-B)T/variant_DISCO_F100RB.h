/*
 *******************************************************************************
 * Copyright (c) 2011-2021, STMicroelectronics
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
// P1 connector
#define PC13                    0
#define PC0                     PIN_A0
#define PC1                     PIN_A1
#define PC2                     PIN_A2
#define PC3                     PIN_A3
#define PA0                     PIN_A4 // User button
#define PA1                     PIN_A5
#define PA2                     PIN_A6
#define PA3                     PIN_A7
#define PA4                     PIN_A8
#define PA5                     PIN_A9
#define PA6                     PIN_A10
#define PA7                     PIN_A11
#define PC4                     PIN_A12
#define PC5                     PIN_A13
#define PB0                     PIN_A14
#define PB1                     PIN_A15
#define PB2                     17
// P2 connector
#define PC6                     18
#define PC7                     19
#define PC8                     20 // LED blue
#define PC9                     21 // LED green
#define PA8                     22
#define PA9                     23
#define PA10                    24
#define PA11                    25
#define PA12                    26
#define PA13                    27
#define PA14                    28
#define PA15                    29
#define PC10                    30
#define PC11                    31
#define PC12                    32
#define PD2                     33
#define PB3                     34
#define PB4                     35
#define PB5                     36 // I2C SCL
#define PB6                     37 // I2C SDA
#define PB7                     38
#define PB8                     39
#define PB9                     40
// P3 connector
#define PB10                    41
#define PB11                    42
#define PB12                    43 // SPI SS
#define PB13                    44 // SPI SCLK
#define PB14                    45 // SPI MISO
#define PB15                    46 // SPI MOSI

// Alternate pins number
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB6_ALT1                (PB6  | ALT1)
#define PB7_ALT1                (PB7  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)

#define NUM_DIGITAL_PINS        47
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#define LED_GREEN               PC9
#define LED_BLUE                PC8
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PA0
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PB12
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PB9
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PB10
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3           PB11
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PB15
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB14
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB13
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB6
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

// Extra HAL modules
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
#endif
