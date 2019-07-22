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
// CN9
#define PC5  0
#define PC4  1
#define PA10 2
#define PB3  3
#define PB5  4
#define PB4  5
#define PB10 6
#define PA8  7
// CN5
#define PA9  8
#define PC7  9
#define PB6  10
#define PA7  11
#define PA6  12
#define PA5  13 // LED
#define PB9  14
#define PB8  15
// CN7 Left Side
#define PC10 16
#define PC12 17
#define PA13 18 // SWDIO
#define PA14 19 // SWCLK
#define PA15 20
#define PB7  21
#define PC13 22
#define PC14 23
#define PC15 24
#define PF0  25
#define PF1  26
#define PC2  27
#define PC3  28
// CN7 Right Side
#define PD2  29
#define PC11 30
// CN10 Left Side
#define PC9  31
// CN8
#define PA0  32 // A0
#define PA1  33 // A1
#define PA4  34 // A2
#define PB0  35 // A3
#define PC1  36 // A4
#define PC0  37 // A5
// CN10 Right side
#define PB14 38 // A6
#define PB15 39 // A7
#define PB1  40 // A8
#define PB2  41 // A9
#define PB11 42 // A10
#define PB12 43 // A11
#define PB13 44
#define PA11 45
#define PA12 46
#define PC6  47
#define PC8  48
#define PA2  49
#define PA3  50

// This must be a literal
#define NUM_DIGITAL_PINS        51
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       12
#define NUM_ANALOG_FIRST        32

// On-board LED pin number
#define LED_BUILTIN             PA5
#define LED_GREEN               LED_BUILTIN

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    0 //Connected to ST-Link

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
#define SERIAL_PORT_HARDWARE  SerialLP1
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
