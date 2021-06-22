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

// This header file override few definitions and then include variant_generic.h

// MOT0
#define M0_A            PB1
#define M0_B            PB0
#define M0_C            PA7
// MOT1
#define M1_A            PA6
#define M1_B            PA3
#define M1_C            PA2
// MOT2
#define M2_A            PB9
#define M2_B            PA1
#define M2_C            PB8

// can control sony/canon and Panasonic cameras
#define IR              PA0
// through 10K / 1.5K voltage divider
#define LIPO            PA5
#define BOOT1           PB2

// #define USB_D           PB5

// I2C 1 & 2
#define I2C2_SCL        PB6
#define I2C2_SDA        PB7
#define I2C1_SCL        PB10
#define I2C1_SDA        PB11

#define LED0            PB12
#define LED_GREEN       PB12
#define LED_BUILTIN     PB12

// EITHER SPI (requires desolder RED LED)
#define SPI2_SCK        PB13
#define SPI2_MISO       PB14
#define SPI2_MOSI       PB15

#define PIN_SPI_SS      AUX2
#define PIN_SPI_SS1     AUX1
#define PIN_SPI_SS2     AUX0
#define PIN_SPI_MOSI    SPI2_MOSI
#define PIN_SPI_MISO    SPI2_MISO
#define PIN_SPI_SCK     SPI2_SCK

// OR
#define LED1            PB13
#define LED_RED         PB13
#define AUX0            PB14
#define AUX1            PB15

#define RC2             PA8
// EITHER
#define RC1             PA9
#define RC0             PA10
// OR
#define USART1_TX       PA9
#define USART1_RX       PA10

#define RC0             PA10

#define SWDIO           PA13
#define SWDCL           PA14
#define AUX2            PA15

#define POT0            PC0
#define POT1            PC1
#define POT2            PC2

#define BUT             PC3
#define XOR             PC4

// Could be connected RC Input  PWM (mapped to TIM8 for interrupts)
#define RC2_0           PC6
#define RC2_1           PC7
#define RC2_2           PC8
#define RC2_3           PC9

#define USART3_TX       PC10
#define USART3_RX       PC11

// On-board user button
#ifndef USER_BTN
  #define USER_BTN      BUT
#endif

// Timer Definitions
#ifndef TIMER_SERVO
  #define TIMER_SERVO   TIM2
#endif

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  3
#endif

// Serial1 is not marked on board (shared with RC1 anf RC2 pins)
#define ENABLE_HWSERIAL1

// Default pin used for 'Serial3' instance
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         USART3_RX
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         USART3_TX
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
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

  #ifndef SERIAL_PORT_USBVIRTUAL
    #define SERIAL_PORT_USBVIRTUAL   SerialUSB
  #endif
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR  Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE_OPEN
    #define SERIAL_PORT_HARDWARE_OPEN  Serial1
  #endif
#endif

#include "variant_generic.h"
