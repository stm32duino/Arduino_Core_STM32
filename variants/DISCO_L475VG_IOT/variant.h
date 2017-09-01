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
// CN3 connector
  PA1,  //D0
  PA0,  //D1
  PD14, //D2
  PB0,  //D3
  PA3,  //D4
  PB4,  //D5
  PB1,  //D6
  PA4,  //D7
// CN1 connector
  PB2,  //D8
  PA15, //D9
  PA2,  //D10
  PA7,  //D11
  PA6,  //D12
  PA5,  //D13
  PB9,  //D14
  PB8,  //D15
// Not on connector
  PB14, //D16
  PC13, //D17
// CN9 USB OTG FS connector
  PA9,  //D18
  PA10, //D19
  PA11, //D20
  PA12, //D21
  PD12, //D22
  PE3,  //D23
// CN10 PMOD connector
  PD0,  //D24
  PD1,  //D25
  PD2,  //D26
  PD3,  //D27
  PD4,  //D28
  PD5,  //D29
  PD6,  //D30
// Sensors / modules pins
  PA8,  //D31
  PB5,  //D32
  PB10, //D33
  PB11, //D34
  PB12, //D35
  PB13, //D36
  PB15, //D37
  PC6,  //D38
  PC7,  //D39
  PC8,  //D40
  PC9,  //D41
  PC10, //D42
  PC11, //D43
  PC12, //D44
  PD7,  //D45
  PD8,  //D46
  PD9,  //D47
  PD10, //D48
  PD11, //D49
  PD13, //D50
  PD15, //D51
  PE0,  //D52
  PE1,  //D53
  PE2,  //D54
  PE4,  //D55
  PE5,  //D56
  PE6,  //D57
  PE7,  //D58
  PE8,  //D59
  PE9,  //D60
  PE10, //D61
  PE11, //D62
  PE12, //D63
  PE13, //D64
  PE14, //D65
  PE15, //D66
// CN4 connector
  PC5,  //D67/A0
  PC4,  //D68/A1
  PC3,  //D69/A2
  PC2,  //D70/A3
  PC1,  //D71/A4
  PC0,  //D72/A5
// Duplicated pins in order to be aligned with PinMap_ADC
  PA1_2,  //D73/A6
  PA0_2,  //D74/A7
  PB0_2,  //D75/A8
  PA3_2,  //D76/A9
  PB1_2,  //D77/A10
  PA4_2,  //D78/A11
  PA2_2,  //D79/A12
  PA7_2,  //D80/A13
  PA6_2,  //D81/A14
  PA5_2,  //D82/A15
  PEND
};

enum {
  A_START_AFTER = D66,
  A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9,
  A10, A11, A12, A13, A14, A15,
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
#define LED1                    LED_BUILTIN
#define LED2                    16
#define LED3                    41
#define LED4                    LED3

//On-board user button
#define USER_BTN                17


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
// #define UART_EMUL_RX            PB13
// #define UART_EMUL_TX            PB14

// Serial Pin Firmata
#define PIN_SERIAL_RX           0
#define PIN_SERIAL_TX           1
#define PIN_SERIAL1_RX          2
#define PIN_SERIAL1_TX          8

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern HardwareSerial Serial;
extern HardwareSerial Serial1;

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
