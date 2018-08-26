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

// CN3 connector
#define  PA1    0
#define  PA0    1
#define  PD14   2
#define  PB0    3
#define  PA3    4
#define  PB4    5
#define  PB1    6
#define  PA4    7
// CN1 connector
#define  PB2    8
#define  PA15   9
#define  PA2    10
#define  PA7    11
#define  PA6    12
#define  PA5    13
#define  PB9    14
#define  PB8    15
// Not on connector
#define  PB14   16
#define  PC13   17
// ST-LINK
#define  PB6    18
#define  PB7    19
// CN9 USB OTG FS connector
#define  PA9    20
#define  PA10   21
#define  PA11   22
#define  PA12   23
#define  PD12   24
#define  PE3    25
// CN10 PMOD connector
#define  PD0    26
#define  PD1    27
#define  PD2    28
#define  PD3    29
#define  PD4    30
#define  PD5    31
#define  PD6    32
// Sensors / modules pins
#define  PA8    33
#define  PB5    34
#define  PB10   35
#define  PB11   36
#define  PB12   37
#define  PB13   38
#define  PB15   39
#define  PC6    40
#define  PC7    41
#define  PC8    42
#define  PC9    43
#define  PC10   44
#define  PC11   45
#define  PC12   46
#define  PD7    47
#define  PD8    48
#define  PD9    49
#define  PD10   50
#define  PD11   51
#define  PD13   52
#define  PD15   53
#define  PE0    54
#define  PE1    55
#define  PE2    56
#define  PE4    57
#define  PE5    58
#define  PE6    59
#define  PE7    60
#define  PE8    61
#define  PE9    62
#define  PE10   63
#define  PE11   64
#define  PE12   65
#define  PE13   66
#define  PE14   67
#define  PE15   68
// CN4 connector
#define  PC5    69
#define  PC4    70
#define  PC3    71
#define  PC2    72
#define  PC1    73
#define  PC0    74
// Duplicated pins in order to be aligned with PinMap_ADC
#define  PA1_2   75
#define  PA0_2   76
#define  PB0_2   77
#define  PA3_2   78
#define  PB1_2   79
#define  PA4_2   80
#define  PA2_2   81
#define  PA7_2   82
#define  PA6_2   83
#define  PA5_2   84
#define  PEND    85

// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        85
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       16
#define NUM_ANALOG_FIRST        69

// On-board LED pin number
#define LED_BUILTIN             13
#define LED1                    LED_BUILTIN
#define LED2                    PB14
#define LED3                    PC9
#define LED4                    LED3

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    1 //Connected to ST-Link
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PB7
#define PIN_SERIAL_TX           PB6

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
