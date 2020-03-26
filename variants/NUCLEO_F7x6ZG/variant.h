/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
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

#define PG9  0
#define PG14 1
#define PF15 2
#define PE13 3
#define PF14 4
#define PE11 5
#define PE9  6
#define PF13 7
#define PF12 8
#define PD15 9
#define PD14 10
#define PA7  A10
#define PA6  A11
#define PA5  A12
#define PB9  14
#define PB8  15
#define PC6  16
#define PB15 17
#define PB13 18
#define PB12 19
#define PA15 20
#define PC7  21
#define PB5  22
#define PB3  23
#define PA4  A13
#define PB4  25
#define PB6  26
#define PB2  27
#define PD13 28
#define PD12 29
#define PD11 30
#define PE2  31
#define PA0  A14
#define PB0  33 // LED_GREEN
#define PE0  34
#define PB11 35
#define PB10 36
#define PE15 37
#define PE14 38
#define PE12 39
#define PE10 40
#define PE7  41
#define PE8  42
#define PC8  43
#define PC9  44
#define PC10 45
#define PC11 46
#define PC12 47
#define PD2  48
#define PG2  49
#define PG3  50
#define PD7  51
#define PD6  52
#define PD5  53
#define PD4  54
#define PD3  55
// 56 is PE2 (31)
#define PE4  57
#define PE5  58
#define PE6  59
#define PE3  60
#define PF8  A15
#define PF7  A16
#define PF9  A17
#define PG1  64
#define PG0  65
#define PD1  66
#define PD0  67
#define PF0  68
#define PF1  69
#define PF2  70
// 71 is PA7 (11)
// 72 is NC
#define PB7  73 // LED_BLUE
#define PB14 74 // LED_RED
#define PC13 75 // USER_BTN
#define PD9  76 // Serial Rx
#define PD8  77 // Serial Tx
#define PA3  A0
#define PC0  A1
#define PC3  A2
#define PF3  A3
#define PF5  A4
#define PF10 A5
#define PB1  A6
#define PC2  A7
#define PF4  A8
#define PF6  A9
// ST Morpho
#define PA1  A18
#define PA2  A19
#define PA8  90
#define PA9  91
#define PA10 92
#define PA11 93
#define PA12 94
#define PA13 95 // SWD
#define PA14 96 // SWD
#define PC1  A20
#define PC4  A21
#define PC5  A22
#define PC14 100
#define PC15 101
#define PD10 102
#define PE1  103
#define PF11 104
#define PG4  105
#define PG5  106
#define PG6  107
#define PG7  108
#define PG8  109
#define PG10 110
#define PG11 111
#define PG12 112
#define PG13 113
#define PG15 114
#define PH0  115 // MCO
#define PH1  116

// This must be a literal
#define NUM_DIGITAL_PINS        117
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       23

// On-board LED pin number
#define LED_BUILTIN             PB0
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PB7
#define LED_RED                 PB14

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    3 //Connected to ST-Link

// Serial pin used for console (ex: stlink)
// Rerquired by Firmata
#define PIN_SERIAL_RX           PD9
#define PIN_SERIAL_TX           PD8

// Value of the External oscillator in Hz
#define HSE_VALUE               8000000U

/* Extra HAL modules */
#define HAL_DAC_MODULE_ENABLED
#define HAL_ETH_MODULE_ENABLED

// Last Flash sector used for EEPROM emulation, address/sector depends on single/dual bank configuration.
// By default 1MB single bank
#define FLASH_BASE_ADDRESS      0x080C0000
#define FLASH_DATA_SECTOR       11

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
