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
#define PC7                     0
#define PC6                     1
#define PG6                     2
#define PB4                     3
#define PG7                     4
#define PI0                     5
#define PH6                     6
#define PI3                     7
#define PI2                     8
#define PA15                    9
#define PA8                     10
#define PB15                    11
#define PB14                    12
#define PI1                     13
#define PB9                     14
#define PB8                     15
#define PA0                     PIN_A0
#define PF10                    PIN_A1
#define PF9                     PIN_A2
#define PF8                     PIN_A3
#define PF7                     PIN_A4
#define PF6                     PIN_A5
#define PI11                    22 // User btn
#define PB7                     23 // ST-Link Rx
#define PA9                     24 // ST-Link Tx
#define PC13                    25 // SD detect
#define PA1                     26
#define PA2                     27
#define PA3                     28
#define PA4                     29
#define PA5                     30
#define PA6                     31
#define PA7                     32
#define PA10                    33
#define PA11                    34
#define PA12                    35
#define PA13                    36
#define PA14                    37
#define PB0                     38
#define PB1                     39
#define PB2                     40
#define PB3                     41
#define PB5                     42
#define PB6                     43
#define PB10                    44
#define PB11                    45
#define PB12                    46
#define PB13                    47
#define PC0                     48
#define PC1                     49
#define PC2                     50
#define PC3                     51
#define PC4                     52
#define PC5                     53
#define PC8                     54
#define PC9                     55
#define PC10                    56
#define PC11                    57
#define PC12                    58
#define PC14                    59
#define PC15                    60
#define PD0                     61
#define PD1                     62
#define PD2                     63
#define PD3                     64
#define PD4                     65
#define PD5                     66
#define PD6                     67
#define PD7                     68
#define PD8                     69
#define PD9                     70
#define PD10                    71
#define PD11                    72
#define PD12                    73
#define PD13                    74
#define PD14                    75
#define PD15                    76
#define PE0                     77
#define PE1                     78
#define PE2                     79
#define PE3                     80
#define PE4                     81
#define PE5                     82
#define PE6                     83
#define PE7                     84
#define PE8                     85
#define PE9                     86
#define PE10                    87
#define PE11                    88
#define PE12                    89
#define PE13                    90
#define PE14                    91
#define PE15                    92
#define PF0                     93
#define PF1                     94
#define PF2                     95
#define PF3                     96
#define PF4                     97
#define PF5                     98
#define PF11                    99
#define PF12                    100
#define PF13                    101
#define PF14                    102
#define PF15                    103
#define PG0                     104
#define PG1                     105
#define PG2                     106
#define PG3                     107
#define PG4                     108
#define PG5                     109
#define PG8                     110
#define PG9                     111
#define PG10                    112
#define PG11                    113
#define PG12                    114
#define PG13                    115
#define PG14                    116
#define PG15                    117
#define PH0                     118
#define PH1                     119
#define PH2                     120
#define PH3                     121
#define PH4                     122
#define PH5                     123
#define PH7                     124
#define PH8                     125
#define PH9                     126
#define PH10                    127
#define PH11                    128
#define PH12                    129
#define PH13                    130
#define PH14                    131
#define PH15                    132
#define PI4                     133
#define PI5                     134
#define PI6                     135
#define PI7                     136
#define PI8                     137
#define PI9                     138
#define PI10                    139
#define PI12                    140
#define PI13                    141
#define PI14                    142
#define PI15                    143
#define PJ0                     144
#define PJ1                     145
#define PJ2                     146
#define PJ3                     147
#define PJ4                     148
#define PJ5                     149
#define PJ6                     150
#define PJ7                     151
#define PJ8                     152
#define PJ9                     153
#define PJ10                    154
#define PJ11                    155
#define PJ12                    156
#define PJ13                    157
#define PJ14                    158
#define PJ15                    159
#define PK0                     160
#define PK1                     161
#define PK2                     162
#define PK3                     163
#define PK4                     164
#define PK5                     165
#define PK6                     166
#define PK7                     167

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

#define NUM_DIGITAL_PINS        168
#define NUM_ANALOG_INPUTS       6

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           13
#endif
#define LED_GREEN               LED_BUILTIN

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PI11
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
  #define SERIAL_UART_INSTANCE  1 //Connected to ST-Link
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PB7
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

// SD detect signal
#ifndef SD_DETECT_PIN
  #define SD_DETECT_PIN         PC13
#endif

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_ETH_MODULE_DISABLED)
  /* for compatibility until STMEthernet library is updated */
  /* #define HAL_ETH_MODULE_ENABLED */
  #define HAL_ETH_LEGACY_MODULE_ENABLED
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
    #define SERIAL_PORT_MONITOR     Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE    Serial
  #endif
#endif
