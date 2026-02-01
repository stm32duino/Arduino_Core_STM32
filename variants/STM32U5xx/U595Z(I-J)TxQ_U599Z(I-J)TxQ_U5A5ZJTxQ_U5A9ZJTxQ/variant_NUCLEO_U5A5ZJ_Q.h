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
#define PG8                     0
#define PG7                     1
#define PF15                    PIN_A9
#define PE13                    3
#define PF14                    PIN_A10
#define PE11                    5
#define PE9                     6
#define PF13                    7
#define PF12                    8
#define PD15                    9
#define PD14                    10
#define PA7                     PIN_A11
#define PA6                     PIN_A12
#define PA5                     PIN_A13
#define PB9                     14
#define PB8                     15
#define PC6                     16
#define PD11                    PIN_A14
#define PB13                    18
#define PD12                    PIN_A15
#define PA4                     PIN_A16 // SB35 ON
#define PB4                     21      // SB36 ON
#define PB5                     22      // UCPD TCPP
#define PB3                     23
// 24 is PA4 (20) as default SB38 ON
// 25 is PB4 (21) as default SB43 ON
// 26 is PA2 (A1) as default SB57 ON
#define PB10                    27      // SB61 ON
#define PE15                    28      // SB66 ON
// 29 is PB0 (A3) as default SB63 ON
#define PE12                    30      // SB68 ON
#define PE14                    31      // SB70 ON
#define PA0                     PIN_A17
#define PA8                     33
#define PE0                     34
#define PB11                    35
// 36 is PB10 (27) as default SB62 ON
// 37 is PE15 (28) as default SB67 ON
// 38 is PE14 (31) as default SB71 ON
// 39 is PE12 (30) as default SB69 ON
#define PE10                    40
#define PE7                     41
#define PE8                     42
#define PC8                     43
#define PC9                     44
#define PC10                    45
#define PC11                    46
#define PC12                    47
#define PD2                     48
#define PF3                     49
#define PF5                     50
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
#define PG1                     PIN_A18
#define PG0                     PIN_A19
#define PD1                     66
#define PD0                     67
#define PF0                     68
#define PF1                     69
#define PF2                     70
#define PB6                     71
#define PB2                     PIN_A20
#define PA3                     PIN_A0
#define PA2                     PIN_A1  // SB57 ON
#define PC3                     PIN_A2
#define PB0                     PIN_A3  // SB64 ON
#define PC1                     PIN_A4
#define PC0                     PIN_A5
#define PB1                     PIN_A6
#define PC2                     PIN_A7
#define PA1                     PIN_A8

#define PA9                     82
#define PA10                    83
#define PA11                    84
#define PA12                    85
#define PA13                    86
#define PA14                    87
#define PA15                    88
#define PB7                     89
#define PB14                    90
#define PB15                    91
#define PC7                     92
#define PC13                    93
#define PC14                    94
#define PC15                    95
#define PD8                     96
#define PD9                     97
#define PD10                    98
#define PD13                    PIN_A21
#define PE1                     100
#define PF4                     101
#define PF6                     102
#define PF10                    103
#define PF11                    104
#define PG2                     105
#define PG3                     106
#define PG4                     107
#define PG5                     108
#define PG6                     109
#define PG9                     110
#define PG10                    111
#define PG12                    112
#define PG13                    113
#define PG14                    114
#define PG15                    115
#define PH0                     116
#define PH1                     117
#define PH3                     118     // BOOT0

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
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
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
#define PC6_ALT2                (PC6  | ALT2)
#define PC7_ALT1                (PC7  | ALT1)
#define PC7_ALT2                (PC7  | ALT2)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PF9_ALT1                (PF9  | ALT1)

#define NUM_DIGITAL_PINS        119
#define NUM_ANALOG_INPUTS       22

// On-board LED pin number
#ifndef LED_LD1
  // SB21 ON/SB23 OFF (default) else PA5 with SB21 OFF/SB23 ON
  #define LED_LD1               PC7
#endif
#define LED_LD2                 PB7
#define LED_LD3                 PG2

#define LED_GREEN               LED_LD1
#define LED_BLUE                LED_LD2
#define LED_RED                 LED_LD3

#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef B1_USER
  // SB58 ON/SB59 OFF (default) else PA0 with SB58 OFF/SB59 ON
  #define B1_USER               PC13
#endif
#ifndef USER_BTN
  #define USER_BTN              B1_USER
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
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
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

// Alternate SYS_WKUP definition
#define PWR_WAKEUP_PIN1_1
#define PWR_WAKEUP_PIN1_2
#define PWR_WAKEUP_PIN2_1
#define PWR_WAKEUP_PIN2_2
#define PWR_WAKEUP_PIN3_1
#define PWR_WAKEUP_PIN3_2
#define PWR_WAKEUP_PIN4_1
#define PWR_WAKEUP_PIN4_2
#define PWR_WAKEUP_PIN5_1
#define PWR_WAKEUP_PIN6_1
#define PWR_WAKEUP_PIN6_2
#define PWR_WAKEUP_PIN7_1
#define PWR_WAKEUP_PIN7_2
#define PWR_WAKEUP_PIN8_1
#define PWR_WAKEUP_PIN8_2

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
