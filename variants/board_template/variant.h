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

#include "Arduino.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
#include "PeripheralPins.h"

extern const PinName digitalPin[];

// Enum defining pin names to match digital pin number --> Dx
// !!!
// !!! Copy the digitalPin[] array in variant.cpp
// !!! and remove all '_': PX_n --> PXn
// !!! For NC, suffix by _x where x is the number of NC:
// !!!   NC_1, NC_2,...
// !!! For duplicated pin name, suffix by _x where x is the number of pin:
// !!! PA7, PA7_2, PA7_3,...
enum {
  PEND
};
// Enum defining Arduino style alias for analog pin number --> Ax
// !!!
// !!! It must be aligned with the number of analog PinName
// !!! defined in digitalPin[] array in variant.cpp
// !!!
enum {
  A_START_AFTER = Dx, // pin number preceding A0
  A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9,
  A10, A11, A12, A13, A14, A15, A16, A17,
  AEND
};

//ADC resolution is 12bits
#define ADC_RESOLUTION          12
#define DACC_RESOLUTION         12

//PWR resolution
#define PWM_RESOLUTION          8
#define PWM_FREQUENCY           1000
#define PWM_MAX_DUTY_CYCLE      255

//On-board LED pin number
#define LED_BUILTIN             Dx
#define LED_GREEN               LED_BUILTIN

//On-board user button
#define USER_BTN                Dx


//SPI definitions
#define SS                      10 // Default for Arduino connector compatibility
#define MOSI                    11 // Default for Arduino connector compatibility
#define MISO                    12 // Default for Arduino connector compatibility
#define SCK                     13 // Default for Arduino connector compatibility

//I2C Definitions
#define SDA                     14 // Default for Arduino connector compatibility
#define SCL                     15 // Default for Arduino connector compatibility

//Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM in PeripheralPins.c
#define TIMER_TONE              TIMx
#define TIMER_UART_EMULATED     TIMx

//Do not use basic timer: OC is required
#define TIMER_SERVO             TIMx  //TODO: advanced-control timers don't work

#define DEBUG_UART              ((USART_TypeDef *) U(S)ARTX) // ex: USART3

// UART Emulation (uncomment if needed, required TIM1)
//#define UART_EMUL_RX            PX_n // PinName used for RX
//#define UART_EMUL_TX            PX_n // PinName used for TX

// Serial Pin Firmata
#define PIN_SERIAL_RX           Dx
#define PIN_SERIAL_TX           Dx
// Define as many PIN_SERIALX than desired
//#define PIN_SERIAL1_RX          Dx
//#define PIN_SERIAL1_TX          Dx
//...

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
// declare here as many UART objects than defined in variant.cpp
extern HardwareSerial Serial;
//extern HardwareSerial SerialX;
//...

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
#define SERIAL_PORT_HARDWARE  Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
