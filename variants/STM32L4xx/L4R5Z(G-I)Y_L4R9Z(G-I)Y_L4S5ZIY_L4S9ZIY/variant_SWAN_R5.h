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
#define PD9                     0
#define PD8                     1
#define PF15                    2
#define PE13                    3
#define PE3                     4
#define PE11                    5
#define PE9                     6
#define PF13                    7
#define PF12                    8
#define PD15                    9
#define PA4                     PIN_A9
#define PA7                     PIN_A10
#define PA6                     PIN_A11
#define PA5                     PIN_A12
#define PB9                     14
#define PE1                     15
#define PA3                     PIN_A0
#define PA1                     PIN_A1
#define PC3                     PIN_A2
#define PC1                     PIN_A3
#define PC4                     PIN_A4
#define PC5                     PIN_A5
#define PB1                     PIN_A6
#define PC2                     PIN_A7
#define PA0                     PIN_A8  // BAT VOLTAGE
#define PA10                    25      // RX
#define PA9                     26      // TX
#define PG12                    27      // RTS
#define PB4                     28      // CTS
#define PD6                     29      // RX2
#define PA2                     PIN_A13 // TX2
#define PD4                     31      // RTS2
#define PD3                     32      // CTS2
#define PB10                    33      // TX3
#define PB11                    34      // RX3
#define PD2                     35      // RTS3
#define PB13                    36      // CTS3
#define PG8                     37      // RX0
#define PG7                     38      // TX0
#define PB7                     39      // SDA
#define PB6                     40      // SCL
#define PF0                     41      // SDA2
#define PF1                     42      // SCL2
#define PC9                     43      // SDA3
#define PC0                     PIN_A14 // SCL3
#define PD0                     45      // CS
#define PB15                    46      // MO
#define PB14                    47      // MI
#define PD1                     48      // SCK
#define PD5                     49      // QEN
#define PE10                    50      // QCLK
#define PC11                    51      // QCS
#define PE12                    52      // QIO0
#define PB0                     PIN_A15 // QIO1
#define PE14                    54      // QIO2
#define PE15                    55      // QIO3
#define PE2                     56      // User LED
#define PC13                    57      // User button - active-low
#define PE4                     58      // Power Switch EN
#define PA11                    59      // USB DM
#define PA12                    60      // USB DP
#define PC6                     61      // USB_DETECT
#define PE6                     62      // DISCHARGE
#define PG0                     63      // Version bit 0
#define PG1                     64      // Version bit 1
#define PG2                     65      // Version bit 2
#define PG3                     66      // Version bit 3
#define PB2                     67      // BOOT1 - Do not connect to VDD
#define PH3                     68      // BOOT0 button
#define PB3                     69      // JTDO
#define PA15                    70      // JTDI
#define PA14                    71      // SWCLK
#define PA13                    72      // SWDIO
#define PC14                    73      // OSC32 IN
#define PC15                    74      // OSC32 OUT

// pins not connected
// #define PA8
// #define PB5
// #define PB8
// #define PB12
// #define PC7
// #define PC8
// #define PC10
// #define PC12
// #define PD7
// #define PD10
// #define PD11
// #define PD12
// #define PD13
// #define PD14
// #define PE0
// #define PE5
// #define PE7
// #define PE8
// #define PF2
// #define PF3
// #define PF4
// #define PF5
// #define PF6
// #define PF7
// #define PF10
// #define PF11
// #define PF14
// #define PG4
// #define PG5
// #define PG6
// #define PG9
// #define PG10
// #define PG13
// #define PH0
// #define PH1

// Alternate pins number
// #define PA0_ALT1                (PA0  | ALT1) // BAT VOLTAGE
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
// #define PB5_ALT1                (PB5  | ALT1) // NC
#define PB6_ALT1                (PB6  | ALT1)
#define PB7_ALT1                (PB7  | ALT1)
// #define PB8_ALT1                (PB8  | ALT1) // NC
#define PB9_ALT1                (PB9  | ALT1)
#define PB10_ALT1               (PB10 | ALT1)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC6_ALT1                (PC6  | ALT1)
// #define PC7_ALT1                (PC7  | ALT1) // NC
// #define PC8_ALT1                (PC8  | ALT1) // NC
#define PC9_ALT1                (PC9  | ALT1)
// #define PC10_ALT1               (PC10 | ALT1) // NC
#define PC11_ALT1               (PC11 | ALT1)

#define NUM_DIGITAL_PINS        75
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PE2
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC13
#endif

// Power switch ENABLE and DISCHARGE pins
#ifndef ENABLE_3V3
  #define ENABLE_3V3            PE4
#endif
#ifndef DISCHARGE_3V3
  #define DISCHARGE_3V3         PE6
  #define DISABLE_DISCHARGING   HIGH
  #define ENABLE_DISCHARGING    LOW
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PD0
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PB15
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB14
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PD1
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB6
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

// LPUART1
#ifndef PIN_SERIAL_LP1_RX
  #define PIN_SERIAL_LP1_RX     PG8
#endif
#ifndef PIN_SERIAL_LP1_TX
  #define PIN_SERIAL_LP1_TX     PG7
#endif

// Virtual COM Port for Swans with a 14-pin STLink Connector mounted.
// To use the STLINK's Virtual COM port, this would be added to an Arduino project:
//     HardwareSerial SerialVCP(PIN_VCP_RX, PIN_VCP_TX);
#ifndef PIN_VCP_RX
  #define PIN_VCP_RX     PIN_SERIAL_LP1_RX
#endif
#ifndef PIN_VCP_TX
  #define PIN_VCP_TX     PIN_SERIAL_LP1_TX
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_OSPI_MODULE_DISABLED)
  #define HAL_OSPI_MODULE_ENABLED
#endif
// Disabled as some SDMMC pins are NC
// #if !defined(HAL_SD_MODULE_DISABLED)
//   #define HAL_SD_MODULE_ENABLED
// #endif

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
