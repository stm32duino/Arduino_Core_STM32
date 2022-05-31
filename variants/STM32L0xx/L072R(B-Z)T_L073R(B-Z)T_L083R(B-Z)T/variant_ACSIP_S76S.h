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
#define PC0                     PIN_A0
#define PC1                     PIN_A1
#define PC2                     PIN_A2
#define PC3                     PIN_A3
#define PA0                     PIN_A4
#define PA2                     PIN_A5  // TX_DA
#define PA3                     PIN_A6  // RX_DA
#define PA4                     PIN_A7  // SPI1_NSS
#define PA5                     PIN_A8  // SPI1_SCK
#define PA6                     PIN_A9  // SPI1_MISO
#define PA7                     PIN_A10 // SPI1_MOSI
#define PC4                     PIN_A11
#define PC5                     PIN_A12
#define PB0                     PIN_A13 // IO_INT1
#define PB1                     PIN_A14 // IO_INT2
#define PC6                     15
#define PC7                     16
#define PC8                     17
#define PC9                     18
#define PA1                     PIN_A15 // RF_FEM_CPS
#define PA8                     20
#define PA10                    21      // USART1 RX
#define PA9                     22      // USART1 TX
#define PA11                    23
#define PA12                    24
#define PA13                    25      // SWDIO
#define PA14                    26      // SWCLK
#define PC10                    27
#define PC11                    28
#define PC12                    29
#define PD2                     30
#define PB5                     31
#define PB6                     32      // SCL
#define PB7                     33      // SDA
#define PB8                     34      // IO_LED_FCT
// Internal pins connected to SX1276
#define PA15                    35      // SX1276 D5
#define PB3                     36      // SX1276 D4
#define PB4                     37      // SX1276 D3
#define PB9                     38      // SX1276 D2
#define PB10                    39      // SX1276 Reset
#define PB11                    40      // SX1276 D0
#define PB12                    41      // SX1276 SPI nCS
#define PB13                    42      // SX1276 SPI2_SCK
#define PB14                    43      // SX1276 SPI2_MISO
#define PB15                    44      // SX1276 SPI2_MOSI
#define PC13                    45      // SX1276 D1
// X-tal
#define PC14                    46      // OSC32_IN
#define PC15                    47      // OSC32_OUT
#define PH0                     48      // OSC_IN
#define PH1                     49      // OSC_OUT

// Pin not available
//#define PB2                     50

// Alternate pins number
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA14_ALT1               (PA14 | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

#define NUM_DIGITAL_PINS        50
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PB8
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PA15
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3           PNUM_NOT_DEFINED
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

// I2C definitions
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
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  4
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

// Extra HAL modules
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
