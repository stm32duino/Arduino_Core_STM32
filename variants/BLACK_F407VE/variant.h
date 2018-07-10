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

enum {
  // Left Side
  //Ext   //Int
  //5V    //5V
  //5V    //5V
  //3V3   //3V3
  //3V3   //3V3
  //GND   //GND
  PE2,    PE3,
  PE4,    PE5,   // PE4: BUT K0  PE5: BUT K1
  PE6,    PC13,
  PC0,    PC1,
  PC2,    PC3,
  //VREF- //VREF+
  PA0,    PA1,   // PA0(WK_UP): BUT K_UP
  PA2,    PA3,
  PA4,    PA5,
  PA6,    PA7,   // PA6: LED D2  PA7: LED D3  (active LOW)
  PC4,    PC5,
  PB0,    PB1,
  PE7,    PE8,
  PE9,    PE10,
  PE11,   PE12,
  PE13,   PE14,
  PE15,   PB10,
  PB11,   PB12,
  PB13,   PB14,
  // Right Side
  //Int   //Ext
  //3V3   //3V3
  //3V3   //3V3
  //BOOT0 //BOOT1
  //GND   //GND
  //GND   //GND
  PE1,    PE0,
  PB9,    PB8,
  PB7,    PB6,
  PB5,    PB3,
  PD7,    PD6,
  PD5,    PD4,
  PD3,    PD2,
  PD1,    PD0,
  PC12,   PC11,
  PC10,   PA15,
  PA12,   PA11, // PA11: USB_DM  PA12: USB_DP
  PA10,   PA9,
  PA8,    PC9,
  PC8,    PC7,
  PC6,    PD15,
  PD14,   PD13,
  PD12,   PD11,
  PD10,   PD9,
  PD8,    PB15,
  PB4,
  // Analog pins
  PA0_A,
  PA1_A,
  PA2_A,
  PA3_A,
  PA4_A,
  PA5_A,
  PB0_A,
  PB1_A,
  PC0_A,
  PC1_A,
  PC2_A,
  PC3_A,
  PC4_A,
  PC5_A,
  PEND
};

// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        89
// This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       14
#define NUM_ANALOG_FIRST        75

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
#define LED_D2                  PA6
#define LED_D3                  PA7
#define LED_BUILTIN             LED_D2
#define LED_GREEN               LED_D2

// On-board user button
#define BTN_K_UP                PA0
#define BTN_K0                  PE4
#define BTN_K1                  PE5
#define USER_BTN                BTN_K0

// Below SPI and I2C definitions already done in the core
// Could be redefined here if differs from the default one
// SPI Definitions
#define PIN_SPI_SS              PB7 // NRF24 connector
#define PIN_SPI_MOSI            PB5 // NRF24 connector
#define PIN_SPI_MISO            PB4 // NRF24 connector
#define PIN_SPI_SCK             PB3 // NRF24 connector

// I2C Definitions
//#define PIN_WIRE_SDA            14 // Default for Arduino connector compatibility
//#define PIN_WIRE_SCL            15 // Default for Arduino connector compatibility

// Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM in PeripheralPins.c
#define TIMER_TONE              TIM6
//#define TIMER_UART_EMULATED     TIMx

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#define SERIAL_UART_INSTANCE    1 //ex: 2 for Serial2 (USART2)
// DEBUG_UART could be redefined to print on another instance than 'Serial'
//#define DEBUG_UART              ((USART_TypeDef *) U(S)ARTX) // ex: USART3
// DEBUG_UART baudrate, default: 9600 if not defined
//#define DEBUG_UART_BAUDRATE     x
// DEBUG_UART Tx pin name, default: the first one found in PinMap_UART_TX for DEBUG_UART
//#define DEBUG_PINNAME_TX        PX_n // PinName used for TX

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
