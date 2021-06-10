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

/*------------------------------------------------------------------
 *        Pins
 * Header pin numbers are numbered anticlockwise from the USB socket,
 * ... as in the schematic.
 * ... Right / Left / Top: oriented relative to USB socket at bottom
 *
 *------------------------------------------------------------------*/

// Header right (as viewed with USB socket at the bottom), numbered from bottom
#define PE3                     0  // Header right, pin 1
#define PE2                     1  // Header right, pin 2
#define PE5                     2  // Header right, pin 3
#define PE4                     3  // Header right, pin 4
#define PC13                    4  // Header right, pin 5
#define PE6                     5  // Header right, pin 6
// Header right, pin 7 = GND
// Header right, pin 8 = 3.3V
#define PC1                     PIN_A11  // Header right, pin 9
#define PC0                     PIN_A10  // Header right, pin 10
#define PA0                     PIN_A0 // Header right, pin 11
#define PC2                     PIN_A12 // Header right, pin 12
#define PA2                     PIN_A2 // Header right, pin 13
#define PA1                     PIN_A1 // Header right, pin 14
#define PA3                     PIN_A3 // Header right, pin 15
#define PC3                     PIN_A13 // Header right, pin 16
#define PA5                     PIN_A5  // Header right, pin 17
#define PA4                     PIN_A4 // Header right, pin 18
#define PA7                     PIN_A7 // Header right, pin 19
#define PA6                     PIN_A6 // Header right, pin 20
#define PC5                     PIN_A15 // Header right, pin 21
#define PC4                     PIN_A14 // Header right, pin 22
#define PB1                     PIN_A9 // Header right, pin 23
#define PB0                     PIN_A8 // Header right, pin 24
#define PB9                     22 // Header right, pin 25
#define PB8                     23 // Header right, pin 26
#define PE7                     24 // Header right, pin 27
#define PE1                     25 // Header right, pin 28
#define PE9                     26 // Header right, pin 29
#define PE8                     27 // Header right, pin 30
#define PB2                     28 // Header right, pin 31
#define PE10                    29 // Header right, pin 32

// Header top (as viewed with USB socket at the bottom), numbered from right
#define PE11                    30 // Header top, pin 1
#define PE12                    31 // Header top, pin 2
#define PE13                    32 // Header top, pin 3
#define PE14                    33 // Header top, pin 4
#define PE15                    34 // Header top, pin 5
#define PB10                    35 // Header top, pin 6
#define PB11                    36 // Header top, pin 7
// Header top, pin 8 = GND
#define PB12                    37 // Header top, pin 9
// Header top, pin 10 = 3.3V
#define PB14                    38 // Header top, pin 11
#define PB13                    39 // Header top, pin 12
#define PD8                     40 // Header top, pin 13
#define PB15                    41 // Header top, pin 14
#define PD10                    42 // Header top, pin 15
#define PD9                     43 // Header top, pin 16
#define PD12                    44 // Header top, pin 17
#define PD11                    45 // Header top, pin 18
#define PD14                    46 // Header top, pin 19
#define PD13                    47 // Header top, pin 20
#define PC6                     48 // Header top, pin 21
#define PD15                    49 // Header top, pin 22
#define PC8                     50 // Header top, pin 23
#define PC7                     51 // Header top, pin 24

// Header left (as viewed with USB socket at the bottom), numbered from top
// Header left, pin 1 = GND
// Header left, pin 2 = Vcc (5V)
#define PA8                     52 // Header left, pin 3
#define PC9                     53 // Header left, pin 4
#define PA10                    54 // Header left, pin 5
#define PA9                     55 // Header left, pin 6
#define PA12                    56 // Header left, pin 7 and USB_DP
#define PA11                    57 // Header left, pin 8 and USB_DM
#define PA14                    58 // Header left, pin 9
#define PA13                    59 // Header left, pin 10
#define PC10                    60 // Header left, pin 11
#define PA15                    61 // Header left, pin 12
#define PC12                    62 // Header left, pin 13
#define PC11                    63 // Header left, pin 14
#define PD1                     64 // Header left, pin 15
#define PD0                     65 // Header left, pin 16
#define PD3                     66 // Header left, pin 17
#define PD2                     67 // Header left, pin 18
#define PD5                     68 // Header left, pin 19
#define PD4                     69 // Header left, pin 20
#define PD7                     70 // Header left, pin 21
#define PD6                     71 // Header left, pin 22
#define PB4                     72 // Header left, pin 23
#define PB3                     73 // Header left, pin 24
#define PB6                     74 // Header left, pin 25
#define PB5                     75 // Header left, pin 26
#define PE0                     76 // Header left, pin 27 and LED_BUILTIN
#define PB7                     77 // Header left, pin 28

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

#define NUM_DIGITAL_PINS        78  // Number of definitions above
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PE0
#endif

// On-board user button
#define BTN_K_UP                PD15
#ifndef USER_BTN
  #define USER_BTN              BTN_K_UP
#endif

// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PB6
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PB5
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB4
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB3
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
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for 'Serial1' instance
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_SD_MODULE_DISABLED)
  #define HAL_SD_MODULE_ENABLED
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
  // SERIAL_PORT_HARDWARE       Hardware serial port.
  //
  // SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
  //                            pins are NOT connected to anything by default.
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial1
  #endif
#endif
