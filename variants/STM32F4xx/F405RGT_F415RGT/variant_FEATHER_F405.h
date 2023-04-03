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
// External (left to right)
// GND
// VBAT
// 5V
#define PB11                    0
#define PB10                    1
#define PB3                     2  // FLASH SCK
#define PB4                     3  // FLASH MISO
#define PB5                     4  // FLASH MOSI
#define PC7                     5
#define PC6                     6
#define PA15                    7  // FLASH CS

#define PC0                     8  // NeoPixel
#define PB8                     9
#define PB9                     10
#define PC3                     11
#define PC2                     12
#define PC1                     13

#define PB7                     14  // SDA
#define PB6                     15  // SCL

#define PA4                     PIN_A0
#define PA5                     PIN_A1
#define PA6                     PIN_A2
#define PA7                     PIN_A3
#define PC4                     PIN_A4
#define PC5                     PIN_A5
#define PA3                     PIN_A6  // VDIV

#define PB13                    23  // SCK
#define PB14                    24  // MISO
#define PB15                    25  // MOSI

#define PC8                     26  // SDIO D0
#define PC9                     27  // SDIO D1
#define PC10                    28  // SDIO D2
#define PC11                    29  // SDIO D3
#define PC12                    30  // SDIO CLK
#define PD2                     31  // SDIO CMD
#define PB12                    32  // SD Detect

#define PC14                    33  // OSC32_IN
#define PC15                    34  // OSC32_OUT

#define PA11                    35  // USB_DM
#define PA12                    36  // USB_DP

#define PA13                    37  // SWDIO
#define PA14                    38  // SWCLK

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA0_ALT2                (PA0  | ALT2)
#define PA1_ALT1                (PA1  | ALT1)
#define PA1_ALT2                (PA1  | ALT2)
#define PA2_ALT1                (PA2  | ALT1)
#define PA2_ALT2                (PA2  | ALT2)
#define PA3_ALT1                (PA3  | ALT1)
#define PA3_ALT2                (PA3  | ALT2)
#define PA4_ALT1                (PA4  | ALT1)
#define PA5_ALT1                (PA5  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC0_ALT2                (PC0  | ALT2)
#define PC1_ALT1                (PC1  | ALT1)
#define PC1_ALT2                (PC1  | ALT2)
#define PC2_ALT1                (PC2  | ALT1)
#define PC2_ALT2                (PC2  | ALT2)
#define PC3_ALT1                (PC3  | ALT1)
#define PC3_ALT2                (PC3  | ALT2)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

// This must be a literal
#define NUM_DIGITAL_PINS        39
// This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       7

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PC1
#endif

#define SD_DETECT_PIN           PB12

// No user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA15
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PB15
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB14
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB13
#endif

// SPI FLASH
#define PIN_SPI3_MOSI           PB5
#define PIN_SPI3_MISO           PB4
#define PIN_SPI3_SCK            PB3
#define PIN_SPI3_SS             PA15

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  3
#endif

// Default pin used for 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PB11
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PB10
#endif

/* HAL configuration */
#define HSE_VALUE               12000000U

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
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
    #define SERIAL_PORT_HARDWARE  Serial3
  #endif
#endif
