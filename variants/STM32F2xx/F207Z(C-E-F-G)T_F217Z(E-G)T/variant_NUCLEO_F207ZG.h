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
#define PA7                     PIN_A10  // RMII RX Data Valid (JP6 ON)
#define PA6                     PIN_A11
#define PA5                     PIN_A12
#define PB9                     14
#define PB8                     15
#define PC6                     16
#define PB15                    17
#define PB13                    18       // RMII TXD1 (JP7 ON)
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
#define PB0                     33       // LED1
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
#define PF8                     PIN_A15
#define PF7                     PIN_A16
#define PF9                     PIN_A17
#define PG1                     64
#define PG0                     65
#define PD1                     66
#define PD0                     67
#define PF0                     68
#define PF1                     69
#define PF2                     70
// 71 is PA7                   (11)
// 72 is                        NC
#define PB7                     73       // LED_BLUE
#define PB14                    74       // LED_RED
#define PC13                    75       // USER_BTN
#define PD9                     76       // Serial Rx
#define PD8                     77       // Serial Tx
#define PA3                     PIN_A0
#define PC0                     PIN_A1
#define PC3                     PIN_A2
#define PF3                     PIN_A3
#define PF5                     PIN_A4
#define PF10                    PIN_A5
#define PB1                     PIN_A6
#define PC2                     PIN_A7
#define PF4                     PIN_A8
#define PF6                     PIN_A9
#define PD10                    88
#define PE1                     89
#define PF11                    90
#define PG4                     91
#define PG5                     92
#define PG8                     93
#define PG10                    94
#define PG12                    95
#define PG15                    96
// Depending of SB or Jumper pins are assigned
// to a dedicated feature
// Ethernet JP6 and JP7 must be ON when using Ethernet
#define PA1                     97       // RMII Reference Clock (SB13 ON)
#define PA2                     98       // RMII MDIO (SB160 ON)
#define PC1                     99       // RMII MDC (SB164 ON)
#define PC4                     100      // RMII RXD0 (SB178 ON)
#define PC5                     101      // RMII_RXD1 (SB181 ON)
#define PG11                    102      // RMII TX Enable (SB183 ON)
#define PG13                    103      // RXII TXD0 (SB182 ON)
// If JP4 OFF USB pins can be used as GPIO on ST Morpho
#define PA8                     104      // USB SOF (Test point TP1)
#define PA9                     105      // USB VBUS (SB 127 ON)
#define PA10                    106      // USB ID (SB125 ON)
#define PA11                    107      // USB DM (SB133 ON)
#define PA12                    108      // USB DP (SB132 ON)
#define PG6                     109      // USB GPIO OUT (SB186 OFF SB187 ON)
#define PG7                     110      // USB GPIO IN (SB184 ON JP4 ON)
#define PA13                    111      // SWDIO
#define PA14                    112      // SWDCLK
// LSE by default
#define PC14                    113      // OSC32_IN (SB144 OFF)
#define PC15                    114      // OSC32_OUT (SB145 OFF)
// MC0 by default
#define PH0                     115      //  OSC_IN (SB8 ON) / MCO (SB149 ON)
#define PH1                     116      //  OSC_OUT (SB9 ON)

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
#define PB12_ALT1               (PB12 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
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

#define NUM_DIGITAL_PINS        117
#define NUM_ANALOG_INPUTS       18

// On-board LED pin number
// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PB0
#endif
#ifndef LED_GREEN
  #define LED_GREEN             LED_BUILTIN
#endif
#ifndef LED_BLUE
  #define LED_BLUE              PB7
#endif
#ifndef LED_RED
  #define LED_RED               PB14
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
#if !defined(HAL_ETH_MODULE_DISABLED)
  #define HAL_ETH_MODULE_ENABLED
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
