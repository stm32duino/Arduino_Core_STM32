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

// USB USER CN2
// By default, SB20,23 (USB-USER) are OFF.
// So PA11,12 are not available.
// If ON and R12,13 removed,
// #define USB_REMOVED
// to get PA11,12 available.

// Linear touch sensor
// By default, SB27,28,29,30,31,32 (touch sensor) are OFF.
// So PA2,3,6,7 and PB0,1 are not available.
// If ON and R38,39,40 and C26,27,28 are removed,
// #define TSC_REMOVED
// to get PA2,3,6,7 and PB0,1 available.

// P2 connector Right side (top view)
#define PB9                     0
#define PB8                     1
#define PB7                     2
#define PB6                     3
#define PB5                     4
#define PB4                     5
#define PB3                     6
#define PD2                     7
#define PC12                    8
#define PC11                    9
#define PC10                    10
#define PA15                    11
#define PA14                    12
#define PA13                    13
#define PA12                    14     // SB20 (default OFF): USB_DP
#define PA11                    15     // SB23 (default OFF): USB_DM
#define PA10                    16
#define PA9                     17
#define PA8                     18
#define PC9                     19     // LED_GREEN (LD4)
#define PC8                     20     // LED_ORANGE (LD3)
#define PC7                     21     // LED_BLUE (LD6)
#define PC6                     22     // LED_RED (LD5)
#define PB15                    23     // SPI2_MOSI (L3GD20)
#define PB14                    24     // SPI2_MISO (L3GD20)
#define PB13                    25     // SPI2_SCK (L3GD20)
// P1 connector Left side (top view)
#define PC13                    26
#define PC14                    27
#define PC15                    28
#define PF0                     29
#define PF1                     30
#define PC0                     PIN_A0 // NCS_MEMS_SPI (L3GD20)
#define PC1                     PIN_A1 // MEMS INT1 (L3GD20)
#define PC2                     PIN_A2 // MEMS INT2 (L3GD20)
#define PC3                     PIN_A3
#define PA0                     PIN_A4 // USER_BTN
#define PA1                     PIN_A5
#define PA2                     PIN_A6 // SB27 (default OFF): TS_G1_IO3
#define PA3                     PIN_A7 // SB28 (default OFF): TS_G1_IO4
#define PA4                     PIN_A8
#define PA5                     PIN_A9
#define PA6                     PIN_A10 // SB29 (default OFF): TS_G2_IO3
#define PA7                     PIN_A11 // SB30 (default OFF): TS_G2_IO4
#define PC4                     PIN_A12
#define PC5                     PIN_A13 // Ext Reset
#define PB0                     PIN_A14 // SB31 (default OFF): TS_G3_IO2
#define PB1                     PIN_A15 // SB32 (default OFF): TS_G3_IO3
#define PB2                     47
#define PB10                    48      // I2C2 SCL: Extension / RF EEprom Connector
#define PB11                    49      // I2C2 SDA: Extension / RF EEprom Connector
#define PB12                    50

// Alternate pins number
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
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
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

#define NUM_DIGITAL_PINS        51
#define NUM_ANALOG_INPUTS       16

//On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PC9
#endif
#define LED_GREEN               LED_BUILTIN
#define LED_ORANGE              PC8
#define LED_BLUE                PC7
#define LED_RED                 PC6

//On-board user button
#ifndef USER_BTN
  #define USER_BTN              PA0
#endif

// SPI definitions
// SPI1 is used
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PC4
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PB12
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3           PB6
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PB5
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB4
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB3
#endif

// I2C Definitions
// I2C1 is used
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB9
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB8
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
  #define SERIAL_UART_INSTANCE  1 // USART 1
#endif

// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
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
  #define SERIAL_PORT_HARDWARE    Serial
#endif
