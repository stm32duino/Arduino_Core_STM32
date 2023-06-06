/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#pragma once


/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
#define PC0                     PIN_A1   //D0
#define PC1                     PIN_A12  //D1

#define PC6                     2        //PWM0
#define PC7                     3        //PWM1

#define PA2                     PIN_A4   //TX1
#define PA3                     PIN_A5   //RX1

#define PD2                     6        //G0
#define PA8                     7        //G1
#define PA0                     PIN_A3   //G2
#define PC8                     9        //G3
#define PC9                     10       //G4
#define PC13                    11       //G5
#define PC2                     PIN_A13  //G6
#define PB13                    13       //G10 - HOST_VBUS
#define PB12                    14       //G11 - HOST_ID

#define PB4                     15       //AUD_OUT
#define PB5                     16       //AUD_IN
#define PA4                     PIN_A6   //AUD_LRCLK
#define PB3                     18       //AUD_BCLK

#define PB9                     19       //CAN_TX
#define PB8                     20       //CAN_RX

#define PB10                    21       //SCL
#define PB11                    22       //SDA
#define PB1                     PIN_A10  //INT

#define PB6                     24       //SCL1
#define PB7                     25       //SDA1

#define PA5                     PIN_A7   //SCK
#define PA7                     PIN_A9   //COPI
#define PA6                     PIN_A8   //CIPO
#define PC4                     PIN_A14  //CS

#define PB14                    30       //HOST_D-
#define PB15                    31       //HOST_D+

#define PA15                    32       //STAT LED

#define PC5                     PIN_A0
#define PB0                     PIN_A1
#define PA1                     PIN_A2   //BATT_VIN/3

#define PC14                    36       //OSC32
#define PC15                    37       //OSC32

#define PA11                    38       //D+
#define PA12                    39       //D-

#define PA13                    40       //SWDIO
#define PA14                    41       //SWCLK

#define PC10                    42       //FLASH_SCK
#define PC11                    43       //FLASH_CIPO
#define PC12                    44       //FLASH_COPI
#define PC3                     45       //FLASH_CS

// This must be a literal
#define NUM_DIGITAL_PINS        46
// This must be a literal with a value less than or equal to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       15

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PA15
#endif

// No user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// Pulse Width Modulation
#define PWM0                    PC6
#define PWM1                    PC7

// General Purpose
#define G0                      PD2
#define G1                      PA8
#define G2                      PA0
#define G3                      PC8
#define G4                      PC9
#define G5                      PC13
#define G6                      PC2
#define G10                     PB13
#define G11                     PB12

// I2S Interface
#define AUD_OUT                 PB4
#define AUD_IN                  PB5
#define AUD_LRCLK               PA4
#define AUD_BCLK                PB3

// Analog Pins
#define BATT_VIN                PA1

// UART1
#define TX1                     PA2
#define RX1                     PA3

// Can Bus
#define CAN_RX                  PB8
#define CAN_TX                  PB9

// SWD
#define SWDIO                   PA13
#define SWDCK                   PA14

// USB Host
#define HOST_DM                 PB14
#define HOST_DP                 PB15
#define HOST_VBUS               PB13
#define HOST_ID                 PB12

// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PC4
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

// SPI FLASH
#define FLASH_SDO               PC11
#define FLASH_SDI               PC12
#define FLASH_SCK               PC10
#define FLASH_CS                PC3

// I2C
#define PIN_WIRE_SCL            PB10
#define PIN_WIRE_SDA            PB11
#define INT PB1

#define SCL1                    PB6
#define SDA1                    PB7


// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  3
#endif

// Default pin used for 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA3
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA2
#endif

/* HAL configuration */
#define HSE_VALUE               12000000U

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
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial1
  #endif
#endif
