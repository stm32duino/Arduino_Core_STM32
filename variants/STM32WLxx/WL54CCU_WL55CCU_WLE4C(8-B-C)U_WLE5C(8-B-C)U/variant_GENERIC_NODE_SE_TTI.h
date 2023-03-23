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
#define PB3                     0
#define PA15                    1
#define PA2                     2
#define PA3                     3
#define PA11                    PIN_A1
#define PA12                    PIN_A2
#define PA13                    PIN_A3
#define PA14                    PIN_A4
#define PA0                     8
#define PA1                     9
#define PA4                     10
#define PA5                     11
#define PA6                     12
#define PA7                     13
#define PA8                     14
#define PA9                     15
#define PA10                    16
#define PB0                     17
#define PB2                     PIN_A0
#define PB4                     19
#define PB5                     20
#define PB6                     21
#define PB7                     22
#define PB8                     23
#define PB12                    24
#define PC13                    25
#define PH3                     26
#define PC14                    27     // OSC32-IN
#define PC15                    28     // OSC32-OUT

// Alternate pins number
#define PA1_ALT1                (PA1 | ALT1)
#define PA2_ALT1                (PA2 | ALT1)
#define PA3_ALT1                (PA3 | ALT1)
#define PA4_ALT1                (PA4 | ALT1)
#define PA5_ALT1                (PA5 | ALT1)
#define PA6_ALT1                (PA6 | ALT1)
#define PA7_ALT1                (PA7 | ALT1)
#define PB8_ALT1                (PB8 | ALT1)

#define NUM_DIGITAL_PINS        29
#define NUM_ANALOG_INPUTS       5

// On-board LED pin number
#define LED_RED                 PB5
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_RED
#endif
#define LED_GREEN               PB6
#define LED_BLUE                PB7


// On-board user button
#define B1_BTN                  PB3
#ifndef USER_BTN
  #define USER_BTN              B1_BTN
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PA15
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PB2
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
  #define PIN_WIRE_SDA          PA10
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PA9
#endif

// Timer Definitions
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

// Alias
#ifndef DEBUG_SUBGHZSPI_MOSI
  #define DEBUG_SUBGHZSPI_MOSI  PA7_ALT1
#endif
#ifndef DEBUG_SUBGHZSPI_MISO
  #define DEBUG_SUBGHZSPI_MISO  PA6_ALT1
#endif
#ifndef DEBUG_SUBGHZSPI_SCLK
  #define DEBUG_SUBGHZSPI_SCLK  PA5_ALT1
#endif
#ifndef DEBUG_SUBGHZSPI_SS
  #define DEBUG_SUBGHZSPI_SS    PA4_ALT1
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif

// LoRaWAN definitions
#define LORAWAN_BOARD_HAS_TCXO          1U

// FE_CTRL1 PA0
// FE_CTRL2 PA1
// FE_CTRL3 PB8
#define LORAWAN_RFSWITCH_PINS           PA0,PA1,PB8
#define LORAWAN_RFSWITCH_PIN_COUNT      3
#define LORAWAN_RFSWITCH_OFF_VALUES     LOW,LOW,LOW
#define LORAWAN_RFSWITCH_RX_VALUES      HIGH,LOW,HIGH
#define LORAWAN_RFSWITCH_RFO_LP_VALUES  HIGH,HIGH,HIGH
#define LORAWAN_RFSWITCH_RFO_HP_VALUES  LOW,HIGH,HIGH

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
