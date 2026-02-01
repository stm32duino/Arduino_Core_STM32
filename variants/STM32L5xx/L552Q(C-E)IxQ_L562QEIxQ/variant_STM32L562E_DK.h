/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
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

// CN12: Arduino connector
#define PB10                    0         // ARD.D0_RX, T.VCP_RX
#define PB11                    1         // ARD.D1_TX, T.VCP_TX
#define PD11                    2         // ARD.D2_IO
#define PD12                    3         // ARD.D3_TIM
#define PF4                     4         // ARD.D4_INT
#define PD13                    5         // ARD.D5_TIM
#define PB8                     6         // ARD.D6_TIM
#define PC6                     7         // ARD.D7_IO

// CN11: Arduino connector
#define PG0                     8         // ARD.D8_IO
#define PB9                     9         // ARD.D9_TIM
#define PE0                     10        // ARD.D10: SPI_CSn and TIM16_CH1
#define PB5                     11        // ARD.D11_TIM_SPI_MOSI, STMod+3_SPI_MOSIp
#define PB4                     12        // ARD.D12_SPI_MISO, STMod+3_SPI_MISOp
#define PG9                     13        // ARD.D13_SPI_SCK
#define PB7                     14        // ARD.D14_I2C1_SDA
#define PB6                     15        // ARD.D15_I2C1_SCL

// CN19: Arduino connector
#define PA0                     PIN_A0     // ARD.A0: ADC1_IN5, shared with STMod+
#define PA1                     PIN_A1     // ARD.A1: ADC1_IN6
#define PA4                     PIN_A2     // ARD_ADC.A2, USB_C.VBUS_VSENSE
#define PA5                     PIN_A3     // ARD_ADC.A3
#define PC4                     PIN_A4     // ARD_ADC.A5
#define PC5                     PIN_A5     // ARD_ADC.A4

// CN17: USB Micro-B
#define PB14                    22        // USB_C.FLT
#define PB15                    23        // USB_C.CC2

// octoSPI pins (no reused pin numbers)
#define PA2                     24        // OCTOSPI.NCS
#define PA3                     25        // OCTOSPI.CLK
#define PA6                     26        // OCTOSPI.IO3
#define PA7                     27        // OCTOSPI.IO2
#define PB0                     28        // OCTOSPI.IO1
#define PB1                     29        // OCTOSPI.IO0
#define PB2                     30        // OCTOSPI.DQS
#define PC0                     31        // OCTOSPI.IO7
#define PC1                     32        // OCTOSPI.IO4
#define PC2                     33        // OCTOSPI.IO5
#define PC3                     34        // OCTOSPI.IO6

// microSD card pins
#define PF2                     35        // SDIO.DETECT
#define PC8                     36        // SDIO.D0
#define PC9                     37        // SDIO.D1
#define PC10                    38        // SDIO.D2
#define PC11                    39        // SDIO.D3
#define PC12                    40        // SDIO.CLK
#define PD2                     41        // SDIO.CMD

// LCD pins
#define PD7                     42        // LCD.FMC_NE1_CS
#define PD5                     43        // LCD.FMC_NWE
#define PD4                     44        // LCD.FMC_NOE
#define PF0                     45        // LCD.FMC_A0
#define PD14                    46        // LCD.FMC_D0
#define PD15                    47        // LCD.FMC_D1
#define PD0                     48        // LCD.FMC_D2
#define PD1                     49        // LCD.FMC_D3
#define PE7                     50        // LCD.FMC_D4
#define PE8                     51        // LCD.FMC_D5
#define PE9                     52        // LCD.FMC_D6
#define PE10                    53        // LCD.FMC_D7
#define PE11                    54        // LCD.FMC_D8
#define PE12                    55        // LCD.FMC_D9
#define PE13                    56        // LCD.FMC_D10
#define PE14                    57        // LCD.FMC_D11
#define PE15                    58        // LCD.FMC_D12
#define PD8                     59        // LCD.FMC_D13
#define PD9                     60        // LCD.FMC_D14
#define PD10                    61        // LCD.FMC_D15
#define PE1                     62        // LCD_BL_CTRL
#define PF1                     63        // LCD.CTP_INT
#define PA8                     64
#define PF14                    65        // LCD.RST
#define PF15                    66        // LCD.CTP_RST
#define PH0                     67        // LCD_PWR_ON

// usb
#define PA11                    68        // USB_C.FS_N
#define PA12                    69        // USB_C.FS_P

// User button
#define PC13                    70        // USER BUTTON (WKUP2), PM_WAKE-UP

// User LED
#define PD3                     71        // LED_RED
#define PG12                    72        // LED_GREEN

// bluetooth low energy and spi
#define PG8                     73        // BLE_RSTN
#define PG6                     74        // BLE_INT
#define PG5                     75        // SPI1.BLE_CS
#define PG4                     76        // SPI1.MOSI
#define PG3                     77        // SPI1.MISO
#define PG2                     78        // SPI1.SCK

// Audio codec interface
#define PG1                     79        // audio RESET (active low)
#define PE2                     80        // SAI.MCLK_A
#define PE3                     81        // SAI.SD_B
#define PE4                     82        // SAI.FS_A
#define PE5                     83        // SAI.SCK_A
#define PE6                     84        // SAI.SD_A

// Digital microphone interface
#define PG7                     85        // DFSDM_CKOUT
#define PB12                    86        // DFSDM_DATIN1
#define PC7                     87        // DFSDM_DATIN3
#define PH1                     88        // Module LED

// 3D ACC/GYRO
#define PF3                     89        // GYRO_ACC_INT.

// Pmod
#define PF11                    90        // STMod+ SEL_12
#define PF12                    91        // STMod+ SEL_34
#define PB13                    92
#define PF5                     93

// STMod+
#define PD6                     94
#define PG10                    95

// STLINK-V3E
#define PB3                     96        // T.SWO
#define PA15                    97        // T.JTDI
#define PA9                     98        // T.VCP_TX
#define PA10                    99        // T.VCP_RX, ARD.D0_RX
#define PA13                    100       // T.SWDIO
#define PA14                    101       // T.SWCLK

#define PC14                    102       // OSC32_IN
#define PC15                    103       // OSC32_OUT

// PF13 NC
// PH3 Boot0

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
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PB6_ALT1                (PB6  | ALT1)
#define PB7_ALT1                (PB7  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)
#define PB10_ALT1               (PB10 | ALT1)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

#define NUM_DIGITAL_PINS        104
#define NUM_ANALOG_INPUTS       6

// On-board LEDs pin number
#define LED1                    PG9
#define LED_BLUE                LED1
#define LED2                    PG12
#define LED_GREEN               LED2
#define LED3                    PD3
#define LED_RED                 LED3

#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_BLUE
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

// Pin UCPD to configure TCPP in default Type-C legacy state (UCPD_DBn for TCPP01)
#define PIN_UCPD_TCPP           PB5

// SDMMC signals not available
#define SDMMC_CKIN_NA
#define SDMMC_CDIR_NA
#define SDMMC_D0DIR_NA
#define SDMMC_D123DIR_NA
// SD detect signal
#ifndef SD_DETECT_PIN
  #define SD_DETECT_PIN         PF2
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
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
