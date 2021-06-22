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
 * Pin                  M200     M300
 * X_MIN_PIN            PB4      -
 * X_MAX_PIN            -        PC13
 * Y_MIN_PIN            PA15     -
 * Y_MAX_PIN            -        PC14
 * Z_MAX_PIN            -        PC15
 * Z_MIN_PIN            PB5      PB7
 * X_STEP_PIN           PB14     PB14
 * X_DIR_PIN            PB15     PB13
 * X_ENABLE_PIN         PA8      PB10
 * Y_STEP_PIN           PB12     PB12
 * Y_DIR_PIN            PB13     PB11
 * Y_ENABLE_PIN         PA8      PB10
 * Z_STEP_PIN           PB10     PB2
 * Z_DIR_PIN            PB2      PB1
 * Z_ENABLE_PIN         PA8      PB10
 * E0_STEP_PIN          PB0      PA7
 * E0_DIR_PIN           PC13     PA6
 * E0_ENABLE_PIN        PB1      PB0
 * HEATER_0_PIN         PB6      PA1
 * HEATER_BED_PIN       PB7      PA5
 * TEMP_0_PIN           PA0      PA0
 * TEMP_BED_PIN         PA1      PA4
 * FAN1_PIN             PB8      PA8
 * FAN2_PIN             PB3      -
 *
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
#define PA12                    8  // USB DP
#define PA11                    9  // USB DM
#define PA10                    10
#define PA9                     11
#define PA8                     12
#define PB15                    13
#define PB14                    14
#define PB13                    15
#define PB12                    16
// Right side
#define PC13                    17
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
#define PB2                     32 // BOOT1
#define PA13                    33 // SWDI0
#define PA14                    34 // SWCLK
#define PF0                     35
#define PF1                     36

// Alternate pins number
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)

#define NUM_DIGITAL_PINS        37
#define NUM_ANALOG_INPUTS       10

// On-board LED pin number
#ifdef ARDUINO_MALYANM200_F070CB
  #define LED_GREEN             PC13
#else // MALYANM300_F070CB
  #define LED_RED               PB15
  #define LED_GREEN             PB8
  #define LED_BLUE              PB9
#endif
#define LED_BUILTIN             LED_GREEN

// SPI Definitions
#ifdef ARDUINO_MALYANM200_F070CB
  #define PIN_SPI_SS            PA4
  #define PIN_SPI_MOSI          PA7
  #define PIN_SPI_MISO          PA6
  #define PIN_SPI_SCK           PA5
#else // MALYANM300_F070CB
  #define PIN_SPI_SS            PB6
  #define PIN_SPI_MOSI          PB5
  #define PIN_SPI_MISO          PB4
  #define PIN_SPI_SCK           PB3
#endif

// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    1
// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9

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
  #define SERIAL_PORT_HARDWARE    Serial1
#endif
