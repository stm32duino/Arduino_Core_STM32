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

#define PC5  0
#define PC4  1
#define PA10 2
#define PB3  3
#define PB5  4
#define PB4  5
#define PB14 6
#define PA8  7
#define PA9  8
#define PC7  9
#define PB0  10 // A6
#define PA7  11 // A7
#define PA6  12 // A8
#define PA5  13 // LED
#define PB9  14
#define PB8  15
// ST Morpho
// CN7 Left Side
#define PC10 16
#define PC12 17
#define PA14 18 // SWD
#define PD0  19
#define PD3  20
#define PA13 21 // SWD
#define PD4  22
#define PA15 23
#define PB7  24
#define PC13 25
#define PC14 26
#define PC15 27
#define PF0  28
#define PF1  29
#define PC2  30
#define PC3  31
// CN7 Right Side
#define PC11 32
#define PD2  33
#define PD1  34
#define PD5  35
// CN10 Left Side
#define PC9  36
// CN10 Right side
#define PC8  37
#define PC6  38
#define PA3  39
#define PD6  40
#define PA11 41
#define PA12 42
#define PC1  43
#define PC0  44
#define PB2  45 // A9
#define PB6  46
#define PB15 47
#define PB10 48 // A10
#define PB13 49
#define PA2  50
#define PD8  51
#define PD9  52
#define PA0  53 // A0
#define PA1  54 // A1
#define PA4  55 // A2
#define PB1  56 // A3
#define PB11 57 // A4
#define PB12 58 // A5

// This must be a literal
#define NUM_DIGITAL_PINS        64
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       11
#define NUM_ANALOG_FIRST        53

// On-board LED pin number
#define LED_BUILTIN             13
#define LED_GREEN               LED_BUILTIN

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA3
#define PIN_SERIAL_TX           PA2

/* Extra HAL modules */
#define HAL_DAC_MODULE_ENABLED

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
#define SERIAL_PORT_HARDWARE  Serial2
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
