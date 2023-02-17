/*
 *******************************************************************************
 * Copyright (c) 2022, STMicroelectronics
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
// CN7 right Arduino Uno connector
#define PB7                     0  // USART_A_RX
#define PB6                     1  // USART_A_TX
#define PG14                    2
#define PE13                    3  // TIMER_A_PWM3
#define PE14                    4
#define PE11                    5  // TIMER_A_PWM2
#define PE9                     6  // TIMER_A_PWM1
#define PG12                    7
#define PF3                     PIN_A19
#define PD15                    9  // TIMER_B_PWM2
#define PD14                    10 // SPI_A_CS/ TIM_B_PWM3
#define PB5                     11 // SPI_A_MOSI/ PA7 if SB33 ON and SB35 OFF
#define PA6                     PIN_A20 // SPI_A_MISO
#define PA5                     PIN_A21 // SPI_A_SCK
#define PB9                     14 // I2C_A_SDA
#define PB8                     15 // I2C_A_SCL
// CN7 left
#define PC6                     16 // I2S_A_MCK
#define PB15                    17 // I2S_A_SD
#define PB13                    18 // I2S_A_CK / RMII TXD1 - JP6 ON (default)
#define PB12                    19 // I2S_A_WS
#define PA15                    20 // I2S_B_WS
#define PC7                     21 // I2S_B_MCK
// 22 is PB5                   (11)
#define PB3                     23 // I2S_B_CK/SPI_B_SCK - SWO
#define PA4                     PIN_A22 // SPI_B_NSS
#define PB4                     25 // SPI_B_MISO
#define PG6                     26 // QSPI_CS
#define PB2                     27 // QSPI_CLK
#define PD13                    28 // QSPI_BK1_IO3
#define PD12                    29 // QSPI_BK1_IO1
#define PD11                    30 // QSPI_BK1_IO0
#define PE2                     31 // SAI_A_MCLK/QSPI_BK1_IO2
#define PA0                     PIN_A23 // TIMER_C_PWM1
#define PB0                     PIN_A24 // TIMER_D_PWM1 - LD1 LED_GREEN
#define PE0                     34 // TIMER_B_ETR
// CN7 right
#define PB11                    35 // TIMER_C_PWM3
#define PB10                    36 // TIMER_C_PWM2
#define PE15                    37 // TIMER_A_BKIN1
#define PE6                     38
#define PE12                    39 // TIMER_A_PWM3N
#define PE10                    40 // TIMER_A_PWM2N
#define PE7                     41 // TIMER_A_ETR
#define PE8                     42 // TIMER_A_PWM1N
// CN8 right
#define PC8                     43 // SDMMC1_D0
#define PC9                     44 // SDMMC1_D1/I2S_A_CKIN
#define PC10                    45 // SDMMC1_D2
#define PC11                    46 // SDMMC1_D3
#define PC12                    47 // SDMMC1_CK
#define PD2                     48 // SDMMC1_CMD
#define PG2                     49
#define PG3                     50
#define PD7                     51 // USART_B_SCLK
#define PD6                     52 // USART_B_RX
#define PD5                     53 // USART_B_TX
#define PD4                     54 // USART_B_RTS
#define PD3                     55 // USART_B_CTS
// 56 is PE2                   (31)
#define PE4                     57 // SAI_A_FS
#define PE5                     58 // SAI_A_SCK
// 59 is PE6                   (38)
#define PE3                     60 // SAI_B_SD
#define PF8                     PIN_A25 // SAI_B_SCK
#define PF7                     PIN_A26 // SAI_B_MCLK
#define PF9                     PIN_A27 // SAI_B_FS
#define PG1                     64
// CN8 left
#define PG0                     65
#define PD1                     66 // CAN_TX
#define PD0                     67 // CAN_RX
#define PF0                     68 // I2C_B_SDA
#define PF1                     69 // I2C_B_SCL
#define PF2                     70 // I2C_B_SMBA
// 71 is PE9                   (6)
// 72 is PB2                   (27)
#define PA3                     PIN_A0
#define PC0                     PIN_A1
#define PC3_C                   PIN_A2
#define PB1                     PIN_A3
#define PC2_C                   PIN_A4
#define PF10                    PIN_A5
// CN7 left (analog part)
#define PF4                     PIN_A6
#define PF5                     PIN_A7
#define PF6                     PIN_A8
// ST morpho
#define PF11                    PIN_A9
#define PA1                     PIN_A10 // RMII Reference Clock - SB57 ON (default)
#define PA2                     PIN_A11 // RMII MDIO - SB72 ON (default)
#define PA7                     PIN_A12 // RMII RX Data Valid - SB31 ON (default)
#define PA8                     86
#define PA9                     87
#define PA10                    88
#define PA11                    89
#define PA12                    90
#define PA13                    91
#define PA14                    92
#define PB14                    93  // LD3 LED_RED
#define PC1                     PIN_A13
#define PC4                     PIN_A14 // RMII RXD0 - SB36 ON (default)
#define PC5                     PIN_A15 // RMII RXD1 - SB29 ON (default)
#define PC13                    97
#define PC14                    98
#define PC15                    99  // USER_BTN
#define PD8                     100
#define PD9                     101
#define PD10                    102 // Serial Tx
#define PE1                     103 // Serial Rx
#define PF12                    PIN_A16
#define PF13                    PIN_A17 // LD2 LED_BLUE
#define PF14                    PIN_A18
#define PF15                    107
#define PG4                     108
#define PG5                     109
#define PG7                     110
#define PG8                     111
#define PG9                     112
#define PG10                    113
#define PG11                    114 // RMII TX Enable - SB27 ON (default)
#define PG13                    115 // RXII TXD0 - SB30 ON (default)
#define PG15                    116
#define PH0                     117
#define PH1                     118

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
#define PA8_ALT1                (PA8  | ALT1)
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
#define PF0_ALT1                (PF0  | ALT1)
#define PF1_ALT1                (PF1  | ALT1)
#define PF6_ALT1                (PF6  | ALT1)
#define PF7_ALT1                (PF7  | ALT1)
#define PF8_ALT1                (PF8  | ALT1)
#define PF8_ALT2                (PF8  | ALT2)
#define PF9_ALT1                (PF9  | ALT1)
#define PF9_ALT2                (PF9  | ALT2)
#define PG13_ALT1               (PG13 | ALT1)

#define NUM_DIGITAL_PINS        119
#define NUM_DUALPAD_PINS        2
#define NUM_ANALOG_INPUTS       28

// On-board LED pin number
#define LED_GREEN               PB0  // LD1
#define LED_YELLOW              PE1  // LD2
#define LED_RED                 PB14 // LD3
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC13
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
  #define SERIAL_UART_INSTANCE  3 //Connected to ST-Link
#endif

// Serial pin used for console (ex: ST-Link)
// Required by Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PD9
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PD8
#endif

// HSE default value is 25MHz in HAL
// By default HSE_BYPASS is based on HSI/2 from STLink
#ifndef HSE_BYPASS_NOT_USED
  #define HSE_VALUE             8000000
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_ETH_MODULE_DISABLED)
  #define HAL_ETH_MODULE_ENABLED
#endif
#if !defined(HAL_OSPI_MODULE_DISABLED)
  #define HAL_OSPI_MODULE_ENABLED
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
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_HARDWARE    Serial
#endif
