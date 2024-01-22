/*
 *******************************************************************************
 * Copyright (c) 2020-2021, STMicroelectronics
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
// Arduino UNO V3
// CN4
#define PC0                     PIN_A9  // STMOD+ 3
#define PB5                     1       // STMOD+ 2
#define PD12                    2
#define PD14                    3
#define PE4                     4
#define PB10                    5
#define PE0                     6
#define PB2                     7
// CN1
#define PD13                    8
#define PD15                    9
#define PA4                     PIN_A10
#define PA7                     PIN_A11 // LD4
#define PB4                     12
#define PA1                     PIN_A12
#define PA10                    14      // STMOD+ 10
#define PB8                     15      // STMOD+ 7
// CN3
#define PC3                     PIN_A0
#define PA2                     PIN_A1
#define PA5                     PIN_A2  // STMOD+ 19
#define PC1                     PIN_A3  // STMOD+ 20
#define PC4                     PIN_A4
#define PC5                     PIN_A5
// STMOD+ (CN5)
#define PD0                     22      // 1
#define PA6                     PIN_A6  // 1
#define PD4                     24      // 2
#define PC2                     PIN_A7  // 3
#define PD1                     26      // 4
#define PB12                    27      // 4
#define PB15                    28      // 8
#define PB14                    29      // 9
#define PE3                     30      // 11
#define PD8                     31      // 12
#define PA0                     PIN_A8  // 13
#define PA15                    33      // 14
#define PC11                    34      // 17
#define PC10                    35      // 18
// USER button
#define PC12                    36      // USER_B1
#define PC13                    37      // USER_B2
// VCP
#define PB6                     38      // VCP TX
#define PB7                     39      // VCP RX
// USB user
#define PA11                    40      // USB_DM
#define PA12                    41      // USB_DP
// QSPI
#define PD3                     42      // QSPI_BK_NCS
#define PA3                     43      // QSPI_BK_SCK
#define PB9                     44      // QSPI_BK_IO0 - IR_OUT
#define PD5                     45      // QSPI_BK_IO1
#define PD6                     46      // QSPI_BK_IO2
#define PD7                     47      // QSPI_BK_IO3
// IMP34DT05TR
#define PA8                     48      // CLK
#define PA9                     49      // DOUT
// Touch sensor
#define PC6                     50      // TSC_G4_IO1
#define PC7                     51      // TSC_G4_IO2
#define PD10                    52      // TSC_G6_IO1
#define PD11                    53      // TSC_G6_IO2
// OLED display
#define PC8                     54      // RST_DISP
#define PC9                     55      // D/C_DISP
#define PH0                     56      // CS_DISP
// I2C interface for ISM330DHCX, STTS22H and VL53L0CXV0DH/1
#define PB11                    57      // I2C3_SDA
#define PB13                    58      // I2C3_SCL
#define PD2                     59      // INT ISM330DHCX
#define PD9                     60      // INT VL53L0CXV0DH/1
#define PE1                     61      // DRDY STTS22H
// Tag connect CN7
#define PA13                    62      // SWDIO
#define PA14                    63      // SWCLK
#define PB3                     64      // SWO
// Other
#define PE2                     65      // GPIO_SELECT1 (Ctrl switch LPUART)
#define PH1                     66      // GPIO_SELECT2 (RGB LED/Infrared LED)
#define PH3                     67      // BOOT0

// Alias
#define LED_SELECT              PH1
#define RGB_LED                 PA7
#define IR_LED                  PB9
#define LPUART_SELECT           PE2

// Alternate pins number
#define PA7_ALT1                (PA7 | ALT1)
#define PB8_ALT1                (PB8 | ALT1)
#define PB9_ALT1                (PB9 | ALT1)

#define NUM_DIGITAL_PINS        68
#define NUM_ANALOG_INPUTS       13

// On-board LED pin number
#define LD4                     PA7     // LED RGB
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LD4
#endif

// On-board user button
#define USER_B1                 PC12
#define USER_B2                 PC13
#ifndef USER_BTN
  #define USER_BTN              USER_B1
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM16
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM17
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PB7
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PB6
#endif

// Only 512k provided for cpu1, so defined the FLASH_PAGE_NUMBER
// for EEPROM emulation to the last 808k pages.
#define FLASH_PAGE_NUMBER       201

// Extra HAL modules
#if !defined(HAL_QSPI_MODULE_DISABLED)
  #define HAL_QSPI_MODULE_ENABLED
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
