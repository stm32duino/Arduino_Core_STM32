/*
 *******************************************************************************
 * Copyright (c) 2017-2021, STMicroelectronics
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
 *        Pins
 *----------------------------------------------------------------------------*/

#define PA3                     0
#define PA2                     1
#define PA10                    2
#define PB13                    3
#define PB5                     4
#define PB7                     5
#define PB2                     6
#define PA8                     7
#define PA9                     8
#define PB12                    9
#define PB6                     10
#define PB15                    11
#define PB14                    12
// 13 is PB13 (3) as default SB2 is closed
#define PB9                     14 // Also on A4 if SB11 closed
#define PB8                     15 // Also on A5 if SB12 closed
// Connector CN2
// 16 is NC - BOOT0
#define PA13                    17 // SWD
#define PA14                    18 // SWD
#define PH1                     19 // named A5 but no analog (SB10 )
#define PH0                     20 // named A4 but no analog (SB1)
// Connector CN3
#define PA1                     21
#define PC2                     22
#define PC1                     23
#define PA12                    24
#define PA11                    25
#define PA0                     PIN_A0 // A1
// 27 is A1 an alias for A0 - requires closing solder bridge SB7
#define PA4                     PIN_A2 //A3 - RADIO_DIO_5_PORT
// 29 is A3 an alias for A2 - requires closing solder bridge SB8
#define PA5                     30 // RADIO_DIO_4_PORT on pin 13 if SB3 closed
#define PC0                     31 // RADIO_RESET_PORT
#define PA7                     32 // RADIO_MOSI_PORT
#define PA6                     33 // RADIO_MISO_PORT
#define PB3                     34 // RADIO_SCLK_PORT
#define PA15                    35 // RADIO_NSS_PORT
#define PB4                     36 // RADIO_DIO_0_PORT
#define PB1                     37 // RADIO_DIO_1_PORT
#define PB0                     38 // RADIO_DIO_2_PORT

// Alternate pins number
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA14_ALT1               (PA14 | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)

#define NUM_DIGITAL_PINS        39
#define NUM_ANALOG_INPUTS       4

// On-board LED pin number
#define LED_GREEN               PB5
#define LED_LD1                 LED_GREEN
#define LED_RED                 PA5
#define LED_LD2                 LED_RED
#define LED_BLUE                PB6
#define LED_LD3                 LED_BLUE
#define LED_RED2                PB7
#define LED_LD4                 LED_RED2
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PB2
#endif

// LORA
#define RADIO_RESET_PORT        PC0
#define RADIO_MOSI_PORT         PA7
#define RADIO_MISO_PORT         PA6
#define RADIO_SCLK_PORT         PB3
#define RADIO_NSS_PORT          PA15
#define RADIO_DIO_0_PORT        PB4
#define RADIO_DIO_1_PORT        PB1
#define RADIO_DIO_2_PORT        PB0
#define RADIO_DIO_3_PORT        PC13
#define RADIO_DIO_4_PORT        PA5
#define RADIO_DIO_5_PORT        PA4

//Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  101 //Connected to ST-Link
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA3
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA2
#endif

/* Backward compatibility */
#define ARDUINO_DISCO_L072CZ_LRWAN1

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
