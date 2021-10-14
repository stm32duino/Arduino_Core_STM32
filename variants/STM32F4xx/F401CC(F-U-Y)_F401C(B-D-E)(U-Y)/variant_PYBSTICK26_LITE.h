/*
 *******************************************************************************
 * Copyright (c) 201-2021, STMicroelectronics
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

#define PB9                     0
#define PB8                     1
#define PB6                     2
#define PA2                     PIN_A0
#define PA3                     PIN_A1
#define PA0                     PIN_A2
#define PB3                     6
#define PB10                    7
#define PB12                    8
#define PB13                    9
#define PB14                    10
#define PA7                     PIN_A3
#define PB4                     12
#define PA5                     PIN_A4
#define PA10                    14
#define PA15                    15
#define PA4                     PIN_A5

#define PA13                    17 // LED_RED
#define PA14                    18 // LED_GREEN
#define PB0                     19 // LED_YELLOW
#define PB1                     20 // LED_BLUE

#define PC13                    21 // USR_BTN

#define PA11                    22 // USB D-, CAN_RX
#define PA12                    23 // USB D+, CAN_TX

#define PC14                    24 // OSC32_IN
#define PC15                    25 // OSC32_OUT
#define PH0                     26 // OSC_IN
#define PH1                     27 // OSC_OUT

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA2_ALT2                (PA2  | ALT2)
#define PA3_ALT1                (PA3  | ALT1)
#define PA3_ALT2                (PA3  | ALT2)
#define PA4_ALT1                (PA4  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)

// This must be a literal
#define NUM_DIGITAL_PINS        28
#define NUM_ANALOG_INPUTS       6

// PYBSTICK26 Sx pinout
#define S3                      PB9
#define S5                      PB8
#define S7                      PB6
#define S8                      PA2
#define S10                     PA3
#define S11                     PB3
#define S12                     PA0
#define S13                     PB10
// #define S13A                      PC3
#define S15                     PB12
// #define S15A                      PC5
#define S16                     PB13
// #define S16A                      PC6
#define S18                     PB14
// #define S18A                      PC7
#define S19                     PA7
#define S21                     PB4
#define S22                     PA10
#define S23                     PA5
#define S24                     PA15
#define S26                     PA4

// On-board LED pin number
#define LED_GREEN               PA14
#define LED_RED                 PA13
#define LED_YELLOW              PB0
#define LED_BLUE                PB1
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_RED
#endif

// On-board user buttons
#ifndef USER_BTN
  #define USER_BTN              PC13
#endif
#define USER_BTN_2              PB6

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA15
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PA15
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PA4
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA7
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB4
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
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM10
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM11
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  2
#endif

// Default pin used for 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA3
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA2
#endif

/* Extra HAL definitions */
#define HSE_VALUE               16000000U

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
    #define SERIAL_PORT_HARDWARE  Serial2
  #endif
  #ifndef SERIAL_PORT_USBVIRTUAL
    #define SERIAL_PORT_USBVIRTUAL  SerialUSB
  #endif
#endif
