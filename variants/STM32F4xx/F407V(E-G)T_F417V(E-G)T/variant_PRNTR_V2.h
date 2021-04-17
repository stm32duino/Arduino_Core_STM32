/*
 *******************************************************************************
 * Copyright (c) 2017-2021, STMicroelectronics
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
#define PE0                    0
#define PE1                    1
#define PE2                    2
#define PE3                    3
#define PE4                    4
#define PE5                    5
#define PE6                    6
#define PE7                    7
#define PE8                    8
#define PE9                    9
#define PE10                   10
#define PE11                   11
#define PE12                   12
#define PE13                   13
#define PE14                   14
#define PE15                   15

#define PB0                    16
#define PB1                    17
#define PB2                    18
#define PB3                    19
#define PB4                    20
#define PB5                    21
#define PB6                    22
#define PB7                    23
#define PB8                    24
#define PB9                    25
#define PB10                   26
#define PB11                   27
#define PB12                   28
#define PB13                   29
#define PB14                   30
#define PB15                   31

#define PC0                    32
#define PC1                    33
#define PC2                    34
#define PC3                    35
#define PC4                    36
#define PC5                    37
#define PC6                    38
#define PC7                    39
#define PC8                    40
#define PC9                    41
#define PC10                   42
#define PC11                   43
#define PC12                   44
#define PC13                   45
#define PC14                   46
#define PC15                   47

#define PD0                    48
#define PD1                    49
#define PD2                    50
#define PD3                    51
#define PD4                    52
#define PD5                    53
#define PD6                    54
#define PD7                    55
#define PD8                    56
#define PD9                    57
#define PD10                   58
#define PD11                   59
#define PD12                   60
#define PD13                   61
#define PD14                   62
#define PD15                   63

#define PA0                    PIN_A0
#define PA1                    PIN_A1
#define PA2                    PIN_A2
#define PA3                    PIN_A3
#define PA4                    PIN_A4
#define PA5                    PIN_A5
#define PA6                    PIN_A6
#define PA7                    PIN_A7
#define PA8                    72
#define PA9                    73
#define PA10                   74
#define PA11                   75
#define PA12                   76
#define PA13                   77
#define PA14                   78
#define PA15                   79

#define NUM_DIGITAL_PINS        80
#define NUM_ANALOG_INPUTS       8

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PNUM_NOT_DEFINED
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// SPI Definitions
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA7
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PA6
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB3
#endif

// I2C Definitions
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
#ifndef TIMER_SERIAL
  #define TIMER_SERIAL          TIM12
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

/* Extra HAL modules */
#if !defined(HAL_SD_MODULE_DISABLED)
  #define HAL_SD_MODULE_ENABLED
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
    #define SERIAL_PORT_HARDWARE  Serial1
  #endif
#endif
