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

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Define pin names to match digital pin number --> Dx
// It could be used with preprocessor tests (e.g. #if PXn == 3)
// so an enum will not work.
// !!!
// !!! Copy the digitalPin[] array from the variant.cpp
// !!! and remove all '_': PX_n --> PXn
// !!! For NC, comment the line to warn x pin number is NC
// !!! // x is NC
// !!! For duplicated pin name, comment the line to warn x pin number
// !!! is PXn which is already defined with y pin number
// !!! // x is PXn (y)
// !!! Ex:
// !!! ...
// !!! #define PA4  20 // A14
// !!! #define PB4  21
// !!! #define PB5  22
// !!! #define PB3  23
// !!! // 24 is PA4 (20)
// !!! // 25 is PB4 (21)
// !!! #define PA2  26 // A15
// !!! ...
//#define PXn x

#define  PA8    0 
#define  PA9    1
#define  PA10   2
#define  PA11   3
#define  PA12   4
#define  PA13   5
#define  PA14   6
#define  PA15   7
#define  PB2    8
#define  PB3    9
#define  PB4    10
#define  PB5    11
#define PB6     12  
#define  PB7    13
#define  PB8    14      
#define  PB9    15  
#define  PB10   16
#define  PB11   17
#define  PB12   18
#define  PB13   19
#define  PB14   20
#define  PB15   21
#define  PC13   22
#define  PC14   23
#define  PC15   24
#define  PA0    25
#define  PA1    26
#define  PA2    27
#define  PA3    28
#define  PA4    29
#define  PA5    30
#define  PA6    31
#define  PA7    32  
#define  PB0    33
#define  PB1    34
#define  PF0    35
#define  PF1    36


// This must be a literal
// It is used with preprocessor tests (e.g. #if NUM_DIGITAL_PINS > 3)
// so an enum will not work.
#define NUM_DIGITAL_PINS        37

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
#define NUM_ANALOG_INPUTS       10
// Define digital pin number of the first analog input  (i.e. which digital pin is A0)
// First analog pin value (A0) must be greater than or equal to NUM_ANALOG_INPUTS
#define NUM_ANALOG_FIRST        26

// Below ADC, DAC and PWM definitions already done in the core
// Could be redefined here if needed
// ADC resolution is 12bits
#define ADC_RESOLUTION          12
//#define DACC_RESOLUTION         12

// PWM resolution
//#define PWM_RESOLUTION          8
//#define PWM_FREQUENCY           1000
//#define PWM_MAX_DUTY_CYCLE      255

// On-board LED pin number
#define LED_BUILTIN             PA15
#define LED_RED                 LED_BUILTIN
#define LED_GREEN               PB3                 

// On-board user button
//#define USER_BTN                x

// Below SPI and I2C definitions already done in the core
// Could be redefined here if differs from the default one
// SPI Definitions
#define PIN_SPI_SS              PA4 // Default for Arduino connector compatibility
#define PIN_SPI_MOSI            PA7 // Default for Arduino connector compatibility
#define PIN_SPI_MISO            PA6 // Default for Arduino connector compatibility
#define PIN_SPI_SCK             PA5 // Default for Arduino connector compatibility

// I2C Definitions
#define PIN_WIRE_SDA            PB7 // Default for Arduino connector compatibility
#define PIN_WIRE_SCL            PB6 // Default for Arduino connector compatibility

// Timer Definitions (optional)
//Do not use timer used by PWM pins when possible. See PinMap_PWM in PeripheralPins.c
#define TIMER_TONE              TIM3

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

// Optional PIN_SERIALn_RX and PIN_SERIALn_TX where 'n' is the U(S)ART number
// Used when user instanciate a hardware Serial using its peripheral name.
// Example: HardwareSerial mySerial(USART3);
// will use PIN_SERIAL3_RX and PIN_SERIAL3_TX if defined.
//#define PIN_SERIALn_RX          x // For U(S)ARTn RX
//#define PIN_SERIALn_TX          x // For U(S)ARTn TX
//#define PIN_SERIALLP1_RX        x // For LPUART1 RX
//#define PIN_SERIALLP1_TX        x // For LPUART1 TX

//Used for the GPS Module
#define PIN_SERIAL2_TX         PA2
#define PIN_SERIAL2_RX         PA3

// SD card slot Definitions
// SD detect signal can be defined if required
//#define SD_DETECT_PIN           x
// SD Read/Write timeout, default value defined in STM32SD library
//#define SD_DATATIMEOUT          x

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
