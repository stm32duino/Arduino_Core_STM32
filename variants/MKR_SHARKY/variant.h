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

#define PB0  0
#define PB1  1
#define PA8  2
#define PA9  3
#define PA10 4
#define PA15 5
#define PE4  6
#define PB2  7
#define PB5  8
#define PB3  9
#define PB4  10
#define PB9  11
#define PB8  12
#define PB7  13
#define PB6  14
#define PH3  15 // BOOT0 / USR BTN

#define PA0  16 // A0
#define PA1  17 // A1
#define PA2  18 // A2
#define PA3  19 // A3
#define PA4  20 // A4
#define PA5  21 // A5
#define PA6  22 // A6
#define PA7  23 // A7 VBAT sense

// This must be a literal
#define NUM_DIGITAL_PINS        24
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       8
#define NUM_ANALOG_FIRST        16

// On-board LED pin number
#define LED                     PE4
#define LED1                    LED
#define LED_BUILTIN             LED

// On-board user button
// Note: use '_BTN' for SW1 and SW2 as they are register name of M24SR64-Y
#define SW1_BTN                 PH3
#define USER_BTN                SW1_BTN

// SPI Definitions
#define PIN_SPI_SS              PB2
#define PIN_SPI_SS1             PA15
#define PIN_SPI_SS2             PA4
#define PIN_SPI_SS3             PE4
#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PB3

// I2C Definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
#define TIMER_TONE              TIM16
#define TIMER_SERVO             TIM17

// UART Definitions
#define SERIAL_UART_INSTANCE    1

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PB7
#define PIN_SERIAL_TX           PB6

/* Extra HAL configuration */
#define HAL_HSEM_MODULE_ENABLED
#define PREFETCH_ENABLE         1U

// Only 512k provided for cpu1, so defined the FLASH_PAGE_NUMBER
// for EEPROM emulation to the last 512k pages.
#define FLASH_PAGE_NUMBER       127

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
#define SERIAL_PORT_HARDWARE  Serial1
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
