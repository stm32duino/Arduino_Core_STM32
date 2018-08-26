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

#define PG9  0
#define PG14 1
#define PF15 2
#define PE13 3
#define PF14 4
#define PE11 5
#define PE9  6
#define PF13 7
#define PF12 8
#define PD15 9
#define PD14 10
#define PA7  11 // A10
#define PA6  12 // A11
#define PA5  13 // A12
#define PB9  14
#define PB8  15
#define PC6  16
#define PB15 17
#define PB13 18
#define PB12 19
#define PA15 20
#define PC7  21
#define PB5  22
#define PB3  23
#define PA4  24 // A13
#define PB4  25
#define PB6  26
#define PB2  27
#define PD13 28
#define PD12 29
#define PD11 30
#define PE2  31
#define PA0  32 // A14
#define PB0  33 // LED_GREEN
#define PE0  34
#define PB11 35
#define PB10 36
#define PE15 37
#define PE14 38
#define PE12 39
#define PE10 40
#define PE7  41
#define PE8  42
#define PC8  43
#define PC9  44
#define PC10 45
#define PC11 46
#define PC12 47
#define PD2  48
#define PG2  49
#define PG3  50
#define PD7  51
#define PD6  52
#define PD5  53
#define PD4  54
#define PD3  55
// 56 is PE2 (31)
#define PE4  57
#define PE5  58
#define PE6  59
#define PE3  60
#define PF8  61 // A15
#define PF7  62 // A16
#define PF9  63 // A17
#define PG1  64
#define PG0  65
#define PD1  66
#define PD0  67
#define PF0  68
#define PF1  69
#define PF2  70
// 71 is PA7 (11)
// 72 is NC
#define PB7  73 // LED_BLUE
#define PB14 74 // LED_RED
#define PC13 75 // USER_BTN
#define PD9  76 // Serial Rx
#define PD8  77 // Serial Tx
#define PA3  78 // A0
#define PC0  79 // A1
#define PC3  80 // A2
#define PF3  81 // A3
#define PF5  82 // A4
#define PF10 83 // A5
#define PB1  84 // A6
#define PC2  85 // A7
#define PF4  86 // A8
#define PF6  87 // A9

// This must be a literal
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
