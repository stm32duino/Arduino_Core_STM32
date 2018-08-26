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
#define  PC13  0
#define  PC0   1
#define  PC1   2
#define  PC2   3
#define  PC3   4
#define  PA0   5
#define  PA1   6
#define  PA2   7
#define  PA3   8
#define  PA4   9
#define  PA5   10
#define  PA6   11
#define  PA7   12
#define  PC4   13
#define  PC5   14
#define  PB0   15
#define  PB1   16
#define  PB2   17
// P2 connector
#define  PC6   18
#define  PC7   19
#define  PC8   20
#define  PC9   21
#define  PA8   22
#define  PA9   23
#define  PA10  24
#define  PA11  25
#define  PA12  26
#define  PA13  27
#define  PA14  28
#define  PA15  29
#define  PC10  30
#define  PC11  31
#define  PC12  32
#define  PD2   33
#define  PB3   34
#define  PB4   35
#define  PB5   36
#define  PB6   37
#define  PB7   38
#define  PB8   39
#define  PB9   40
// P3 connector
#define  PB10  41
#define  PB11  42
#define  PB12  43
#define  PB13  44
#define  PB14  45
#define  PB15  46
  // Duplicated pins in order to be aligned with PinMap_ADC
#define  PC0_2  47
#define  PC1_2  48
#define  PC2_2  49
#define  PC3_2  50
#define  PA0_2  51
#define  PA1_2  52
#define  PA2_2  53
#define  PA3_2  54
#define  PA4_2  55
#define  PA5_2  56
#define  PA6_2  57
#define  PA7_2  58
#define  PC4_2  59
#define  PC5_2  60
#define  PB0_2  61
#define  PB1_2  62
#define  PEND   63

// This must be a literal with the same value as PEND
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
