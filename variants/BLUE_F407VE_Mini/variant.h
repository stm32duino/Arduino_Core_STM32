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
// External (left to right)
// GND
// VBAT
// 5V
#define PE0  0
#define PE2  1
#define PE4  2
#define PE6  3
#define PC14 4  // OSC32_IN
#define PC0  5  // A8
#define PC2  6  // A10
#define PA0  7  // A0
#define PA1  8  // A1
#define PA4  9  // A4
#define PA6  10
#define PC4  11 // A12
#define PB0  12 // A6
#define PB2  13
#define PE8  14
#define PE9  15
#define PE11 16
#define PE13 17
#define PE15 18
#define PB11 19
#define PB13 20
#define PB15 21
#define PD9  22
#define PD11 23
#define PD13 24
#define PD15 25
#define PC6  26
#define PC8  27
#define PC9  28
#define PA9  29
#define PA11 30 // USB_DM
#define PA13 31
#define PA15 32
#define PC11 33
#define PC12 34
#define PD1  35
#define PD3  36
#define PD5  37
#define PD7  38
#define PB4  39
#define PB6  40
#define PB8  41
// GND
// 3V3
// GND
// Internal (left to right)
// GND
// 3V3
// 5V
#define PE1  42
#define PE3  43
#define PE5  44
#define PC13 45
#define PC15 46 // OSC32_OUT
#define PC1  47 // A9
#define PC3  48 // A11
#define PA2  49 // A2
#define PA3  50 // A3
#define PA5  51 // A5
#define PA7  52
#define PC5  53 // A13
#define PB1  54 // A7
#define PE7  55
#define PE10 56
#define PE12 57
#define PE14 58
#define PB10 59
#define PB12 60
#define PB14 61
#define PD8  62
#define PD10 63
#define PD12 64
#define PD14 65
#define PC7  66
#define PA8  67
#define PA10 68
#define PA12 69 // USB_DP
#define PA14 70
#define PC10 71
#define PD0  72
#define PD2  73
#define PD4  74
#define PD6  75
#define PB3  76
#define PB5  77
#define PB7  78
#define PB9  79 // LED

// GND
// 3V3
// GND

// This must be a literal
#define NUM_DIGITAL_PINS        94
// This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       14
#define NUM_ANALOG_FIRST        80

// Below ADC, DAC and PWM definitions already done in the core
// Could be redefined here if needed
// ADC resolution is 12bits
//#define ADC_RESOLUTION          12
//#define DACC_RESOLUTION         12

// PWM resolution
//#define PWM_RESOLUTION          8
//#define PWM_FREQUENCY           1000
//#define PWM_MAX_DUTY_CYCLE      255

// On-board LED pin number
#define LED_BUILTIN             PB9

// On-board user button
//#define BTN_K_UP                PA0   - no user button

// Below SPI and I2C definitions already done in the core
// Could be redefined here if differs from the default one
// SPI Definitions
#define PIN_SPI_MOSI            PB15
#define PIN_SPI_MISO            PB14
#define PIN_SPI_SCK             PB13
#define PIN_SPI_SS              PB12

// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6

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
