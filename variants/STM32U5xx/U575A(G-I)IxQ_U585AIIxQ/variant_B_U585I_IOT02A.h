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
// Ardunio connector pinout
#define PD9                     0
#define PD8                     1
#define PD15                    2
#define PB2                     PIN_A6
#define PE7                     4
#define PE0                     5
#define PB6                     6
#define PF13                    7
#define PC1                     PIN_A7
#define PA8                     9
#define PE12                    10
#define PE15                    11
#define PE14                    12
#define PE13                    13      // LD2 - LDE_BLUE - LED_BUILTIN
#define PB9                     14
#define PB8                     15
#define PC0                     PIN_A0
#define PC2                     PIN_A1
#define PC4                     PIN_A2
#define PC5                     PIN_A3
#define PA7                     PIN_A4
#define PB0                     PIN_A5
// Miscellaneous
#define PH6                     22      // LD6 - LED_RED
#define PH7                     23      // LD7 - LED_GREEN
#define PC13                    24      // B3 - USER_BTN
#define PA9                     25      // VCP_TX
#define PA10                    26      // VCP_RX
// MEMS modules
// TCPP03: USB Type-C port protection for USB DRP Power Delivery
// HTS221: Relative humidity and temperature sensor
// VEML6030: Ambient Light Sensor
// VL53L5CXV0GC: Time-of-Flight ranging and gesture detection sensor
// LPS22HH: pressure sensor
// IIS2MDCTR: 3-axis digital output magnetometer
// ISM330DHCX: 3D accelerometer and 3D gyroscope
// M24256-DFMC6TG: EEPROM
// STSAFA110S8SPL03: Authentication and security
#define PH4                     27      // SCL (I2C2_SCL)
#define PH5                     28      // SDA (I2C2_SDA)
#define PD10                    29      // INT/DRDY (Mems.INT_IIS2MDC)
#define PE11                    30      // INT1 (Mems.ISM330DLC_INT1)
#define PG2                     31      // INT/DRDY (Mems.INT_LPS22HH)
#define PG5                     32      // GPIO1 (Mems.VLX_GPIO)
#define PH1                     33      // LPn (Mems.VL53_xshut)
#define PF11                    34      // Mems.STSAFE_RESET

// Microphones I/O configuration (MP23DB01HPTR)
// Mic1
#define PE9                     35      // MIC_CCK0
#define PE10                    36      // IC_SDINx
// Mic2
#define PB1                     37      // MIC_SDIN0
#define PF10                    38      // MIC_CCK1
// USB Type-C FS Power Delivery configuration
#define PA11                    39      // USB.C_N / DM
#define PA12                    40      // USB.C_P / DP
#define PA15                    41      // CC1 (USB.UCPD_CC1)
#define PB5                     42      // EN (UCPD_PWR)
#define PB15                    43      // CC2 (USB.UCPD_CC2)
#define PD13                    44      // IANA (USB.IANA)
#define PE8                     45      // FLGn (USB.UCPD_FLT)
#define PF14                    PIN_A18 // USB.VBUS_SENSE
// Octo‑SPI Flash I/O configuration
#define PF0                     47
#define PF1                     48
#define PF2                     49
#define PF3                     50
#define PF4                     51
#define PF12                    52
#define PH9                     53
#define PH10                    54
#define PH11                    55
#define PH12                    56
#define PI5                     57
// Octo‑SPI RAM I/O configuration
#define PB10                    58
#define PB11                    59
#define PC3                     60
#define PD7                     61
#define PE3                     62
#define PF6                     63
#define PF7                     64
#define PF8                     65
#define PF9                     66
#define PH2                     67
#define PI0                     68
// RF modules
// Bluetooth STM32WB5MMG
#define PG6                     69      // WRLS.WKUP_B
#define PC10                    70      // WRLS.UART4_TX
#define PC11                    71      // WRLS.UART4_RX
// MXCHIP EMW3080
#define PB12                    72      // CS (WRLS.SPI2_NSS)
#define PD1                     73      // CK (WRLS.SPI2_SCK)
#define PD3                     74      // MISO (WRLS.SPI2_MISO)
#define PD4                     75      // MOSI (WRLS.SPI2_MOSI)
#define PD14                    76      // GPIO14 (WRLS.NOTIFY)
#define PF15                    77      // Chip_En (WRLS.WKUP_W)
#define PG15                    78      // GPIO13 (WRLS.FLOW)
// STMod+ connector
#define PH15                    79      // select either UART or SPI
// CN2
// Alternate configuration (UART) PH15 set HIGH
#define PD11                    PIN_A8  // 1
//      PD8                                2
//      PD9                                3
#define PD12                    PIN_A9  // 4
// Standard configuration (SPI) PH15 set LOW
#define PG12                    82      // 1
#define PD6                     83      // 2
#define PG10                    84      // 3
#define PG9                     85      // 4

//      PH4                             // 7
#define PC12                    86      // 8
#define PB4                     87      // 9
//      PH5                             // 10
#define PE6                     88      // 11
#define PB13                    89      // 12
#define PG0                     PIN_A10 // 13
#define PC9                     91      // 14
#define PG1                     PIN_A11 // 17
#define PD2                     93      // 18
#define PD5                     94      // 19
#define PG8                     95      // 20
// CN3
// Alternate configuration (UART) PH13 set HIGH
#define PA0                     PIN_A12 // 1
#define PA2                     PIN_A13 // 2
#define PA3                     PIN_A14 // 2
#define PA1                     PIN_A15 // 3
// Standard configuration (SPI) PH13 set LOW
#define PA4                     PIN_A16 // 1
//      PE15                               2
//      PE14                               3
//      PE13                               4
//      PH4                                7
#define PG4                     101     // 8
#define PG3                     102      // 8
//      PH5                                10

#define PE4                     103     // 11
#define PG7                     104     // 12
#define PA5                     PIN_A17 // 13
#define PE5                     106     // 14
#define PE2                     107     // 17
#define PD0                     108     // 18
#define PF5                     109     // 19
#define PB14                    110     // 20
// Pmod connector
//
#define PH13                    111     // select either UART or SPI
// Alternate configuration (UART) PH13 set HIGH
//      PA0                                1
//      PA2                                2
//      PA3                                3
//      PA1                                4
// Standard configuration (SPI) PH13 set LOW
//      PA4                                1
//      PE15                               2
//      PE14                               3
//      PE13                               4

//      PE4                                7
//      PG7                                8
// Camera daughterboard connector
// CN7
#define PA6                     112
#define PB7                     113
#define PC6                     114
#define PC7                     115
#define PC8                     116
#define PE1                     117
#define PH8                     118
#define PH14                    119
#define PI1                     120
#define PI2                     121
#define PI3                     122
#define PI4                     123
#define PI6                     124
#define PI7                     125
#define PA13                    126    // SWDIO
#define PA14                    127    // SWCLK
#define PB3                     128    // SWO
#define PH0                     129    // OSC_IN / T.MCO
#define PC14                    130    // OSC32_IN
#define PC15                    131    // OSC32_OUT
#define PH3                     132    // BOOT0

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
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
#define PB6_ALT1                (PB6  | ALT1)
#define PB7_ALT1                (PB7  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB10_ALT1               (PB10 | ALT1)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC1_ALT1                (PC1  | ALT1)
#define PC2_ALT1                (PC2  | ALT1)
#define PC3_ALT1                (PC3  | ALT1)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC6_ALT2                (PC6  | ALT2)
#define PC7_ALT1                (PC7  | ALT1)
#define PC7_ALT2                (PC7  | ALT2)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PF9_ALT1                (PF9  | ALT1)
#define PH12_ALT1               (PH12 | ALT1)

#define NUM_DIGITAL_PINS        133
#define NUM_ANALOG_INPUTS       19

// On-board LED pin number
#define LD2                     PE13
#define LD6                     PH6
#define LD7                     PH7
#define LED_BLUE                LD2
#define LED_RED                 LD6
#define LED_GREEN               LD7
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LD2
#endif

// On-board user button
#define B3_BTN                  PC13
#ifndef USER_BTN
  #define USER_BTN              B3_BTN
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

// Pin UCPD to configure TCPP in default Type-C legacy state (UCPD_PWR for TCPP03)
#define PIN_UCPD_TCPP           PB5

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_OSPI_MODULE_DISABLED)
  #define HAL_OSPI_MODULE_ENABLED
#endif
// #if !defined(HAL_SD_MODULE_DISABLED)
//   #define HAL_SD_MODULE_ENABLED
// #endif

// Alternate SYS_WKUP definition
#define PWR_WAKEUP_PIN1_1
#define PWR_WAKEUP_PIN1_2
#define PWR_WAKEUP_PIN2_1
#define PWR_WAKEUP_PIN2_2
#define PWR_WAKEUP_PIN3_1
#define PWR_WAKEUP_PIN3_2
#define PWR_WAKEUP_PIN4_1
#define PWR_WAKEUP_PIN4_2
#define PWR_WAKEUP_PIN5_1
#define PWR_WAKEUP_PIN5_2
#define PWR_WAKEUP_PIN6_1
#define PWR_WAKEUP_PIN6_2
#define PWR_WAKEUP_PIN7_1
#define PWR_WAKEUP_PIN7_2
#define PWR_WAKEUP_PIN8_1
#define PWR_WAKEUP_PIN8_2

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
