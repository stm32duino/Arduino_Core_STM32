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
#define PB12                    0
#define PC11                    1
#define PC10                    2
#define PC9                     3
#define PC8                     4
#define PD2                     5
#define PC12                    6
#define PG10                    7
#define PG11                    8
#define PB4                     9
#define PB5                     10
#define PB8                     11
#define PB9                     12
#define PB6                     13
#define PB7                     14
#define PC0                     PIN_A0
#define PA3                     PIN_A1
#define PA6                     PIN_A2
#define PB1                     PIN_A3
#define PA2                     PIN_A4
#define PA7                     PIN_A5
#define PC1                     21
#define PC4                     PIN_A6
#define PA5                     23
#define PA4                     24
#define PA1                     25
#define PA0                     26
#define PD11                    27
#define PG9                     28
#define PB14                    29
#define PB15                    30
#define PC7                     31
#define PD7                     32
#define PG14                    33
#define PA8                     34
#define PD13                    35
#define PC6                     36
#define PG13                    37

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
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB4_ALT1                (PB4  | ALT1)
#define PB4_ALT2                (PB4  | ALT2)
#define PB5_ALT1                (PB5  | ALT1)
#define PB5_ALT2                (PB5  | ALT2)
#define PB6_ALT1                (PB6  | ALT1)
#define PB6_ALT2                (PB6  | ALT2)
#define PB7_ALT1                (PB7  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC0_ALT2                (PC0  | ALT2)
#define PC1_ALT1                (PC1  | ALT1)
#define PC1_ALT2                (PC1  | ALT2)
#define PC4_ALT1                (PC4  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC7_ALT2                (PC7  | ALT2)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

#define NUM_DIGITAL_PINS        38
#define NUM_ANALOG_INPUTS       7

// On-board LED pin number
#define LED_BUILTIN             PNUM_NOT_DEFINED
#define LED_RED                 PNUM_NOT_DEFINED

// SPI Definitions
#define PIN_SPI_SS              PG10
#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PG11

// I2C Definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// I2C timing definitions (optional), avoid time spent to compute if defined
#define I2C_TIMING_SM           0x30E0628A
#define I2C_TIMING_FM           0x20D01132
#define I2C_TIMING_FMP          0x1080091A

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE              TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO             TIM7
#endif

// UART Definitions
#define SERIAL_UART_INSTANCE    1

// Serial pin used for console
// Required by Firmata
#define PIN_SERIAL_RX           PB7
#define PIN_SERIAL_TX           PB6

// HSE is 16MHz on Daisy Seed.
#define HSE_VALUE               (16000000UL)

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
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_HARDWARE    Serial
#endif
