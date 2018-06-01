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
  //P1 connector Right side (bottom view)
  PC13,  //D0
  PC14,  //D1
  PC15, //D2
  PF0,  //D3 
  PF1,  //D4
  PC0,  //D5
  PC1, //D6 
  PC2,  //D7
  PC3,  //D8
  PA0,  //D9
  PA1,  //D10
  PA2,  //D11
  PA3,  //D12
  PF4,  //D13
  PF5,  //D14
  PA4,  //D15
  PA5, //D16
  PA6, //D17
  PA7,  //D18
  PC4,  //D19
  PC5, //D20 
  PB0, //D21 
  PB1, //D22
  PB2,  //D23
  PB10, //D24
  PB11, //D25
  PB12, //D26
  //P2 connector Left side (bottom view)
  PB9,  //D27
  PB8,  //D28
  PB7,  //D29
  PB6,  //D30
  PB5, //D31
  PB4,  //D32
  PB3,  //D33
  PD2,  //D34
  PC12,  //D35
  PC11,  //D36
  PC10, //D37
  PA15, //D38
  PA14, //D39
  PF7, //D40
  PF6,  //D41
  PA13,  //D42
  PA12, //D43
  PA11, //D44
  PA10, //D45
  PA9,  //D46
  PA8,  //D47
  PC9,  //D48
  PC8,  //D49
  PC7,  //D50
  PC6,  //D51
  PB15,  //D52
  PB14,  //D53
  PB13,  //D54
  // Duplicated pins in order to be aligned with PinMap_ADC
  PC_0_A,  //D55/A0 = D5
  PC_1_A,  //D56/A1 = D6
  PC_2_A,  //D57/A2 = D7
  PC_3_A,  //D58/A3 = D8
  PA_0_A,  //D59/A4 = D9
  PA_1_A,  //D60/A5 = D10
  PA_2_A,  //D61/A6 = D11
  PA_3_A,  //D62/A7 = D12
  PA_4_A,  //D63/A8 = D15
  PA_5_A,  //D64/A9 = D16
  PA_6_A,  //D65/A10= D17
  PA_7_A,  //D66/A11= D18
  PC_4_A, //D67/A12 = D19
  PC_5_A, //D68/A13 = D20
  PB_0_A, //D69/A14 = D21
  PB_1_A,  //D70/A15 = D22
  PEND
};

// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        71
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       16
#define NUM_ANALOG_FIRST        55

//ADC resolution is 12bits
#define ADC_RESOLUTION          12

//PWR resolution
#define PWM_RESOLUTION          8
#define PWM_FREQUENCY           1000
#define PWM_MAX_DUTY_CYCLE      255

//On-board LED pin number
#define LED_BUILTIN             48
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                49   

//On-board user button
#define USER_BTN                9


//SPI definitions
// SPI1 is used
#define PIN_SPI_SS                      30 //PB6
#define PIN_SPI_SS1                     31 //PB5
#define PIN_SPI_SS2                     47 //PA8
#define PIN_SPI_SS3                     46 //PA9
#define PIN_SPI_MOSI                    18 //PA7
#define PIN_SPI_MISO                    17 //PA6
#define PIN_SPI_SCK                     16 //PA5

//I2C Definitions
// I2C1 is used
#define PIN_WIRE_SDA                     27 //PB9
#define PIN_WIRE_SCL                     28 //PB8

//Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6

//Do not use basic timer: OC is required
#define TIMER_SERVO             TIM3  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    1 // USART 1 Connected to ST-Link
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           45// PA10
#define PIN_SERIAL_TX           46 // PA9

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
