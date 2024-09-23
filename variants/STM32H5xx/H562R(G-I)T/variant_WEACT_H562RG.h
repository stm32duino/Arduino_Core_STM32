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
/*
 Board orientation
P1                P2
..           OOO  ..
..                ..
..                ..
..                ..
..                ..
..                ..
..                ..
..                ..
..                ..
..  SWD    _____  ..
..  ||||  | USB | ..
..        |_____| ..
*/

// Connector P1
// Left side
#define PC14                    0       // OSC32_IN
#define PC0                     PIN_A0
#define PC2                     PIN_A1
#define PA0                     PIN_A2
#define PA2                     PIN_A3
#define PA4                     PIN_A4  // SPI CS
#define PA6                     PIN_A5  // SPI MISO
#define PC4                     PIN_A6
#define PB0                     PIN_A7
#define PB2                     9       // LED_BUILTIN
// PB11/VCAP
// Right side
#define PC13                    10      // USER_BTN
#define PC15                    11      // OSC32_OUT
#define PC1                     PIN_A8
#define PC3                     PIN_A9
#define PA1                     PIN_A10
#define PA3                     PIN_A11
#define PA5                     PIN_A12 // SPI SCK
#define PA7                     PIN_A13 // SPI MOSI
#define PC5                     PIN_A14
#define PB1                     PIN_A15
#define PB10                    20
// Connector P2
// Left side
// PB9/VCAP
#define PB7                     21      // I2C SDA
#define PB5                     22
#define PB3                     23
#define PC12                    24      // SDX_CLK
#define PC10                    25      // SDX_D2
#define PA12                    26      // USB DP
#define PA10                    27      // Rx
#define PA8                     28      // SD_DETECT
#define PC8                     29      // SDX_D0
#define PC6                     30
#define PB14                    31
#define PB12                    32
// Right side
#define PB8                     33
#define PB6                     34      // I2C SCL
#define PB4                     35
#define PD2                     36      // SDX_CMD
#define PC11                    37      // SDX_D3
#define PA15                    38
#define PA11                    39      // USB DM
#define PA9                     40      // Tx
#define PC9                     41      // SDX_D1
#define PC7                     42
#define PB15                    43
#define PB13                    44
// Other pins
#define PA13                    45      // SWDIO
#define PA14                    46      // SWCLK
#define PH0                     47      // OSC_IN
#define PH1                     48      // OSC_OUT

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA1_ALT2                (PA1  | ALT2)
#define PA2_ALT1                (PA2  | ALT1)
#define PA2_ALT2                (PA2  | ALT2)
#define PA3_ALT1                (PA3  | ALT1)
#define PA3_ALT2                (PA3  | ALT2)
#define PA4_ALT1                (PA4  | ALT1)
#define PA4_ALT2                (PA4  | ALT2)
#define PA5_ALT1                (PA5  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA9_ALT1                (PA9  | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PA11_ALT1               (PA11 | ALT1)
#define PA12_ALT1               (PA12 | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PA15_ALT2               (PA15 | ALT2)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB3_ALT2                (PB3  | ALT2)
#define PB4_ALT1                (PB4  | ALT1)
#define PB4_ALT2                (PB4  | ALT2)
#define PB5_ALT1                (PB5  | ALT1)
#define PB5_ALT2                (PB5  | ALT2)
#define PB6_ALT1                (PB6  | ALT1)
#define PB6_ALT2                (PB6  | ALT2)
#define PB7_ALT1                (PB7  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC1_ALT1                (PC1  | ALT1)
#define PC2_ALT1                (PC2  | ALT1)
#define PC3_ALT1                (PC3  | ALT1)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

#define NUM_DIGITAL_PINS        49
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PB2
#endif
#define LED_BLUE                LED_BUILTIN

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC13
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PA15
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

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  101
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_OSPI_MODULE_DISABLED)
  #define HAL_OSPI_MODULE_ENABLED
#endif
#if !defined(HAL_SD_MODULE_DISABLED)
  #define HAL_SD_MODULE_ENABLED
#endif

#define HSE_VALUE               8000000UL

// SD card slot Definitions
// SDMMC signals not available
#define SDMMC_CDIR_NA
#define SDMMC_CKIN_NA
#define SDMMC_D0DIR_NA

// SD detect signal can be defined if required
#ifndef SD_DETECT_PIN
  #define SD_DETECT_PIN         PA8
#endif
#ifndef SD_DETECT_LEVEL
  #define SD_DETECT_LEVEL       HIGH
#endif

#ifndef SDX_D0
  #define SDX_D0                PC8
#endif
#ifndef SDX_D1
  #define SDX_D1                PC9
#endif
#ifndef SDX_D2
  #define SDX_D2                PC10
#endif
#ifndef SDX_D3
  #define SDX_D3                PC11
#endif
#ifndef SDX_CMD
  #define SDX_CMD               PD2
#endif
#ifndef SDX_CK
  #define SDX_CK                PC12
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
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
#endif
