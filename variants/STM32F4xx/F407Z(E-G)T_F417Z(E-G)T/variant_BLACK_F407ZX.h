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
 *        STM32 pins number
 *----------------------------------------------------------------------------*/

// Left Side
#define PB12                    0
#define PB13                    1
#define PB14                    2
#define PB15                    3
#define PD8                     4
#define PD9                     5
#define PD10                    6
#define PD11                    7
#define PD12                    8
#define PD13                    9
#define PD14                    10
#define PD15                    11
#define PG2                     12
#define PG3                     13
#define PG4                     14
#define PG5                     15
#define PG6                     16
#define PG7                     17
#define PG8                     18
#define PC6                     19
#define PC7                     20
#define PC8                     21
#define PC9                     22
#define PA8                     23
#define PA9                     24
#define PA10                    25
#define PA11                    26 // USB_DM
#define PA12                    27 // USB_DP
#define PA13                    28
#define PA14                    29
#define PA15                    30
#define PC10                    31
#define PC11                    32
#define PC12                    33
#define PD0                     34
#define PD1                     35
#define PD2                     36
#define PD3                     37
#define PD4                     38
#define PD5                     39
#define PD6                     40
#define PD7                     41
#define PG9                     42
#define PG10                    43
#define PG11                    44
#define PG12                    45
#define PG13                    46
#define PG14                    47
#define PG15                    48
#define PB3                     49
#define PB4                     50
#define PB5                     51
#define PB6                     52
#define PB7                     53
#define PB8                     54
#define PB9                     55

// Right Side
#define PB10                    56
#define PB11                    57
#define PE14                    58
#define PE15                    59
#define PE12                    60
#define PE13                    61
#define PE10                    62
#define PE11                    63
#define PE8                     64
#define PE9                     65
#define PG1                     66
#define PE7                     67
#define PF15                    68
#define PG0                     69
#define PF13                    70
#define PF14                    71
#define PF11                    72
#define PF12                    73
#define PB2                     74
#define PB1                     PIN_A0
#define PC5                     PIN_A1
#define PB0                     PIN_A2
#define PA7                     PIN_A3
#define PC4                     PIN_A4
#define PA5                     PIN_A5
#define PA6                     PIN_A6
#define PA3                     PIN_A7
#define PA4                     PIN_A8
#define PA1                     PIN_A9
#define PA2                     PIN_A10
#define PC3                     PIN_A11
#define PA0                     PIN_A12 //PA_0(WK_UP): BUT K_UP)
#define PC1                     PIN_A13
#define PC2                     PIN_A14
#define PC0                     PIN_A15
#define PF8                     PIN_A16
#define PF6                     PIN_A17
#define PF7                     PIN_A18
#define PF9                     94 // LED D1 (active low)
#define PF10                    95 // LED D2 (active low)
#define PF4                     96
#define PF5                     97
#define PF2                     98
#define PF3                     99
#define PF0                     100
#define PF1                     101
#define PE6                     102
#define PC13                    103
#define PE4                     104 // BUT K0
#define PE5                     105 // BUT K1
#define PE2                     106
#define PE3                     107
#define PE0                     108
#define PE1                     109

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

#define NUM_DIGITAL_PINS        110
#define NUM_ANALOG_INPUTS       19

// On-board LED pin number
#define LED_D2                  PF10
#define LED_D1                  PF9

#define LED_GREEN               LED_D2
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_D2
#endif

// On-board user button
#define BTN_WK_UP               PA0
#define BTN_K0                  PE4
#define BTN_K1                  PE3
#ifndef USER_BTN
  #define USER_BTN              BTN_K0
#endif

// Below SPI and I2C definitions already done in the core
// Could be redefined here if differs from the default one
// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PB7 // NRF24 connector
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PB0 // W25Q16 (on board flash)
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PB5 // NRF24 connector & W25Q16 (on board flash)
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB4 // NRF24 connector & W25Q16 (on board flash)
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB3 // NRF24 connector & W25Q16 (on board flash)
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

// Default pin used for 'Serial' instance
// Mandatory for Firmata
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

// This indicates that there is an external and fixed 1.5k pullup
// on the D+ line. This define is only needed on boards that have
// internal pullups *and* an external pullup. Note that it would have
// been better to omit the pullup and exclusively use the internal
// pullups instead.
#define USBD_FIXED_PULLUP

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
    #define SERIAL_PORT_HARDWARE  Serial1
  #endif
#endif
