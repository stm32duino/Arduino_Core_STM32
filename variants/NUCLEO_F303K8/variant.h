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

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
extern const PinName digitalPin[];

enum {
  PA10, //D0
  PA9,  //D1
  PA12, //D2
  PB0,  //D3
  PB7,  //D4
  PB6,  //D5
  PB1,  //D6
  PF0,  //D7
  PF1,  //D8
  PA8,  //D9
  PA11, //D10
  PB5,  //D11
  PB4,  //D12
  PB3,  //D13 - LED
  PA0,  //D14/A0
  PA1,  //D15/A1
  PA3,  //D16/A2
  PA4,  //D17/A3
  PA5,  //D18/A4 - if SB18 ON (default) connected to PB7
  PA6,  //D19/A5 - if SB16 ON (default) connected to PB6
  PA7,  //D20/A6
  PA2,  //D21/A7 - STLink Tx
  PA15, //D22    - STLink Rx
  PEND
};

enum {
  A_START_AFTER = D13,
  A0,  A1,  A2,  A3,  A4,  A5,  A6,
  AEND
};

// On-board LED pin number
#define LED_BUILTIN             13
#define LED_GREEN               LED_BUILTIN

// On-board user button
//#define USER_BTN              NC

// I2C Definitions
#define SDA                     4
#define SCL                     5

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

 // UART Definitions
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link

// Serial Pin Firmata
#define PIN_SERIAL_RX           PA15 // 22
#define PIN_SERIAL_TX           PA2  // 21

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
#define SERIAL_PORT_HARDWARE  Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
