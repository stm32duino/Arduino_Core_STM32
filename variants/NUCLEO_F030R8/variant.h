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

enum {
  PA3,  //D0
  PA2,  //D1
  PA10, //D2
  PB3,  //D3 - no PWM
  PB5,  //D4
  PB4,  //D5
  PB10, //D6 - no PWM
  PA8,  //D7
  PA9,  //D8
  PC7,  //D9
  PB6,  //D10
  PA7,  //D11
  PA6,  //D12
  PA5,  //D13
  PB9,  //D14
  PB8,  //D15
// ST Morpho
// CN7 Left Side
  PC10, //D16
  PC12, //D17
  PF6,  //D18
  PF7,  //D19
  PA13, //D20 - SWD
  PA14, //D21 - SWD
  PA15, //D22
  PB7,  //D23
  PC13, //D24
  PC14, //D25
  PC15, //D26
  PF0,  //D27
  PF1,  //D28
  PC2,  //D29
  PC3,  //D30
// CN7 Right Side
  PC11, //D31
  PD2,  //D32
// CN10 Left Side
  PC9,  //D33
// CN10 Right side
  PC8,  //D34
  PC6,  //D35
  PC5,  //D36
  PA12, //D37
  PA11, //D38
  PB12, //D39
  PB11, //D40
  PB2,  //D41
  PB1,  //D42
  PB15, //D43
  PB14, //D44
  PB13, //D45
  PC4,  //D46
  PF5,  //D47
  PF4,  //D48
  PA0,  //D49/A0
  PA1,  //D50/A1
  PA4,  //D51/A2
  PB0,  //D52/A3
  PC1,  //D53/A4
  PC0,  //D54/A5
  // Duplicated pins in order to be aligned with PinMap_ADC
  PA7_2,//D55/A6  = D11
  PA6_2,//D56/A7  = D12
  PC2_2,//D57/A8  = D29
  PC3_2,//D58/A9  = D30
  PC5_2,//D59/A10 = D36
  PC4_2,//D60/A11 = D46
  PEND
};

// This must be a literal with the same value as PEND
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
