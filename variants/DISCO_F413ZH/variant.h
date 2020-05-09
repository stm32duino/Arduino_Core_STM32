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

#define PF6  0  // D0
#define PF7  1  // D1
#define PG13 2  // D2
#define PF10 3  // D3
#define PB6  4  // D4
#define PE6  5  // D5
#define PB0  A8 // D6
#define PC13 7  // D7
#define PA4  A11// D8
#define PB8  9  // D9
#define PA15 10 // D10 - SPI_SSEL
#define PB5  11 // D11 - SPI_MOSI, ISM43362_WIFI_MOSI
#define PB4  12 // D12 - SPI_MISO, ISM43362_WIFI_MISO
#define PB12 13 // D13 - SPI_SCK, LED_GREEN, ISM43362_WIFI_SCLK
#define PB11 14 // D14 - I2C_SDA
#define PB10 15 // D15 - I2C_SCL
#define PC0  A0 // D16
#define PA1  A1 // D17
#define PA2  A2 // D18
#define PA5  A3 // D19
#define PB1  A4 // D20
#define PC4  A5 // D21
#define PG14 22 // D22 - STLink Tx
#define PG9  23 // D23 - STLink Rx
// not on connector
#define PE3  24  // D24 - LD4, LED1_RED
#define PC5  A15 // D25 - LD3, LED2_GREEN
#define PA0  A9  // D26 - User button
#define PG11 27  // D27 - ISM43362_WIFI_NSS
#define PH1  28  // D28 - ISM43362_WIFI_RESET
#define PG12 29  // D29 - ISM43362_WIFI_DATAREADY
#define PB15 30  // D30 - ISM43362_WIFI_WAKEUP
#define PE2  31  // D31
#define PE4  32  // D32
#define PE5  33  // D33
#define PC14 34  // D34
#define PC15 35  // D35
#define PF0  36  // D36
#define PF1  37  // D37
#define PF2  38  // D38
#define PF3  39  // D39
#define PF4  40  // D40
#define PF5  41  // D41
#define PF8  42  // D42
#define PF9  43  // D43
#define PC1  A12 // D44
#define PC2  A13 // D45
#define PC3  A14 // D46
#define PA3  A10 // D47
#define PA6  A6  // D48
#define PA7  A7  // D49
#define PB2  50  // D50
#define PF11 51  // D51
#define PF12 52  // D52
#define PF13 53  // D53
#define PF14 54  // D54
#define PF15 55  // D55
#define PG0  56  // D56
#define PG1  57  // D57
#define PE7  58  // D58
#define PE8  59  // D59
#define PE9  60  // D60
#define PE10 61  // D61
#define PE11 62  // D62
#define PE12 63  // D63
#define PE13 64  // D64
#define PE14 65  // D65
#define PE15 66  // D66
#define PB13 67  // D67
#define PB14 68  // D68
#define PB15 69  // D69
#define PD8  70  // D70
#define PD9  71  // D71
#define PD10 72  // D72
#define PD11 73  // D73
#define PD12 74  // D74
#define PD13 75  // D75
#define PD14 76  // D76
#define PD15 77  // D77
#define PG2  78  // D78
#define PG3  79  // D79
#define PG4  80  // D80
#define PG5  81  // D81
#define PG6  82  // D82
#define PG7  83  // D83
#define PG8  84  // D84
#define PC6  85  // D85
#define PC7  86  // D86
#define PC8  87  // D87
#define PC9  88  // D88
#define PA8  89  // D89
#define PA9  90  // D90
#define PA10 91  // D91
#define PA11 92  // D92
#define PA12 93  // D93
#define PA13 94  // D94
#define PA14 95  // D95
#define PC10 96  // D96
#define PC11 97  // D97
#define PC12 98  // D98
#define PD0  99  // D99
#define PD1  100 // D100
#define PD2  101 // D101
#define PD3  102 // D102
#define PD4  103 // D103
#define PD5  104 // D104
#define PD6  105 // D105
#define PD7  106 // D106
#define PG10 107 // D107
#define PG11 108 // D108
#define PG12 109 // D109
#define PG15 110 // D110
#define PB3  111 // D111
#define PB7  112 // D112
#define PB9  113 // D113
#define PE0  114 // D114
#define PE1  115 // D115

// This must be a literal
// It is used with preprocessor tests (e.g. #if NUM_DIGITAL_PINS > 3)
// so an enum will not work.
#define NUM_DIGITAL_PINS        116

// Allow to define Arduino style alias for analog input pin number --> Ax
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#define LED_BUILTIN             PB12
#define LED_GREEN               LED_BUILTIN
#define LED_GREEN2              PC5
#define LED_RED                 PE3

// On-board user button
#define USER_BTN                PA0

// Timer Definitions (optional)
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    2 //ex: 2 for Serial2 (USART2)

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PG9
#define PIN_SERIAL_TX           PG14

// SD detect signal
#define SD_DETECT_PIN           PF11
/* Extra HAL modules */
#define HAL_DAC_MODULE_ENABLED
#define HAL_SD_MODULE_ENABLED

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
