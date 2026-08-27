/*
 * Copyright (c) 2026, Seeed Technology Co., Ltd.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#pragma once

/* XIAO connector pin numbers. */
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA2                     PIN_A2
#define PA3                     PIN_A3
#define PB7                     4
#define PB6                     5
#define PA9                     6
#define PA10                    7
#define PE2                     8
#define PB0                     9
#define PB15                    10
#define PB8                     11
#define PB9                     12
#define PB5                     13
#define PB13                    14
#define PB14                    15

/* Board-only pins: they follow the XIAO connector pins in digitalPin[]. */
#define PB12                    16
#define PIN_IMU_SCL             17  // PB3 / I2C2_SCL
#define PIN_IMU_SDA             18  // PB4 / I2C2_SDA
#define PIN_IMU_INT1            19  // PC13 / LSM6DS3TR-C INT1
#define PIN_IMU_HEATER          20  // PA8 / TIM1_CH1

/* Alternate functions used by the default board peripherals. */
#define PA9_ALT1                (PA9 | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)

#define NUM_DIGITAL_PINS        21
#define NUM_ANALOG_INPUTS       4

#ifndef LED_BUILTIN
  #define LED_BUILTIN           PB12
#endif

/* SPI3: D8/SCK (PE2), D9/MISO (PB0), D10/MOSI (PB15).
 * No board-default chip-select is assigned; sketches control device CS. */
#define PIN_SPI_SS              NUM_DIGITAL_PINS
#define PIN_SPI_SS1             NUM_DIGITAL_PINS
#define PIN_SPI_SS2             NUM_DIGITAL_PINS
#define PIN_SPI_SS3             NUM_DIGITAL_PINS
#define PIN_SPI_MOSI            PB15_ALT2
#define PIN_SPI_MISO            PB0
#define PIN_SPI_SCK             PE2

#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6

#define TIMER_TONE              TIM16
#define TIMER_SERVO             TIM17

/* Serial is USB CDC when enabled. Serial1 is the connector UART on D6/D7. */
#define SERIAL_UART_INSTANCE    1
#define PIN_SERIAL_TX           PA9_ALT1
#define PIN_SERIAL_RX           PA10_ALT1

#ifndef HSE_VALUE
  #define HSE_VALUE             48000000U
#endif

/* USBDevice includes the selected variant, so these remain board-owned
 * descriptor strings without adding quoted compiler flags to every recipe. */
#ifndef USB_MANUFACTURER_STRING
  #define USB_MANUFACTURER_STRING "Seeed Studio"
#endif
#ifndef USB_PRODUCT_STRING
  #define USB_PRODUCT_STRING      "XIAO STM32C5"
#endif

#ifdef __cplusplus
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR       Serial
  #endif
  #ifndef SERIAL_PORT_USBVIRTUAL
    #define SERIAL_PORT_USBVIRTUAL    Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE      Serial1
  #endif
  #ifndef SERIAL_PORT_HARDWARE_OPEN
    #define SERIAL_PORT_HARDWARE_OPEN Serial1
  #endif
#endif
