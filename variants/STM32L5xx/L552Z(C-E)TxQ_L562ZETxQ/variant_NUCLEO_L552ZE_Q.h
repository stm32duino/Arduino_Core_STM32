/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
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
// CN10
#define PD9                     0
#define PD8                     1
#define PF15                    2
#define PE13                    3
#define PF14                    4
#define PE11                    5
#define PE9                     6
#define PF13                    7
// CN7
#define PF12                    8
#define PD15                    9
#define PD14                    10
#define PA7                     PIN_A11
#define PA6                     PIN_A12
#define PA5                     PIN_A13
#define PB9                     14
#define PB8                     15
#define PC6                     16
#define PD11                    17
#define PB13                    18
#define PD12                    19
#define PA4                     PIN_A9
#define PB4                     21
#define PB5                     22      // UCPD TCPP
#define PB3                     23
// 24 is PA4                   (20)
// 25 is PB4                   (21)
// CN10
#define PA2                     PIN_A1
#define PB10                    27
#define PE15                    28
#define PB0                     PIN_A3
#define PE12                    30
#define PE14                    31
#define PA0                     PIN_A10
#define PA8                     33
#define PE0                     34
#define PB11                    35
// 36 is PB10                  (27)
// 37 is PE15                  (28)
// 38 is PE14                  (31)
// 39 is PE12                  (30)
#define PE10                    40
#define PE7                     41
#define PE8                     42
// CN8
#define PC8                     43
#define PC9                     44
#define PC10                    45
#define PC11                    46
#define PC12                    47
#define PD2                     48
#define PF3                     49
#define PF5                     50
// CN9
#define PD7                     51
#define PD6                     52
#define PD5                     53
#define PD4                     54
#define PD3                     55
#define PE2                     56
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
#define PB6                     71
#define PB2                     72
// ST Morpho
#define PA10                    73
#define PA11                    74
#define PA12                    75
#define PA13                    76
#define PA14                    77
#define PA15                    78
#define PA9                     79
#define PB14                    80
#define PB15                    81
#define PB7                     82
#define PC13                    83
#define PC14                    84
#define PC15                    85
#define PC7                     86
#define PD10                    87
#define PD13                    88
#define PE1                     89
#define PF10                    90
#define PF11                    91
#define PF4                     92
#define PF6                     93
#define PG10                    94
#define PG12                    95
#define PG13                    96
#define PG14                    97
#define PG15                    98
#define PG2                     99
#define PG3                     100
#define PG4                     101
#define PG5                     102
#define PG6                     103
#define PG7                     104
#define PG8                     105
#define PG9                     106
#define PH0                     107
#define PH1                     108
#define PH3                     109
// Analog pins
#define PA3                     PIN_A0
#define PC3                     PIN_A2
#define PC1                     PIN_A4
#define PC0                     PIN_A5
#define PB1                     PIN_A6
#define PC2                     PIN_A7
#define PA1                     PIN_A8

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
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
#define PB6_ALT1                (PB6  | ALT1)
#define PB7_ALT1                (PB7  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)
#define PB10_ALT1               (PB10 | ALT1)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC1_ALT1                (PC1  | ALT1)
#define PC2_ALT1                (PC2  | ALT1)
#define PC3_ALT1                (PC3  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PF9_ALT1                (PF9  | ALT1)

#define NUM_DIGITAL_PINS        117
#define NUM_ANALOG_INPUTS       14

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED1
#endif
// Green led
#ifndef LED1
  #define LED1                  PC7
#endif
// Blue led
#ifndef LED2
  #define LED2                  PB7
#endif
// Red led
#ifndef LED3
  #define LED3                  PA9
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
  #define SERIAL_UART_INSTANCE  101
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PG8
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PG7
#endif

// Pin UCPD to configure TCPP in default Type-C legacy state (UCPD_DBn for TCPP01)
#define PIN_UCPD_TCPP           PB5

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
  #define SERIAL_PORT_MONITOR   Serial
  #define SERIAL_PORT_HARDWARE  Serial
#endif
