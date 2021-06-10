/*
 *******************************************************************************
 * Copyright (c) 2019-2021, STMicroelectronics
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
#define PA3                     PIN_A0 // Z_PROBE_A    ADC
#define PA2                     PIN_A1 // PWRMON ADC   ADC
#define PA10                    2 // USART1_RX
#define PB3                     3 // E1_DIAG
#define PB5                     4 // N.C.
#define PB4                     5 // N.C.
#define PB10                    6 // Z_DIR
#define PA8                     7 // USD_CD (card detect)
#define PA9                     8 // USART1_TX
#define PC7                     9 // X_DIR
#define PB6                     10 // SD_CS
#define PA7                     11 // SPI1_MOSI   EXP2 OR onboard SD
#define PA6                     12 // SPI1_MISO
#define PA5                     13 // SPI1_SCK
#define PB9                     14 // SDA1
#define PB8                     15 // SCL1
#define PC10                    16 // USER BTN
#define PC12                    17
// 18 is NC - BOOT0
#define PA13                    19 // SWDIO
#define PA14                    20 // SWCLK
#define PA15                    21 // SERVO
#define PB7                     22 // SD_CD
#define PC13                    23 // E2_STEP
#define PC14                    24 // E2_DIR
#define PC15                    25 // E2_CS
#define PH0                     26 // OSC_IN
#define PH1                     27 // OSC_OUT
#define PC2                     PIN_A4 // THERM2_ADC  ADC
#define PC3                     PIN_A5 // THERM3_ADC  ADC
#define PC11                    30 // LCD_RS
#define PD2                     31 // LCD_D6
#define PC9                     32 // BEEPER
#define PC8                     33 // X_CS
#define PC6                     34 // X_STEP
#define PC5                     35 // E1_DIR
#define PA12                    36 // USB_DP
#define PA11                    37 // USB_DM
#define PB12                    38      // USED FOR ??
// 39 is NC
#define PB2                     40 // E0_DIR
#define PB1                     41 // E0_STEP
#define PB15                    42
#define PB14                    43 // STAT_LED
#define PB13                    44      // USED FOR ??
#define PC4                     45 // E1_STEP
#define PB11                    46
#define PD0                     47 // BTN_EN2
#define PD1                     48 // LCD_D4
#define PD3                     49 // LCD_D5
#define PD4                     50 // LCD_D7
#define PD5                     51 // KILL
#define PD6                     52 // BTN_EN1
#define PD7                     53 // LCD_EN
#define PD8                     54 // Z_CS
#define PD9                     55 // Y_STEP
#define PD10                    56 // Y_DIR
#define PD11                    57 // Y_CS
#define PD12                    58 // HB_PWM
#define PD13                    59 // F0_PWM
#define PD14                    60 // H1_PWM
#define PD15                    61 // H0_PWM
#define PE0                     62 // PS_ON
#define PE1                     63 // E4_STEP
#define PE2                     64 // E4_DIR
#define PE3                     65 // E4_CS
#define PE4                     66 // E3_DIR
#define PE5                     67 // E3_STEP
#define PE6                     68 // E3_CS
#define PE7                     69 // E_STOP
#define PE8                     70 // Z_STOP
#define PE9                     71 // Y_STOP
#define PE10                    72 // X_STOP
#define PE11                    73 // E0_CS
#define PE12                    74 // SPI4_SCK
#define PE13                    75 // SPI4_MISO
#define PE14                    76 // SPI4_MOSI
#define PE15                    77 // Z_STEP
#define PA0                     78 // F1_PWM  or serial
#define PA1                     79 // F2_PWM  or serial
#define PA4                     80 // Z_PROBE_D
#define PB0                     81 // E1_CS
#define PC1                     PIN_A2 // THERM1_ADC  ADC
#define PC0                     PIN_A3 // THERM0_ADC  ADC

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
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
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

#define NUM_DIGITAL_PINS        84
#define NUM_ANALOG_INPUTS       6

// On-board LED pin number
#define LED_LD2                 PB14
#define LED_GREEN               LED_LD2
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC10
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

#define ENABLE_HWSERIAL4
#ifndef PIN_SERIAL4_RX
  #define PIN_SERIAL4_RX          PA1
#endif
#ifndef PIN_SERIAL4_TX
  #define PIN_SERIAL4_TX          PA0
#endif

/* HAL configuration */
#define HSE_VALUE               12000000U

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
    #define SERIAL_PORT_MONITOR   Serial4
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial1
  #endif
#endif
