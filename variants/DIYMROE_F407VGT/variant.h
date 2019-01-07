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

/*
 * This version created by Andrew W Symons (AWS), 19-Nov-18
 * for DIYMROE_STM32F407VGT board
 */

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

/*------------------------------------------------------------------
 *        Headers
 *------------------------------------------------------------------*/
#include "PeripheralPins.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*------------------------------------------------------------------
 *        Pins
 * Header pin numbers are numbered anticlockwise from the USB socket,
 * ... as in the schematic.
 * ... Right / Left / Top: oriented relative to USB socket at bottom
 *
 *------------------------------------------------------------------*/
extern const PinName digitalPin[];

// Header right (as viewed with USB socket at the bottom), numbered from bottom
#define PE3  0  // Header right, pin 1
#define PE2  1  // Header right, pin 2
#define PE5  2  // Header right, pin 3
#define PE4  3  // Header right, pin 4
#define PC13 4  // Header right, pin 5
#define PE6  5  // Header right, pin 6
                // Header right, pin 7 = GND
                // Header right, pin 8 = 3.3V
#define PC1  6  // Header right, pin 9
#define PC0  7  // Header right, pin 10
#define PA0  8  // Header right, pin 11
#define PC2  9  // Header right, pin 12
#define PA2  10 // Header right, pin 13
#define PA1  11 // Header right, pin 14
#define PA3  12 // Header right, pin 15
#define PC3  13 // Header right, pin 16
#define PA5  14 // Header right, pin 17
#define PA4  15 // Header right, pin 18
#define PA7  16 // Header right, pin 19
#define PA6  17 // Header right, pin 20
#define PC5  18 // Header right, pin 21
#define PC4  19 // Header right, pin 22
#define PB1  20 // Header right, pin 23
#define PB0  21 // Header right, pin 24
#define PB9  22 // Header right, pin 25
#define PB8  23 // Header right, pin 26
#define PE7  24 // Header right, pin 27
#define PE1  25 // Header right, pin 28
#define PE9  26 // Header right, pin 29
#define PE8  27 // Header right, pin 30
#define PB2  28 // Header right, pin 31
#define PE10 29 // Header right, pin 32

// Header top (as viewed with USB socket at the bottom), numbered from right
#define PE11 30 // Header top, pin 1
#define PE12 31 // Header top, pin 2
#define PE13 32 // Header top, pin 3
#define PE14 33 // Header top, pin 4
#define PE15 34 // Header top, pin 5
#define PB10 35 // Header top, pin 6
#define PB11 36 // Header top, pin 7
                // Header top, pin 8 = GND
#define PB12 37 // Header top, pin 9
                // Header top, pin 10 = 3.3V
#define PB14 38 // Header top, pin 11
#define PB13 39 // Header top, pin 12
#define PD8  40 // Header top, pin 13
#define PB15 41 // Header top, pin 14
#define PD10 42 // Header top, pin 15
#define PD9  43 // Header top, pin 16
#define PD12 44 // Header top, pin 17
#define PD11 45 // Header top, pin 18
#define PD14 46 // Header top, pin 19
#define PD13 47 // Header top, pin 20
#define PC6  48 // Header top, pin 21
#define PD15 49 // Header top, pin 22
#define PC8  50 // Header top, pin 23
#define PC7  51 // Header top, pin 24

// Header left (as viewed with USB socket at the bottom), numbered from top
                // Header left, pin 1 = GND
                // Header left, pin 2 = Vcc (5V)
#define PA8  52 // Header left, pin 3
#define PC9  53 // Header left, pin 4
#define PA10 54 // Header left, pin 5
#define PA9  55 // Header left, pin 6
#define PA12 56 // Header left, pin 7 and USB_DP
#define PA11 57 // Header left, pin 8 and USB_DM
#define PA14 58 // Header left, pin 9
#define PA13 59 // Header left, pin 10
#define PC10 60 // Header left, pin 11
#define PA15 61 // Header left, pin 12
#define PC12 62 // Header left, pin 13
#define PC11 63 // Header left, pin 14
#define PD1  64 // Header left, pin 15
#define PD0  65 // Header left, pin 16
#define PD3  66 // Header left, pin 17
#define PD2  67 // Header left, pin 18
#define PD5  68 // Header left, pin 19
#define PD4  69 // Header left, pin 20
#define PD7  70 // Header left, pin 21
#define PD6  71 // Header left, pin 22
#define PB4  72 // Header left, pin 23
#define PB3  73 // Header left, pin 24
#define PB6  74 // Header left, pin 25
#define PB5  75 // Header left, pin 26
#define PE0  76 // Header left, pin 27 and LED_BUILTIN
#define PB7  77 // Header left, pin 28

// This must be a literal
#define NUM_DIGITAL_PINS        94  // Number of definitions above

// This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       16
#define NUM_ANALOG_FIRST        78

// On-board LED pin number
#define LED_BUILTIN             PE0

// On-board user button
#define BTN_K_UP                PD15

// SPI Definitions
#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PB3
#define PIN_SPI_SS              PB6

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

// Default pin used for 'Serial1' instance
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
// SERIAL_PORT_HARDWARE       Hardware serial port.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR     Serial
#define SERIAL_PORT_HARDWARE    Serial1
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
