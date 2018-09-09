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

// Enum defining pin names to match digital pin number --> Dx
// !!!
// !!! Copy the digitalPin[] array in variant.cpp
// !!! and remove all '_': PX_n --> PXn
// !!! For NC, suffix by _x where x is the number of NC:
// !!!   NC_1, NC_2,...
// !!! For duplicated pin name, suffix by _x where x is the number of pin:
// !!! PA7, PA7_2, PA7_3,...
enum {
  PA0, //D0
  PA1, //D1
  PA2, //D2
  PA8, //D3
  PA9, //D4
  PA10, //D5
  PA11, //DIO0
  PA12, //D6 - LED1
  PA13, //D7
  PA14, //D8
  PA15, //D9
  PB2, //D10
  PB3, //D11
  PB4, //D12 - LED2
  PB5, //D13
  PB8, //D15
  PB9, //D14
  PB10, //D16
  PB11, //D17
  PB12, //D18/A18
  PB14, //D19/A20
  PB13, //RESET LORA
  PB15, //D20/A21
  PA5, //SCK RADIO LORA
  PA6, //MISO RADIO LORA
  PA7, //MOSI RADIO LORA
  PB0, //NSS RADIO LORA
  PB1, //DIO1
  PA3, //DIO2
  PH0, //DIO3
  PC13, //DIO4
  PEND
};

// This must be a literal with the same value as PEND
// It is used with preprocessor tests (e.g. #if NUM_DIGITAL_PINS > 3)
// so an enum will not work.
#define NUM_DIGITAL_PINS        31

// Allow to define Arduino style alias for analog input pin number --> Ax
// All pins are digital, analog inputs are a subset of digital pins
// and must be contiguous to be able to loop on each value
// This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
// defined in pin_arduino.h
// It is used with preprocessor tests (e.g. #if NUM_ANALOG_INPUTS > 3)
// so an enum will not work.
// !!!
// !!! It must be aligned with the number of analog PinName
// !!! defined in digitalPin[] array in variant.cpp
// !!!
#define NUM_ANALOG_INPUTS       3
// Define digital pin number of the first analog input  (i.e. which digital pin is A0)
// First analog pin value (A0) must be greater than or equal to NUM_ANALOG_INPUTS
#define NUM_ANALOG_FIRST        18

// Below ADC, DAC and PWM definitions already done in the core
// Could be redefined here if needed
// ADC resolution is 12bits
//#define ADC_RESOLUTION          12
//#define DACC_RESOLUTION         12

// PWM resolution
//#define PWM_RESOLUTION          8
//#define PWM_FREQUENCY           1000
//#define PWM_MAX_DUTY_CYCLE      255

// On-board LED pin number
#define LED_BUILTIN             PA12
#define LED_GREEN               LED_BUILTIN

// On-board user button
//#define USER_BTN                x

// Below SPI and I2C definitions already done in the core
// Could be redefined here if differs from the default one
// SPI Definitions
//#define PIN_SPI_SS              10 // Default for Arduino connector compatibility
//#define PIN_SPI_MOSI            11 // Default for Arduino connector compatibility
//#define PIN_SPI_MISO            12 // Default for Arduino connector compatibility
//#define PIN_SPI_SCK             13 // Default for Arduino connector compatibility

// LORA
#define RADIO_RESET_PORT        PB13
#define RADIO_MOSI_PORT         PA7
#define RADIO_MISO_PORT         PA6
#define RADIO_SCLK_PORT         PA5
#define RADIO_NSS_PORT          PB0
#define RADIO_DIO_0_PORT        PA11
#define RADIO_DIO_1_PORT        PB1
#define RADIO_DIO_2_PORT        PA3
#define RADIO_DIO_3_PORT        PH0
#define RADIO_DIO_4_PORT        PC13
//#define RADIO_DIO_5_PORT        PA4

#define RADIO_RF_CRX_RX                             PB_6  //CRF3 (ANT_SWITCH_TX_BOOST) RADIO_ANT_SWITCH_RX 
#define RADIO_RF_CBT_HF                             PB_7  //CRF2 HF (ANT_SWITCH_TX_RFO)
#define RADIO_RF_CTX_PA                             PA_4  //CRF1 PA (ANT_SWITCH_RX) RADIO_ANT_SWITCH_TX_PA
#define RADIO_XTAL_EN                               PH_1

// I2C Definitions
#define PIN_WIRE_SDA            PB9 // Default for Arduino connector compatibility
#define PIN_WIRE_SCL            PB8 // Default for Arduino connector compatibility

// Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM in PeripheralPins.c
#define TIMER_TONE              TIM10
//#define TIMER_UART_EMULATED     TIMx

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#define SERIAL_UART_INSTANCE    2 //ex: 2 for Serial2 (USART2)
// DEBUG_UART could be redefined to print on another instance than 'Serial'
//#define DEBUG_UART              ((USART_TypeDef *) U(S)ARTX) // ex: USART3
// DEBUG_UART baudrate, default: 9600 if not defined
//#define DEBUG_UART_BAUDRATE     x
// DEBUG_UART Tx pin name, default: the first one found in PinMap_UART_TX for DEBUG_UART
//#define DEBUG_PINNAME_TX        PX_n // PinName used for TX

// UART Emulation (uncomment if needed, required TIM1)
//#define UART_EMUL_RX            PX_n // PinName used for RX
//#define UART_EMUL_TX            PX_n // PinName used for TX

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           5
#define PIN_SERIAL_TX           4

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