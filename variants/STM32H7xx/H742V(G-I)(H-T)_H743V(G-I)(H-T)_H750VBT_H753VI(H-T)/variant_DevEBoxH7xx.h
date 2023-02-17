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
/* J2 connector - Left side */
#define PD9                     0
#define PD8                     1
#define PD11                    2       // FLASH QSPI BK1 IO0
#define PD10                    3
#define PD13                    4       // FLASH QSPI BK1 IO3
#define PD12                    5       // FLASH QSPI BK1 IO1
#define PD15                    6
#define PD14                    7
#define PC7                     8       // DCMI D1
#define PC6                     9       // DCMI D0
#define PC9                     10      // µSD SDMMC1 D1
#define PC8                     11      // µSD SDMMC1 D0
#define PA9                     12
#define PA8                     13      // DCMI XCLK
#define PA11                    14      // USB DM
#define PA10                    15
#define PA15                    16
#define PA12                    17      // USB DP
#define PC11                    18      // µSD SDMMC1 D3
#define PC10                    19      // µSD SDMMC1 D2
#define PD0                     20
#define PC12                    21      // µSD SDMMC1 CK
#define PD2                     22      // µSD SDMMC1 CMD
#define PD1                     23
#define PD4                     24
#define PD3                     25      // DCMI D5
#define PD6                     26
#define PD5                     27
#define PB3                     28
#define PD7                     29
#define PB5                     30
#define PB4                     31
#define PB7                     32      // DCMI VSYNC
#define PB6                     33      // FLASH QSPI BK1 NCS
#define PB9                     34
#define PB8                     35
#define PE1                     36      // DCMI D3
#define PE0                     37      // DCMI D2
/* J3 connector - Right side */
#define PB15                    38      // TFT SDI / MOSI
#define PB14                    39      // TFT SDO / MISO
#define PB13                    40      // TFT SCL / SCK
#define PB12                    41      // TFT CS
#define PB11                    42      // DCMI SDA
#define PB10                    43      // DCMI SCL
#define PE15                    44
#define PE14                    45
#define PE13                    46
#define PE12                    47
#define PE11                    48
#define PE10                    49
#define PE9                     50
#define PE8                     51
#define PE7                     52
#define PB2                     53      // FLASH QSPI CLK
#define PB1                     PIN_A0  // TFT D/C / RS
#define PB0                     PIN_A1  // TFT BLK
#define PC5                     PIN_A2
#define PC4                     PIN_A3  // DCMI RESET
#define PA7                     PIN_A4  // DCMI PWDN
#define PA6                     PIN_A5  // DCMI PCLK
#define PA5                     PIN_A6  // DCMI CH1
#define PA4                     PIN_A7  // DCMI HREF
#define PA3                     PIN_A8
#define PA2                     PIN_A9
#define PA1                     PIN_A10
#define PA0                     PIN_A11
#define PC3_C                   PIN_A12
#define PC2_C                   PIN_A13
#define PC1                     PIN_A14
#define PC0                     PIN_A15
#define PC13                    70
#define PE6                     71      // DCMI D7
#define PE5                     72      // DCMI D6
#define PE4                     73      // DCMI D4
#define PE3                     74
#define PE2                     75      // FLASH QSPI BK1 IO2
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
#define LED_D2                  PA1
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_D2
#endif

// On-board user button
#define BTN_K1                  PE3
#define BTN_K2                  PC5
#ifndef USER_BTN
  #define USER_BTN              BTN_K1
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PD7
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
  #define PIN_SPI_MOSI          PB5
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB4
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB3
#endif

// I2C definitions
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
