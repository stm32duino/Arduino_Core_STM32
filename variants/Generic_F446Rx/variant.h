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

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

//                  | DIGITAL | ANALOG IN  | ANALOG OUT | UART/USART            | TWI                  | SPI                               | SPECIAL   |
//                  |---------|------------|------------|-----------------------|----------------------|-----------------------------------|-----------|
#define PA0  A0  // | 0       | A0 (ADC1)  |            | UART4_TX              |                      |                                   |           |
#define PA1  A1  // | 1       | A1 (ADC1)  |            | UART4_RX              |                      |                                   |           |
#define PA2  A2  // | 2       | A2 (ADC1)  |            | USART2_TX             |                      |                                   |           |
#define PA3  A3  // | 3       | A3 (ADC1)  |            | USART2_RX             |                      |                                   |           |
#define PA4  A4  // | 4       | A4 (ADC1)  | DAC_OUT1   |                       |                      | SPI1_SS, (SPI3_SS)                |           |
#define PA5  A5  // | 5       | A5 (ADC1)  | DAC_OUT2   |                       |                      | SPI1_SCK                          |           |
#define PA6  A6  // | 6       | A6 (ADC1)  |            |                       |                      | SPI1_MISO                         |           |
#define PA7  A7  // | 7       | A7 (ADC1)  |            |                       |                      | SPI1_MOSI                         |           |
#define PA8  8   // | 8       |            |            |                       | TWI3_SCL             |                                   |           |
#define PA9  9   // | 9       |            |            | USART1_TX             |                      | SPI2_SCK                          |           |
#define PA10 10  // | 10      |            |            | USART1_RX             |                      |                                   |           |
#define PA11 11  // | 11      |            |            |                       |                      |                                   |           |
#define PA12 12  // | 12      |            |            |                       |                      |                                   |           |
#define PA13 13  // | 13      |            |            |                       |                      |                                   | SWD_SWDIO |
#define PA14 14  // | 14      |            |            |                       |                      |                                   | SWD_SWCLK |
#define PA15 15  // | 15      |            |            |                       |                      | SPI3_SS, (SPI1_SS)                |           |
//                  |---------|------------|------------|-----------------------|----------------------|-----------------------------------|-----------|
#define PB0  A8  // | 16      | A8 (ADC1)  |            |                       |                      | SPI3_MOSI                         |           |
#define PB1  A9  // | 17      | A9 (ADC1)  |            |                       |                      |                                   |           |
#define PB2  18  // | 18      |            |            |                       |                      | SPI3_MOSI                         | BOOT1     |
#define PB3  19  // | 19      |            |            |                       | TWI2_SDA             | SPI3_SCK,  (SPI1_SCK)             |           |
#define PB4  20  // | 20      |            |            |                       | TWI3_SDA             | SPI3_MISO, (SPI1_MISO), (SPI2_SS) |           |
#define PB5  21  // | 21      |            |            |                       |                      | SPI3_MOSI, (SPI1_MOSI)            |           |
#define PB6  22  // | 22      |            |            | USART1_TX             | TWI1_SCL             |                                   |           |
#define PB7  23  // | 23      |            |            | USART1_RX             | TWI1_SDA             |                                   |           |
#define PB8  24  // | 24      |            |            |                       | TWI1_SCL             |                                   |           |
#define PB9  25  // | 25      |            |            |                       | TWI1_SDA             | SPI2_SS                           |           |
#define PB10 26  // | 26      |            |            | USART3_TX, (UART4_TX) | TWI2_SCL             | SPI2_SCK                          |           |
#define PB12 27  // | 27      |            |            |                       |                      | SPI3_SCK                          |           |
#define PB13 28  // | 28      |            |            |                       |                      | SPI2_SCK                          |           |
#define PB14 29  // | 29      |            |            |                       |                      | SPI2_MISO                         |           |
#define PB15 30  // | 30      |            |            |                       |                      | SPI2_MOSI                         |           |
//                  |---------|------------|------------|-----------------------|----------------------|-----------------------------------|-----------|
#define PC0  A10 // | 31      | A10 (ADC1) |            |                       |                      |                                   |           |
#define PC1  A11 // | 32      | A11 (ADC1) |            |                       |                      | SPI2_MOSI, (SPI3_MOSI)            |           |
#define PC2  A12 // | 33      | A12 (ADC1) |            |                       |                      | SPI2_MISO                         |           |
#define PC3  A13 // | 34      | A13 (ADC1) |            |                       |                      | SPI2_MOSI                         |           |
#define PC4  A14 // | 35      | A14 (ADC1) |            |                       |                      |                                   |           |
#define PC5  A15 // | 36      | A15 (ADC1) |            | USART3_RX             |                      |                                   |           |
#define PC6  37  // | 37      |            |            | USART6_TX             | (FMP_TWI1_SCL)       |                                   |           |
#define PC7  38  // | 38      |            |            | USART6_RX             | (FMP_TWI1_SDA)       | SPI2_SCK                          |           |
#define PC8  39  // | 39      |            |            |                       |                      |                                   |           |
#define PC9  40  // | 40      |            |            | USART3_TX             | TWI3_SDA             |                                   |           |
#define PC10 41  // | 41      |            |            |                       |                      | SPI3_SCK                          |           |
#define PC11 42  // | 42      |            |            | USART3_RX, (UART4_RX) |                      | SPI3_MISO                         |           |
#define PC12 43  // | 43      |            |            | UART5_TX              | TWI2_SDA             | SPI3_MOSI                         |           |
#define PC13 44  // | 44      |            |            |                       |                      |                                   |           |
#define PC14 45  // | 45      |            |            |                       |                      |                                   | OSC32_IN  |
#define PC15 46  // | 46      |            |            |                       |                      |                                   | OSC32_OUT |
//                  |---------|------------|------------|-----------------------|----------------------|-----------------------------------|-----------|
#define PD2  47  // | 47      |            |            | UART5_RX              |                      |                                   |           |
//                  |---------|------------|------------|-----------------------|----------------------|-----------------------------------|-----------|
#define PH0  48  // | 48      |            |            |                       |                      |                                   | OSC_IN    |
#define PH1  49  // | 49      |            |            |                       |                      |                                   | OSC_OUT   |
//                  |---------|------------|------------|-----------------------|----------------------|-----------------------------------|-----------|

/// This must be a literal
#define NUM_DIGITAL_PINS        50
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#ifndef LED_BUILTIN
#define LED_BUILTIN             PA5
#endif
#define LED_GREEN               LED_BUILTIN

// On-board user button
#ifndef USER_BTN
#define USER_BTN                PC13
#endif

// SPI definitions
#define PIN_SPI_SS              PA4
#define PIN_SPI_SS1             PA4
#define PIN_SPI_SS2             PB9
#define PIN_SPI_SS3             PA15
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5

// I2C definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    2 // Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA3
#define PIN_SERIAL_TX           PA2

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
