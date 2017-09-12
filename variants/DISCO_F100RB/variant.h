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
// P1 connector
  PC13, //D0
  PC0,  //D1
  PC1,  //D2
  PC2,  //D3
  PC3,  //D4
  PA0,  //D5 - User button
  PA1,  //D6
  PA2,  //D7
  PA3,  //D8
  PA4,  //D9
  PA5,  //D10
  PA6,  //D11
  PA7,  //D12
  PC4,  //D13
  PC5,  //D14
  PB0,  //D15
  PB1,  //D16
  PB2,  //D17
// P2 connector
  PC6,  //D18
  PC7,  //D19
  PC8,  //D20 - LED blue
  PC9,  //D21 - LED green
  PA8,  //D22
  PA9,  //D23
  PA10, //D24
  PA11, //D25
  PA12, //D26
  PA13, //D27
  PA14, //D28
  PA15, //D29
  PC10, //D30
  PC11, //D31
  PC12, //D32
  PD2,  //D33
  PB3,  //D34
  PB4,  //D35
  PB5,  //D36 - I2C SCL
  PB6,  //D37 - I2C SDA
  PB7,  //D38
  PB8,  //D39
  PB9,  //D40
// P3 connector
  PB10, //D41
  PB11, //D42
  PB12, //D43 - SPI SS
  PB13, //D44 - SPI SCLK
  PB14, //D45 - SPI MISO
  PB15, //D46 - SPI MOSI
  // Duplicated pins in order to be aligned with PinMap_ADC
  PC0_2,//D47/A0 = D0
  PC1_2,//D48/A1 = D1
  PC2_2,//D49/A2 = D2
  PC3_2,//D50/A3 = D3
  PA0_2,//D51/A4 = D4
  PA1_2,//D52/A5 = D5
  PA2_2,//D53/A6 = D6
  PA3_2,//D54/A7 = D7
  PA4_2,//D55/A8 = D8
  PA5_2,//D56/A9 = D9
  PA6_2,//D57/A10 = D10
  PA7_2,//D58/A11 = D11
  PC4_2,//D59/A12 = D12
  PC5_2,//D60/A13 = D13
  PB0_2,//D61/A14 = D14
  PB1_2,//D62/A15 = D15
  PEND
};

enum {
  A_START_AFTER = D46,
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
#define LED_BUILTIN             21
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                20

//On-board user button
#define USER_BTN                5

//SPI definitions
#define SS                      43
#define SS1                     40
#define SS2                     41
#define SS3                     42
#define MOSI                    46
#define MISO                    45
#define SCK                     44

//I2C Definitions
#define SDA                     38
#define SCL                     37

//Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM15
#define TIMER_UART_EMULATED     TIM16

//Do not use basic timer: OC is required
#define TIMER_SERVO             TIM17  //TODO: advanced-control timers don't work

#define DEBUG_UART              ((USART_TypeDef *) USART2)

// Serial Pin Firmata
#define PIN_SERIAL_RX           8
#define PIN_SERIAL_TX           7
#define PIN_SERIAL1_RX          24
#define PIN_SERIAL1_TX          23
#define PIN_SERIAL2_RX          42
#define PIN_SERIAL2_TX          41

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
 #define SERIAL_PORT_MONITOR    Serial
 #define SERIAL_PORT_HARDWARE   Serial
 #endif

#endif /* _VARIANT_ARDUINO_STM32_ */
