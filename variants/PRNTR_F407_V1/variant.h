/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
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

#define PE0    0
#define PE1    1
#define PE2    2
#define PE3    3
#define PE4    4
#define PE5    5
#define PE6    6
#define PE7    7
#define PE8    8
#define PE9    9
#define PE10   10
#define PE11   11
#define PE12   12
#define PE13   13
#define PE14   14
#define PE15   15

#define PB0    16
#define PB1    17
#define PB2    18
#define PB3    19
#define PB4    20
#define PB5    21
#define PB6    22
#define PB7    23
#define PB8    24
#define PB9    25
#define PB10   26
#define PB11   27
#define PB12   28
#define PB13   29
#define PB14   30
#define PB15   31

#define PC0    32
#define PC1    33
#define PC2    34
#define PC3    35
#define PC4    36
#define PC5    37
#define PC6    38
#define PC7    39
#define PC8    40
#define PC9    41
#define PC10   42
#define PC11   43
#define PC12   44
#define PC13   45
#define PC14   46
#define PC15   47

#define PD0    48
#define PD1    49
#define PD2    50
#define PD3    51
#define PD4    52
#define PD5    53
#define PD6    54
#define PD7    55
#define PD8    56
#define PD9    57
#define PD10   58
#define PD11   59
#define PD12   60
#define PD13   61
#define PD14   62
#define PD15   63

#define PA0    64
#define PA1    65
#define PA2    66
#define PA3    67
#define PA4    68
#define PA5    69
#define PA6    70
#define PA7    71
#define PA8    72
#define PA9    73
#define PA10   74
#define PA11   75
#define PA12   76
#define PA13   77
#define PA14   78
#define PA15   79

#define EXP1_1  PE0
#define EXP1_2  PE1
#define EXP1_3  PE2
#define EXP1_4  PE3
#define EXP1_5  PE4
#define EXP1_6  PE5
#define EXP1_7  PE6
//      EXP1_8  5V
//      EXP1_9  GND
//      EXP1_10 3.3V

#define EXP2_1  PA3
#define EXP2_2  PA4
#define EXP2_3  PA5
#define EXP2_4  PA6
#define EXP2_5  PA7
#define EXP2_6  PA8
#define EXP2_7  PA15
//      EXP2_8  5V
//      EXP2_9  GND
//      EXP2_10 12-24V

#define EXP3_1  PD5  // UART2_TX
#define EXP3_2  PC2  // SPI2_MISO
#define EXP3_3  PD6  // UART2_RX
#define EXP3_4  PC3  // SPI2_MOSI
#define EXP3_5  PB9  // I2C_SDA
#define EXP3_6  PB10 // SPI2_CLK
#define EXP3_7  PB8  // I2C_SCL
//      EXP3_8  3.3V
//      EXP3_9  GND
//      EXP3_10 5V

#define EXP4_1  PA4
#define EXP4_2  PB4  // SPI_MISO
#define EXP4_3  PA5
#define EXP4_4  PB5  // SPI_MOSI
#define EXP4_5  PC1  // !EN_MOTORS
#define EXP4_6  PB3  // SPI_CLK
//      EXP4_7  12-24V
//      EXP4_8  3.3V
//      EXP4_9  GND
//      EXP4_10 5V

// This must be a literal
#define NUM_DIGITAL_PINS        80
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       8
#define NUM_ANALOG_FIRST        64

// On-board LED pin number
#define LED_BUILTIN             PB2
#define LED_GREEN               LED_BUILTIN

// On-board user button
//#define USER_BTN                -1

// SPI Definitions
//#define PIN_SPI_SS2             -1
#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PB3

// I2C Definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
// Do not use timer used by PWM pin. See PinMap_PWM.
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    1 //Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9

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
#define SERIAL_PORT_HARDWARE    Serial1
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
