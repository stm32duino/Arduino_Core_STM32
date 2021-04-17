/*
 *******************************************************************************
 * Copyright (c) 2019, STMicroelectronics
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

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PG15
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PB1
#endif

// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PC4
#endif

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA9
#endif

// Default pin used for 'Serial2' instance
#define ENABLE_HWSERIAL2
#ifndef PIN_SERIAL2_RX
  #define PIN_SERIAL2_RX        PA3
#endif
#ifndef PIN_SERIAL2_TX
  #define PIN_SERIAL2_TX        PA2
#endif

// Default pin used for 'Serial3' instance
#define ENABLE_HWSERIAL3
#ifndef PIN_SERIAL3_RX
  #define PIN_SERIAL3_RX        PB11
#endif
#ifndef PIN_SERIAL3_TX
  #define PIN_SERIAL3_TX        PB10
#endif

// SD card slot Definitions
// SD detect signal can be defined if required
#define SD_DETECT_PIN           PF10

#include "variant_generic.h"
