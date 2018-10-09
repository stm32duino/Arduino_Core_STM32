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
  PG9,  //D0
  PG14, //D1
  PF15, //D2
  PE13, //D3
  PF14, //D4
  PE11, //D5
  PE9,  //D6
  PF13, //D7
  PF12, //D8
  PD15, //D9
  PD14, //D10
  PA7,  //D11
  PA6,  //D12
  PA5,  //D13
  PB9,  //D14
  PB8,  //D15
  PC6,  //D16
  PB15, //D17
  PB13, //D18
  PB12, //D19
  PA15, //D20
  PC7,  //D21
  PB5,  //D22
  PB3,  //D23
  PA4,  //D24
  PB4,  //D25
  PB6,  //D26
  PB2,  //D27
  PD13, //D28
  PD12, //D29
  PD11, //D30
  PE2,  //D31
  PA0,  //D32
  PB0,  //D33 - LED_GREEN
  PE0,  //D34
  PB11, //D35
  PB10, //D36
  PE15, //D37
  PE14, //D38
  PE12, //D39
  PE10, //D40
  PE7,  //D41
  PE8,  //D42
  PC8,  //D43
  PC9,  //D44
  PC10, //D45
  PC11, //D46
  PC12, //D47
  PD2,  //D48
  PG2,  //D49
  PG3,  //D50
  PD7,  //D51
  PD6,  //D52
  PD5,  //D53
  PD4,  //D54
  PD3,  //D55
  PE2_2,//D56
  PE4,  //D57
  PE5,  //D58
  PE6,  //D59
  PE3,  //D60
  PF8,  //D61
  PF7,  //D62
  PF9,  //D63
  PG1,  //D64
  PG0,  //D65
  PD1,  //D66
  PD0,  //D67
  PF0,  //D68
  PF1,  //D69
  PF2,  //D70
  PA7_2,//D71
  NC_1, //D72
  PB7,  //D73 - LED_BLUE
  PB14, //D74 - LED_RED
  PC13, //D75 - USER_BTN
  PD9,  //D76 - Serial Rx
  PD8,  //D77 - Serial Tx
  PA3,  //D78/A0
  PC0,  //D79/A1
  PC3,  //D80/A2
  PF3,  //D81/A3
  PF5,  //D82/A4
  PF10, //D83/A5
  PB1,  //D84/A6
  PC2,  //D85/A7
  PF4,  //D86/A8
  PF6,  //D87/A9
  // Duplicated pins in order to be aligned with PinMap_ADC
  PA7_3,  //D88/A10 = D11
  PA6_2,  //D89/A11 = D12
  PA5_2,  //D90/A12 = D13
  PA4_2,  //D91/A13 = D24
  PA0_2,  //D92/A14 = D32
  PF8_2,  //D93/A15 = D61
  PF7_2,  //D94/A16 = D62
  PF9_2,  //D95/A17 = D63
  PEND
};

// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        96
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       18
#define NUM_ANALOG_FIRST        78

// On-board LED pin number
#define LED_BUILTIN             PB0
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PB7
#define LED_RED                 PB14

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    3 //Connected to ST-Link

// Serial pin used for console (ex: stlink)
// Rerquired by Firmata
#define PIN_SERIAL_RX           PD9
#define PIN_SERIAL_TX           PD8

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
