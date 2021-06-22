/*
 *******************************************************************************
 * Copyright (c) 2019-2021, STMicroelectronics
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

#define PF6                     0  // D0
#define PF7                     1  // D1
#define PG13                    2  // D2
#define PF10                    3  // D3
#define PB6                     4  // D4
#define PE6                     5  // D5
#define PB0                     PIN_A8 // D6
#define PC13                    7  // D7
#define PA4                     PIN_A11// D8
#define PB8                     9  // D9
#define PA15                    10 // D10 - SPI_SSEL
#define PB5                     11 // D11 - SPI_MOSI, ISM43362_WIFI_MOSI
#define PB4                     12 // D12 - SPI_MISO, ISM43362_WIFI_MISO
#define PB12                    13 // D13 - SPI_SCK, LED_GREEN, ISM43362_WIFI_SCLK
#define PB11                    14 // D14 - I2C_SDA
#define PB10                    15 // D15 - I2C_SCL
#define PC0                     PIN_A0 // D16
#define PA1                     PIN_A1 // D17
#define PA2                     PIN_A2 // D18
#define PA5                     PIN_A3 // D19
#define PB1                     PIN_A4 // D20
#define PC4                     PIN_A5 // D21
#define PG14                    22 // D22 - STLink Tx
#define PG9                     23 // D23 - STLink Rx
// not on connector
#define PE3                     24  // D24 - LD4, LED1_RED
#define PC5                     PIN_A15 // D25 - LD3, LED2_GREEN
#define PA0                     PIN_A9  // D26 - User button
#define PG11                    27  // D27 - ISM43362_WIFI_NSS
#define PH1                     28  // D28 - ISM43362_WIFI_RESET
#define PG12                    29  // D29 - ISM43362_WIFI_DATAREADY
#define PB15                    30  // D30 - ISM43362_WIFI_WAKEUP
#define PE2                     31  // D31
#define PE4                     32  // D32
#define PE5                     33  // D33
#define PC14                    34  // D34
#define PC15                    35  // D35
#define PF0                     36  // D36
#define PF1                     37  // D37
#define PF2                     38  // D38
#define PF3                     39  // D39
#define PF4                     40  // D40
#define PF5                     41  // D41
#define PF8                     42  // D42
#define PF9                     43  // D43
#define PC1                     PIN_A12 // D44
#define PC2                     PIN_A13 // D45
#define PC3                     PIN_A14 // D46
#define PA3                     PIN_A10 // D47
#define PA6                     PIN_A6  // D48
#define PA7                     PIN_A7  // D49
#define PB2                     50  // D50
#define PF11                    51  // D51
#define PF12                    52  // D52
#define PF13                    53  // D53
#define PF14                    54  // D54
#define PF15                    55  // D55
#define PG0                     56  // D56
#define PG1                     57  // D57
#define PE7                     58  // D58
#define PE8                     59  // D59
#define PE9                     60  // D60
#define PE10                    61  // D61
#define PE11                    62  // D62
#define PE12                    63  // D63
#define PE13                    64  // D64
#define PE14                    65  // D65
#define PE15                    66  // D66
#define PB13                    67  // D67
#define PB14                    68  // D68
#define PD8                     69  // D69
#define PD9                     70  // D70
#define PD10                    71  // D71
#define PD11                    72  // D72
#define PD12                    73  // D73
#define PD13                    74  // D74
#define PD14                    75  // D75
#define PD15                    76  // D76
#define PG2                     77  // D77
#define PG3                     78  // D78
#define PG4                     79  // D79
#define PG5                     80  // D80
#define PG6                     81  // D81
#define PG7                     82  // D82
#define PG8                     83  // D83
#define PC6                     84  // D84
#define PC7                     85  // D85
#define PC8                     86  // D86
#define PC9                     87  // D87
#define PA8                     88  // D88
#define PA9                     89  // D89
#define PA10                    90  // D90
#define PA11                    91  // D91
#define PA12                    92  // D92
#define PA13                    93  // D93
#define PA14                    94  // D94
#define PC10                    95  // D95
#define PC11                    96  // D96
#define PC12                    97  // D97
#define PD0                     98  // D98
#define PD1                     99  // D99
#define PD2                     100 // D100
#define PD3                     101 // D101
#define PD4                     102 // D102
#define PD5                     103 // D103
#define PD6                     104 // D104
#define PD7                     105 // D105
#define PG10                    106 // D106
#define PG15                    107 // D107
#define PB3                     108 // D108
#define PB7                     109 // D109
#define PB9                     110 // D110
#define PE0                     111 // D111
#define PE1                     112 // D112
#define PH0                     113 // D113

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
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
#define PA10_ALT1               (PA10 | ALT1)
#define PA12_ALT1               (PA12 | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PB6_ALT1                (PB6  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)
#define PB12_ALT1               (PB12 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PE2_ALT1                (PE2  | ALT1)
#define PE4_ALT1                (PE4  | ALT1)
#define PE5_ALT1                (PE5  | ALT1)
#define PE6_ALT1                (PE6  | ALT1)
#define PE11_ALT1               (PE11 | ALT1)
#define PE12_ALT1               (PE12 | ALT1)
#define PE13_ALT1               (PE13 | ALT1)
#define PE14_ALT1               (PE14 | ALT1)

#define NUM_DIGITAL_PINS        114
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#define LED_GREEN               PB12
#define LED_GREEN2              PC5
#define LED_RED                 PE3
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PA0
#endif

// Timer Definitions (optional)
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  2 //ex: 2 for Serial2 (USART2)
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PG9
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PG14
#endif

// SD detect signal
#ifndef SD_DETECT_PIN
  #define SD_DETECT_PIN         PF11
#endif

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
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
