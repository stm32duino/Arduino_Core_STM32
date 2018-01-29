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

enum {
//P1 connector Right side
  PC0,  //D0
  PC2,  //D1
  PA0,  //D2
  PA2,  //D3
  PA4,  //D4
  PA6,  //D5
  PC4,  //D6
  PB0,  //D7
  PB2,  //D8
  PE8,  //D9
  PE10, //D10
  PE12, //D11
  PE14, //D12
  PB10, //D13
  PB12, //D14
  PB14, //D15
  PD8,  //D16
  PD10, //D17
  PD12, //D18
  PD14, //D19
//P2 connector Left side
  PH0,  //D20
  PC14, //D21
  PE6,  //D22
  PE4,  //D23
  PE2,  //D24
  PE0,  //D25
  PB8,  //D26
  PB6,  //D27
  PB4,  //D28
  PD7,  //D29
  PD5,  //D30
  PD3,  //D31
  PD1,  //D32
  PC12, //D33
  PC10, //D34
  PA10, //D35
  PA8,  //D36
  PC8,  //D37
  PC6,  //D38
//P1 Connector Left Side
  PC1,  //D39
  PC3,  //D40
  PA1,  //D41
  PA3,  //D42
  PA5,  //D43
  PA7,  //D44
  PC5,  //D45
  PB1,  //D46
  PE7,  //D47
  PE9,  //D48
  PE11, //D49
  PE13, //D50
  PE15, //D51
  PB11, //D52
  PB13, //D53
  PB15, //D54
  PD9,  //D55
  PD11, //D56
  PD13, //D57
  PD15, //D58
//P2 connector Right side
  PH1,  //D59
  PC15, //D60
  PC13, //D61
  PE5,  //D62
  PE3,  //D63
  PE1,  //D64
  PB9,  //D65
  PB7,  //D66
  PB5,  //D67
  PB3,  //D68
  PD6,  //D69
  PD4,  //D70
  PD2,  //D71
  PD0,  //D72
  PC11, //D73
  PA15, //D74
  PA13, //D75
  PA9,  //D76
  PC9,  //D77
  PC7,  //D78
//Duplicated to have A0-A5 as F407 do not have Uno like connector
// and to be aligned with PinMap_ADC
  PC2_2,//D79/A0 = D1
  PC4_2,//D80/A1 = D6
  PB0_2,//D81/A2 = D7
  PC1_2,//D82/A3 = D39
  PC3_2,//D83/A4 = D40
  PA1_2,//D84/A5 = D41
  PC5_2,//D85/A6 = D45
  PB1_2,//D86/A7 = D46
  PEND
};

// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        87
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       8
#define NUM_ANALOG_FIRST        79

// On-board LED pin number
#define LED_BUILTIN             PD12
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PD15
#define LED_RED                 PD14
#define LED_ORANGE              PD13

// On-board user button
#define USER_BTN                2

// SPI Definitions
#define PIN_SPI_SS2             14
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            5
#define PIN_SPI_SCK             PA5

// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB8

// Timer Definitions
// Do not use timer used by PWM pin. See PinMap_PWM.
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA3
#define PIN_SERIAL_TX           PA2

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
#define SERIAL_PORT_MONITOR     Serial // Require connections for ST-LINK VCP on U2 pin 12 and 13.
                                   // See UM §6.1.3 ST-LINK/V2-A VCP configuration)
#define SERIAL_PORT_HARDWARE_OPEN  Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
