/*
 *******************************************************************************
 * Copyright (c) 2026, STMicroelectronics
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
// Arduino Uno V3 header
#define PA3                     0   // D0  - USART2_RX
#define PA2                     1   // D1  - USART2_TX
#define PC5                     2   // D2
#define PE5                     3   // D3  - TIM9_CH1
#define PH3                     4   // D4
#define PB0                     5   // D5  - TIM3_CH3
#define PE6                     6   // D6  - TIM9_CH2
#define PE3                     7   // D7
#define PE4                     8   // D8
#define PH6                     9   // D9  - TIM12_CH1
#define PA1                     10  // D10 - TIM2_CH2 / SPI1_NSS
#define PB5                     11  // D11 - TIM3_CH2 / SPI1_MOSI
#define PB4                     12  // D12 - SPI1_MISO
#define PA5                     13  // D13 - SPI1_SCK
#define PH5                     14  // D14 - I2C2_SDA
#define PH4                     15  // D15 - I2C2_SCL
#define PA6                     PIN_A0
#define PA4                     PIN_A1
#define PC4                     PIN_A2
#define PF10                    PIN_A3  // ADC3_IN8
#define PC0                     PIN_A4
#define PC1                     PIN_A5

// System / on-board devices
#define PA0                     22  // User button (WAKEUP)
#define PA7                     23  // LED_RED  (LD_USER1)
#define PB1                     24  // LED_GREEN (LD_USER2)
#define PC6                     25  // ST-LINK VCP TX (USART6_TX)
#define PC7                     26  // ST-LINK VCP RX (USART6_RX)

// Remaining pins (touch panel, USB FS/HS, QSPI flash, FMC LCD/PSRAM bus,
// SAI2 audio codec, PMOD/STMOD+ connectors, WiFi header, ...)
// Not exposed as Dxx/Axx aliases but usable directly through their PinName
// (e.g. digitalWrite(PC9, ...)) by advanced sketches/libraries.
#define PA8                     27  // CTP_SCL (I2C3, touch panel)
#define PA9                     28  // USB_OTG_FS_VBUS
#define PA10                    29  // USB_OTG_FS_ID
#define PA11                    30  // USB_OTG_FS_DM
#define PA12                    31  // USB_OTG_FS_DP
#define PA13                    32  // SWDIO
#define PA14                    33  // SWCLK
#define PA15                    34  // STMOD TIM2_CH1/ETR
#define PB2                     35  // QSPI_CLK
#define PB3                     36  // SWO
#define PB6                     37  // QSPI_NCS
#define PB7                     38  // FMC_NL (NC)
#define PB8                     39  // I2C1_SCL (audio codec)
#define PB9                     40  // I2C1_SDA (audio codec)
#define PB10                    41  // USB_OTG_FS overcurrent
#define PB11                    42  // PMOD INT
#define PB12                    43  // USB_OTG_HS ID
#define PB13                    44  // USB_OTG_HS VBUS
#define PB14                    45  // USB_OTG_HS DM
#define PB15                    46  // USB_OTG_HS DP
#define PC2                     47  // STMOD SPI2 MISO
#define PC3                     48  // STMOD SPI2 MOSI
#define PC8                     49  // LCD_TE (tearing effect)
#define PC9                     50  // QSPI_D0
#define PC10                    51  // QSPI_D1
#define PC11                    52  // STMOD UART4 RX (spare route)
#define PC12                    53  // UART5_TX (WiFi header)
#define PC13                    54
#define PC14                    55  // OSC32_IN
#define PC15                    56  // OSC32_OUT
#define PD0                     57  // FMC LCD/PSRAM D2
#define PD1                     58  // FMC LCD/PSRAM D3
#define PD2                     59  // UART5_RX (WiFi header)
#define PD3                     60  // WIFI_CH_PD
#define PD4                     61  // FMC_NOE
#define PD5                     62  // FMC_NWE
#define PD6                     63  // WIFI_GPIO2
#define PD7                     64  // FMC_NE1 (PSRAM CS)
#define PD8                     65  // FMC LCD/PSRAM D13
#define PD9                     66  // FMC LCD/PSRAM D14
#define PD10                    67  // FMC LCD/PSRAM D15
#define PD11                    68  // FMC_A16/CLE (PSRAM)
#define PD12                    69  // FMC_A17/ALE (PSRAM)
#define PD13                    70  // QSPI_D3
#define PD14                    71  // FMC LCD/PSRAM D0
#define PD15                    72  // FMC LCD/PSRAM D1
#define PE0                     73  // FMC_NBL0 (PSRAM)
#define PE1                     74  // FMC_NBL1 (PSRAM)
#define PE2                     75  // QSPI_D2
#define PE7                     76  // FMC LCD/PSRAM D4
#define PE8                     77  // FMC LCD/PSRAM D5
#define PE9                     78  // FMC LCD/PSRAM D6
#define PE10                    79  // FMC LCD/PSRAM D7
#define PE11                    80  // FMC LCD/PSRAM D8
#define PE12                    81  // FMC LCD/PSRAM D9
#define PE13                    82  // FMC LCD/PSRAM D10
#define PE14                    83  // FMC LCD/PSRAM D11
#define PE15                    84  // FMC LCD/PSRAM D12
#define PF0                     85  // FMC_A0 (PSRAM)
#define PF1                     86  // FMC_A1 (PSRAM)
#define PF2                     87  // FMC_A2 (PSRAM)
#define PF3                     88  // FMC_A3 (PSRAM)
#define PF4                     89  // FMC_A4 (PSRAM)
#define PF5                     90  // FMC_A5 (PSRAM)
#define PF6                     91  // PMOD UART7 RX
#define PF7                     92  // PMOD UART7 TX
#define PF8                     93  // PMOD UART7 RTS
#define PF9                     94  // PMOD UART7 CTS
#define PF11                    95  // PMOD RESET
#define PF12                    96  // FMC_A6 (PSRAM)
#define PF13                    97  // FMC_A7 (PSRAM)
#define PF14                    98  // FMC_A8 (PSRAM)
#define PF15                    99  // FMC_A9 (PSRAM)
#define PG0                     100 // FMC_A10 (PSRAM)
#define PG1                     101 // FMC_A11 (PSRAM)
#define PG2                     102 // FMC_A12 (PSRAM)
#define PG3                     103 // FMC_A13 (PSRAM)
#define PG4                     104 // FMC_A14/BA0 (PSRAM)
#define PG5                     105 // FMC_A15/BA1 (PSRAM)
#define PG8                     106 // USB_OTG_FS power switch enable
#define PG9                     107 // FMC_NE2 (LCD CS)
#define PG10                    108 // SAI2_SD_B (audio codec)
#define PG11                    109
#define PG12                    110 // PMOD GPIO0
#define PG13                    111 // WIFI_GPIO0
#define PG14                    112 // WIFI_RST
#define PG15                    113 // SAI2_INT (audio codec IRQ)
#define PH0                     114 // OSC_IN (HSE)
#define PH1                     115 // OSC_OUT (HSE)
#define PH2                     116 // PMOD GPIO1
#define PH7                     117 // LCD_RST
#define PH8                     118 // CTP_SDA
#define PH9                     119 // CTP_RST
#define PH10                    120 // USB_OTG_HS overcurrent
#define PH11                    121 // LCD_BL (backlight enable)
#define PH12                    122 // USB_OTG_HS power switch enable
#define PH13                    123 // STMOD UART4 TX
#define PH14                    124 // STMOD UART4 RX
#define PH15                    125 // PMOD SEL0
#define PI0                     126 // PMOD SPI2 NSS
#define PI1                     127 // PMOD SPI2 SCK
#define PI2                     128 // PMOD SPI2 MISO
#define PI3                     129 // PMOD SPI2 MOSI
#define PI4                     130 // SAI2_MCLK_A (audio codec)
#define PI5                     131 // SAI2_SCK_A (audio codec)
#define PI6                     132 // SAI2_SD_A (audio codec)
#define PI7                     133 // SAI2_FS_A (audio codec)
#define PI8                     134
#define PI9                     135 // CTP_INT
#define PI10                    136
#define PI11                    137

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

#define NUM_DIGITAL_PINS        138
#define NUM_ANALOG_INPUTS       6

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PA7
#endif
#define LED_RED                 PA7
#define LED_GREEN               PB1

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PA0
#endif

// SPI definitions (Arduino Uno V3 header, SPI1)
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA1
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PB5
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB4
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PA5
#endif

// I2C definitions (Arduino Uno V3 header, I2C2)
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PH5
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PH4
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
  #define SERIAL_UART_INSTANCE  6 // Connected to ST-Link VCP (USART6)
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PC7
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PC6
#endif

// SDMMC signals not available
#define SDMMC_CKIN_NA
#define SDMMC_CDIR_NA
#define SDMMC_D0DIR_NA
#define SDMMC_D123DIR_NA

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_QSPI_MODULE_DISABLED)
  #define HAL_QSPI_MODULE_ENABLED
#endif
#if !defined(HAL_SRAM_MODULE_DISABLED)
  #define HAL_SRAM_MODULE_ENABLED
#endif
#if !defined(HAL_SAI_MODULE_DISABLED)
  #define HAL_SAI_MODULE_ENABLED
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
    #define SERIAL_PORT_MONITOR     Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE    Serial
  #endif
#endif
