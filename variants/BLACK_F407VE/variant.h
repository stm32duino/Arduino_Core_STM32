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
#define PE2  0
#define PE3  1
#define PE4  2  // BUT K0
#define PE5  3  // BUT K1
#define PE6  4
#define PC13 5
#define PC0  6  // A8
#define PC1  7  // A9
#define PC2  8  // A10
#define PC3  9  // A11
#define PA0  10 // A0/WK_UP: BUT K_UP
#define PA1  11 // A1
#define PA2  12 // A2
#define PA3  13 // A3
#define PA4  14 // A4
#define PA5  15 // A5
#define PA6  16 // LED D2
#define PA7  17 // LED D3 (active LOW)
#define PC4  18 // A12
#define PC5  19 // A13
#define PB0  20 // A6
#define PB1  21 // A7
#define PE7  22
#define PE8  23
#define PE9  24
#define PE10 25
#define PE11 26
#define PE12 27
#define PE13 28
#define PE14 29
#define PE15 30
#define PB10 31
#define PB11 32
#define PB12 33
#define PB13 34
#define PB14 35
// Right Side
#define PE1  36
#define PE0  37
#define PB9  38
#define PB8  39
#define PB7  40
#define PB6  41
#define PB5  42
#define PB3  43
#define PD7  44
#define PD6  45
#define PD5  46
#define PD4  47
#define PD3  48
#define PD2  49
#define PD1  50
#define PD0  51
#define PC12 52
#define PC11 53
#define PC10 54
#define PA15 55
#define PA12 56 // USB_DP
#define PA11 57 // USB_DM
#define PA10 58
#define PA9  59
#define PA8  60
#define PC9  61
#define PC8  62
#define PC7  63
#define PC6  64
#define PD15 65
#define PD14 66
#define PD13 67
#define PD12 68
#define PD11 69
#define PD10 70
#define PD9  71
#define PD8  72
#define PB15 73
#define PB4  74

// This must be a literal
#define NUM_DIGITAL_PINS        89
// This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       14
#define NUM_ANALOG_FIRST        75

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
#define LED_D2                  PA6
#define LED_D3                  PA7
#define LED_BUILTIN             LED_D2
#define LED_GREEN               LED_D2

// On-board user button
#define BTN_K_UP                PA0
#define BTN_K0                  PE4
#define BTN_K1                  PE5
#define USER_BTN                BTN_K0

// Below SPI and I2C definitions already done in the core
// Could be redefined here if differs from the default one
// SPI Definitions
#define PIN_SPI_SS              PB7 // NRF24 connector
#define PIN_SPI_SS1             PB0 // W25Q16 (on board flash)
#define PIN_SPI_MOSI            PB5 // NRF24 connector & W25Q16 (on board flash)
#define PIN_SPI_MISO            PB4 // NRF24 connector & W25Q16 (on board flash)
#define PIN_SPI_SCK             PB3 // NRF24 connector & W25Q16 (on board flash)

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
