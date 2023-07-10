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
 *        Pins
 *----------------------------------------------------------------------------*/

// CN3 connector
#define PA1                     PIN_A6  //UART4_RX
#define PA0                     PIN_A7  //UART4_TX
#define PD14                    2
#define PB0                     PIN_A8  //PWM
#define PA3                     PIN_A9
#define PB4                     5   // PWM
#define PB1                     PIN_A10 //PWM
#define PA4                     PIN_A11
// CN1 connector
#define PB2                     8
#define PA15                    9   // PWM
#define PA2                     PIN_A12 //SPI_SSN/PWM
#define PA7                     PIN_A13 //SPI1_MOSI/PWM
#define PA6                     PIN_A14 //SPI1_MISO
#define PA5                     PIN_A15 //SPI1_SCK/LED1
#define PB9                     14  // I2C1_SDA
#define PB8                     15  // I2C1_SCL
// Not on connector
#define PB14                    16  // LED2
#define PC13                    17  // USER_BTN
// ST-LINK
#define PB6                     18  // ST-LINK-UART1_TX
#define PB7                     19  // ST-LINK-UART1_RX
// CN9 USB OTG FS connector
#define PA9                     20  // USB_OTG_FS_VBUS
#define PA10                    21  // USB_OTG_FS_ID
#define PA11                    22  // USB_OTG_FS_DM
#define PA12                    23  // USB_OTG_FS_DP
#define PD12                    24  // USB_OTG_FS_PWR_EN
#define PE3                     25  // USB_OTG_OVRCR_EXTI3
// CN10 PMOD connector
#define PD0                     26  // PMOD-RESET
#define PD1                     27  // PMOD-SPI2_SCK
#define PD2                     28  // PMOD-IRQ_EXTI2
#define PD3                     29  // PMOD-UART2_CTS/SPI2_MISO
#define PD4                     30  // PMOD-UART2_RTS/SPI2_MOSI
#define PD5                     31  // PMOD-UART2_TX/SPI2_CSN
#define PD6                     32  // PMOD-UART2_RX
// Sensors / modules pins
#define PA8                     33  // SPBTLE-RF-RST
#define PB5                     34  // SPSGRF-915-SPI3_CSN
#define PB10                    35  // INTERNAL-I2C2_SCL
#define PB11                    36  // INTERNAL-I2C2_SDA
#define PB12                    37  // ISM43362-BOOT0
#define PB13                    38  // ISM43362-WAKEUP
#define PB15                    39  // SPSGRF-915-SDN
#define PC6                     40  // VL53L0X_XSHUT
#define PC7                     41  // VL53L0X_GPIO1_EXTI7
#define PC8                     42  // LIS3MDL_DRDY_EXTI8
#define PC9                     43  // LED3 (WIFI) & LED4 (BLE)
#define PC10                    44  // INTERNAL-SPI3_SCK
#define PC11                    45  // INTERNAL-SPI3_MISO
#define PC12                    46  // INTERNAL-SPI3_MOSI
#define PD7                     47  // STSAFE-A100-RESET
#define PD8                     48  // INTERNAL-UART3_TX
#define PD9                     49  // INTERNAL-UART3_RX
#define PD10                    50  // LPS22HB_INT_DRDY_EXTI10
#define PD11                    51  // LSM6DSL_INT1_EXTI11
#define PD13                    52  // SPBTLE-RF-SPI3_CSN
#define PD15                    53  // HTS221_DRDY_EXTI15
#define PE0                     54  // ISM43362-SPI3_CSN
#define PE1                     55  // ISM43362-DRDY_EXTI1
#define PE2                     56  // M24SR64-Y-RF_DISABLE
#define PE4                     57  // M24SR64-Y-GPO
#define PE5                     58  // SPSGRF-915-GPIO3_EXTI5
#define PE6                     59  // SPBTLE-RF-IRQ_EXTI6
#define PE7                     60  // DFSDM1_DATIN2
#define PE8                     61  // ISM43362-RST
#define PE9                     62  // DFSDM1_CKOUT
#define PE10                    63  // QUADSPI_CLK
#define PE11                    64  // QUADSPI_NCS
#define PE12                    65  // QUADSPI_BK1_IO0
#define PE13                    66  // QUADSPI_BK1_IO1
#define PE14                    67  // QUADSPI_BK1_IO2
#define PE15                    68  // QUADSPI_BK1_IO3
// CN4 connector
#define PC5                     PIN_A0
#define PC4                     PIN_A1
#define PC3                     PIN_A2
#define PC2                     PIN_A3
#define PC1                     PIN_A4
#define PC0                     PIN_A5
// Extra
#define PA13                    75  // SWDIO
#define PA14                    76  // SWCLK
#define PB3                     77  // SWO
#define PC14                    78  // OSC32_IN
#define PC15                    79  // OSC32_OUT
#define PH0                     80  // OSC_IN
#define PH1                     81  // OSC_OUT

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
#define PB13_ALT1               (PB13 | ALT1)
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

#define NUM_DIGITAL_PINS        82
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN             PA5
#endif
#ifndef LED1
  #define LED1                    LED_BUILTIN
#endif
#ifndef LED2
  #define LED2                    PB14
#endif
#ifndef LED3
  #define LED3                    PC9
#endif
#ifndef LED4
  #define LED4                    LED3
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN                PC13
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE              TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO             TIM7
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE    1 //Connected to ST-Link
#endif
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX           PB7
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX           PB6
#endif

// SDMMC signals not available
#define SDMMC_CKIN_NA
#define SDMMC_CDIR_NA
#define SDMMC_D0DIR_NA
#define SDMMC_D123DIR_NA

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_QSPI_MODULE_DISABLED)
  #define HAL_QSPI_MODULE_ENABLED
#endif

/* QSPI pins for MX25R6435F */
#define MX25R6435F_D0           PE12
#define MX25R6435F_D1           PE13
#define MX25R6435F_D2           PE14
#define MX25R6435F_D3           PE15
#define MX25R6435F_SCLK         PE10
#define MX25R6435F_SSEL         PE11

/* Backward compatibility */
#define ARDUINO_DISCO_L475VG_IOT

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
