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
// See UM2408, Figure 18. NUCLEO-H7A3ZI-Q extension connectors
// CN10 right Arduino Uno connector
#define PB7                     0
#define PB6                     1
#define PG14                    2
#define PE13                    3
#define PE14                    4
#define PE11                    5
#define PA8                     6
#define PG12                    7
// CN7 right Arduino Uno connector
#define PG9                     8
#define PD15                    9
#define PD14                    10
#define PA7                     PIN_A11
#define PA6                     PIN_A12
#define PA5                     PIN_A13
#define PB9                     14
#define PB8                     15
// CN7 left
#define PC6                     16
#define PB15                    17
#define PB13                    18
#define PB12                    19
#define PA15                    20
#define PC7                     21
#define PB5                     22
#define PB3                     23
#define PA4                     PIN_A14
#define PB4                     25
// CN10 Left
#define PG6                     26
#define PB2                     27
#define PD13                    28
#define PD12                    29
#define PD11                    30
#define PE2                     31
#define PA0                     PIN_A15
#define PB0                     PIN_A16
#define PE0                     34
// CN10 Right
#define PB11                    35
#define PB10                    36
#define PE15                    37
#define PE6                     38
#define PE12                    39
#define PE10                    40
#define PE7                     41
#define PE8                     42
// CN8 Left
#define PC8                     43
#define PC9                     44
#define PC10                    45
#define PC11                    46
#define PC12                    47
#define PD2                     48
#define PG10                    49
#define PG8                     50
// CN9 Left
#define PD7                     51
#define PD6                     52
#define PD5                     53
#define PD4                     54
#define PD3                     55
// 56 is PE2                   (31)
#define PE4                     57
#define PE5                     58
// 59 is PE6                   (38)
#define PE3                     60
#define PF8                     61
#define PF7                     62
#define PF9                     63
#define PD10                    64
// CN9 Right
#define PB14                    65
#define PD1                     66
#define PD0                     67
#define PF15                    68
#define PF14                    PIN_A17
// 70 is PB5                   (22)
#define PE9                     71
// 72 is PB2                   (27)
#define PA3                     PIN_A0
#define PC0                     PIN_A1
#define PC3_C                   PIN_A2
#define PB1                     PIN_A3
#define PC2_C                   PIN_A4
#define PF11                    PIN_A5
// CN7 left (analog part)
#define PC1                     PIN_A6
#define PC5                     PIN_A7
#define PA2                     PIN_A8
// ST morpho
#define PA1                     PIN_A9
#define PA9                     83
#define PA10                    84
#define PA11                    85
#define PA12                    86
#define PA13                    87
#define PA14                    88
#define PC4                     PIN_A10
#define PC13                    90
#define PC14                    91
#define PC15                    92
#define PD8                     93
#define PD9                     94
#define PE1                     95
#define PF6                     96
#define PF10                    97
#define PG7                     98
#define PG11                    99
#define PG13                    100
#define PH0                     101
#define PH1                     102

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
#define PB9_ALT1                (PB9  | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC1_ALT1                (PC1  | ALT1)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PF8_ALT1                (PF8  | ALT1)
#define PF9_ALT1                (PF9  | ALT1)
#define PG13_ALT1               (PG13 | ALT1)

#define NUM_DIGITAL_PINS        103
#define NUM_DUALPAD_PINS        2
#define NUM_ANALOG_INPUTS       18

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
  #define SERIAL_UART_INSTANCE  3
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PD9
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PD8
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

// HSE default value is 25MHz in HAL
// By default HSE_BYPASS is based on HSI/2 from STLink
#ifndef HSE_BYPASS_NOT_USED
  #define HSE_VALUE             8000000
#endif

#define USE_PWR_DIRECT_SMPS_SUPPLY

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
