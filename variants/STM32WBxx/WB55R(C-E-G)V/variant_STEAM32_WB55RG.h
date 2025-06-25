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

// micro:bit Edge connector
#define PC4                     PIN_A1
#define PA5                     PIN_A3
#define PC5                     PIN_A5
#define PA2                     PIN_A0
#define PA4                     PIN_A2
#define PA7                     5
#define PC3                     6
#define PA9                     7
#define PA15                    8
#define PC2                     9
#define PA6                     PIN_A4
#define PA8                     11
#define PC6                     12
#define PB13                    13
#define PB14                    14
#define PB15                    15
#define PE4                     16
#define PC0                     17
#define PC1                     18

// Not on connectors
#define PB2                     19
#define PD0                     20
#define PB8                     21
#define PB9                     22
#define PC13                    23
#define PB12                    24
#define PB0                     25
#define PD1                     26
#define PB6                     27
#define PB7                     28
#define PC10                    29
#define PH3                     30
#define PC11                    31
#define PC12                    32
#define PA0                     33
#define PA3                     34
#define PA10                    35
#define PA12                    36
#define PB1                     37
#define PB10                    38
#define PB11                    39
#define PA11                    40
#define PB4                     41
#define PB5                     42
#define PA1                     43

#define NUM_DIGITAL_PINS        44
#define NUM_ANALOG_INPUTS       6

// GPIO expander
// Not used by Arduino only here for documentation purpose
// Upper pad
// GPIO1 --> P28
// GPIO2 --> P29
// GPIO3 --> P24
// GPIO4 --> P25

// 4 directions switches
// GPIO5
// GPIO6
// GPIO7
// GPIO8

// STeaMi's PinName
#define ACTIVATE_3V3_STLINK     PB2
#define CS_DISPLAY              PD0
#define I2C_EXT_SCL             PC0
#define I2C_EXT_SDA             PC1
#define I2C_INT_SCL             PB8
#define I2C_INT_SDA             PB9
#define INT_ACC                 PC13
#define INT_DIST                PB12
#define INT_EXPANDER            PB0
#define INT_MAG                 PD1
#define JACDAC_DATA_TX          PB6
#define JACDAC_DATA_RX          PB7
#define MENU_BUTTON             PA0
#define MIC_CLK                 PA3
#define MIC_IN                  PA10

#define P0                      PC4
#define P1                      PA5
#define P2                      PC5
#define P3                      PA2
#define P4                      PA4
#define P5                      PA7
#define P6                      PC3
#define P7                      PA9
#define P8                      PA15
#define P9                      PC2
#define P10                     PA6
#define P11                     PA8
#define P12                     PC6
#define P13                     PB13
#define P14                     PB14
#define P15                     PB15
#define P16                     PE4
#define P19                     PC1
#define P20                     PC0
#define P24                     GPIO3
#define P25                     GPIO4
#define P28                     GPIO1
#define P29                     GPIO2

#define RST_DISPLAY             PA12
#define RST_EXPANDER            PB1

#define SERIAL_RX               PB10
#define SERIAL_TX               PB11

#define SPEAKER                 PA11

#define SPI_EXT_MISO            PB14
#define SPI_EXT_MOSI            PB15
#define SPI_EXT_SCK             PB13

#define SPI_INT_MISO            PB4
#define SPI_INT_MOSI            PB5
#define SPI_INT_SCK             PA1

// On-board LED pin number
#define LED1                    PC10
#define LED2                    PC11
#define LED3                    PC12
#define LED4                    PH3

#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED1
#endif

#define LED_BLUE                LED1
#define LED_GREEN               LED2
#define LED_RED                 LED3

#define LED_BLE                 LED4

// On-board user button
#define A_BUTTON                PA7
#define B_BUTTON                PA8
#define MENU_BUTTON             PA0

// DOWN_BUTTON  --> GPIO6
// LEFT_BUTTON  --> GPIO7
// RIGHT_BUTTON --> GPIO5
// UP_BUTTON    --> GPIO8

#ifndef USER_BTN
  #define USER_BTN              MENU_BUTTON
#endif

// SPI Definitions
#define PIN_SPI_SS              P16
#define PIN_SPI_MOSI            SPI_EXT_MOSI
#define PIN_SPI_MISO            SPI_EXT_MISO
#define PIN_SPI_SCK             SPI_EXT_SCK

// I2C Definitions
#define PIN_WIRE_SDA            I2C_EXT_SDA
#define PIN_WIRE_SCL            I2C_EXT_SCL

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
  #define SERIAL_UART_INSTANCE  101  // Connected to ST-Link
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         SERIAL_RX
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         SERIAL_TX
#endif

// Only 512k provided for cpu1, so defined the EEPROM_FLASH_PAGE_NUMBER
// for EEPROM emulation to the last 512k pages.
#define EEPROM_FLASH_PAGE_NUMBER  127

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
  #define SERIAL_PORT_MONITOR  Serial
  #define SERIAL_PORT_HARDWARE Serial1
#endif
