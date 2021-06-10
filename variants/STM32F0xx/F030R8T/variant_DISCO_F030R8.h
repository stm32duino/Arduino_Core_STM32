/*
 *******************************************************************************
 * Copyright (c) 2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#pragma once

/*----------------------------------------------------------------------------
 *        STM32 pins number
 *----------------------------------------------------------------------------*/

// P1 connector Right side (bottom view)
#define PC13                    0
#define PC14                    1
#define PC15                    2
#define PF0                     3
#define PF1                     4
#define PC0                     PIN_A0
#define PC1                     PIN_A1
#define PC2                     PIN_A2
#define PC3                     PIN_A3
#define PA0                     PIN_A4 // USER_BTN
#define PA1                     PIN_A5
#define PA2                     PIN_A6
#define PA3                     PIN_A7
#define PF4                     13
#define PF5                     14
#define PA4                     PIN_A8
#define PA5                     PIN_A9
#define PA6                     PIN_A10
#define PA7                     PIN_A11
#define PC4                     PIN_A12
#define PC5                     PIN_A13
#define PB0                     PIN_A14
#define PB1                     PIN_A15
#define PB2                     23
#define PB10                    24
#define PB11                    25
#define PB12                    26
// P2 connector Left side (bottom view)
#define PB9                     27
#define PB8                     28
#define PB7                     29
#define PB6                     30
#define PB5                     31
#define PB4                     32
#define PB3                     33
#define PD2                     34
#define PC12                    35
#define PC11                    36
#define PC10                    37
#define PA15                    38
#define PA14                    39
#define PF7                     40
#define PF6                     41
#define PA13                    42
#define PA12                    43
#define PA11                    44
#define PA10                    45
#define PA9                     46
#define PA8                     47
#define PC9                     48 // LED_GREEN (LD3)
#define PC8                     49 // LED_BLUE (LD4)
#define PC7                     50
#define PC6                     51
#define PB15                    52
#define PB14                    53
#define PB13                    54

// Alternate pins number
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)

#define NUM_DIGITAL_PINS        55
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN             PC9 // LD3
#endif
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PC8 // LD4

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PA0
#endif

// SPI definitions
// SPI1 is used
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PC4
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PB12
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3           PC6
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

// I2C definitions
// I2C1 is used
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB9
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB8
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM14
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
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
