/*
 *******************************************************************************
 * Copyright (c) 2018-2021, STMicroelectronics
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
// USB connector on the top, MCU side
// Left Side
#define PB9                     0
#define PB8                     1
#define PB7                     2
#define PB6                     3
#define PB5                     4
#define PB4                     5
#define PB3                     6
#define PA15                    7
#define PA12                    8  // USB DP
#define PA11                    9  // USB DM
#define PA10                    10
#define PA9                     11
#define PA8                     12
#define PB15                    13
#define PB14                    14
#define PB13                    15
#define PB12                    16
// Right side
#define PC13                    17 // LED
#define PC14                    18
#define PC15                    19
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA2                     PIN_A2
#define PA3                     PIN_A3
#define PA4                     PIN_A4
#define PA5                     PIN_A5
#define PA6                     PIN_A6
#define PA7                     PIN_A7
#define PB0                     PIN_A8
#define PB1                     PIN_A9
#define PB10                    30
#define PB11                    31
// Other
#define PB2                     32 // BOOT1
#define PA13                    33 // SWDI0
#define PA14                    34 // SWCLK

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA4_ALT1                (PA4  | ALT1)
#define PA5_ALT1                (PA5  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA8_ALT1                (PA8  | ALT1)
#define PA9_ALT1                (PA9  | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PA11_ALT1               (PA11 | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB10_ALT1               (PB10 | ALT1)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)

#define NUM_DIGITAL_PINS        35
#define NUM_ANALOG_INPUTS       10

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PNUM_NOT_DEFINED
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA7
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PA6
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PA5
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB6
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM3
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM4
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

// USB, pull this pin low to *disable* the USB attach pullup
#define USBD_DETACH_PIN         PB9
#define USBD_DETACH_LEVEL       LOW

/* Dedicated definitions */
#ifndef MAX_PRIORITY
  #define MAX_PRIORITY            15
#endif
#ifndef MIN_PRIORITY
  #define MIN_PRIORITY            0
#endif

#ifndef SYSTICK_INT_PRIORITY
  #if FREERTOS
    #define SYSTICK_INT_PRIORITY  MAX_PRIORITY
    #define STM32_INT_PRIORITY    5
  #else
    #define SYSTICK_INT_PRIORITY  MIN_PRIORITY
    #define STM32_INT_PRIORITY    5
  #endif
#endif

#ifndef TAMPER_PRIORITY           /*f1 2*/
  #define TAMPER_PRIORITY         STM32_INT_PRIORITY
#endif
#ifndef RTC_PRIORITY              /*f1 3*/
  #define RTC_PRIORITY            STM32_INT_PRIORITY
#endif
#ifndef RCC_PRIORITY              /*f1 5*/
  #define RCC_PRIORITY            STM32_INT_PRIORITY
#endif
#ifndef EXTI_PRIORITY             /*f1 6~10,23,40*/
  #define EXTI_PRIORITY           MAX_PRIORITY+1  //f1 6~9 button use 0x0f
#endif
#ifndef DMA1_PRIORITY             /*f1 11~17*/
  #define DMA1_PRIORITY           STM32_INT_PRIORITY
#endif
#ifndef ADC_PRIORITY              /*f1 18*/
  #define ADC_PRIORITY            STM32_INT_PRIORITY
#endif
#ifndef USB_HP_PRIORITY           /*f1 19*/
  #define USB_HP_PRIORITY         STM32_INT_PRIORITY
#endif
#ifndef USB_LP_PRIORITY           /*f1 20*/
  #define USB_LP_PRIORITY         STM32_INT_PRIORITY
#endif
#ifndef TIM_PRIORITY              /*f1 24~30 43~46 54~55*/
  #define TIM_PRIORITY            STM32_INT_PRIORITY
#endif
#ifndef I2C_PRIORITY              /*f1 31~34*/
  #define I2C_PRIORITY            STM32_INT_PRIORITY
#endif
#ifndef SPI_PRIORITY              /*f1 35 36 51*/
  #define SPI_PRIORITY            STM32_INT_PRIORITY
#endif
#ifndef USART_PRIORITY            /*f1 37~39 52~53*/
  #define USART_PRIORITY          STM32_INT_PRIORITY
#endif
#ifndef SDIO_PRIORITY             /*f1 49*/
  #define SDIO_PRIORITY           STM32_INT_PRIORITY-1
#endif
#ifndef DMA2_PRIORITY             /*f1 56~59*/
  #define DMA2_PRIORITY           STM32_INT_PRIORITY
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
    #define SERIAL_PORT_HARDWARE  Serial1
  #endif
#endif
