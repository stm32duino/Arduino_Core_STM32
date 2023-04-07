/*
 *******************************************************************************
 * Copyright (c) 2023, STMicroelectronics
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
#define PA0                     0       // D0
#define PA2                     1       // TX2
#define PA3                     2       // RX2
#define PC1                     3       // TX1
#define PC0                     4       // RX1
#define PB6                     5       // TX
#define PB7                     6       // RX
#define PA15                    PIN_A0  // SDA
#define PB15                    8       // SCL
#define PA9                     9       // D9
#define PB10                    10      // D10
#define PB13                    PIN_A1  // SCK/BOOT
#define PB9                     12      // NSS
#define PB14                    PIN_A2  // MISO
#define PA10                    PIN_A5  // MOSI
#define PA14                    PIN_A6  // SWDCLK
#define PA13                    PIN_A7  // SWDIO
#define PB3                     PIN_A3  // A3
#define PB4                     PIN_A4  // A4
// Dedicated pins
#define PB5                     19      // LED RED
#define PA4                     20      // RF_CTRL1
#define PA5                     21      // RF_CTRL2
#define PB0                     22      // VDD_TCXO Supply voltage of TCXO
#define PC15                    23      // OSC32_OUT
#define PC14                    24      // OSC32_IN
#define PA7                     25      // SUBGHZSPI
#define PA6                     26      // SUBGHZSPI

// Not connected
// #define PA1
// #define PA8
// #define PA11
// #define PA12
// #define PB1
// #define PB2
// #define PB8
// #define PB11
// #define PB12
// #define PC2
// #define PC3
// #define PC4
// #define PC5
// #define PC6
// #define PC13
// #define PH3

// Alternate pins number
// #define PA1_ALT1                (PA1 | ALT1)
#define PA2_ALT1                (PA2 | ALT1)
#define PA3_ALT1                (PA3 | ALT1)
// #define PA4_ALT1                (PA4 | ALT1)
// #define PA5_ALT1                (PA5 | ALT1)
// #define PA6_ALT1                (PA6 | ALT1)
// #define PA7_ALT1                (PA7 | ALT1)
// #define PB8_ALT1                (PB8 | ALT1)
#define PB9_ALT1                (PB9 | ALT1)

#define NUM_DIGITAL_PINS        27
#define NUM_ANALOG_INPUTS       8

// On-board LED pin number
#define LED_RED                 PB5
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_RED
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PB13
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PB9
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
  #define PIN_SPI_MOSI          PA10
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB14
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB13
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PA15
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB15
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
  #define PIN_SERIAL_RX         PB7
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PB6
#endif

// Alias
#ifndef DEBUG_SUBGHZSPI_MOSI
  #define DEBUG_SUBGHZSPI_MOSI  PA7
#endif
#ifndef DEBUG_SUBGHZSPI_MISO
  #define DEBUG_SUBGHZSPI_MISO  PA6
#endif
#ifndef DEBUG_SUBGHZSPI_SCLK
  #define DEBUG_SUBGHZSPI_SCLK  PA5
#endif
#ifndef DEBUG_SUBGHZSPI_SS
  #define DEBUG_SUBGHZSPI_SS    PA4
#endif

#ifndef UART_WAKEUP_EXTI_LINE
  // For LPUART1
  #define UART_WAKEUP_EXTI_LINE LL_EXTI_LINE_28
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif

// LoRaWAN definitions
#define LORAWAN_BOARD_HAS_TCXO          1U
#define LORAWAN_BOARD_HAS_DCDC          1U
#define LORAWAN_TX_CONFIG               RBI_CONF_RFO_HP

#define LORAWAN_RFSWITCH_PINS           PA4,PA5
#define LORAWAN_RFSWITCH_PIN_COUNT      2
#define LORAWAN_RFSWITCH_OFF_VALUES     LOW,LOW
#define LORAWAN_RFSWITCH_RX_VALUES      HIGH,LOW
#define LORAWAN_RFSWITCH_RFO_LP_VALUES  HIGH,HIGH
#define LORAWAN_RFSWITCH_RFO_HP_VALUES  LOW,HIGH

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
