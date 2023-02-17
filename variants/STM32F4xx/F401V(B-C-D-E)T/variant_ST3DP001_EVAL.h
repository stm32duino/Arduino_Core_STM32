/*
 *******************************************************************************
 * Copyright (c) 2011-2021, STMicroelectronics
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
// USART1_MAIN
#define PA9                     0  // TX
#define PA10                    1  // RX

// WIFI
#define PD3                     2  // CTS
#define PD4                     3  // RTS
#define PD5                     4  // TX
#define PD6                     5  // RX
#define PB5                     6  // WIFI_WAKEUP
#define PE11                    7  // WIFI_RESET
#define PE12                    8  // WIFI_BOOT

// STATUS_LED
#define PE1                      9 // STATUS_LED

// SPI USER
#define PB12                    10 // SPI_CS
#define PB15                    11 // SPI_MOSI
#define PB14                    12 // SPI_MISO
#define PB13                    13 // SPI_SCK

// I2C USER
#define PB7                     14 // SDA
#define PB6                     15 // SCL

// SPI
#define PA4                     16 // SPI_CS
#define PA5                     17 // SPI_SCK
#define PA6                     18 // SPI_MISO
#define PA7                     19 // SPI_MOSI

// JTAG
#define PA13                    20 // JTAG_TMS/SWDIO
#define PA14                    21 // JTAG_TCK/SWCLK
#define PB3                     22 // JTAG_TDO/SWO

// SDCARD
#define PC8                     23 // SDIO_D0
#define PC9                     24 // SDIO_D1
#define PA15                    25 // SD_CARD_DETECT
#define PC10                    26 // SDIO_D2
#define PC11                    27 // SDIO_D3
#define PC12                    28 // SDIO_CK
#define PD2                     29 // SDIO_CMD

// OTG
#define PA11                    30 //OTG_DM
#define PA12                    31 //OTG_DP

// IR/PROBE
#define PD1                     32 //IR_OUT
#define PC1                     33 //IR_ON

// USER_PINS
#define PD7                     34 // USER3
#define PB9                     35 // USER1
#define PE0                     36 // USER2
#define PB4                     37 // USER4

// USERKET
#define PE7                     38 // USER_BUTTON

// ENDSTOPS
#define PD8                     39 // X_STOP
#define PD9                     40 // Y_STOP
#define PD10                    41 // Z_STOP
#define PD11                    42 // U_STOP
#define PA8                     43 // V_STOP
#define PD0                     44 // W_STOP

// HEATERS
#define PD13                    45 // BED_HEAT_2
#define PD14                    46 // BED_HEAT_1
#define PD15                    47 // BED_HEAT_3
#define PC7                     48 // E1_HEAT_PWM
#define PB0                     49 // E2_HEAT_PWM
#define PB1                     50 // E3_HEAT_PWM

// THERMISTOR
#define PC2                     PIN_A0 // BED_THERMISTOR_1
#define PC3                     PIN_A1 // BED_THERMISTOR_2
#define PA3                     PIN_A2 // BED_THERMISTOR_3
#define PA0                     PIN_A3 // E1_THERMISTOR
#define PA1                     PIN_A4 // E2_THERMISTOR
#define PA2                     PIN_A5 // E3_THERMISTOR

// FANS
#define PC4                     57 // E1_FAN
#define PC5                     58 // E2_FAN
#define PE8                     59 // E3_FAN

// X_MOTOR
#define PE13                    60 // X_RESET
#define PE14                    61 // X_PWM
#define PE15                    62 // X_DIR

// Y_MOTOR
#define PE10                    63 // Y_RESET
#define PB10                    64 // Y_PWM
#define PE9                     65 // Y_DIR

// Z_MOTOR
#define PC15                    66 // Z_RESET
#define PC6                     67 // Z_PWM
#define PC0                     68 // Z_DIR

// E1_MOTOR
#define PC14                    69 // E1_RESET
#define PC13                    70 // E1_DIR
#define PD12                    71 // E1_PWM

// E2_MOTOR
#define PE4                     72 // E2_RESET
#define PE5                     73 // E2_PWM
#define PE6                     74 // E2_DIR

// E3_MOTOR
#define PE3                     75 // E3_RESET
#define PE2                     76 // E3_DIR
#define PB8                     77 // E3_PWM

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA2_ALT2                (PA2  | ALT2)
#define PA3_ALT1                (PA3  | ALT1)
#define PA3_ALT2                (PA3  | ALT2)
#define PA4_ALT1                (PA4  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)

#define NUM_DIGITAL_PINS        78
#define NUM_ANALOG_INPUTS       6

// On-board LED pin number
#define LED_GREEN               PE1
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PE7
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1 //Connected to ST-Link
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

/* SD detect signal */
/*
 * By default, R67 is not provided, so SD card detect is not used.
 * Note: SD CD (pin 16 of expansion connector J23) can be connected
 * to GND in order to be able to use SD_DETECT_PIN
 */
/*#define SD_DETECT_PIN           PA15*/

/* HAL configuration */
#define HSE_VALUE               25000000U

// Extra HAL modules
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
