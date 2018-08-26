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

#define PA0  0  // GPS_PPS_PIN
#define PA8  1
#define PA9  2  // UART_TX
#define PA10 3  // UART_RX
#define PA12 4  // LED1
#define PA13 5
#define PA14 6
#define PA15 7  // GPS_POWER_ON_PIN
#define PB2  8
#define PB3  9
#define PB4  10 // LED2
#define PB5  11
#define PB8  12 // I2C_SCL
#define PB9  13 // I2C_SDA
#define PB10 14 // GPS_UART_TX
#define PB11 15 // GPS_UART_RX
#define PA1  16 // A0
#define PA2  17 // A1 - ADC_VBAT
#define PB12 18 // A2
#define PB14 19 // LIS3DH_INT1_PIN
#define PB15 20 // LIS3DH_INT2_PIN
#define PB13 21 // RADIO_RESET
#define PH1  22 // RADIO_XTAL_EN
#define PA7  23 // RADIO_MOSI
#define PA6  24 // RADIO_MISO
#define PA5  25 // RADIO_SCLK
#define PB0  26 // RADIO_NSS
#define PA11 27 // RADIO_DIO_0
#define PB1  28 // RADIO_DIO_1
#define PA3  29 // RADIO_DIO_2
#define PH0  30 // RADIO_DIO_3
#define PC13 31 // RADIO_DIO_4
#define PB6  32 // RADIO_RF_CRX_RX
#define PB7  33 // RADIO_RF_CBT_HF
#define PA4  34 // RADIO_RF_CTX_PA

// This must be a literal
#define NUM_DIGITAL_PINS        35
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       3
#define NUM_ANALOG_FIRST        16

// On-board LED pin number
#define LED_BUILTIN             PA12
#define LED1                    LED_BUILTIN
#define LED2                    PB4

// SPI Definitions
#define PIN_SPI_SS              PB0
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5

// I2C Definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM10

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    1
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9

// LoRa Definitions
#define RADIO_RESET             PB13
#define RADIO_XTAL_EN           PH1

#define RADIO_MOSI              PA7
#define RADIO_MISO              PA6
#define RADIO_SCLK              PA5
#define RADIO_NSS               PB0

#define RADIO_DIO_0             PA11
#define RADIO_DIO_1             PB1
#define RADIO_DIO_2             PA3
#define RADIO_DIO_3             PH0
#define RADIO_DIO_4             PC13

#define RADIO_RF_CRX_RX         PB6 //CRF3
#define RADIO_RF_CBT_HF         PB7 //CRF2 HF
#define RADIO_RF_CTX_PA         PA4 //CRF1 PA

// GPS Definitions
#define GPS_PPS_PIN             PA0
#define GPS_UART                USART3
#define GPS_POWER_ON_PIN        PA15
#define GPS_UART_TX             PB10
#define GPS_UART_RX             PB11

// MEMS (LIS3DH)
#define LIS3DH_INT1_PIN	        PB14
#define LIS3DH_INT2_PIN	        PB15

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
