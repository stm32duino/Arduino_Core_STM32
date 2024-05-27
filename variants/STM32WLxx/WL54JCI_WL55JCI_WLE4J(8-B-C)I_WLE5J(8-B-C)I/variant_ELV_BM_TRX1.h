/*
 *******************************************************************************
 * Copyright (c) 2024, STMicroelectronics
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

// J2
#define PB12                    1
#define PA0                     2
#define PB14                    PIN_A0
#define PC13                    4
#define PA9                     5
#define PA10                    6
#define PA11                    7
#define PA12                    8
// J1
#define PA14                    PIN_A1
#define PA13                    PIN_A2
#define PA2                     19
#define PA3                     20
#define PA4                     21
#define PA5                     22
#define PA6                     23
#define PA7                     24
// Not on connectors
#define PA15                    25
#define PB3                     26
#define PC4                     27
#define PC5                     28

// Not connected
// PA1
// PA8
// PB0
// PB1
// PB2
// PB4
// PB5
// PB6
// PB7
// PB8
// PB9
// PB10
// PB11
// PB13
// PB15
// PC0
// PC1
// PC2
// PC3
// PC6
// PC14
// PC15
// PH3

// Alternate pins number
#define PA2_ALT1                (PA2 | ALT1)
#define PA3_ALT1                (PA3 | ALT1)
#define PA4_ALT1                (PA4 | ALT1)
#define PA5_ALT1                (PA5 | ALT1)
#define PA6_ALT1                (PA6 | ALT1)
#define PA7_ALT1                (PA7 | ALT1)

#define NUM_DIGITAL_PINS        29
#define NUM_ANALOG_INPUTS       3

// On-board LED pin number
#define LED1                    PB3
#define LED2                    PA15
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED1
#endif
#define LED_GREEN               LED1
#define LED_RED                 LED2

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PA0
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PNUM_NOT_DEFINED
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
  #define PIN_WIRE_SDA          PA11
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PA12
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

// LORAWAN settings
#define LORAWAN_RFSWITCH_PINS           PC4,PC5
#define LORAWAN_RFSWITCH_PIN_COUNT      2
#define LORAWAN_RFSWITCH_OFF_VALUES     LOW,LOW
#define LORAWAN_RFSWITCH_RX_VALUES      HIGH,LOW
#define LORAWAN_RFSWITCH_RFO_LP_VALUES  HIGH,HIGH
#define LORAWAN_RFSWITCH_RFO_HP_VALUES  LOW,HIGH
#define XTAL_DEFAULT_CAP_VALUE          ( 0x14UL )
#define LORAWAN_BOARD_HAS_TCXO          0
#define LORAWAN_BOARD_HAS_DCDC          1
#define LORAWAN_TX_CONFIG               RBI_CONF_RFO_LP
#define EU868_TX_MAX_DATARATE           DR_5
#define EU868_RX_MAX_DATARATE           DR_5
#define EU868_DEFAULT_ANTENNA_GAIN      2.0f
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
