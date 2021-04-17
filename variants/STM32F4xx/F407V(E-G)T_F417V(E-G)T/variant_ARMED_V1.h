/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

/*----------------------------------------------------------------------------
 *        STM32 pins number
 *----------------------------------------------------------------------------*/

#define PA0                     0  //D0
#define PA1                     1  //D1
#define PA2                     2  //D2
#define PA3                     3  //D3
#define PA4                     4  //D4
#define PA5                     5  //D5
#define PA6                     6  //D6
#define PA7                     7  //D7
#define PA8                     8  //D8
#define PA9                     9  //D9
#define PA10                    10 //D10
#define PA11                    11 //D11
#define PA12                    12 //D12
#define PA13                    13 //D13
#define PA14                    14 //D14
#define PA15                    15 //D15
#define PB0                     16 //D16
#define PB1                     17 //D17
#define PB2                     18 //D18
#define PB3                     19 //D19
#define PB4                     20 //D20
#define PB5                     21 //D21
#define PB6                     22 //D22
#define PB7                     23 //D23
#define PB8                     24 //D24
#define PB9                     25 //D25
#define PB10                    26 //D26
#define PB11                    27 //D27
#define PB12                    28 //D28
#define PB13                    29 //D29
#define PB14                    30 //D30
#define PB15                    31 //D31
#define PC0                     PIN_A0 //D32
#define PC1                     PIN_A1 //D33
#define PC2                     PIN_A2 //D34
#define PC3                     35 //D35
#define PC4                     36 //D36
#define PC5                     37 //D37
#define PC6                     38 //D38
#define PC7                     39 //D39
#define PC8                     40 //D40
#define PC9                     41 //D41
#define PC10                    42 //D42
#define PC11                    43 //D43
#define PC12                    44 //D44
#define PC13                    45 //D45
#define PC14                    46 //D46
#define PC15                    47 //D47
#define PD0                     48 //D48
#define PD1                     49 //D49
#define PD2                     50 //D50
#define PD3                     51 //D51
#define PD4                     52 //D52
#define PD5                     53 //D53
#define PD6                     54 //D54
#define PD7                     55 //D55
#define PD8                     56 //D56
#define PD9                     57 //D57
#define PD10                    58 //D58
#define PD11                    59 //D59
#define PD12                    60 //D60
#define PD13                    61 //D61
#define PD14                    62 //D62
#define PD15                    63 //D63
#define PE0                     64 //D64
#define PE1                     65 //D65
#define PE2                     66 //D66
#define PE3                     67 //D67
#define PE4                     68 //D68
#define PE5                     69 //D69
#define PE6                     70 //D70
#define PE7                     71 //D71
#define PE8                     72 //D72
#define PE9                     73 //D73
#define PE10                    74 //D74
#define PE11                    75 //D75
#define PE12                    76 //D76
#define PE13                    77 //D77
#define PE14                    78 //D78
#define PE15                    79 //D79

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA0_ALT2                (PA0  | ALT2)
#define PA1_ALT1                (PA1  | ALT1)
#define PA1_ALT2                (PA1  | ALT2)
#define PA2_ALT1                (PA2  | ALT1)
#define PA2_ALT2                (PA2  | ALT2)
#define PA3_ALT1                (PA3  | ALT1)
#define PA3_ALT2                (PA3  | ALT2)
#define PA4_ALT1                (PA4  | ALT1)
#define PA5_ALT1                (PA5  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC0_ALT2                (PC0  | ALT2)
#define PC1_ALT1                (PC1  | ALT1)
#define PC1_ALT2                (PC1  | ALT2)
#define PC2_ALT1                (PC2  | ALT1)
#define PC2_ALT2                (PC2  | ALT2)
#define PC3_ALT1                (PC3  | ALT1)
#define PC3_ALT2                (PC3  | ALT2)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

#define NUM_DIGITAL_PINS        80
#define NUM_ANALOG_INPUTS       3

// PWM resolution
#define PWM_FREQUENCY           20000 // >= 20 Khz => inaudible noise for fans
#define PWM_MAX_DUTY_CYCLE      255

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PB7
#endif
#define LED_HEARTBEAT           LED_BUILTIN

// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PE7
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA7
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PA6
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PA5
#endif

// I2C Definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB9
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB8
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM10
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM11
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  4 // Connected to SER1 header
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PC11
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PC10
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
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
#endif
