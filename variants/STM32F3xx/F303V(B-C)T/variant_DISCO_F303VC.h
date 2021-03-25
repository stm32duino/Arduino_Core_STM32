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
//P1 connector Right side
#define PC0                     PIN_A0
#define PC2                     PIN_A1
#define PF2                     PIN_A2
#define PA0                     PIN_A23
#define PA2                     PIN_A25
#define PA4                     PIN_A27
#define PA6                     PIN_A29
#define PC4                     PIN_A3
#define PB0                     PIN_A4
#define PB2                     PIN_A5
#define PE8                     PIN_A31
#define PE10                    PIN_A33
#define PE12                    PIN_A35
#define PE14                    PIN_A37
#define PB10                    14
#define PB12                    PIN_A6
#define PB14                    PIN_A7
#define PD8                     PIN_A8
#define PD10                    PIN_A9
#define PD12                    PIN_A10
#define PD14                    PIN_A11
#define PC7                     21
//P2 connector Left side
#define PF9                     22
#define PF0                     23
#define PC14                    24
#define PE6                     25
#define PE4                     26
#define PE2                     27
#define PE0                     28
#define PB8                     29
#define PB6                     30
#define PB4                     31
#define PD7                     32
#define PD5                     33
#define PD3                     34
#define PD1                     35
#define PC12                    36
#define PC10                    37
#define PA14                    38
#define PF6                     39
#define PA12                    40
#define PA10                    41
#define PA8                     42
#define PC8                     43
//P1 Connector Left Side
#define PC1                     PIN_A12
#define PC3                     PIN_A13
#define PA1                     PIN_A24
#define PA3                     PIN_A26
#define PF4                     PIN_A14
#define PA5                     PIN_A28
#define PA7                     PIN_A30
#define PC5                     PIN_A15
#define PB1                     PIN_A16
#define PE7                     PIN_A17
#define PE9                     PIN_A32
#define PE11                    PIN_A34
#define PE13                    PIN_A36
#define PE15                    PIN_A38
#define PB11                    58
#define PB13                    PIN_A18
#define PB15                    PIN_A19
#define PD9                     PIN_A20
#define PD11                    PIN_A21
#define PD13                    PIN_A22
#define PD15                    64
#define PC6                     65
//P2 connector Right side
#define PF10                    66
#define PF1                     67
#define PC15                    68
#define PC13                    69
#define PE5                     70
#define PE3                     71
#define PE1                     72
#define PB9                     73
#define PB7                     74
#define PB5                     75
#define PB3                     76
#define PD6                     77
#define PD4                     78
#define PD2                     79
#define PD0                     80
#define PC11                    81
#define PA15                    82
#define PA13                    83
#define PA11                    84
#define PA9                     85
#define PC9                     86

// Alternate pins number
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA4_ALT1                (PA4  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA9_ALT1                (PA9  | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PA11_ALT1               (PA11 | ALT1)
#define PA11_ALT2               (PA11 | ALT2)
#define PA12_ALT1               (PA12 | ALT1)
#define PA12_ALT2               (PA12 | ALT2)
#define PA13_ALT1               (PA13 | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB4_ALT2                (PB4  | ALT2)
#define PB5_ALT1                (PB5  | ALT1)
#define PB5_ALT2                (PB5  | ALT2)
#define PB6_ALT1                (PB6  | ALT1)
#define PB6_ALT2                (PB6  | ALT2)
#define PB7_ALT1                (PB7  | ALT1)
#define PB7_ALT2                (PB7  | ALT2)
#define PB8_ALT1                (PB8  | ALT1)
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB14_ALT1               (PB14 | ALT1)
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
#define PD10_ALT1               (PD10 | ALT1)
#define PD11_ALT1               (PD11 | ALT1)
#define PD12_ALT1               (PD12 | ALT1)
#define PD13_ALT1               (PD13 | ALT1)
#define PD14_ALT1               (PD14 | ALT1)
#define PE8_ALT1                (PE8  | ALT1)
#define PF2_ALT1                (PF2  | ALT1)

#define NUM_DIGITAL_PINS        87
#define NUM_ANALOG_INPUTS       39

// On-board LED pin number
#define LED_BLUE                PE8
#define LED_RED                 PE9
#define LED_ORANGE              PE10
#define LED_GREEN               PE11
#define LED_BLUE2               PE12
#define LED_RED2                PE13
#define LED_ORANGE2             PE14
#define LED_GREEN2              PE15
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_BLUE
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PA0
#endif

// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA7
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PA6
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PA5
#endif

// I2C Definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB6
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
#define SERIAL_UART_INSTANCE    1 //Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PC5
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PC4
#endif

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
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
