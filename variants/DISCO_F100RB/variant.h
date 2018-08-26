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

// P1 connector
#define PC13 0
#define PC0  1  // A0
#define PC1  2  // A1
#define PC2  3  // A2
#define PC3  4  // A3
#define PA0  5  // A4/User button
#define PA1  6  // A5
#define PA2  7  // A6
#define PA3  8  // A7
#define PA4  9  // A8
#define PA5  10 // A9
#define PA6  11 // A10
#define PA7  12 // A11
#define PC4  13 // A12
#define PC5  14 // A13
#define PB0  15 // A14
#define PB1  16 // A15
#define PB2  17
// P2 connector
#define PC6  18
#define PC7  19
#define PC8  20 // LED blue
#define PC9  21 // LED green
#define PA8  22
#define PA9  23
#define PA10 24
#define PA11 25
#define PA12 26
#define PA13 27
#define PA14 28
#define PA15 29
#define PC10 30
#define PC11 31
#define PC12 32
#define PD2  33
#define PB3  34
#define PB4  35
#define PB5  36 // I2C SCL
#define PB6  37 // I2C SDA
#define PB7  38
#define PB8  39
#define PB9  40
// P3 connector
#define PB10 41
#define PB11 42
#define PB12 43 // SPI SS
#define PB13 44 // SPI SCLK
#define PB14 45 // SPI MISO
#define PB15 46 // SPI MOSI

// This must be a literal
#define NUM_DIGITAL_PINS        63
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       16
#define NUM_ANALOG_FIRST        47

// On-board LED pin number
#define LED_BUILTIN             PC9
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PC8

// On-board user button
#define USER_BTN                5

// SPI Definitions
#define PIN_SPI_SS              PB12
#define PIN_SPI_SS1             PB9
#define PIN_SPI_SS2             PB10
#define PIN_SPI_SS3             PB11
#define PIN_SPI_MOSI            PB15
#define PIN_SPI_MISO            PB14
#define PIN_SPI_SCK             PB13

// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM15

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM17  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           8
#define PIN_SERIAL_TX           7

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
