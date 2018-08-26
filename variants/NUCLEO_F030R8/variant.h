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

#define PA3  0
#define PA2  1
#define PA10 2
#define PB3  3  // no PWM
#define PB5  4
#define PB4  5
#define PB10 6  // no PWM
#define PA8  7
#define PA9  8
#define PC7  9
#define PB6  10
#define PA7  11 // A6
#define PA6  12 // A7
#define PA5  13
#define PB9  14
#define PB8  15
// ST Morpho
// CN7 Left Side
#define PC10 16
#define PC12 17
#define PF6  18
#define PF7  19
#define PA13 20 // SWD
#define PA14 21 // SWD
#define PA15 22
#define PB7  23
#define PC13 24
#define PC14 25
#define PC15 26
#define PF0  27
#define PF1  28
#define PC2  29 // A8
#define PC3  30 // A9
// CN7 Right Side
#define PC11 31
#define PD2  32
// CN10 Left Side
#define PC9  33
// CN10 Right side
#define PC8  34
#define PC6  35
#define PC5  36 // A10
#define PA12 37
#define PA11 38
#define PB12 39
#define PB11 40
#define PB2  41
#define PB1  42
#define PB15 43
#define PB14 44
#define PB13 45
#define PC4  46 // A11
#define PF5  47
#define PF4  48
#define PA0  49 // A0
#define PA1  50 // A1
#define PA4  51 // A2
#define PB0  52 // A3
#define PC1  53 // A4
#define PC0  54 // A5

// This must be a literal
#define NUM_DIGITAL_PINS        61
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       12
#define NUM_ANALOG_FIRST        49

// On-board LED pin number
#define LED_BUILTIN             13
#define LED_GREEN               LED_BUILTIN

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM3  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           0
#define PIN_SERIAL_TX           1

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
