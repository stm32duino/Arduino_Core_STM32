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

#define PB9  0
#define PB8  1
#define PB7  2
#define PA2  A0
#define PA3  A1
#define PA0  A2
#define PB3  6
#define PB10 7
#define PB12 8
#define PB13 9
#define PB14 10
#define PA7  A3
#define PB4  12
#define PA5  A4
#define PA10 14
#define PA15 15
#define PA4  A5
#define PC3  A6
#define PC5  A7
#define PC6  19
#define PC7  20

#define PA13 21 // LED_RED
#define PA14 22 // LED_GREEN
#define PB0  23 // LED_YELLOW
#define PB1  24 // LED_BLUE

#define PC13 25 // USR_BTN

#define PA11 26 // USB D-, CAN_RX
#define PA12 27 // USB D+, CAN_TX

#define PC14 28 // OSC32_IN
#define PC15 29 // OSC32_OUT
#define PH0  30 // OSC_IN
#define PH1  31 // OSC_OUT

#define PA6  32 // SDIO CMD
#define PB6  33 // SDIO D0 / QSPI BK1 NCS
#define PA8  34 // SDIO D1
#define PA9  35 // SDIO D2
#define PB5  36 // SDIO D3
#define PB15 37 // SDIO CK

#define PC9  38 // QSPI BK1 IO0
#define PC10 39 // QSPI BK1 IO1
#define PC8  40 // QSPI BK1 IO2
#define PA1  41 // QSPI BK1 IO3
#define PB2  42 // QSPI CLK

// This must be a literal
#define NUM_DIGITAL_PINS        43
#define NUM_ANALOG_INPUTS       8

// PYBSTICK26 Sx pinout
#define S3  PB9
#define S5  PB8
#define S7  PB7
#define S8  PA2
#define S10 PA3
#define S11 PB3
#define S12 PA0
#define S13 PB10
#define S13A  PC3
#define S15 PB12
#define S15A  PC5
#define S16 PB13
#define S16A  PC6
#define S18 PB14
#define S18A  PC7
#define S19 PA7
#define S21 PAB4
#define S22 PA10
#define S23 PA5
#define S24 PA15
#define S26 PA4

// On-board LED pin number
#define LED_GREEN               PA14
#define LED_RED                 PA13
#define LED_YELLOW              PB0
#define LED_BLUE                PB1

#define LED_BUILTIN             LED_RED

// On-board user buttons
#define USER_BTN                PC13
#define USER_BTN_2              PB6

// SPI definitions
#define PIN_SPI_SS              PA4
#define PIN_SPI_SS1             PA4
#define PIN_SPI_SS2             PA15
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PA5

// I2C definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    2

// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA3
#define PIN_SERIAL_TX           PA2

/* Extra HAL definitions */
#define HAL_SD_MODULE_ENABLED
#define HAL_QSPI_MODULE_ENABLED
#define HSE_VALUE               16000000U

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
  #define SERIAL_PORT_USBVIRTUAL  SerialUSB
  #define SERIAL_PORT_HARDWARE    Serial2
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
