/*
 *******************************************************************************
 * Copyright (c) 2023, STMicroelectronics
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
// CN15 Arduino connector
#define PB11                    0
#define PB10                    1
#define PG15                    2
#define PB5                     3
#define PG4                     4
#define PH11                    5
#define PH10                    6
#define PG5                     7
// CN13 Arduino connector
#define PG8                     8
#define PA8                     9
#define PA3                     PIN_A6
#define PB15                    11
#define PI2                     12
#define PI1                     13
#define PB7                     14      // STMOD#10
#define PB6                     15      // STMOD#7
// CN16 Arduino connector
#define PB0                     PIN_A0
#define PA4                     PIN_A1
#define PA0                     PIN_A2
#define PA5                     PIN_A3
#define PA6                     PIN_A4
#define PF12                    PIN_A5
// User button
#define PC13                    22      // USER_BTN
// User LED
#define PI8                     23      // LD1 Green
#define PI9                     24      // LD2 Orange
#define PF1                     25      // LD3 Red
#define PF4                     26      // LD4 Blue
// OSPI
#define PG6                     27      // OSPI_NCS
#define PF10                    28      // OSPI_CLK
#define PB2                     29      // OSPI_DQS
#define PB1                     30      // OSPI_IO0
#define PD12                    31      // OSPI_IO1
#define PC2                     32      // OSPI_IO2
#define PD13                    33      // OSPI_IO3
#define PH2                     34      // OSPI_IO4
#define PH3                     35      // OSPI_IO5
#define PG9                     36      // OSPI_IO6
#define PC0                     37      // OSPI_IO7
// microSD
#define PC8                     38      // SDMMC_D0
#define PC9                     39      // SDMMC_D1
#define PC10                    40      // SDMMC_D2
#define PC11                    41      // SDMMC_D3
#define PC12                    42      // SDMMC_CK
#define PD2                     43      // SDMMC_CMD
#define PH14                    44      // SDMMC_Detect
// Audio
#define PI4                     45      // SAI2_MCLK_A
#define PI5                     46      // SAI2_SCK_A
#define PI7                     47      // SAI2_FS_A
#define PI6                     48      // SAI2_SD_A
#define PG10                    49      // SAI2_SD_B
#define PI11                    50      // AUDIO_NRST
// I2C4
#define PB8                     51      // I2C4_SCL
#define PB9                     52      // I2C4_SDA
// Microphone
#define PD6                     53      // PDM_SAI1_CK1
#define PD11                    54      // PDM_SAI1_SD1
#define PE0                     55      // DETECTn
#define PE1                     56      // MEMS_LED
#define PC3                     57      // PDM_SAI1_SD3
#define PE4                     58      // PDM_SAI1_SD2
// RMII
#define PG11                    59      // RMII_TX_EN
#define PG13                    60      // RMII_TXD0
#define PG12                    61      // RMII_TXD1
#define PC4                     62      // RMII_RXD0
#define PC5                     63      // RMII_RXD1
#define PI10                    64      // RMII_RX_ER
#define PA7                     65      // RMII_CRS_DV
#define PC1                     66      // RMII_MDC
#define PA2                     67      // RMII_MDIO
#define PA1                     68      // RMII_REF_CLK
// TFT LCD
#define PD14                    69      // LCD_D0
#define PD15                    70      // LCD_D1
#define PD0                     71      // LCD_D2
#define PD1                     72      // LCD_D3
#define PE7                     73      // LCD_D4
#define PE8                     74      // LCD_D5
#define PE9                     75      // LCD_D6
#define PE10                    76      // LCD_D7
#define PE11                    77      // LCD_D8
#define PE12                    78      // LCD_D9
#define PE13                    79      // LCD_D10
#define PE14                    80      // LCD_D11
#define PE15                    81      // LCD_D12
#define PD8                     82      // LCD_D13
#define PD9                     83      // LCD_D14
#define PD10                    84      // LCD_D15
#define PD3                     85      // LCD_TE
#define PD4                     86      // LCD_NOE
#define PD5                     87      // LCD_NWE
#define PC7                     88      // LCD_NE1_CS
#define PF0                     89      // LCD_A0_RS
#define PH13                    90      // LCD_RST
// Backlight driver
#define PI3                     91      // LCD_BL_CTRL
// Touch panel connector
#define PG3                     92      // LCD_CTP_RST
#define PG7                     93      // LCD_CTP_INT
// LCD PWR enable
#define PC6                     94      // LCD_PWR_ON
// PMOD
#define PF6                     95      // STMOD#1
#define PF9                     96      // STMOD#2
#define PF7                     97      // STMOD#3
#define PF8                     98      // STMOD#4
#define PH8                     99      // STMOD#8
#define PH7                     100     // STMOD#9
#define PH9                     101     // STMOD#11
#define PH6                     102     // STMOD#12
#define PF11                    PIN_A7  // STMOD#13
#define PH12                    104     // STMOD#14
#define PF3                     105     // STMOD#17
#define PB12                    106     // STMOD#18
#define PH4                     107     // STMOD#19
#define PH5                     108     // STMOD#20
// VCP
#define PA9                     109     // VCP_TX
#define PA10                    110     // VCP_RX
// USB
#define PA11                    111     // USB_FS_N
#define PA12                    112     // USB_FS_P
#define PG0                     113     // UCPD_PWR
#define PF13                    PIN_A8  // IBUS_SENSE
#define PB13                    115     // UCPD_CC1
#define PB14                    116     // UCPD_CC2
#define PG1                     117     // UCPD_FLT
#define PF14                    PIN_A9  // VBUS_SENSE
// JTAG
#define PA13                    119     // JTMS
#define PA14                    120     // JTCK
#define PA15                    121     // JTDI
#define PB3                     122     // JTDO
#define PB4                     123     // NJTRST
#define PE2                     124     // TRACECLK
#define PE3                     125     // TRACED0
#define PG14                    126     // TRACED1
#define PE5                     127     // TRACED2
#define PE6                     128     // TRACED3
// Clock
#define PH0                     129     // OCS_25M
#define PC14                    130     // OSC32_IN
#define PC15                    131     // OSC32_OUT
// Not connected
// PD7
// PF2
// PF5
// PF15
// PG2
// PH1
// PH15

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA1_ALT2                (PA1  | ALT2)
#define PA2_ALT1                (PA2  | ALT1)
#define PA2_ALT2                (PA2  | ALT2)
#define PA3_ALT1                (PA3  | ALT1)
#define PA3_ALT2                (PA3  | ALT2)
#define PA4_ALT1                (PA4  | ALT1)
#define PA4_ALT2                (PA4  | ALT2)
#define PA5_ALT1                (PA5  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA9_ALT1                (PA9  | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PA11_ALT1               (PA11 | ALT1)
#define PA12_ALT1               (PA12 | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PA15_ALT2               (PA15 | ALT2)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB3_ALT2                (PB3  | ALT2)
#define PB4_ALT1                (PB4  | ALT1)
#define PB4_ALT2                (PB4  | ALT2)
#define PB5_ALT1                (PB5  | ALT1)
#define PB5_ALT2                (PB5  | ALT2)
#define PB6_ALT1                (PB6  | ALT1)
#define PB6_ALT2                (PB6  | ALT2)
#define PB7_ALT1                (PB7  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB9_ALT3                (PB9  | ALT3)
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
#define PF8_ALT1                (PF8  | ALT1)
#define PF9_ALT1                (PF9  | ALT1)
#define PG13_ALT1               (PG13 | ALT1)
#define PH6_ALT1                (PH6  | ALT1)
#define PH6_ALT2                (PH6  | ALT2)
#define PH7_ALT1                (PH7  | ALT1)
#define PH8_ALT1                (PH8  | ALT1)
#define PH9_ALT1                (PH9  | ALT1)
#define PH9_ALT2                (PH9  | ALT2)
#define PH10_ALT1               (PH10 | ALT1)
#define PH10_ALT2               (PH10 | ALT2)
#define PH11_ALT1               (PH11 | ALT1)
#define PH11_ALT2               (PH11 | ALT2)
#define PH12_ALT1               (PH12 | ALT1)
#define PH13_ALT1               (PH13 | ALT1)

#define NUM_DIGITAL_PINS        132
#define NUM_ANALOG_INPUTS       10

// On-board LED pin number
#define LED1                    PI9
#define LED_GREEN               LED1
#define LED2                    PI8
#define LED_ORANGE              LED2
#define LED3                    PF1
#define LED_RED                 LED3
#define LED4                    PF4
#define LED_BLUE                LED3
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC13
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
  #define SERIAL_UART_INSTANCE  101
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

// SD detect signal
#ifndef SD_DETECT_PIN
  #define SD_DETECT_PIN         PH14
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_ETH_MODULE_DISABLED)
  #define HAL_ETH_MODULE_ENABLED
#endif
#if !defined(HAL_OSPI_MODULE_DISABLED)
  #define HAL_OSPI_MODULE_ENABLED
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
