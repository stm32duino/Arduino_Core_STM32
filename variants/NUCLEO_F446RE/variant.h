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
  PA3,  //D0
  PA2,  //D1
  PA10, //D2
  PB3,  //D3
  PB5,  //D4
  PB4,  //D5
  PB10, //D6
  PA8,  //D7
  PA9,  //D8
  PC7,  //D9
  PB6,  //D10
  PA7,  //D11
  PA6,  //D12
  PA5,  //D13 - LD2
  PB9,  //D14
  PB8,  //D15
// ST Morpho
// CN7 Left Side
  PC10, //D16
  PC12, //D17
  NC_1, //D18 - BOOT0
  PA13, //D19 - SWD
  PA14, //D20 - SWD
  PA15, //D21
  PB7,  //D22
  PC13, //D23 - USER_BTN
  PC14, //D24 - NC by default SB49 opened
  PC15, //D25 - NC by default SB48 opened
  PH0,  //D26 - NC by default SB55 opened
  PH1,  //D27
  PC2,  //D28
  PC3,  //D29
// CN7 Right Side
  PC11, //D30
  PD2,  //D31
// CN10 Left Side
  PC9,  //D32
// CN10 Right side
  PC8,  //D33
  PC6,  //D34
  PC5,  //D35
  PA12, //D36
  PA11, //D37
  PB12, //D38
  NC_2, //D39
  PB2,  //D40
  PB1,  //D41
  PB15, //D42
  PB14, //D43
  PB13, //D44
  PC4,  //D45
  PA0,  //D46/A0
  PA1,  //D47/A1
  PA4,  //D48/A2
  PB0,  //D49/A3
  PC1,  //D50/A4
  PC0,  //D51/A5
  // Duplicated pins in order to be aligned with PinMapADC
  PA7_2,//D52/A6  = D11
  PA6_2,//D53/A7  = D12
  PA5_2,//D54/A8  = D13
  PC2_2,//D55/A9  = D28
  PC3_2,//D56/A10 = D29
  PC5_2,//D57/A11 = D35
  PB1_2,//D58/A12 = D41
  PC4_2,//D59/A13 = D45
  PEND
};

enum {
  A_START_AFTER = D45,
  A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9,
  A10, A11, A12, A13,
  AEND
};

// On-board LED pin number
#define LED_BUILTIN             13
#define LED_LD2                 LED_BUILTIN
#define LED_GREEN               LED_BUILTIN

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM10

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

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
