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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "PeripheralPins.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
extern const PinName digitalPin[];

#define PC7  0
#define PC6  1
#define PG6  2
#define PB4  3
#define PG7  4
#define PI0  5
#define PH6  6
#define PI3  7
#define PI2  8
#define PA15 9
#define PA8  10
#define PB15 11
#define PB14 12
#define PI1  13
#define PB9  14
#define PB8  15
#define PA0  16 // A0
#define PF10 17 // A1
#define PF9  18 // A2
#define PF8  19 // A3
#define PF7  20 // A4
#define PF6  21 // A5
#define PI11 22 // User btn
#define PB7  23 // ST-Link Rx
#define PA9  24 // ST-Link Tx
#define PC13 25 // SD detect

// This must be a literal
#define NUM_DIGITAL_PINS        26
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       6
#define NUM_ANALOG_FIRST        16

// On-board LED pin number
#define LED_BUILTIN             13
#define LED_GREEN               LED_BUILTIN

// On-board user button
#define USER_BTN                PI11

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    1 //Connected to ST-Link
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PB7
#define PIN_SERIAL_TX           PA9

// SD detect signal
#define SD_DETECT_PIN           PC13

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
