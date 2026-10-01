/*
 *******************************************************************************
 * Copyright (c) 2020-2026, STMicroelectronics
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
// ARDUINO® Uno V3 connectors
// CN9
#define PA8                     0
#define PB4                     1
#define PA10                    2
#define PF1                     3
#define PD3                     4
#define PG15                    5
#define PF3                     6
#define PE9                     PIN_A6
// CN5
#define PA9                     8
#define PF4                     9
#define PE11                    PIN_A7
#define PE14                    PIN_A8
#define PE13                    PIN_A9
#define PE12                    PIN_A10
#define PG6                     14
#define PF5                     15
// CN8
#define PA6                     PIN_A0
#define PA7                     PIN_A1
#define PA4                     PIN_A2
#define PB0                     PIN_A3
#define PF12                    PIN_A4
#define PF11                    PIN_A5
// Dedicated pins
#define PA3                     22      // LED green
#define PF0                     23      // LED red
#define PE5                     24      // LED blue
#define PC13                    25      // User button
#define PD8                     26      // USART3 Tx
#define PD9                     27      // USART3 Rx
// Ethernet
#define PA1                     28
#define PA2                     29
#define PC1                     30
#define PD1                     31
#define PC4                     32
#define PC5                     33
#define PA5                     34
#define PB12                    35
#define PG12                    36
#define PD4                     37
// UCPD
#define PB13                    38
#define PB14                    39
#define PA11                    40
#define PB8                     41
#define PB9                     42
// CN19 M.2 Key A connector
// Odd pins of the M.2 Key A connector
#define PD7                     43
#define PG9                     44
#define PG10                    45
#define PB2                     46
#define PC0                     47
#define PE7                     48
#define PD12                    49
#define PD11                    50
#define PF10                    51
#define PB5                     52
// PC0
#define PD6                     53
#define PD5                     54
// PE7
#define PD13                    55
#define PF7                     56
// PD12
// PD11
// PF10
// PB5
// Even pins of the M.2 Key A connector
#define PG11                    57
#define PG5                     58
#define PB10                    59
#define PD0                     60
// PD6
// PD5
// PD13
// PF7
// PD0
// PB2
#define PB7                     61
#define PB6                     62
#define PG13                    63
// CN7 ST morpho connector
// Odd pins of the ST morpho connector
#define PC10                    64
#define PC12                    65
#define PG0                     66
#define PB3                     67
#define PA13                    68
#define PA14                    69
#define PA15                    70
#define PG2                     71
#define PA0                     PIN_A11
#define PC14                    73
#define PC15                    74
#define PH0                     75
#define PH1                     76
#define PC2                     PIN_A12
#define PC3                     PIN_A13
// Even pins of the ST morpho connector
#define PC11                    79
#define PF15                    80
#define PG1                     81
#define PG4                     82
// Shared pin with the ARDUINO® Uno V3 connector.
// PA6
// PA7
// PA4
// PB0
// PF12
// PF11
// CN10 ST morpho connector
// Odd pins of the CN10 ST morpho connector
#define PC9                     83
// Shared pin with the ARDUINO® Uno V3 connector.
// PF5
// PG6
// PE12
// PE13
// PE14
// PE11
// PF4
// PA9
// PE9
// PF3
// PG15
// PD3
// PF1
// PA10
// PB4
// PA8
// Even pins of the CN10 ST morpho connector
#define PF6                     84
#define PD14                    85
#define PD15                    86
#define PE0                     87
#define PE15                    PIN_A14
#define PB1                     PIN_A15
#define PF2                     90
#define PF14                    PIN_A16
#define PB15                    92
#define PE10                    PIN_A17
#define PE8                     PIN_A18
#define PF13                    PIN_A19
#define PF8                     96
#define PF9                     97
// CN11 expansion connector
// Most of pins already defined for the M.2 key A connector
// Odd pins of the CN11 expansion connector
// PD11
// PD12
// PF7
// PD13
// PE7
// PD5
// PD6
// PC0
// PB10
// PD0
// PB2
// PF10
// PB5
// CN12 ST morpho connector
// Odd pins of the CN12 ST morpho connector
// PB7
// PB6
// PG5
// PG13
// Even pins of the CN12 ST morpho connector
// PG10
// PG11
// PG9
// PD7
#define PG3                     98
#define PD10                    99
#define PE4                     100
#define PG7                     101
// TRACE
// PE2
// PE3
// PG14
// PD2
// PE6
// Not connected
// PA12


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
#define PB2_ALT1                (PB2  | ALT1)
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
#define PB12_ALT1               (PB12 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC1_ALT1                (PC1  | ALT1)
#define PC2_ALT1                (PC2  | ALT1)
#define PC2_ALT2                (PC2  | ALT2)
#define PC3_ALT1                (PC3  | ALT1)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PD1_ALT1                (PD1  | ALT1)
#define PD8_ALT1                (PD8  | ALT1)
#define PD13_ALT1               (PD13 | ALT1)
#define PE4_ALT1                (PE4  | ALT1)
#define PE5_ALT1                (PE5  | ALT1)
#define PE7_ALT1                (PE7  | ALT1)
#define PE8_ALT1                (PE8  | ALT1)
#define PE11_ALT1               (PE11 | ALT1)
#define PF8_ALT1                (PF8  | ALT1)
#define PF9_ALT1                (PF9  | ALT1)
#define PG6_ALT1                (PG6  | ALT1)
#define PG9_ALT1                (PG9  | ALT1)
#define PG11_ALT1               (PG11 | ALT1)
#define PG12_ALT1               (PG12 | ALT1)
#define PG13_ALT1               (PG13 | ALT1)
#define PG14_ALT1               (PG14 | ALT1)

#define NUM_DIGITAL_PINS        102
#define NUM_ANALOG_INPUTS       20

// On-board LED pin number
#define LED_GREEN               PA3 // active HIGH
#define LED_RED                 PF0 // active LOW
#define LED_BLUE                PE5 // active HIGH
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC13 // active HIGH
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
#if !defined(HAL_ETH_MODULE_DISABLED)
  #define HAL_ETH_MODULE_ENABLED
#endif
#if !defined(HAL_I3C_MODULE_DISABLED)
  #define HAL_I3C_MODULE_ENABLED
#endif
#if !defined(HAL_OSPI_MODULE_DISABLED)
  #define HAL_OSPI_MODULE_ENABLED
#endif
#if !defined(HAL_SD_MODULE_DISABLED)
  #define HAL_SD_MODULE_ENABLED
#endif

// Value of the External oscillator in Hz
#define HSE_VALUE               48000000UL

// Pin UCPD to configure TCPP in default Type-C legacy state (UCPD_DBn for TCPP01)
#define PIN_UCPD_TCPP           PB9

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
