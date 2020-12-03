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
 *        STM32 pins number
 *----------------------------------------------------------------------------*/
#define PD9  0 // USART3_RX
#define PD8  1 // USART3_TX
#define PF15 2
#define PE13 3
#define PF14 4
#define PE11 5
#define PE9  6
#define PF13 7
#define PF12 8
#define PD15 9
#define PD14 10
#define PA7  11 // SPI_A_MOSI
#define PA6  12 // SPI_A_MISO
#define PA5  13 // SPI_A_SCK
#define PB9  14 // I2C_A_SDA
#define PB8  15 // I2C_A_SCL
#define PC6  16
#define PD11 17
#define PB13 18
#define PD12 19
#define PA4 20
#define PB4 21
#define PB5 22 // SPI_B_MOSI
#define PB3 23 // SPI_B_SCK
#define PA4 24 // SPI_B_NSS
#define PB4 25 // SPI_B_MISO
#define PA2 26
#define PB10 27
#define PE15 28
#define PB0 29
#define PE12 30
#define PE14 31
#define PA0 32
#define PB0 33
#define PE0 34
#define PB11 35
#define PB10 36
#define PE15 37
#define PE14 38
#define PE12 39
#define PE10 40
#define PE7 41
#define PE8 42
#define PC8 43
#define PC9 44
#define PC10 45
#define PC11 46
#define PC12 47
#define PD2 48
#define PF3 49
#define PF5 50
#define PD7 51
#define PD6 52
#define PD5 53
#define PD4 54
#define PD3 55
#define PE2 56
#define PE4 57
#define PE5 58
#define PE6 59
#define PE3 60
#define PF8 61
#define PF7 62
#define PF9 63
#define PG1 64
#define PG0 65
#define PD1 66
#define PD0 67
#define PF0 68
#define PF1 69
#define PF2 70
#define PB6 71
#define PB2 72
// ST Morpho
#define PA8  73
#define PA9  74
#define PA10 75
#define PA11 76
#define PA12 77
#define PA15 78
#define PB7  79  // LED_BLUE
#define PB14 80  // LED_RED
#define PC7  81  // LED_GREEN
#define PC13 82  // USER_BTN
#define PC14 83
#define PC15 84
#define PD10 85
#define PD11 86
#define PD12 87
#define PD13 88
#define PE1  89
#define PF10 90
#define PF11 91
#define PG2  92
#define PG3  93
#define PG4  94
#define PG5  95
#define PG6  96
#define PG7  97  // Serial Tx
#define PG8  98  // Serial Rx
#define PG9  99
#define PG10 100
#define PG11 101
#define PG12 102
#define PG13 103
#define PG14 104
#define PH0  105
#define PH1  106
// Analog pins
#define PA3                     A0
#define PA2                     A1
#define PC3                     A2
#define PB0                     A3
#define PC1                     A4
#define PC0                     A5
#define PB1                     A6
#define PC2                     A7
#define PA1                     A8

#define PA0_ALT0                A14
#define PA1_ALT0                A15
#define PA1_ALT1                113
#define PA2_ALT0                A16
#define PA2_ALT1                115
#define PA3_ALT0                A17
#define PA3_ALT1                117
#define PA4_ALT0                A18
#define PA5_ALT0                A19
#define PA6_ALT0                A20
#define PA7_ALT0                A21
#define PA7_ALT1                122
#define PA7_ALT2                123
#define PA15_ALT0               124
#define PB0_ALT0                A22
#define PB0_ALT1                126
#define PB1_ALT0                A23
#define PB1_ALT1                128
#define PB3_ALT0                129
#define PB4_ALT0                130
#define PB5_ALT0                131
#define PB6_ALT0                132
#define PB7_ALT0                133
#define PB8_ALT0                134
#define PB9_ALT0                135
#define PB10_ALT0               136
#define PB11_ALT0               137
#define PB13_ALT0               138
#define PB14_ALT0               139
#define PB14_ALT1               140
#define PB15_ALT0               141
#define PB15_ALT1               142
#define PC0_ALT0                A24
#define PC1_ALT0                A25
#define PC2_ALT0                A26
#define PC3_ALT0                A27
#define PC6_ALT0                147
#define PC7_ALT0                148
#define PC8_ALT0                149
#define PC9_ALT0                150
#define PC10_ALT0               151
#define PC11_ALT0               152
#define PF9_ALT0                153

#define NUM_DIGITAL_PINS        154
#define NUM_ALTERNATE_PINS      43
#define NUM_ANALOG_INPUTS       28

// On-board LED pin number
#ifndef LED_BUILTIN
#define LED_BUILTIN             PC7
#endif
// green led
#ifndef LED1
#define LED1              PC7
#endif
// blue led
#ifndef LED2
#define LED2              PB7
#endif
// red led
#ifndef LED3
#define LED3              PA9
#endif

// On-board user button
#ifndef USER_BTN
#define USER_BTN                PC13
#endif

// SPI definitions
#ifndef PIN_SPI_SS
#define PIN_SPI_SS              PD14
#endif
#ifndef PIN_SPI_MOSI
#define PIN_SPI_MOSI            PA7
#endif
#ifndef PIN_SPI_MISO
#define PIN_SPI_MISO            PA6
#endif
#ifndef PIN_SPI_SCK
#define PIN_SPI_SCK             PA5
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
#define PIN_WIRE_SDA            PB9
#endif
#ifndef PIN_WIRE_SCL
#define PIN_WIRE_SCL            PB8
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
#define TIMER_TONE              TIM6
#endif
#ifndef TIMER_SERVO
#define TIMER_SERVO             TIM7
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
#define SERIAL_UART_INSTANCE    0
#endif

// Default pin used for generic 'Serial' instance (ex: stlink)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
#define PIN_SERIAL_RX           PG8
#endif
#ifndef PIN_SERIAL_TX
#define PIN_SERIAL_TX           PG7
#endif

// Extra HAL modules
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
  #define SERIAL_PORT_MONITOR   Serial
  #define SERIAL_PORT_HARDWARE  Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
