/*
 *******************************************************************************
 * Copyright (c) 2019-2021, STMicroelectronics
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
// board doesn't breakout r3 connectors so listing in chip order
// LEFT
#define PC13                    0   // PHASE_UL
#define PC14                    1   // CAN_TERM
#define PC15                    2   // x (NOT_CONNECTED)
#define PF0                     3   // OSC_IN
#define PF1                     4   // OSC_OUT
#define PG10                    5   // NRST
#define PA0                     PIN_A0  // VBUS
#define PA1                     PIN_A1  // CURR1_H
#define PA2                     PIN_A2  // OP1_OUT
#define PA3                     PIN_A3  // CURR1_L
#define PA4                     PIN_A4  // BEMF1
// BOTTOM
#define PA5                     PIN_A5  // CURR2_L
#define PA6                     PIN_A6  // OP2_OUT
#define PA7                     PIN_A7  // CURR2_H
#define PC4                     PIN_A8  // BEMF2
#define PB0                     PIN_A9  // CURR3_H
#define PB1                     PIN_A10 // OP3_OUT
#define PB2                     PIN_A11 // CURR3_L
#define PB10                    18  // x
#define PB11                    PIN_A12 // BEMF3
// RIGHT
#define PB12                    PIN_A13 // POTENTIOMETER
#define PB13                    21  // x
#define PB14                    PIN_A14  // TEMPERATURE
#define PB15                    PIN_A15  // PHASE_WL
#define PC6                     24  // LED_BUILTIN
#define PA8                     25  // PHASE_UH
#define PA9                     26  // PHASE_VH
#define PA10                    27  // PHASE_WH
#define PA11                    28  // CAN_RX
#define PA12                    29  // PHASE_VL
#define PA13                    30  // SWDIO
// TOP
#define PA14                    31  // SWCLK
#define PA15                    32  // PWM
#define PC10                    33  // BUTTON
#define PC11                    34  // CAN_SHDN
#define PB3                     35  // USART2_TX
#define PB4                     36  // USART2_RX
#define PB5                     37  // GPIO_BEMF
#define PB6                     38  // HALL1/ENCODER_A
#define PB7                     39  // HALL2/ENCODER_B
#define PB8                     40  // HALL3/ENCODER_Z
#define PB9                     41  // CAN_TX

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA4_ALT1                (PA4  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA9_ALT1                (PA9  | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PA11_ALT1               (PA11 | ALT1)
#define PA11_ALT2               (PA11 | ALT2)
#define PA12_ALT1               (PA12 | ALT1)
#define PA12_ALT2               (PA12 | ALT2)
#define PA13_ALT1               (PA13 | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB4_ALT2                (PB4  | ALT2)
#define PB5_ALT1                (PB5  | ALT1)
#define PB5_ALT2                (PB5  | ALT2)
#define PB6_ALT1                (PB6  | ALT1)
#define PB6_ALT2                (PB6  | ALT2)
#define PB7_ALT1                (PB7  | ALT1)
#define PB7_ALT2                (PB7  | ALT2)
#define PB8_ALT1                (PB8  | ALT1)
#define PB8_ALT2                (PB8  | ALT2)
#define PB9_ALT1                (PB9  | ALT1)
#define PB9_ALT2                (PB9  | ALT2)
#define PB9_ALT3                (PB9  | ALT3)
#define PB11_ALT1               (PB11 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC6_ALT1                (PC6  | ALT1)
#define PC13_ALT1               (PC13 | ALT1)

#define NUM_DIGITAL_PINS        42
#define NUM_ANALOG_INPUTS       16

/* Alias */
#define A_PHASE_UL              PC13
#define A_CAN_TERM              PC14
#define A_VBUS                  PA0
#define A_CURR1_H               PA1
#define A_OP1_OUT               PA2
#define A_CURR1_L               PA3
#define A_BEMF1                 PA4
#define A_CURR2_L               PA5
#define A_OP2_OUT               PA6
#define A_CURR2_H               PA7
#define A_BEMF2                 PC4
#define A_CURR3_H               PB0
#define A_OP3_OUT               PB1
#define A_CURR3_L               PB2
#define A_BEMF3                 PB11
#define A_POTENTIOMETER         PB12
#define A_TEMPERATURE           PB14
#define A_PHASE_WL              PB15
#define A_PHASE_UH              PA8
#define A_PHASE_VH              PA9
#define A_PHASE_WH              PA10
#define A_CAN_RX                PA11
#define A_PHASE_VL              PA12
#define A_SWDIO                 PA13
#define A_SWCLK                 PA14
#define A_PWM                   PA15
#define A_BUTTON                PC10
#define A_CAN_SHDN              PC11
#define A_USART2_TX             PB3
#define A_USART2_RX             PB4
#define A_GPIO_BEMF             PB5
#define A_HALL1                 PB6
#define A_HALL2                 PB7
#define A_HALL3                 PB8
#define A_ENCODER_A             PB6
#define A_ENCODER_B             PB7
#define A_ENCODER_Z             PB8
#define A_CAN_TX                PB9

// On-board LED pin number
#define LED_RED                 PC6
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_RED
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC10
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3           PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PNUM_NOT_DEFINED
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PB7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB8
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
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PB4
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PB3
#endif

/* HAL configuration */
#define HSE_VALUE               (24000000UL)

/* Extra HAL modules */
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_FDCAN_MODULE_DISABLED)
  #define HAL_FDCAN_MODULE_ENABLED
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
  #define SERIAL_PORT_MONITOR   Serial
  #define SERIAL_PORT_HARDWARE  SerialLP1
#endif
