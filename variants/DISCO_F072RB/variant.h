/*
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
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

// USB USER CN2
// By default, SB20,23 (USB-USER) are OFF.
// So PA11,12 are not available.
// If ON and R12,13 removed,
// #define USB_REMOVED
// to get PA11,12 available.

// Linear touch sensor
// By default, SB27,28,29,30,31,32 (touch sensor) are OFF.
// So PA2,3,6,7 and PB0,1 are not available.
// If ON and R38,39,40 and C26,27,28 are removed,
// #define TSC_REMOVED
// to get PA2,3,6,7 and PB0,1 available.

// P2 connector Right side (top view)
#define PB9  0
#define PB8  1
#define PB7  2
#define PB6  3
#define PB5  4
#define PB4  5
#define PB3  6
#define PD2  7
#define PC12 8
#define PC11 9
#define PC10 10
#define PA15 11
#define PA14 12
#define PA13 13
#define PA12 14 // SB20 (default OFF): USB_DP
#define PA11 15 // SB23 (default OFF): USB_DM
#define PA10 16
#define PA9  17
#define PA8  18
#define PC9  19 // LED_GREEN (LD4)
#define PC8  20 // LED_ORANGE (LD3)
#define PC7  21 // LED_BLUE (LD6)
#define PC6  22 // LED_RED (LD5)
#define PB15 23 // SPI2_MOSI (L3GD20)
#define PB14 24 // SPI2_MISO (L3GD20)
#define PB13 25 // SPI2_SCK (L3GD20)
// P1 connector Left side (top view)
#define PC13 26
#define PC14 27
#define PC15 28
#define PF0  29
#define PF1  30
#define PC0  31 // A0 - NCS_MEMS_SPI (L3GD20)
#define PC1  32 // A1 - MEMS INT1 (L3GD20)
#define PC2  33 // A2 - MEMS INT2 (L3GD20)
#define PC3  34 // A3
#define PA0  35 // A4 - USER_BTN
#define PA1  36 // A5
#define PA2  37 // A6 - SB27 (default OFF): TS_G1_IO3
#define PA3  38 // A7 - SB28 (default OFF): TS_G1_IO4
#define PA4  39 // A8
#define PA5  40 // A9
#define PA6  41 // A10 - SB29 (default OFF): TS_G2_IO3
#define PA7  42 // A11 - SB30 (default OFF): TS_G2_IO4
#define PC4  43 // A12
#define PC5  44 // A13 - Ext Reset
#define PB0  45 // A14 - SB31 (default OFF): TS_G3_IO2
#define PB1  46 // A15 - SB32 (default OFF): TS_G3_IO3
#define PB2  47
#define PB10 48 // I2C2 SCL: Extension / RF EEprom Connector
#define PB11 49 // I2C2 SDA: Extension / RF EEprom Connector
#define PB12 50

// This must be a literal
#define NUM_DIGITAL_PINS        51
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       16
#define NUM_ANALOG_FIRST        31

//On-board LED pin number
#define LED_BUILTIN             PC9
#define LED_GREEN               LED_BUILTIN
#define LED_ORANGE              PC8
#define LED_BLUE                PC7
#define LED_RED                 PC6

//On-board user button
#define USER_BTN                PA0

// SPI definitions
// SPI1 is used
#define PIN_SPI_SS              PA4
#define PIN_SPI_SS1             PC4
#define PIN_SPI_SS2             PB12
#define PIN_SPI_SS3             PB6
#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PB3

// I2C Definitions
// I2C1 is used
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6

//Do not use basic timer: OC is required
#define TIMER_SERVO             TIM3  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    1 // USART 1

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
#define SERIAL_PORT_HARDWARE    Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
