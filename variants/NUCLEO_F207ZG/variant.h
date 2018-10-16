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

// Defining Arduino style alias for digital pin number --> Dx
#define  PG9    0
#define  PG14   1
#define  PF15   2
#define  PE13   3
#define  PF14   4
#define  PE11   5
#define  PE9    6
#define  PF13   7
#define  PF12   8
#define  PD15   9
#define  PD14   10
#define  PA7    11
#define  PA6    12
#define  PA5    13
#define  PB9    14
#define  PB8    15
#define  PC6    16
#define  PB15   17
#define  PB13   18
#define  PB12   19
#define  PA15   20
#define  PC7    21
#define  PB5    22
#define  PB3    23
#define  PA4    24
#define  PB4    25
#define  PB6    26
#define  PB2    27
#define  PD13   28
#define  PD12   29
#define  PD11   30
#define  PE2    31
#define  PA0    32
#define  PB0    33
#define  PE0    34
#define  PB11   35
#define  PB10   36
#define  PE15   37
#define  PE14   38
#define  PE12   39
#define  PE10   40
#define  PE7    41
#define  PE8    42
#define  PC8    43
#define  PC9    44
#define  PC10   45
#define  PC11   46
#define  PC12   47
#define  PD2    48
#define  PG2    49
#define  PG3    50
#define  PD7    51
#define  PD6    52
#define  PD5    53
#define  PD4    54
#define  PD3    55
#define  PE2_2  56
#define  PE4    57
#define  PE5    58
#define  PE6    59
#define  PE3    60
#define  PF8    61
#define  PF7    62
#define  PF9    63
#define  PG1    64
#define  PG0    65
#define  PD1    66
#define  PD0    67
#define  PF0    68
#define  PF1    69
#define  PF2    70
#define  PA7_2  71
#define  NC_1   72
#define  PB7    73
#define  PB14   74
#define  PC13   75
#define  PD9    76
#define  PD8    77
#define  PA3    78
#define  PC0    79
#define  PC3    80
#define  PF3    81
#define  PF5    82
#define  PF10   83
#define  PB1    84
#define  PC2    85
#define  PF4    86
#define  PF6    87
  // Duplicated pins in order to be aligned with PinMap_ADC
#define  PA7_3  88
#define  PA6_2  89
#define  PA5_2  90
#define  PA4_2  91
#define  PA0_2  92
#define  PF8_2  93
#define  PF7_2  94
#define  PF9_2  95
#define  PEND   96

// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        96
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       18
#define NUM_ANALOG_FIRST        78

// On-board LED pin number
#define LED_BUILTIN             PB0
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PB7
#define LED_RED                 PB14

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM in PeripheralPins.c
#define TIMER_TONE              TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    3 //Connected to ST-Link
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PD9
#define PIN_SERIAL_TX           PD8

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
