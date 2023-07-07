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
#define PC11                    0
#define PC10                    1
#define PB14                    2
#define PD12                    3
#define PD13                    4
#define PD14                    5
#define PD15                    6
#define PC6                     7
#define PC7                     8
#define PC8                     9
#define PC9                     10
#define PA8                     11
#define PA9                     12
#define PA15                    13
#define PD5                     14
#define PD6                     15
#define PB10                    16
#define PB11                    17
#define PE8                     18
#define PE7                     19
#define PF15                    20
#define PF14                    21
#define PG6                     22
#define PG7                     23
#define PG4                     24
#define PG5                     25
#define PG2                     26
#define PG3                     27
#define PE11                    28
#define PE15                    29
#define PE9                     30
#define PE10                    31
#define PG0                     32
#define PG1                     33
#define PF13                    34
#define PF12                    35
#define PF11                    36
#define PG9                     37
#define PG10                    38
#define PG11                    39
#define PG12                    40
#define PG13                    41
#define PG14                    42
#define PF10                    43
#define PF4                     PIN_A14   // A14
#define PF3                     PIN_A15   // A15
#define PC14                    46
#define PC15                    47
#define PC13                    48
#define PE6                     49
#define PE5                     50
#define PE4                     51
#define PE3                     52
#define PE2                     53
#define PC0                     PIN_A0    // A0
#define PC1                     PIN_A1    // A1
#define PC2                     PIN_A2    // A2
#define PC3                     PIN_A3    // A3
#define PA0                     PIN_A4    // A4
#define PA1                     PIN_A5    // A5
#define PA2                     PIN_A6    // A6
#define PA3                     PIN_A7    // A7
#define PA6                     PIN_A8    // A8
#define PA7                     PIN_A9    // A9
#define PC4                     PIN_A10   // A10
#define PC5                     PIN_A11   // A11
#define PA5                     PIN_A12   // DAC0 / A12
#define PA4                     PIN_A13   // DAC1 / A13
#define PD0                     68        // CANRX
#define PD1                     69        // CANTX
#define PB3                     70        // LED_1 / LED_BUILTIN
#define PB8                     71        // SCL1
#define PB9                     72        // SDA1
#define PE12                    73        // MOSI
#define PE13                    74        // MISO
#define PE14                    75        // SCK
#define PG15                    76        // LED_2
#define PA11                    77        // USB DM
#define PA12                    78        // USB DP
#define PF0                     79        // ECAT_SYNC0
#define PF1                     80        // ECAT_SYNC1
#define PF2                     81        // ECAT_IRQ
#define PF5                     82        // ECAT_RST
#define PF6                     83        // ECAT_D3
#define PF7                     84        // ECAT_D2
#define PF8                     85        // ECAT_D0
#define PF9                     86        // ECAT_D1
#define PB2                     87        // ECAT_SCK
#define PB4                     88        // ECAT_LED_RUN
#define PB5                     89        // ECAT_LED_ERR
#define PB6                     90        // ECAT_CS


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
#define PB3_ALT1                (PB3  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
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

#define NUM_DIGITAL_PINS        91
#define NUM_ANALOG_INPUTS       16

#define CANRX                   PD0
#define CANTX                   PD1

// EtherCAT controller pins (not broken out)
#define ECAT_SYNC0              PF0
#define ECAT_SYNC1              PF1
#define ECAT_IRQ                PF2
#define ECAT_RST                PF5
#define ECAT_D3                 PF6
#define ECAT_D2                 PF7
#define ECAT_D0                 PF8
#define ECAT_D1                 PF9
#define ECAT_SCK                PB2
#define ECAT_LED_RUN            PB4
#define ECAT_LED_ERR            PB5
#define ECAT_CS                 PB6

// Serial pins
#define TX0                     PC10          // UART4
#define RX0                     PC11          // UART4
#define TX0_ALT                 PC10_ALT1     // USART3
#define RX0_ALT                 PC11_ALT1     // USART3

#define TX1                     PE8           // UART7
#define RX1                     PE7           // UART7

#define TX2                     PB10          // USART3
#define RX2                     PB11          // USART3

#define TX3                     PD5           // USART2
#define RX3                     PD6           // USART2

// I2C pins
#define SDA0                    PF15          // I2C4
#define SCL0                    PF14          // I2C4

#define SDA1                    PB9
#define SCL1                    PB8

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PB3
#endif
#define LED_1                   LED_BUILTIN
#define LED_2                   PG15

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PE11
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
  #define PIN_SPI_MOSI          PE14
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PE13
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PE12
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          SDA0
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          SCL0
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
  #define SERIAL_UART_INSTANCE  4
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PC11
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PC10
#endif

// Value of the External oscillator in Hz
#define HSE_VALUE               8000000U

// SDMMC signals not available
#define SDMMC_CKIN_NA
#define SDMMC_CDIR_NA
#define SDMMC_D0DIR_NA
#define SDMMC_D123DIR_NA

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
// ETH is not used -> external controller
// is interfaced using QSPI
// #if !defined(HAL_ETH_MODULE_DISABLED)
//   #define HAL_ETH_MODULE_ENABLED
// #endif
#if !defined(HAL_QSPI_MODULE_DISABLED)
  #define HAL_QSPI_MODULE_ENABLED
#endif
// Some pins are not available
// #if !defined(HAL_SD_MODULE_DISABLED)
//   #define HAL_SD_MODULE_ENABLED
// #endif

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
