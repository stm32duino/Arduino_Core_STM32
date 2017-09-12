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

#include "Arduino.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
#include "PeripheralPins.h"

extern const PinName digitalPin[];

enum {
  PC7,  //D0
  PC6,  //D1
  PG6,  //D2
  PB4,  //D3
  PG7,  //D4
  PI0,  //D5
  PH6,  //D6
  PI3,  //D7
  PI2,  //D8
  PA15, //D9
  PA8,  //D10
  PB15, //D11
  PB14, //D12
  PI1,  //D13
  PB9,  //D14
  PB8,  //D15
  PA0,  //D16/A0
  PF10, //D17/A1
  PF9,  //D18/A2
  PF8,  //D19/A3
  PF7,  //D20/A4
  PF6,  //D21/A5
  PI11, //D22 User btn
  PB7,  //D23 ST-Link Rx
  PA9,  //D24 ST-Link Tx
  PEND
};

enum {
  A_START_AFTER = D15,
  A0,  A1,  A2,  A3,  A4,  A5,
  AEND
};

//ADC resolution is 12bits
#define ADC_RESOLUTION          12
#define DACC_RESOLUTION         12

//PWR resolution
#define PWM_RESOLUTION          8
#define PWM_FREQUENCY           1000
#define PWM_MAX_DUTY_CYCLE      255

//On-board LED pin number
#define LED_BUILTIN             13
#define LED_GREEN               LED_BUILTIN

//On-board user button
#define USER_BTN                22


//SPI definitions
#define SS                      10
#define SS1                     4
#define SS2                     7
#define SS3                     8
#define MOSI                    11
#define MISO                    12
#define SCK                     13

//I2C Definitions
#define SDA                     14
#define SCL                     15

//Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6
#define TIMER_UART_EMULATED     TIM7

//Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

#define DEBUG_UART              ((USART_TypeDef *) USART1)

// UART Emulation
//#define UART_EMUL_RX            PX_n
//#define UART_EMUL_TX            PX_n

// Serial Pin Firmata
#define PIN_SERIAL_RX           23
#define PIN_SERIAL_TX           24
#define PIN_SERIAL1_RX          0
#define PIN_SERIAL1_TX          1
#define PIN_SERIAL2_RX          21
#define PIN_SERIAL2_TX          20

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;

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
#define SERIAL_PORT_HARDWARE  Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
