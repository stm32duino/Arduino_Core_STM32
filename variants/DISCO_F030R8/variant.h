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

enum {
  //P1 connector Right side (bottom view)
  PC13, //D0
  PC14, //D1
  PC15, //D2
  PF0,  //D3
  PF1,  //D4
  PC0,  //D5
  PC1,  //D6
  PC2,  //D7
  PC3,  //D8
  PA0,  //D9 - USER_BTN
  PA1,  //D10
  PA2,  //D11
  PA3,  //D12
  PF4,  //D13
  PF5,  //D14
  PA4,  //D15
  PA5,  //D16
  PA6,  //D17
  PA7,  //D18
  PC4,  //D19
  PC5,  //D20
  PB0,  //D21
  PB1,  //D22
  PB2,  //D23
  PB10, //D24
  PB11, //D25
  PB12, //D26
  //P2 connector Left side (bottom view)
  PB9,  //D27
  PB8,  //D28
  PB7,  //D29
  PB6,  //D30
  PB5,  //D31
  PB4,  //D32
  PB3,  //D33
  PD2,  //D34
  PC12, //D35
  PC11, //D36
  PC10, //D37
  PA15, //D38
  PA14, //D39
  PF7,  //D40
  PF6,  //D41
  PA13, //D42
  PA12, //D43
  PA11, //D44
  PA10, //D45
  PA9,  //D46
  PA8,  //D47
  PC9,  //D48 - LED_GREEN (LD3)
  PC8,  //D49 - LED_BLUE (LD4)
  PC7,  //D50
  PC6,  //D51
  PB15, //D52
  PB14, //D53
  PB13, //D54
  // Duplicated pins in order to be aligned with PinMap_ADC
  PC_0_A, //D55/A0 = D5
  PC_1_A, //D56/A1 = D6
  PC_2_A, //D57/A2 = D7
  PC_3_A, //D58/A3 = D8
  PA_0_A, //D59/A4 = D9
  PA_1_A, //D60/A5 = D10
  PA_2_A, //D61/A6 = D11
  PA_3_A, //D62/A7 = D12
  PA_4_A, //D63/A8 = D15
  PA_5_A, //D64/A9 = D16
  PA_6_A, //D65/A10 = D17
  PA_7_A, //D66/A11 = D18
  PC_4_A, //D67/A12 = D19
  PC_5_A, //D68/A13 = D20
  PB_0_A, //D69/A14 = D21
  PB_1_A, //D70/A15 = D22
  PEND
};

// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        71
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       16
#define NUM_ANALOG_FIRST        55

//On-board LED pin number
#define LED_BUILTIN             PC9 // LD3
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PC8 // LD4

//On-board user button
#define USER_BTN                PA0

// SPI definitions
// SPI1 is used
#define PIN_SPI_SS              PA4
#define PIN_SPI_SS1             PC4
#define PIN_SPI_SS2             PB12
#define PIN_SPI_SS3             PC6
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5

// I2C Definitions
// I2C1 is used
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6

//Do not use basic timer: OC is required
#define TIMER_SERVO             TIM3  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    1 // USART 1

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
#define SERIAL_PORT_HARDWARE    Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
