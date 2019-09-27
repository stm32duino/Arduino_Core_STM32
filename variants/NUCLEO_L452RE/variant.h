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
#ifdef ARDUINO_NUCLEO_L452RE
#define PA3  0
#define PA2  1
#define PA10 2
#define PB3  3
#define PB5  4
#define PB4  5
#define PB10 6
#define PA8  7
#define PA9  8
#define PC7  9
#define PB6  10
#define PA7  11 // A6
#define PA6  12 // A7
#define PA5  13 // LED
#define PB9  14
#define PB8  15
// ST Morpho
// CN7 Left Side
#define PC10 16
#define PC12 17
#define PA13 18 // SWD
#define PA14 19 // SWD
#define PA15 20
#define PB7  21
#define PC13 22
#define PC14 23
#define PC15 24
#define PH0  25
#define PH1  26
#define PC2  27 // A8
#define PC3  28 // A9
// CN7 Right Side
#define PC11 29
#define PD2  30
// CN10 Left Side
#define PC9  31
// CN10 Right side
#define PC8  32
#define PC6  33
#define PC5  34 // A12
#define PA12 35
#define PA11 36
#define PB12 37
#define PB11 38
#define PB2  39
#define PB1  40 // A11
#define PB15 41
#define PB14 42
#define PB13 43
#define PC4  44 // A10
#define PA0  45 // A0
#define PA1  46 // A1
#define PA4  47 // A2
#define PB0  48 // A3
#define PC1  19 // A4
#define PC0  50 // A5
#else
#define PA10 0
#define PA9  1
#define PA12 2
#define PB3  3
#define PB5  4
#define PA15 5
#define PB10 6
#define PC7  7
#define PB6  8
#define PA8  9
#define PA11 10
#define PB15 11
#define PB14 12
#define PB13 13 // LED
#define PB7  14
#define PB8  15
// ST Morpho
// CN5 Left Side
#define PC10 16
#define PC12 17
#define PB12 18
#define PA13 19 // SWD
#define PA14 20 // SWD
#define PC13 21
#define PC14 22
#define PC15 23
#define PH0  24
#define PH1  25
#define PB4  26
#define PB9  27
// CN5 Right Side
#define PC11 28
#define PD2  29
// CN6 Left Side
#define PC9  30
// CN6 Right side
#define PC8  31
#define PC6  32
#define PC5  33
#define PB0  34 // A10
#define PB11 35
#define PB2  36
#define PB1  37 // A11
#define PA7  38 // A9
#define PA6  39 // A8
#define PA5  40 // A7
#define PA4  41 // A6
#define PC4  42 // A12
#define PA3  43
#define PA2  44
#define PA0  45 // A0
#define PA1  46 // A1
#define PC3  47 // A2
#define PC2  48 // A3
#define PC1  49 // A4
#define PC0  50 // A5
#endif

// This must be a literal
#ifdef ARDUINO_NUCLEO_L452RE
// This must be a literal
#define NUM_DIGITAL_PINS        56
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       11
#else
// This must be a literal
#define NUM_DIGITAL_PINS        58
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       13
#endif

#define NUM_ANALOG_FIRST        45

// On-board LED pin number
#define LED_BUILTIN             13
#define LED_GREEN               LED_BUILTIN

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Use TIM6 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM2

// UART Definitions
#ifdef ARDUINO_NUCLEO_L452RE
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link
#else
#define SERIAL_UART_INSTANCE    0 //Connected to ST-Link
#endif

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
