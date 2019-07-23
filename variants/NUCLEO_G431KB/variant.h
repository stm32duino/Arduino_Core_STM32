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

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
// CN4
#define PA10 0
#define PA9  1
#define PA12 2
#define PB0  3
#define PB7  4
#define PA15 5
#define PB6  6
#define PF0  7
#define PF1  8
#define PA8  9
#define PA11 10
#define PB5  11
#define PB4  12
// CN3
#define PB8  13 // LED - SB7 ON SB6 OFF
#define PA0  14 // A0
#define PA1  15 // A1
#define PA4  16 // A2 (A3 silkscreen)
#define PA5  17 // A3 (A4 silkscreen) - SB3 ON also connected to PB7
#define PA6  18 // A4 (A5 silkscreen) - SB2 ON also connected to PA15
#define PA7  19 // A5 (A6 silkscreen)
#define PA2  20 // (A7 silkscreen) - SB1 ON VCP TX
#define PA3  21 // (A2 silkscreen) - SB12 ON VCP RX

// This must be a literal
#define NUM_DIGITAL_PINS        22
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       6
#define NUM_ANALOG_FIRST        14

// On-board LED pin number
#define LED_BUILTIN             PB8
#define LED_GREEN               LED_BUILTIN

// SPI Definitions
#define PIN_SPI_SS              PA4
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5

// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PA15

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA3
#define PIN_SERIAL_TX           PA2

/* HAL configuration */
#define HSE_VALUE               (24000000UL)

/* Extra HAL modules */
#define HAL_DAC_MODULE_ENABLED

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
#define SERIAL_PORT_MONITOR   Serial
#define SERIAL_PORT_HARDWARE  Serial2
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
