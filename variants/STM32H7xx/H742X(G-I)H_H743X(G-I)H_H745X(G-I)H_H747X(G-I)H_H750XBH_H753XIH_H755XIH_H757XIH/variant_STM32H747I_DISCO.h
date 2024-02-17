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
#define PJ9                             0       // UART8_RX
#define PJ8                             1       // UART8_TX
#define PJ3                             2
#define PF8                             3       // S_TIM13_CH1 / PMOD #14
#define PJ4                             4
#define PA6                             5       // DCMI_PIXCK
#define PJ7                             6       // TIM8_CH2N
#define PJ0                             7
#define PJ5                             8
#define PJ6                             9       // S_TIM8_CH2
#define PK1                             10      // SPI5_NSS
#define PJ10                            11      // SPI5_MOSI
#define PJ11                            12      // SPI5_MISO
#define PK0                             13      // SPI5_SCK
#define PD13                            14      // I2C4_SDA / PMOD #10
#define PD12                            15      // I2C4_SCL / PMOD #7
#define PA4                             PIN_A0  // Pin 16 - ADC12_INP18 / DCMI_HSYNC / PMOD #13
#define PF10                            PIN_A1  // Pin 17 - ADC3_INP6
#define PA0_C                           PIN_A2  // Pin 18 - ADC12_INP0
#define PA1_C                           PIN_A3  // Pin 19 - ADC12_INP1
#define PC2_C                           PIN_A4  // Pin 20 - ADC3_INP0
#define PC3_C                           PIN_A5  // Pin 21 - ADC3_INP1

// User LEDs
#define PI12                            22      // LED1
#define PI13                            23      // LED2
#define PI14                            24      // LED3
#define PI15                            25      // LED4

// ST-Link UART
#define PA10                            26      // USART1_RX / ST-Link Tx
#define PA9                             27      // USART1_TX / ST-Link Rx

// SPI
#define PA11                            28      // SPI2_NSS / PMOD #1 NSS
#define PA12                            29      // SPI2_SCK / PMOD #4 SCK
#define PC2                             30      // SPI2_MISO / PMOD #3 MISOp
#define PC3                             31      // SPI2_MOSI / PMOD #2 MOSIp

// GPIO Buttons
#define PK2                             32      // JOY_SEL
#define PK3                             33      // JOY_DOWN
#define PK4                             34      // JOY_LEFT
#define PK5                             35      // JOY_RIGHT
#define PK6                             36      // JOY_UP
#define PC13                            37      // Wakeup Button / RTC_TAMP1

// QuadSPI
#define PB2                             38      // QUADSPI_CLK
#define PG6                             39      // QUADSPI_BK1_NCS
#define PD11                            40      // QUADSPI_BK1_IO0
#define PF9                             41      // QUADSPI_BK1_IO1
#define PF7                             42      // QUADSPI_BK1_IO2
#define PF6                             43      // QUADSPI_BK1_IO3
#define PH2                             44      // QUADSPI_BK2_IO0
#define PH3                             45      // QUADSPI_BK2_IO1
#define PG9                             46      // QUADSPI_BK2_IO2
#define PG14                            47      // QUADSPI_BK2_IO3

// SDIO/SDMMC
#define PC8                             48      // SDMMC1_D0 / SDIO1_D0
#define PC9                             49      // SDMMC1_D1 / SDIO1_D1 / DCMI_D3
#define PC10                            50      // SDMMC1_D2 / SDIO1_D2
#define PC11                            51      // SDMMC1_D3 / SDIO1_D3 / DCMI_D4
#define PC12                            52      // SDMMC1_CK / SDIO1_CK
#define PD2                             53      // SDMMC1_CMD / SDIO1_CMD
#define PI8                             54      // uSD_Detect

// Digital Camera Interface
#define PG10                            55      // DCMI_D2
#define PB7                             56      // DCMI_VSYNC
#define PJ14                            57      // DCMI_PWR_EN

// USB
#define PA5                             58      // USB_OTG_HS_ULPI_CK
#define PA3                             59      // USB_OTG_HS_ULPI_D0
#define PB0                             60      // USB_OTG_HS_ULPI_D1
#define PB1                             61      // USB_OTG_HS_ULPI_D2
#define PB10                            62      // USB_OTG_HS_ULPI_D3
#define PB11                            63      // USB_OTG_HS_ULPI_D4
#define PB12                            64      // USB_OTG_HS_ULPI_D5
#define PB13                            65      // USB_OTG_HS_ULPI_D6
#define PB5                             66      // USB_OTG_HS_ULPI_D7
#define PC0                             67      // USB_OTG_HS_ULPI_STP
#define PH4                             68      // USB_OTG_HS_ULPI_NXT
#define PI11                            69      // USB_OTG_HS_ULPI_DIR
#define PJ1                             70      // OTG_HS_OverCurrent

// Audio
#define PD7                             71      // SPDIF_RX0
#define PE3                             72      // SAI1_SD_B
#define PE4                             73      // SAI1_FS_A
#define PE5                             74      // SAI1_SCK_A
#define PE6                             75      // SAI1_SD_A
#define PG7                             76      // SAI1_MCLK_A
#define PC1                             77      // SAI4_D1  / ETH_MDC
#define PE2                             78      // SAI4_CK1 / ETH_nINT
#define PJ15                            79      // Audio_INT (Audio Codec IRQ)

// Pmod™
#define PA0                             80      // PMOD #1 CTS
#define PD5                             81      // PMOD #2 TX
#define PD6                             82      // PMOD #3 RX
#define PD4                             83      // PMOD #4 RTS
#define PB15                            84      // PMOD #8
#define PB14                            85      // PMOD #9
#define PC6                             86      // PMOD #11 / DCMI_D0
#define PJ13                            87      // PMOD #12
#define PC7                             88      // PMOD #17 / DCMI_D1
#define PD3                             89      // PMOD #18 / DCMI_D5
#define PB9                             90      // PMOD #19
#define PB8                             91      // PMOD #20

// Clock outputs
#define PH0                             92      // RCC_OSC_IN
#define PH1                             93      // RCC_OSC_OUT
#define PC14                            94      // RCC_OSC32_IN
#define PC15                            95      // RCC_OSC32_OUT
#define PA8                             96      // CEC_CK / RCC_MCO_1

// LCD/DSI
#define PJ12                            97      // LCD_BL_CTRL
#define PG3                             98      // DSI_Reset
#define PJ2                             99      // DSI_TE
#define PB6                             100     // HDMI_CEC

// Touch Screen Controller
#define PK7                             101     // TOUCH_INT

// Flash Memory Controller
#define PE0                             102     // FMC_NBL0
#define PE1                             103     // FMC_NBL1
#define PI4                             104     // FMC_NBL2
#define PI5                             105     // FMC_NBL3
#define PG8                             106     // FMC_SDCLK
#define PH5                             107     // FMC_SDNWE
#define PH6                             108     // FMC_SDNE1
#define PH7                             109     // FMC_SDCKE1
#define PF11                            110     // FMC_SDNRAS
#define PG15                            111     // FMC_SDNCAS
#define PD14                            112     // FMC_D0
#define PD15                            113     // FMC_D1
#define PD0                             114     // FMC_D2
#define PD1                             115     // FMC_D3
#define PE7                             116     // FMC_D4
#define PE8                             117     // FMC_D5
#define PE9                             118     // FMC_D6
#define PE10                            119     // FMC_D7
#define PE11                            120     // FMC_D8
#define PE12                            121     // FMC_D9
#define PE13                            122     // FMC_D10
#define PE14                            123     // FMC_D11
#define PE15                            124     // FMC_D12
#define PD8                             125     // FMC_D13
#define PD9                             126     // FMC_D14
#define PD10                            127     // FMC_D15
#define PH8                             128     // FMC_D16
#define PH9                             129     // FMC_D17
#define PH10                            130     // FMC_D18
#define PH11                            131     // FMC_D19
#define PH12                            132     // FMC_D20
#define PH13                            133     // FMC_D21
#define PH14                            134     // FMC_D22
#define PH15                            135     // FMC_D23
#define PI0                             136     // FMC_D24
#define PI1                             137     // FMC_D25
#define PI2                             138     // FMC_D26
#define PI3                             139     // FMC_D27
#define PI6                             140     // FMC_D28
#define PI7                             141     // FMC_D29
#define PI9                             142     // FMC_D30
#define PI10                            143     // FMC_D31
#define PF0                             144     // FMC_A0
#define PF1                             145     // FMC_A1
#define PF2                             146     // FMC_A2
#define PF3                             147     // FMC_A3
#define PF4                             148     // FMC_A4
#define PF5                             149     // FMC_A5
#define PF12                            150     // FMC_A6
#define PF13                            151     // FMC_A7
#define PF14                            152     // FMC_A8
#define PF15                            153     // FMC_A9
#define PG0                             154     // FMC_A10
#define PG1                             155     // FMC_A11
#define PG2                             156     // FMC_A12
// FMC_A13 does not exist
#define PG4                             157     // FMC_A14
#define PG5                             158     // FMC A15

// JTAG/SWD
#define PA13                            159     // TMS / SWDIO
#define PA14                            160     // TCK / SWCLK
#define PA15                            161     // TDI
#define PB3                             162     // TDO / SWO
#define PB4                             163     // TRST

/* WARNING: Ethernet is unusable by default on the board */
// Ethernet port
#define PA1                             164     // ETH_REF_CLK
#define PA2                             165     // ETH_MDIO
#define PA7                             166     // ETH_CRS_DV
#define PC4                             167     // ETH_RXD0
#define PC5                             168     // ETH_RXD1
#define PG11                            169     // ETH_TX_EN
#define PG12                            170     // ETH_TXD1
#define PG13                            171     // ETH_TXD0

// Alternate pins number
#define PA0_ALT1                        (PA0   | ALT1)
#define PA0_C_ALT1                      (PA0_C | ALT1)
#define PA1_C_ALT1                      (PA1_C | ALT1)
#define PA1_C_ALT2                      (PA1_C | ALT2)
#define PA4_ALT1                        (PA4   | ALT1)
#define PA6_ALT1                        (PA6   | ALT1)
#define PA9_ALT                         (PA9   | ALT1)
#define PA10_ALT1                       (PA10  | ALT1)
#define PA11_ALT1                       (PA11  | ALT1)
#define PA12_ALT1                       (PA12  | ALT1)
#define PB8_ALT1                        (PB8   | ALT1)
#define PB9_ALT1                        (PB9   | ALT1)
#define PB14_ALT1                       (PB14  | ALT1)
#define PB14_ALT2                       (PB14  | ALT2)
#define PB15_ALT1                       (PB15  | ALT1)
#define PB15_ALT2                       (PB15  | ALT2)
#define PC2_ALT1                        (PC2   | ALT1)
#define PC2_ALT2                        (PC2   | ALT2)
#define PC3_ALT1                        (PC3   | ALT1)
#define PC6_ALT1                        (PC6   | ALT1)
#define PC7_ALT1                        (PC7   | ALT1)
#define PC8_ALT1                        (PC8   | ALT1)
#define PF8_ALT1                        (PF8   | ALT1)
#define PJ8_ALT1                        (PJ8   | ALT1)
#define PJ9_ALT1                        (PJ9   | ALT1)
#define PJ10_ALT1                       (PJ10  | ALT1)
#define PJ11_ALT1                       (PJ11  | ALT1)
#define PK0_ALT1                        (PK0   | ALT1)
#define PK1_ALT1                        (PK1   | ALT1)

#define NUM_DIGITAL_PINS        172
#define NUM_DUALPAD_PINS        4
#define NUM_ANALOG_INPUTS       6

// On-board LED pin number
#define LED_GREEN   PI12  //LED1
#define LED_ORANGE  PI13  //LED2
#define LED_RED     PI14  //LED3
#define LED_BLUE    PI15  //LED4

#ifndef LED_BUILTIN
  #define LED_BUILTIN LED_GREEN
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN    PC13    //Wakeup button
#endif

// SPI Definitions are provided by "pins_arduino.h"
// I2C definitions are provided by "pins_arduino.h"

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  101 //LPUART1 is connected to ST-Link
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// Default pin used for generic 'Serial' instance (wired to ST-Link)
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

// SDMMC signals - only define not available,
// the rest is automatically provided by PeripheralPins
#define SDMMC_CKIN_NA
#define SDMMC_CDIR_NA
#define SDMMC_D0DIR_NA
#define SDMMC_D123DIR_NA

// SD detect signal
#ifndef SD_DETECT_PIN
  #define SD_DETECT_PIN         PI8
#endif

// HAL configuration
#define HSE_VALUE               25000000U

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_ETH_MODULE_DISABLED)
  #define HAL_ETH_MODULE_ENABLED
#endif
#if !defined(HAL_QSPI_MODULE_DISABLED)
  #define HAL_QSPI_MODULE_ENABLED
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
