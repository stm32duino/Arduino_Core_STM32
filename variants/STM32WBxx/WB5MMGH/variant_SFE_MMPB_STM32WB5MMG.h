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
#define PA0                     0
#define PA1                     1
#define PA2                     2
#define PA3                     3
#define PA4                     4
#define PA5                     5
#define PA6                     6
#define PA7                     7
#define PA8                     8
#define PA9                     9
#define PA10                    10
#define PA11                    11
#define PA12                    12
#define PA13                    13
#define PA14                    14
#define PB3                     15
#define PB4                     16
#define PB5                     17
#define PB6                     18
#define PB7                     19
#define PB8                     20
#define PB9                     21
#define PB12                    22
#define PB13                    23
#define PB14                    24
#define PB15                    25
#define PC0                     26
#define PC1                     27
#define PC2                     PIN_A0
#define PC3                     PIN_A1
#define PC4                     PIN_A2
#define PC11                    31
#define PC13                    32
#define PD3                     33
#define PD4                     34
#define PD5                     35
#define PD6                     36
#define PD7                     37
#define PD8                     38
#define PD14                    39
#define PD15                    40
#define PE0                     41
#define PE3                     42
#define PE4                     43
#define PH0                     44
#define PH1                     45
#define PH3                     46

// Alternate pins number
#define PA7_ALT1                (PA7 | ALT1)
#define PB8_ALT1                (PB8 | ALT1)
#define PB9_ALT1                (PB9 | ALT1)

#define NUM_DIGITAL_PINS        47
#define NUM_ANALOG_INPUTS       3

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PA2
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PH0
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PH1
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3           PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA7
  #ifndef PIN_SPI_PICO
    #define PIN_SPI_PICO        PIN_SPI_MOSI
  #endif
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PA6
  #ifndef PIN_SPI_POCI
    #define PIN_SPI_POCI        PIN_SPI_MISO
  #endif
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PA5
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
  #define TIMER_TONE            TIM16
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM17
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

#ifndef PIN_SERIALLP1_RX
  #define PIN_SERIALLP1_RX      PC0
#endif
#ifndef PIN_SERIALLP1_TX
  #define PIN_SERIALLP1_TX      PC1
#endif

// Extra HAL modules
#if !defined(HAL_QSPI_MODULE_DISABLED)
  #define HAL_QSPI_MODULE_ENABLED
  #define QSPI_CLK                PA3
  #define QSPI_CS                 PD3
  #define QSPI_IO0                PD4
  #define QSPI_IO1                PD5
  #define QSPI_IO2                PD6
  #define QSPI_IO3                PD7
#endif

#if !defined(HAL_TIM_MODULE_DISABLED)
  #define HAL_TIM_MODULE_ENABLED
#endif

#if !defined(HAL_I2S_MODULE_DISABLED)
  #define HAL_I2S_MODULE_ENABLED
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
  #ifndef SERIAL_PORT_HARDWARE_OPEN
    #define SERIAL_PORT_HARDWARE_OPEN SerialOpen
  #endif
#endif
