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
// Left Side
#define PD10  0
#define PD11  1
#define PB15  2
#define PD9   3
#define PB12  4
#define PD8   5
#define PB14  6
#define PB11  7
#define PE8   8
#define PB13  9
#define PB10 10
#define PE7  11
#define PE14 12
#define PE15 13
#define PE12 14
#define PE13 15
#define PE11 16
#define PE10 17
#define PE9  18
#define PB1  19
#define PB2  20
#define PC5  21
#define PB0  22
#define PA7  23
#define PC4  24
#define PA6  25
#define PA5  26
#define PA3  27
#define PA4  28
#define PC3  29
#define PA0  30
#define PA2  31
#define PA1  32
#define PD13 33
#define PD14 34
#define PC0  35
#define PC1  36
#define PC2  37
// Right Side
#define PA12 38
#define PA11 39
#define PA10 40
#define PD12 41
#define PC9  42
#define PA9  43
#define PA8  44
#define PC10 45
#define PC11 46
#define PC12 47
#define PD0  48
#define PD1  49
#define PD2  50
#define PD3  51
#define PD4  52
#define PD5  53
#define PB5  54
#define PB4  55
#define PB7  56
#define PB6  57
#define PB9  58
#define PB8  59
#define PE1  60
#define PE0  61
#define PE2  62
#define PE6  63
#define PE3  64
#define PE5  65
#define PB3  66
#define PE4  67
#define PD6  68
#define PD7  69
#define PC7  70
#define PC8  71
#define PD15 72
#define PC6  73
#define PC13 74
#define PA15 75

// This must be a literal
#define NUM_DIGITAL_PINS        92
// This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       16
#define NUM_ANALOG_FIRST        76

// On-board LED pin number
#define LED_D1                  PC13
#define LED_BUILTIN             LED_D1

// On-board user button
#define BTN_KEY                 PA15
#define USER_BTN                BTN_KEY

// Below SPI and I2C definitions already done in the core
// Could be redefined here if differs from the default one
// SPI Definitions

#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PB3

// I2C Definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM in PeripheralPins.c
#define TIMER_TONE              TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#define SERIAL_UART_INSTANCE    1 //ex: 2 for Serial2 (USART2)
// DEBUG_UART could be redefined to print on another instance than 'Serial'
//#define DEBUG_UART              ((USART_TypeDef *) U(S)ARTX) // ex: USART3
// DEBUG_UART baudrate, default: 9600 if not defined
//#define DEBUG_UART_BAUDRATE     x
// DEBUG_UART Tx pin name, default: the first one found in PinMap_UART_TX for DEBUG_UART
//#define DEBUG_PINNAME_TX        PX_n // PinName used for TX

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
