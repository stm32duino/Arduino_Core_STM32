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
// Arduino UNO V3
// CN9
#define PB7                     0
#define PB6                     1
#define PB12                    2
#define PB3                     PIN_A6
#define PB5                     4
#define PB8                     5
#define PB10                    6
#define PC1                     7
// CN5
#define PC2                     8
#define PA9                     9
#define PA4                     10
#define PA7                     11
#define PA6                     12
#define PA5                     13
#define PA11                    PIN_A7
#define PA12                    PIN_A8
// CN8
#define PB1                     PIN_A0
#define PB2                     PIN_A1
#define PA10                    PIN_A2
#define PB4                     PIN_A3
#define PB14                    PIN_A4
#define PB13                    PIN_A5
// ST Morpho
// CN10 Left Side
#define PA0                     22
// CN10 Right Side
#define PC3                     23      // FE_CTRL3
#define PA1                     24
#define PB11                    25
#define PB15                    26
#define PB9                     27
#define PB0                     28      // VDD_TCXO Supply voltage of TCXO
#define PA8                     29
#define PC0                     30
#define PC6                     31
#define PC5                     32      // FE_CTRL2
#define PC4                     33      // FE_CTRL1
// CN7 Left Side
#define PC15                    34      // OSC32_OUT - SB11 OFF not connected to ST Morpho
#define PC14                    35      // OSC32_IN - SB14 OFF not connected to ST Morpho
#define PC13                    36
#define PA15                    PIN_A9
#define PA14                    PIN_A10
#define PA13                    PIN_A11
// Not on connectors
#define PA2                     40     // Could be on D1. See Solder bridge configuration.
#define PA3                     41     // Could be on D0. See Solder bridge configuration.
#define PH3                     42     // BOOT0 - JP3 - GND

// Alternate pins number
#define PA1_ALT1                (PA1 | ALT1)
#define PA2_ALT1                (PA2 | ALT1)
#define PA3_ALT1                (PA3 | ALT1)
#define PA4_ALT1                (PA4 | ALT1)
#define PA5_ALT1                (PA5 | ALT1)
#define PA6_ALT1                (PA6 | ALT1)
#define PA7_ALT1                (PA7 | ALT1)
#define PB8_ALT1                (PB8 | ALT1)
#define PB9_ALT1                (PB9 | ALT1)

#define NUM_DIGITAL_PINS        43
#define NUM_ANALOG_INPUTS       12

// On-board LED pin number
#define LED1                    PB15
#define LED2                    PB9
#define LED3                    PB11
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED1
#endif
#define LED_BLUE                LED1
#define LED_GREEN               LED2
#define LED_RED                 LED3

// On-board user button
#define B1_BTN                  PA0 // PC13 (!SB16 SB15)
#define B2_BTN                  PA1
#define B3_BTN                  PC6
#ifndef USER_BTN
  #define USER_BTN              B1_BTN
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

#define LORAWAN_RFSWITCH_PINS           PC3,PC4,PC5
#define LORAWAN_RFSWITCH_PIN_COUNT      3
#define LORAWAN_RFSWITCH_OFF_VALUES     LOW,LOW,LOW
#define LORAWAN_RFSWITCH_RX_VALUES      HIGH,HIGH,LOW
#define LORAWAN_RFSWITCH_RFO_LP_VALUES  HIGH,HIGH,HIGH
#define LORAWAN_RFSWITCH_RFO_HP_VALUES  HIGH,LOW,HIGH

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
