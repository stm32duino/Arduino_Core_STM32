/*
 *******************************************************************************
 * Copyright (c) 2019-2022, STMicroelectronics
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

#define PG9                     0
#define PG14                    1
#define PF15                    2
#define PE13                    3
#define PF14                    4
#define PE11                    5
#define PE9                     6
#define PF13                    7
#define PF12                    8
#define PD15                    9
#define PD14                    10
#define PA7                     PIN_A10
#define PA6                     PIN_A11
#define PA5                     PIN_A12
#define PB9                     14
#define PB8                     15
#define PC6                     16
#define PB15                    17
#define PB13                    18
#define PB12                    19
#define PA15                    20
#define PC7                     21
#define PB5                     22
#define PB3                     23
#define PA4                     PIN_A13
#define PB4                     25
#define PB6                     26
#define PB2                     27
#define PD13                    28
#define PD12                    29
#define PD11                    30
#define PE2                     31
#define PA0                     PIN_A14
#define PB0                     PIN_A15 // LED_GREEN
#define PE0                     34
#define PB11                    35
#define PB10                    36
#define PE15                    37
#define PE14                    38
#define PE12                    39
#define PE10                    40
#define PE7                     41
#define PE8                     42
#define PC8                     43
#define PC9                     44
#define PC10                    45
#define PC11                    46
#define PC12                    47
#define PD2                     48
#define PG2                     49
#define PG3                     50
#define PD7                     51
#define PD6                     52
#define PD5                     53
#define PD4                     54
#define PD3                     55
// 56 is PE2                   (31)
#define PE4                     57
#define PE5                     58
#define PE6                     59
#define PE3                     60
#define PF8                     61
#define PF7                     62
#define PF9                     63
#define PG1                     64
#define PG0                     65
#define PD1                     66
#define PD0                     67
#define PF0                     68
#define PF1                     69
#define PF2                     70
#define PB7                     71 // LED_BLUE
#define PB14                    72 // LED_RED
#define PC13                    73 // USER_BTN
#define PD9                     74 // Serial Rx
#define PD8                     75 // Serial Tx
#define PA3                     PIN_A0
#define PC0                     PIN_A1
#define PC3                     PIN_A2
#define PC1                     PIN_A3
#define PC4                     PIN_A4
#define PC5                     PIN_A5
#define PB1                     PIN_A6
#define PC2                     PIN_A7
#define PA2                     PIN_A8
// ST Morpho
#define PF6                     85
#define PA1                     PIN_A9
#define PF4                     87
#define PA8                     88
#define PA9                     89
#define PA10                    90
#define PA11                    91
#define PA12                    92
#define PA13                    93 // SWD
#define PA14                    94 // SWD
#define PF3                     95
#define PF5                     96
#define PF10                    97
#define PC14                    98
#define PC15                    99
#define PD10                    100
#define PE1                     101
#define PF11                    102
#define PG4                     103
#define PG5                     104
#define PG6                     105
#define PG7                     106
#define PG8                     107
#define PG10                    108
#define PG11                    109
#define PG12                    110
#define PG13                    111
#define PG15                    112
#define PH0                     113 // MCO
#define PH1                     114

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

#define NUM_DIGITAL_PINS        115
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#define LED_GREEN               PB0
#define LED_BLUE                PB7
#define LED_RED                 PB14
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC13
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
  #define SERIAL_UART_INSTANCE  3 //ex: 2 for Serial2 (USART2)
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PD9
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PD8
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

// HSE default value is 25MHz in HAL
// HSE_BYPASS is 8MHz
#ifndef HSE_BYPASS_NOT_USED
  #define HSE_VALUE             8000000
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
