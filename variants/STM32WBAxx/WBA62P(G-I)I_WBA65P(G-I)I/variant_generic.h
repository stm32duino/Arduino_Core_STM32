/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
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
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA2                     PIN_A2
#define PA3                     PIN_A3
#define PA4                     PIN_A4
#define PA5                     PIN_A5
#define PA6                     PIN_A6
#define PA7                     PIN_A7
#define PA8                     PIN_A8
#define PA9                     9
#define PA10                    10
#define PA11                    11
#define PA12                    12
#define PA13                    13
#define PA14                    14
#define PA15                    15
#define PB0                     16
#define PB1                     17
#define PB2                     18
#define PB3                     19
#define PB4                     20
#define PB5                     21
#define PB6                     22
#define PB7                     23
#define PB8                     24
#define PB9                     PIN_A9
#define PB10                    26
#define PB11                    27
#define PB12                    28
#define PB13                    29
#define PB14                    30
#define PB15                    31
#define PC0                     32
#define PC1                     33
#define PC2                     34
#define PC3                     35
#define PC4                     36
#define PC5                     37
#define PC6                     38
#define PC7                     39
#define PC8                     40
#define PC9                     41
#define PC10                    42
#define PC11                    43
#define PC12                    44
#define PC13                    45
#define PC14                    46
#define PC15                    47
#define PD0                     48
#define PD1                     49
#define PD2                     50
#define PD3                     51
#define PD4                     52
#define PD5                     53
#define PD6                     54
#define PD7                     55
#define PD8                     56
#define PD9                     57
#define PD10                    58
#define PD11                    59
#define PD12                    60
#define PD13                    61
#define PD14                    62
#define PD15                    63
#define PE0                     64
#define PE1                     65
#define PE2                     66
#define PE3                     67
#define PE4                     68
#define PE5                     69
#define PE6                     70
#define PG2                     71
#define PG3                     72
#define PG4                     73
#define PG5                     74
#define PG6                     75
#define PG7                     76
#define PG8                     77
#define PG9                     78
#define PG10                    79
#define PG11                    80
#define PG12                    81
#define PG13                    82
#define PG14                    83
#define PG15                    84
#define PH3                     85

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA1_ALT2                (PA1  | ALT2)
#define PA2_ALT1                (PA2  | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB2_ALT1                (PB2  | ALT1)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB6_ALT1                (PB6  | ALT1)
#define PB7_ALT1                (PB7  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB9_ALT3                (PB9  | ALT3)
#define PB10_ALT1               (PB10 | ALT1)
#define PB11_ALT1               (PB11 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PC3_ALT1                (PC3  | ALT1)
#define PD9_ALT1                (PD9  | ALT1)

#define NUM_DIGITAL_PINS        86
#define NUM_ANALOG_INPUTS       10

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PNUM_NOT_DEFINED
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA12
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PG5
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3           PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA15
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB3
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB4
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PA7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PA6
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM16
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM17
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  101
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA1
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA2
#endif

// Alternate SYS_WKUP definition
#define PWR_WAKEUP_PIN1_1
#define PWR_WAKEUP_PIN2_1
#define PWR_WAKEUP_PIN3_1
#define PWR_WAKEUP_PIN4_1
#define PWR_WAKEUP_PIN5_1
#define PWR_WAKEUP_PIN6_1
#define PWR_WAKEUP_PIN7_1
#define PWR_WAKEUP_PIN8_1

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
