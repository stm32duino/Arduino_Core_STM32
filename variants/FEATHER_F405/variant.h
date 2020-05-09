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

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
// External (left to right)
// GND
// VBAT
// 5V
#define PB11 0
#define PB10 1
#define PB3  2  // FLASH SCK
#define PB4  3  // FLASH MISO
#define PB5  4  // FLASH MOSI
#define PC7  5
#define PC6  6
#define PA15 7  // FLASH CS

#define PC0  8  // NeoPixel
#define PB8  9
#define PB9  10
#define PC3  11
#define PC2  12
#define PC1  13

#define PB7  14  // SDA
#define PB6  15  // SCL

#define PA4  16  // A0
#define PA5  17  // A1
#define PA6  18  // A2
#define PA7  19  // A3
#define PC4  20  // A4
#define PC5  21  // A5
#define PA3  22  // A6 - VDIV

#define PB13 23  // SCK
#define PB14 24  // MISO
#define PB15 25  // MOSI

#define PC8  26  // SDIO D0
#define PC9  27  // SDIO D1
#define PC10 28  // SDIO D2
#define PC11 29  // SDIO D3
#define PC12 30  // SDIO CLK
#define PD2  31  // SDIO CMD
#define PB12 32  // SD Detect


#define PC14 33  // OSC32_IN
#define PC15 34  // OSC32_OUT

#define PA11 35  // USB_DM
#define PA12 36  // USB_DP

#define PA13 37  // SWDIO
#define PA14 38  // SWCLK 

// This must be a literal
#define NUM_DIGITAL_PINS        39
// This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       7
#define NUM_ANALOG_FIRST        16

// On-board LED pin number
#define LED_BUILTIN             PC1

#define SD_DETECT_PIN           PB12

// No user button

// SPI Definitions
#define PIN_SPI_MOSI            PB15
#define PIN_SPI_MISO            PB14
#define PIN_SPI_SCK             PB13
#define PIN_SPI_SS              PA15

// SPI FLASH
#define PIN_SPI3_MOSI           PB5
#define PIN_SPI3_MISO           PB4
#define PIN_SPI3_SCK            PB3
#define PIN_SPI3_SS             PA15

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#define SERIAL_UART_INSTANCE    3

// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PB11
#define PIN_SERIAL_TX           PB10

/* HAL configuration */
#define HSE_VALUE               12000000U

/* Extra HAL modules */
#define HAL_DAC_MODULE_ENABLED
#define HAL_SD_MODULE_ENABLED

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
