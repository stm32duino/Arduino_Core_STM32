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

// CN9
#define PB7                     0
#define PB6                     1
#define PA10                    2
#define PB3                     3
#define PB10                    PIN_A16
#define PB4                     5
#define PB5                     6
#define PA15                    7

// CN5
#define PA9                     8
#define PC7                     9
#define PB0                     PIN_A14
#define PA7                     PIN_A10
#define PA6                     PIN_A9
#define PA5                     PIN_A8 // LED
#define PB9                     14
#define PB8                     15

// CN7 Left Side
#define PD0                     16
#define PD2                     17
#define PA14                    PIN_A13
#define PA13                    PIN_A12
#define PC6                     20
#define PC13                    21 // Button
#define PC14                    22 // OSCX_IN
#define PF0                     23 // OSC_IN
#define PF1                     24 // OSC_OUT
#define PB11                    PIN_A17
#define PA2                     PIN_A6 // VCP_TX

// CN7 Right Side
#define PD1                     27

// CN10 Left Side
#define PD3                     28
#define PC11                    29

// CN8 Left Side
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA4                     PIN_A2
#define PB1                     PIN_A3
#define PA11                    PIN_A4
#define PA12                    PIN_A5

// CN10 Right side
#define PA3                     PIN_A7 // VCP_RX
#define PC15                    37 // OSCX_OUT
#define PB12                    PIN_A18
#define PB2                     PIN_A15
#define PF3                     40
#define PA8                     PIN_A11
#define PB15                    42
#define PB14                    43
#define PB13                    44

// Others
#define PF2                     45 // NRST


#define NUM_DIGITAL_PINS        46
#define NUM_ANALOG_INPUTS       19

// On-board LED pin number
#define LED_GREEN               PA5
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC13
#endif

// I2C Definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB9
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB8
#endif

// Timer Definitions
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM16
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM17
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  2
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA3
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA2
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
