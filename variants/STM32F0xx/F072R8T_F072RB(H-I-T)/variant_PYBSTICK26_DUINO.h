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
#define PC3                     PIN_A6
#define PC5                     PIN_A7
#define PC6                     19
#define PC7                     20

#define PA13                    21 // LED_RED
#define PA14                    22 // LED_GREEN
#define PB0                     23 // LED_YELLOW
#define PB1                     24 // LED_BLUE

#define PC13                    25 // USR_BTN

#define PA11                    26 // USB D-, CAN_RX
#define PA12                    27 // USB D+, CAN_TX

#define PC14                    28 // OSC32_IN
#define PC15                    29 // OSC32_OUT
#define PF0                     30 // OSC_IN
#define PF1                     31 // OSC_OUT

// Alternate pins number
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB14_ALT1               (PB14 | ALT1)

#define NUM_DIGITAL_PINS        32
#define NUM_ANALOG_INPUTS       8

// PYBSTICK26 Sx pinout
#define S3                      PB9
#define S5                      PB8
#define S7                      PB6
#define S8                      PA2
#define S10                     PA3
#define S11                     PB3
#define S12                     PA0
#define S13                     PB10
#define S13A                    PC3
#define S15                     PB12
#define S15A                    PC5
#define S16                     PB13
#define S16A                    PC6
#define S18                     PB14
#define S18A                    PC7
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

#define LED_BUILTIN             LED_RED

// On-board user buttons
#define USER_BTN                PC13
#define USER_BTN_2              PB6

// SPI definitions
#define PIN_SPI_SS              PA15
#define PIN_SPI_SS1             PA15
#define PIN_SPI_SS2             PA4
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PA5

// I2C definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    2

// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA3
#define PIN_SERIAL_TX           PA2

/* Extra HAL definitions */
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
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_USBVIRTUAL  SerialUSB
  #define SERIAL_PORT_HARDWARE    Serial2
#endif
