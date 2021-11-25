/*
 *******************************************************************************
 * Copyright (c) 2020-2021, STMicroelectronics
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
/* P1 connector - Left side */
#define PE1                     0       // DVP D3
#define PE0                     1       // DVP D2
#define PB9                     2       // DVP I2C1 SDA
#define PB8                     3       // DVP I2C1 SCL
#define PB7                     4       // DVP VSYNC
#define PB6                     5       // QSPI NCS
#define PB5                     6
#define PB4                     7       // SPI1 Flash MISO
#define PB3                     8       // SPI1 Flash CLK
#define PD7                     9       // SPI1 Flash MOSI
#define PD6                     10      // SPI SW Flash CS if SB3
#define PD5                     11
#define PD4                     12      // µSD SW if SB2
#define PD3                     13      // DVP D5
#define PD2                     14      // µSD SDMMC1 CMD
#define PD1                     15
#define PD0                     16
#define PC12                    17      // µSD SDMMC1 CK
#define PC11                    18      // µSD SDMMC1 D3
#define PC10                    19      // µSD SDMMC1 D2
#define PA15                    20
#define PA12                    21      // USB DP
#define PA11                    22      // USB DM
#define PA10                    23
#define PA9                     24
#define PA8                     25      // DVP XCLK RCC_MCO_1
#define PC9                     26      // µSD SDMMC1 D1
#define PC8                     27      // µSD SDMMC1 D0
#define PC7                     28      // DVP D1
#define PC6                     29      // DVP D0
#define PD15                    30
#define PD14                    31
#define PD13                    32      // QSPI IO3
#define PD12                    33      // QSPI IO1
#define PD11                    34      // QSPI IO0
#define PD10                    35
#define PD9                     36
#define PD8                     37
#define PB15                    38      // SPI2 MOSI
#define PB14                    39      // SPI2 MISO
#define PB13                    40      // SPI2 CLM
#define PB12                    41      // SPI2 SSEL
/* P2 connector - Right side */
#define PE2                     42      // QSPI IO2
#define PE3                     43      // BLUE_LED
#define PE4                     44      // DVP D4
#define PE5                     45      // DVP D6
#define PE6                     46      // DVP D7
#define PC13                    47      // K1
#define PC0                     PIN_A0
#define PC1                     PIN_A1
#define PC2_C                   PIN_A2
#define PC3_C                   PIN_A3
#define PA0                     PIN_A4
#define PA1                     PIN_A5
#define PA2                     PIN_A6
#define PA3                     PIN_A7
#define PA4                     PIN_A8  // DVP HSYNC
#define PA5                     PIN_A9
#define PA6                     PIN_A10 // DVP PCLK
#define PA7                     PIN_A11 // DVP PWDN if SB1
#define PC4                     PIN_A12
#define PC5                     PIN_A13
#define PB0                     PIN_A14
#define PB1                     PIN_A15
#define PB2                     64      // QSPI CLK
#define PE7                     65
#define PE8                     66
#define PE9                     67
#define PE10                    68      // TFT-LCD
#define PE11                    69      // TFT-LCD
#define PE12                    70      // TFT-LCD
#define PE13                    71      // TFT-LCD
#define PE14                    72      // TFT-LCD
#define PE15                    73
#define PB10                    74
#define PB11                    75
// Other
#define PA13                    76      // SWDIO
#define PA14                    77      // SWCLK
#define PC14                    78      // OSC32_IN
#define PC15                    79      // OSC32_OUT
#define PH0                     80      // OSC_IN
#define PH1                     81      // OSC_OUT

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
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC0_ALT2                (PC0  | ALT2)
#define PC1_ALT1                (PC1  | ALT1)
#define PC1_ALT2                (PC1  | ALT2)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC6_ALT2                (PC6  | ALT2)
#define PC7_ALT1                (PC7  | ALT1)
#define PC7_ALT2                (PC7  | ALT2)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

#define NUM_DIGITAL_PINS        82
#define NUM_DUALPAD_PINS        2
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#define LED_BLUE                PE3
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_BLUE
#endif

// On-board user button
#define BTN_K1                  PC13
#ifndef USER_BTN
  #define USER_BTN              BTN_K1
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PB12
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
  #define PIN_SPI_MOSI          PB15
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB14
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB13
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB11
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB10
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
// #if !defined(HAL_ETH_MODULE_DISABLED)
//   #define HAL_ETH_MODULE_ENABLED
// #endif
#if !defined(HAL_QSPI_MODULE_DISABLED)
  #define HAL_QSPI_MODULE_ENABLED
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
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Power saving mode, mcu runs significantly cooler
 * Sysclock 240 Mhz, bus clocks 120 Mhz
 */
void SysClkHalfSpeed();

/*
 * Full speed - sysclk from PLL1 P - 480 Mhz
 * Sysclock 480 Mhz, bus clocks 240 Mhz
 */
void SysClkFullSpeed();

#ifdef __cplusplus
}
#endif
