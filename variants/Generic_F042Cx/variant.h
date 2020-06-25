/*
 *******************************************************************************
 * Copyright (c) 2019, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

#define PA0 A0
#define PA1 A1
#define PA2 A2
#define PA3 A3
#define PA4 A4
#define PA5 A5
#define PA6 A6
#define PA7 A7
#define PA8 20
#define PA9  21
#define PA10 22
#define PA11 23
#define PA12 24
#define PA13 25
#define PA14 26
#define PA15 27
#define PB0 11
#define PB1 12
#define PB2 13
#define PB3  28
#define PB4  29
#define PB5  30
#define PB6  31
#define PB7  32
#define PB8  34
#define PB9  35
#define PB10 14
#define PB11 15
#define PB12 16
#define PB13 17
#define PB14 18
#define PB15 19
#define PC13 0
#define PF0 1
#define PF1 2
#define PF11 33


#define NUM_DIGITAL_PINS        36
#define NUM_ANALOG_INPUTS       8

// UART Definitions
#define SERIAL_UART_INSTANCE    2

#define PIN_SERIAL_RX           PA3
#define PIN_SERIAL_TX           PA2

#ifdef __cplusplus
} // extern "C"
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

#endif /* _VARIANT_ARDUINO_STM32_ */
