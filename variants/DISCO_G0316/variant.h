/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
#define PA0  A0 // package pin number 4
#define PA1  A1 // package pin number 4
#define PA2  A2 // package pin number 4

#define PA8  3  // package pin number 5
#define PA9  4  // package pin number 5 - shared with PA11
#define PA10 5  // package pin number 6 - shared with PA12
#define PA11 A3 // package pin number 5
#define PA12 A4 // package pin number 6 - LED
#define PA13 A5 // package pin number 7 - SWDIO
#define PA14 A6 // package pin number 8 - SWCLK - BOOT0
#define PA15 10 // package pin number 8

#define PB0  A7 // package pin number 5
#define PB1  A8 // package pin number 5
#define PB5  13 // package pin number 8
#define PB6  14 // package pin number 8
#define PB7  A9 // package pin number 1
#define PB8  16 // package pin number 1
#define PB9  17 // package pin number 1

#define PC14 18 // package pin number 1

#define PF2  19 // package pin number 4

// This must be a literal
#define NUM_DIGITAL_PINS        20
#define NUM_ANALOG_INPUTS       10

// On-board LED pin number
#define LED_BUILTIN             PA12
#define LED_GREEN               LED_BUILTIN

// On-board user button
#define USER_BTN                PF2

// Below SPI and I2C definitions already done in the core
// Could be redefined here if differs from the default one
// SPI Definitions
#define PIN_SPI_MOSI            PA12
#define PIN_SPI_MISO            PA11
#define PIN_SPI_SCK             PA1
#define PIN_SPI_SS              PA13

// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6

// Timer Definitions
// Use TIM14/TIM16/TIM17 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM16
#define TIMER_SERVO             TIM17

// UART Definitions
#define SERIAL_UART_INSTANCE    1

// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PB7
#define PIN_SERIAL_TX           PB6

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
  #define SERIAL_PORT_MONITOR   Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
