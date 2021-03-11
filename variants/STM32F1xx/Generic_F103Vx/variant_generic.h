/*
 *******************************************************************************
 * Copyright (c) 2019, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// ** = F103VC-D-E-F-G
//  * = F103V8-B    | DIGITAL | ANALOG         | USART                    | TWI       | SPI                    | SPECIAL   |
//                  |---------|----------------|--------------------------|-----------|------------------------|-----------|
#define PA0  A0  // | 0       | A0             |                          |           |                        |           |
#define PA1  A1  // | 1       | A1             |                          |           |                        |           |
#define PA2  A2  // | 2       | A2             | USART2_TX                |           |                        |           |
#define PA3  A3  // | 2       | A2, DAC_OUT1** | USART2_RX                |           |                        |           |
#define PA4  A4  // | 4       | A4, DAC_OUT2** |                          |           | SPI1_SS                |           |
#define PA5  A5  // | 5       | A5             |                          |           | SPI1_SCK               |           |
#define PA6  A6  // | 6       | A6             |                          |           | SPI1_MISO              |           |
#define PA7  A7  // | 7       | A7             |                          |           | SPI1_MOSI              |           |
#define PA8  8   // | 8       |                |                          |           |                        |           |
#define PA9  9   // | 9       |                | USART1_TX                |           |                        |           |
#define PA10 10  // | 10      |                | USART1_RX                |           |                        |           |
#define PA11 11  // | 11      |                |                          |           |                        | USB_DM    |
#define PA12 12  // | 12      |                |                          |           |                        | USB_DP    |
#define PA13 13  // | 13      |                |                          |           |                        | SWD_SWDIO |
#define PA14 14  // | 14      |                |                          |           |                        | SWD_SWCLK |
#define PA15 15  // | 15      |                |                          |           | SPI1_SS*/SPI3_SS**     |           |
//                  |---------|----------------|--------------------------|-----------|------------------------|-----------|
#define PB0  A8  // | 16      | A8             |                          |           |                        |           |
#define PB1  A9  // | 17      | A9             |                          |           |                        |           |
#define PB2  18  // | 18      |                |                          |           |                        | BOOT1     |
#define PB3  19  // | 19      |                |                          |           | SPI1_SCK*/SPI3_SCK**   |           |
#define PB4  20  // | 20      |                |                          |           | SPI1_MISO*/SPI3_MISO** |           |
#define PB5  21  // | 21      |                |                          |           | SPI1_MOSI*/SPI3_MOSI** |           |
#define PB6  22  // | 22      |                | USART1_TX                | TWI1_SCL  |                        |           |
#define PB7  23  // | 23      |                | USART1_RX                | TWI1_SDA  |                        |           |
#define PB8  24  // | 24      |                |                          | TWI1_SCL  |                        |           |
#define PB9  25  // | 25      |                |                          | TWI1_SDA  |                        |           |
#define PB10 26  // | 26      |                | USART3_TX                | TWI2_SCL  |                        |           |
#define PB11 27  // | 27      |                | USART3_RX                | TWI2_SDA  |                        |           |
#define PB12 28  // | 28      |                |                          |           | SPI2_SS                |           |
#define PB13 29  // | 29      |                |                          |           | SPI2_SCK               |           |
#define PB14 30  // | 30      |                |                          |           | SPI2_MISO              |           |
#define PB15 31  // | 31      |                |                          |           | SPI2_MOSI              |           |
//                  |---------|----------------|--------------------------|-----------|------------------------|-----------|
#define PC0  A10 // | 32      | A10            |                          |           |                        |           |
#define PC1  A11 // | 33      | A11            |                          |           |                        |           |
#define PC2  A12 // | 34      | A12            |                          |           |                        |           |
#define PC3  A13 // | 35      | A13            |                          |           |                        |           |
#define PC4  A14 // | 36      | A14            |                          |           |                        |           |
#define PC5  A15 // | 37      | A15            |                          |           |                        |           |
#define PC6  38  // | 38      |                |                          |           |                        |           |
#define PC7  39  // | 39      |                |                          |           |                        |           |
#define PC8  40  // | 40      |                |                          |           |                        |           |
#define PC9  41  // | 41      |                |                          |           |                        |           |
#define PC10 42  // | 42      |                | USART3_TX*/UART4_TX**    |           |                        |           |
#define PC11 43  // | 43      |                | USART3_RX*/UART4_RX**    |           |                        |           |
#define PC12 44  // | 44      |                | UART5_TX**               |           |                        |           |
#define PC13 45  // | 45      |                |                          |           |                        |           |
#define PC14 46  // | 46      |                |                          |           |                        | OSC32_IN  |
#define PC15 47  // | 47      |                |                          |           |                        | OSC32_OUT |
//                  |---------|----------------|--------------------------|-----------|------------------------|-----------|
#define PD0  48  // | 48      |                |                          |           |                        | OSC_IN    |
#define PD1  49  // | 48      |                |                          |           |                        | OSC_OUT   |
#define PD2  50  // | 50      |                | UART5_RX**               |           |                        |           |
#define PD3  51  // | 51      |                |                          |           |                        |           |
#define PD4  52  // | 52      |                |                          |           |                        |           |
#define PD5  53  // | 53      |                | USART2_TX                |           |                        |           |
#define PD6  54  // | 54      |                | USART2_RX                |           |                        |           |
#define PD7  55  // | 55      |                |                          |           |                        |           |
#define PD8  56  // | 56      |                | USART3_TX                |           |                        |           |
#define PD9  57  // | 57      |                | USART3_RX                |           |                        |           |
#define PD10 58  // | 58      |                |                          |           |                        |           |
#define PD11 59  // | 59      |                |                          |           |                        |           |
#define PD12 60  // | 60      |                |                          |           |                        |           |
#define PD13 61  // | 61      |                |                          |           |                        |           |
#define PD14 62  // | 62      |                |                          |           |                        |           |
#define PD15 63  // | 63      |                |                          |           |                        |           |
//                  |---------|----------------|--------------------------|-----------|------------------------|-----------|
#define PE0  64  // | 64      |                |                          |           |                        |           |
#define PE1  65  // | 65      |                |                          |           |                        |           |
#define PE2  66  // | 66      |                |                          |           |                        |           |
#define PE3  67  // | 67      |                |                          |           |                        |           |
#define PE4  68  // | 68      |                |                          |           |                        |           |
#define PE5  69  // | 69      |                |                          |           |                        |           |
#define PE6  70  // | 70      |                |                          |           |                        |           |
#define PE7  71  // | 71      |                |                          |           |                        |           |
#define PE8  72  // | 72      |                |                          |           |                        |           |
#define PE9  73  // | 73      |                |                          |           |                        |           |
#define PE10 74  // | 74      |                |                          |           |                        |           |
#define PE11 75  // | 75      |                |                          |           |                        |           |
#define PE12 76  // | 76      |                |                          |           |                        |           |
#define PE13 77  // | 77      |                |                          |           |                        |           |
#define PE14 78  // | 78      |                |                          |           |                        |           |
#define PE15 79  // | 79      |                |                          |           |                        |           |
//                  |---------|----------------|--------------------------|-----------|------------------------|-----------|

// This must be a literal
#define NUM_DIGITAL_PINS        80
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#ifndef LED_BUILTIN
#define LED_BUILTIN             PB11
#endif

// On-board user button
#ifndef USER_BTN
#define USER_BTN                PC13
#endif

// SPI Definitions
#define PIN_SPI_SS              PC4
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5

// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6

// Timer Definitions (optional)
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM3
#define TIMER_SERVO             TIM2

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#define SERIAL_UART_INSTANCE    1

// Extra HAL modules
#if defined(STM32F103xE) || defined(STM32F103xG)
#define HAL_DAC_MODULE_ENABLED
#define HAL_SD_MODULE_ENABLED
#endif

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
