/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
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
 *        Arduino digital pin numbers on the right (indexes into the digitalPin[] array)
 *        and the STM32 pins they correspond to on the left.  The only apparent
 *        function I can see is to reference a pin in a sketch in something
 *        like digitalWrite() and have it index into digitalPin[] to find the
 *        actual pin.  On the other hand, PIN_A* are numbers offset by PNUM_ANALOG_BASE,
 *        which serves to say that this IS an analog pin and which tells analogWrite
 *        to index into the digitalPin[] array to find the actual pin.
 *----------------------------------------------------------------------------*/
#define PA0                     PIN_A0  // A0/D0
#define PA1                     PIN_A1  // A1/D1
#define PA2                     PIN_A2  // A2/D2
#define PA3                     PIN_A3  // A3/D3
#define PB1                     PIN_A4  // A4/D4
#define PB8                     5       // D5
#define PB9                     6       // D6
#define PA4                     PIN_A6  // BAT_VOLTAGE
#define PA8                     8       // LED_BUILTIN
#define PB14                    9       // D9
#define PB13                    10      // D10
#define PB0                     11      // D11
#define PB15                    12      // D12
#define PB4                     13      // D13
#define PA5                     14      // CK
#define PA6                     15      // MI
#define PA7                     PIN_A5  // A5
#define PA9                     17      // TX
#define PA10                    18      // RX
#define PA11                    19      // USB_DM
#define PA12                    20      // USB_DP
#define PA13                    21      // SWDIO
#define PA14                    22      // SWCLK
#define PA15                    23      // CHARGE_DETECT
#define PB3                     24      // USB_DETECT
#define PB5                     25      // MO
#define PB6                     26      // SCL
#define PB7                     27      // SDA
#define PB10                    28      // LPUART1_VCP_RX
#define PB11                    29      // LPUART1_VCP_TX
#define PC13                    30      // USER_BTN
#define PC14                    31      // OSC32_IN
#define PC15                    32      // OSC32_OUT
#define PH0                     33      // ENABLE_3V3
#define PH1                     34      // DISCHARGE_3V3
#define PH3                     35      // B

// Alternate pins number
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA4_ALT1                (PA4  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB15_ALT1               (PB15 | ALT1)

#define NUM_DIGITAL_PINS        36
#define NUM_ANALOG_INPUTS       7

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PA8
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PC13
#endif

// Power switch ENABLE and DISCHARGE pins
#ifndef ENABLE_3V3
  #define ENABLE_3V3            PH0
#endif
#ifndef DISCHARGE_3V3
  #define DISCHARGE_3V3         PH1
  #define DISABLE_DISCHARGING   HIGH
  #define ENABLE_DISCHARGING    LOW
#endif
#ifndef CHARGE_DETECT
  #define CHARGE_DETECT         PA15
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PB8  // Just default to D5, because we don't have a CS pin
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
  #define PIN_SPI_MOSI          PB5
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
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
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

// LPUART1
#ifndef PIN_SERIAL_LP1_RX
  #define PIN_SERIAL_LP1_RX     PB10
#endif
#ifndef PIN_SERIAL_LP1_TX
  #define PIN_SERIAL_LP1_TX     PB11
#endif

// Virtual COM Port for Cygnet with a 14-pin STLink Connector mounted.
// To use the STLINK's Virtual COM port, this would be added to an Arduino project:
//     HardwareSerial SerialVCP(PIN_VCP_RX, PIN_VCP_TX);
#ifndef PIN_VCP_RX
  #define PIN_VCP_RX     PIN_SERIAL_LP1_RX
#endif
#ifndef PIN_VCP_TX
  #define PIN_VCP_TX     PIN_SERIAL_LP1_TX
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
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
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
#endif
