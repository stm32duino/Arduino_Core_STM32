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

#define PA3  0
#define PA2  1
#define PC6  2
#define PA10 3
#define PC10 4
#define PA15 5
#define PA8  6
#define PC13 7
#define PC12 8
#define PA9  9
#define PA4  10 // PB10 (SB41 !SB42)
#define PA7  11
#define PA6  12
#define PA5  13
#define PB9  14
#define PB8  15
// ST Morpho
// CN7 Left Side
#define PB11 16
#define PC5  17
#define PA13 18 // SWD
#define PA14 19 // SWD
#define PC14 20
#define PC15 21
// CN7 Right Side
#define PB2  22
#define PE4  23
// CN10 Left Side
#define PC4  24 // SW1
// CN10 Right side
#define PB4  25
#define PB7  26
#define PA12 27
#define PA11 28
#define PB12 29
#define PB0  30 // LED2
#define PB1  31 // LED3
#define PB15 32 // PB4 (SB7 !SB9 !SB10) or PA9 (!SB7 !SB9 SB10)
#define PB14 33
#define PB13 34 // PB3 (!SB12 SB13)
#define PB6  35
#define PD0  36 // SW2
#define PD1  37 // SW3
#define PC0  38 // A0
#define PC1  39 // A1
#define PA1  40 // A2
#define PA0  41 // A3
#define PC3  42 // A4
#define PC2  43 // A5
// Not on connectors
#define PB5  44 // LED1
#define PB10 45
#define PC11 46

// This must be a literal
#define NUM_DIGITAL_PINS        47
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       6
#define NUM_ANALOG_FIRST        38

// On-board LED pin number
#define LED1                    PB5
#define LED2                    PB0
#define LED3                    PB1
#define LED_BUILTIN             LED1
#define LED_BLUE                LED1
#define LED_GREEN               LED2
#define LED_RED                 LED3

// On-board user button
// Note: use '_BTN' for SW1 and SW2 as they are register name of M24SR64-Y
#define SW1_BTN                 PC4 // PC13 (!SB47 SB48)
#define SW2_BTN                 PD0
#define SW3_BTN                 PD1
#define USER_BTN                SW1_BTN

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM16
#define TIMER_SERVO             TIM17

// UART Definitions
#define SERIAL_UART_INSTANCE    1 //Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PB7
#define PIN_SERIAL_TX           PB6

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
