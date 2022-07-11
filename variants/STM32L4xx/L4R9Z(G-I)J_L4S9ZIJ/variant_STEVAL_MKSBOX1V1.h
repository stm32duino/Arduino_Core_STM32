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
/* SPI1: ACCELEROMETER */
#define PE13                    0  // SPI1_CLK
#define PE14                    1  // SPI1_MISO
#define PE15                    2  // SPI1_MOSI

/* LSM6DSOX (3D ACC+GYR) */
#define PA2                     3  // INT1_INEMO
#define PE3                     4  // INT2_INEMO
#define PE12                    5  // CS_INEMO

/* LIS3DHH (ACCELEROMETER) */
#define PE10                    6  // CS_ACC2
#define PC13                    7  // ACC2_INT1
#define PE6                     8  // ACC2_INT2

/* LIS2DW12 (ACCELEROMETER) */
#define PE11                    9  // CS_ACC
#define PC5                     10 // ACC_INT1
#define PD14                    11 // ACC_INT2

/* SPI2: BLE */
#define PC3                     12 // SPI2_MOSI
#define PD1                     13 // SPI2_SCK
#define PD3                     14 // SPI2_MISO
#define PD0                     15 // SPI2_CS

/* USART2: BLE */
#define PD5                     16 // USART2_BLE-RX_uC-TX
#define PD6                     17 // USART2_BLE-TX_uC-RX

/* SPBTLE-1S (BLE) */
#define PA8                     18 // NRST_BLE
#define PD4                     19 // BLE_INT

/* SPI3: MAGNETOMETER */
#define PB3                     20 // SPI3_CLK
#define PB4                     21 // SPI3_MISO
#define PB5                     22 // SPI3_MOSI

/* LIS2MDLTR (MAGNETOMETER) */
#define PA15                    23 // CS_MAG
#define PD12                    24 // INT_MAG

/* I2C1: LPS22HH + NU */
#define PB6                     25 // I2C1_SCL
#define PB7                     26 // I2C1_SDA

/* LPS22HH (PRESSURE) */
#define PD15                    27 // INT_PRESS

/* HTS221 (HUM + TEMP) */
#define PD13                    28 // INT_HTS

/* I2C3: STTS751-0DP3F */
#define PG7                     29 // I2C3_SCL
#define PG8                     30 // I2C3_SDA

/* STTS751-0DP3F (TEMPERATURE) */
#define PG5                     31 // INT_STT
#define PG6                     32 // EVENT_STT
#define PE1                     33 // INT_STT

/* STBB3JR (BUCK-BOOST) */
#define PE4                     34 // SD_EN
#define PF0                     35 // BB_MODE

/* STBC02AJR (CHG+PP+LDO) */
#define PG4                     36 // SW_SEL
#define PG2                     37 // BTN_PWR
#define PG3                     38 // CHG_LED
#define PG10                    39 // CHG_LED2
#define PC4                     PIN_A0 // AN_VBAT

/* MP23ABS1TR (MIC) */
/* TS922EIJT (OPAMP) */
#define PA3                     PIN_A1 // M1P
#define PB0                     PIN_A2 // MREF
#define PA4                     43 // DAC_OUT1

/* LDK130PU-R */
#define PF7                     44 // 2V7_EN

/* ST6G3244MEBJR (SD) */
#define PB12                    45 // SD_DETECT
#define PE5                     46 // SD_SEL
#define PB8                     47 // SDMMC1_CLK_F
#define PB9                     48 // SDMMC1_CMDDIR
#define PC6                     49 // SDMMC1_DAT0DIR
#define PC7                     50 // SDMMC1_DAT123DIR
#define PC8                     51 // SDMMC1_D0
#define PC9                     52 // SDMMC1_D1
#define PC10                    53 // SDMMC1_D2
#define PC11                    54 // SDMMC1_D3
#define PC12                    55 // SDMMC1_CK
#define PD2                     56 // SDMMC1_CMD

/* Other*/
#define PG1                     57 // USER_PB1
#define PH3                     58 // BOOT0
#define PB15                    59 // CPU_LED
#define PF2                     60 // CPU_LED2

/* USB */
/*#define PA11                    62 // USB_DM*/
/*#define PA12                    63 // USB_DP*/

/* SWD */
/*#define PA13                    64 // SWDIO*/
/*#define PA14                    65 // SWCLK*/

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
#define PB9_ALT1                (PB9  | ALT1)
#define PB10_ALT1               (PB10 | ALT1)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PF9_ALT1                (PF9  | ALT1)

#define NUM_DIGITAL_PINS        61
#define NUM_ANALOG_INPUTS       3

/* On-board LED pin number */
#define LED_BUILTIN             PF2  // CPU_LED2
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PB15 // CPU_LED

/* On-board user button */
#define USER_BTN                PG1
#define PWR_BTN                 PG2

/* Set default Wire instance on I2C1 */
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6

/* Set default SPI instance on SPI1 */
#define PIN_SPI_MOSI            PE15
#define PIN_SPI_MISO            PE14
#define PIN_SPI_SCK             PE13
#define PIN_SPI_SS              PE11

/* SD detect signal */
#define SD_DETECT_PIN           PB12
/* SD Transceiver */
/* SD_TRANSCEIVER_MODE is deprecated */
#define SD_TRANSCEIVER_MODE     SD_TRANSCEIVER_ENABLE
#define USE_SD_TRANSCEIVER      1U
#define SD_TRANSCEIVER_EN       PE4
#define SD_TRANSCEIVER_SEL      PE5

/* HAL configuration */
#define HSE_VALUE               16000000U

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
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
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_HARDWARE    Serial
#endif
