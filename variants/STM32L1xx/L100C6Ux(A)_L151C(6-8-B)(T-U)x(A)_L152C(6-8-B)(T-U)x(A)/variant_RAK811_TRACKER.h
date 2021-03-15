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
#define PA0                     0  // GPS_PPS_PIN
#define PA8                     1
#define PA9                     2  // UART_TX
#define PA10                    3  // UART_RX
#define PA12                    4  // LED1
#define PA13                    5
#define PA14                    6
#define PA15                    7  // GPS_POWER_ON_PIN
#define PB2                     8
#define PB3                     9
#define PB4                     10 // LED2
#define PB5                     11
#define PB8                     12 // I2C_SCL
#define PB9                     13 // I2C_SDA
#define PB10                    14 // GPS_UART_TX
#define PB11                    15 // GPS_UART_RX
#define PA1                     PIN_A0
#define PA2                     PIN_A1 // ADC_VBAT
#define PB12                    PIN_A2
#define PB14                    19 // LIS3DH_INT1_PIN
#define PB15                    20 // LIS3DH_INT2_PIN
#define PB13                    21 // RADIO_RESET
#define PH1                     22 // RADIO_XTAL_EN
#define PA7                     23 // RADIO_MOSI
#define PA6                     24 // RADIO_MISO
#define PA5                     25 // RADIO_SCLK
#define PB0                     26 // RADIO_NSS
#define PA11                    27 // RADIO_DIO_0
#define PB1                     28 // RADIO_DIO_1
#define PA3                     29 // RADIO_DIO_2
#define PH0                     30 // RADIO_DIO_3
#define PC13                    31 // RADIO_DIO_4
#define PB6                     32 // RADIO_RF_CRX_RX
#define PB7                     33 // RADIO_RF_CBT_HF
#define PA4                     34 // RADIO_RF_CTX_PA

// Alternate pins number
#define PA2_ALT1                (PA2 | ALT1)
#define PA3_ALT1                (PA3 | ALT1)
#define PA6_ALT1                (PA6 | ALT1)
#define PA7_ALT1                (PA7 | ALT1)
#define PB8_ALT1                (PB8 | ALT1)
#define PB9_ALT1                (PB9 | ALT1)

#define NUM_DIGITAL_PINS        35
#define NUM_ANALOG_INPUTS       3

// On-board LED pin number
#define LED_BUILTIN             PA12
#define LED1                    LED_BUILTIN
#define LED2                    PB4

// SPI Definitions
#define PIN_SPI_SS              PB0
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5

// I2C Definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB8

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// UART Definitions
#define SERIAL_UART_INSTANCE    1
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9

// LoRa Definitions
#define RADIO_RESET             PB13
#define RADIO_XTAL_EN           PH1

#define RADIO_MOSI              PA7
#define RADIO_MISO              PA6
#define RADIO_SCLK              PA5
#define RADIO_NSS               PB0

#define RADIO_DIO_0             PA11
#define RADIO_DIO_1             PB1
#define RADIO_DIO_2             PA3
#define RADIO_DIO_3             PH0
#define RADIO_DIO_4             PC13

#define RADIO_RF_CRX_RX         PB6 //CRF3
#define RADIO_RF_CBT_HF         PB7 //CRF2 HF
#define RADIO_RF_CTX_PA         PA4 //CRF1 PA

// GPS Definitions
#define GPS_PPS_PIN             PA0
#define GPS_UART                USART3
#define GPS_POWER_ON_PIN        PA15
#define GPS_UART_TX             PB10
#define GPS_UART_RX             PB11

// MEMS (LIS3DH)
#define LIS3DH_INT1_PIN         PB14
#define LIS3DH_INT2_PIN         PB15

/* HAL configuration */
#define HSE_VALUE               12000000U

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
