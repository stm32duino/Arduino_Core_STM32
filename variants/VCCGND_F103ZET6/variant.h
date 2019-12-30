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
// !!! #define PA4  20 // A14 <-- if NUM_ANALOG_FIRST not defined
// !!! or
// !!! #define PA4  A14 // 20 <-- if NUM_ANALOG_FIRST defined
// !!! #define PB4  21
// !!! #define PB5  22
// !!! #define PB3  23
// !!! // 24 is PA4 (20)
// !!! // 25 is PB4 (21)
// !!! #define PA2  26 // A15 <-- if NUM_ANALOG_FIRST not defined
// !!! or
// !!! #define PA2  A15 // 26 <-- if NUM_ANALOG_FIRST defined
// !!! ...
//#define PXn x
#define  PE0   0
#define  PE1   1
#define  PE2   2
#define  PE3   3
#define  PE4   4
#define  PE5   5
#define  PE6   6
#define  PC13  7
#define  PC14  8 // LSE
#define  PC15  9 // LSE
#define  PF0   10
#define  PF1   11
#define  PF2   12
#define  PF3   13
#define  PF4   14
#define  PF5   15
#define  PF6   16
#define  PF7   17
#define  PF8   18
#define  PF9   19
#define  PF10  20
#define  PC0   21
#define  PC1   22
#define  PC2   23
#define  PC3   24
#define  PA0   25
#define  PA1   26
#define  PA2   27
#define  PA3   28
#define  PA4   29
#define  PA5   30 // SPI SCLK
#define  PA6   31 // SPI MISO
#define  PA7   32 // SPI MOSI
#define  PC4   33
#define  PC5   34
#define  PB0   35
#define  PB1   36
#define  PB2   37 // BOOT1
#define  PF11  38
#define  PF12  39
#define  PF13  40
#define  PF14  41
#define  PF15  42
#define  PG0   43
#define  PG1   44
#define  PE7   45
#define  PE8   46
#define  PE9   47
#define  PE10  48
#define  PE11  49
#define  PE12  50
#define  PE13  51
#define  PE14  52
#define  PE15  53
#define  PB10  54
#define  PB11  55
#define  PB12  56
#define  PB13  57
#define  PB14  58
#define  PB15  59
#define  PD8   60
#define  PD9   61
#define  PD10  62
#define  PD11  63
#define  PD12  64
#define  PD13  65
#define  PD14  66
#define  PD15  67
#define  PG2   68
#define  PG3   69
#define  PG4   70
#define  PG5   71
#define  PG6   72
#define  PG7   73
#define  PG8   74
#define  PC6   75
#define  PC7   76
#define  PC8   77
#define  PC9   78
#define  PA8   79
#define  PA9   80
#define  PA10  81
#define  PA11  82 // USB DM
#define  PA12  83 // USB DP
#define  PA13  84 // SWDI0
#define  PA14  85 // SWCLK
#define  PA15  86
#define  PC10  87
#define  PC11  88
#define  PC12  89
#define  PD0   90
#define  PD1   91
#define  PD2   92
#define  PD3   93
#define  PD4   94
#define  PD5   95
#define  PD6   96
#define  PD7   97
#define  PG9   98
#define  PG10  99
#define  PG11  100
#define  PG12  101
#define  PG13  102
#define  PG14  103
#define  PG15  104 // LEDBUILTIN
#define  PB3   105
#define  PB4   106
#define  PB5   107
#define  PB6   108 // I2C SCL
#define  PB7   109 // I2C SDA
#define  PB8   110
#define  PB9   111

// This must be a literal
// It is used with preprocessor tests (e.g. #if NUM_DIGITAL_PINS > 3)
// so an enum will not work.
#define NUM_DIGITAL_PINS        112

// Allow to define Arduino style alias for analog input pin number --> Ax
// If no analog pin required then NUM_ANALOG_INPUTS could not be defined
// or set to `0`
// All pins are digital, analog inputs are a subset of digital pins.
// This must be a literal
// It is used with preprocessor tests (e.g. #if NUM_ANALOG_INPUTS > 3)
// so an enum will not work.
// !!!
// !!! It must be aligned with the number of analog PinName
// !!! defined in digitalPin[] array in variant.cpp
// !!!
#define NUM_ANALOG_INPUTS       6

// They are 2 possibles way to define analog pins:
//-------------------------------------------------------------------------------------------
//   - If they are contiguous in the digitalPin array:
//     Simply defined `NUM_ANALOG_FIRST` and all pins Ax will be automatically defined.
//     It define the digital pin number of the first analog input  (i.e. which digital pin is A0)
//     First analog pin value (A0) must be greater than or equal to NUM_ANALOG_INPUTS
//     This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
//     defined in pin_arduino.h
#define NUM_ANALOG_FIRST        112
//------------------------------------OR------------------------------------------------------
//   - If they are not contiguous in the digitalPin array:
//     Add an analogInputPin array in the variant.cpp without defining NUM_ANALOG_FIRST
//     In that case the defined PYn for analog pin have to define the Ax definition instead of
//     index in digitalPin[] array:
//     #define PA4  A14
//-------------------------------------------------------------------------------------------


// Below ADC and PWM definitions already done in the core
// Could be redefined here if needed
// ADC resolution is 10 bits
//#define ADC_RESOLUTION          10

// PWM resolution
//#define PWM_RESOLUTION          8
//#define PWM_FREQUENCY           1000
//#define PWM_MAX_DUTY_CYCLE      255

// On-board LED pin number
#define LED_BUILTIN             PG15
#define LED_BLUE                LED_BUILTIN

// On-board user button
//#define USER_BTN                x

// Below SPI and I2C definitions already done in the core
// Could be redefined here if differs from the default one
// SPI Definitions
//#define PIN_SPI_SS              10 // Default for Arduino connector compatibility
#define PIN_SPI_MOSI            PA7 // Default for Arduino connector compatibility
#define PIN_SPI_MISO            PA6 // Default for Arduino connector compatibility
#define PIN_SPI_SCK             PA5 // Default for Arduino connector compatibility

// I2C Definitions
#define PIN_WIRE_SDA            PB7 // Default for Arduino connector compatibility
#define PIN_WIRE_SCL            PB6 // Default for Arduino connector compatibility

// I2C timing definitions (optional), avoid time spent to compute if defined
// * I2C_TIMING_SM for Standard Mode (100kHz)
// * I2C_TIMING_FM for Fast Mode (400kHz)
// * I2C_TIMING_FMP for Fast Mode Plus (1000kHz)
//#define I2C_TIMING_SM           0x00000000
//#define I2C_TIMING_FM           0x00000000
//#define I2C_TIMING_FMP          0x00000000

// Timer Definitions (optional)
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

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

// UART Definitions
#define SERIAL_UART_INSTANCE    2
// Default pin used for 'Serial2' instance
#define PIN_SERIAL1_RX           PA3
#define PIN_SERIAL1_TX           PA2

// UART Definitions
#define SERIAL_UART_INSTANCE    3
// Default pin used for 'Serial3' instance
#define PIN_SERIAL2_RX           PB11
#define PIN_SERIAL2_TX           PB10


// Optional PIN_SERIALn_RX and PIN_SERIALn_TX where 'n' is the U(S)ART number
// Used when user instanciate a hardware Serial using its peripheral name.
// Example: HardwareSerial mySerial(USART3);
// will use PIN_SERIAL3_RX and PIN_SERIAL3_TX if defined.
//#define PIN_SERIALn_RX          x // For U(S)ARTn RX
//#define PIN_SERIALn_TX          x // For U(S)ARTn TX
//#define PIN_SERIALLP1_RX        x // For LPUART1 RX
//#define PIN_SERIALLP1_TX        x // For LPUART1 TX

// SD card slot Definitions
// SD detect signal can be defined if required
#define SD_DETECT_PIN           PF10
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
#define SERIAL_PORT_HARDWARE    Serial1
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
