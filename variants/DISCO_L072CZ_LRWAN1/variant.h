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

#define  PA3   0
#define  PA2   1
#define  PA10  2
#define  PB13  3
#define  PB5   4
#define  PB7   5
#define  PB2   6
#define  PA8   7
#define  PA9   8
#define  PB12  9
#define  PB6   10
#define  PB15  11
#define  PB14  12
#define  PB13_2 13
#define  PB9   14
#define  PB8   15
// Connector CN2
#define  NC_1  16
#define  PA13  17
#define  PA14  18
#define  PH1   19
#define  PH0   20
// Connector CN3
#define  PA1   21
#define  PC2   22
#define  PC1   23
#define  PA12  24
#define  PA11  25
#define  PA0   26
#define  PA0_2 27
#define  PA4   28
#define  PA4_2 29
#define  PB9_2 30
#define  PB8_2 31
#define  PA5   32
#define  PC0   33
#define  PA7   34
#define  PA6   35
#define  PB3   36
#define  PA15  37
#define  PB4   38
#define  PB1   39
#define  PB0   40
#define  PC13  41
#define  PEND  42


// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        42
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       7
#define NUM_ANALOG_FIRST        26

// On-board LED pin number
#define LED_BUILTIN             PA5
#define LED_LD2                 LED_BUILTIN
#define LED_GREEN2              LED_BUILTIN
#define LED_GREEN               4
#define LED_LD1                 LED_GREEN
#define LED_BLUE                10
#define LED_LD3                 LED_BLUE
#define LED_RED                 5
#define LED_LD4                 LED_RED

// On-board user button
#define USER_BTN                6

// LORA
#define RADIO_RESET_PORT        PC0
#define RADIO_MOSI_PORT         PA7
#define RADIO_MISO_PORT         PA6
#define RADIO_SCLK_PORT         PB3
#define RADIO_NSS_PORT          PA15
#define RADIO_DIO_0_PORT        PB4
#define RADIO_DIO_1_PORT        PB1
#define RADIO_DIO_2_PORT        PB0
#define RADIO_DIO_3_PORT        PC13
#define RADIO_DIO_4_PORT        PA5
#define RADIO_DIO_5_PORT        PA4

//Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM22

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
