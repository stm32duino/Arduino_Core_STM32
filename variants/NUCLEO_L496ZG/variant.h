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

// Match Table 11. NUCLEO-L496ZG, NUCLEO-L496ZG-P pin assignments
// from UM2179 STM32 Nucleo-144 board
enum {
  PD9,  //D0
  PD8,  //D1
  PF15, //D2
  PE13, //D3
  PF14, //D4
  PE11, //D5
  PE9,  //D6
  PF13, //D7
  PF12, //D8
  PD15, //D9
  PD14, //D10
  PA7,  //D11
  PA6,  //D12
  PA5,  //D13
  PB9,  //D14
  PB8,  //D15
  PC6,  //D16
  PB15, //D17
  PB13, //D18
  PB12, //D19
  PA4,  //D20
  PB4,  //D21
  PB5,  //D22
  PB3,  //D23
  PA4_2,//D24
  PB4_2,//D25
  PA2,  //D26
  PB10, //D27
  PE15, //D28
  PB0,  //D29
  PE12, //D30
  PE14, //D31
  PA0,  //D32
  PB0_2,//D33
  PE0,  //D34
#ifdef ARDUINO_NUCLEO_L496ZG
  PB11, //D35
#else
  NC_1, //D35
#endif
  PB10_2,//D36
  PE15_2,//D37
  PE14_2,//D38
  PE12_2,//D39
  PE10, //D40
  PE7,  //D41
  PE8,  //D42
  PC8,  //D43
  PC9,  //D44
  PC10, //D45
  PC11, //D46
  PC12, //D47
  PD2,  //D48
  PF3,  //D49
  PF5,  //D50
  PD7,  //D51
  PD6,  //D52
  PD5,  //D53
  PD4,  //D54
  PD3,  //D55
  PE2,  //D56
  PE4,  //D57
  PE5,  //D58
  PE6,  //D59
  PE3,  //D60
  PF8,  //D61
  PF7,  //D62
  PF9,  //D63
  PG1,  //D64
  PG0,  //D65
  PD1,  //D66
  PD0,  //D67
  PF0,  //D68
  PF1,  //D69
  PF2,  //D70
  PB6,  //D71
  PB2,  //D72
// ST Morpho
  PA8,  //D73
  PA9,  //D74
  PA10, //D75
  PA11, //D76
  PA12, //D77
  PA15, //D78
  PB7,  //D79 - LEDBLUE
  PB14, //D80 - LEDRED
  PC7,  //D81 - LEDGREEN
  PC13, //D82 - USERBTN
  PC14, //D83
  PC15, //D84
  PD10, //D85
  PD11, //D86
  PD12, //D87
  PD13, //D88
  PE1,  //D89
  PF10, //D90
  PF11, //D91
  PG2,  //D92
  PG3,  //D93
  PG4,  //D94
  PG5,  //D95
  PG6,  //D96
  PG7,  //D97 - Serial Tx
  PG8,  //D98 - Serial Rx
  PG9,  //D99
  PG10, //D100
  PG11, //D101
  PG12, //D102
  PG13, //D103
  PG14, //D104
  PH0,  //D105
  PH1,  //D106
  // Analog pins
  PA3,  //D107/A0
  PC0,  //D108/A1
  PC3,  //D109/A2
  PC1,  //D110/A3
  PC4,  //D111/A4
  PC5,  //D112/A5
  PB1,  //D113/A6
  PC2,  //D114/A7
  PA1,  //D115/A8
  PF4,  //D116/A9
  PF6,  //D117/A10
  // Duplicated pins in order to be aligned with PinMapADC
  PA7_3, //D118/A11 = D11
  PA6_2, //D119/A12 = D12
  PA5_2, //D120/A13 = D13
  PA4_3, //D121/A14 = D20
  PA2_2, //D122/A15 = D26
  PB0_3, //D123/A16 = D29
  PA0_2, //D124/A17 = D32
  PF3_2, //D125/A18 = D49
  PF5_2, //D126/A19 = D50
  PF8_2, //D127/A20 = D61
  PF7_2, //D128/A21 = D62
  PF9_2, //D129/A22 = D63
  PF10_2,//D130/A23 = D91
#ifdef ARDUINO_NUCLEO_L496ZG
  PG15,  //D131
#endif
  // PA13 and PA14 are shared with SWD signals connected to ST-LINK/V2-1.
  // If ST-LINK part is not cut, it is not recommended to use them as I/O pins.
//PA13,  //D132
//PA14,  //D133
  PEND
};

// This must be a literal with the same value as PEND
#ifdef ARDUINO_NUCLEO_L496ZG
#define NUM_DIGITAL_PINS        132
#else
#define NUM_DIGITAL_PINS        131
#endif
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       24
#define NUM_ANALOG_FIRST        107

// On-board LED pin number
#define LED_BUILTIN             PC7
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PB7
#define LED_RED                 PB14

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    0 //Connected to ST-Link - LPUART1

// Serial pin used for console (ex: stlink)
// Rerquired by Firmata
#define PIN_SERIAL_RX           PG8
#define PIN_SERIAL_TX           PG7

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
