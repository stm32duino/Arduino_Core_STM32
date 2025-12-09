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
 *        STM32 pins number
 *----------------------------------------------------------------------------
 *        Arduino digital pin numbers on the right (indexes into the digitalPin[] array)
 *        and the STM32 pins they correspond to on the left.  The only apparent
 *        function I can see is to reference a pin in a sketch in something
 *        like digitalWrite() and have it index into digitalPin[] to find the
 *        actual pin.  On the other hand, PIN_A* are numbers offset by PNUM_ANALOG_BASE,
 *        which serves to say that this IS an analog pin and which tells analogWrite
 *        to index into the digitalPin[] array to find the actual pin.
 *----------------------------------------------------------------------------*/
#define PA0                       PIN_A0  // A0/D0
#define PA1                       PIN_A1  // A1/D1
#define PA2                       PIN_A2  // A2/D2
#define PA3                       PIN_A3  // A3/D3
#define PA4                       PIN_A8  // A8/BATTERY_VOLTAGE (STAT)
#define PA5                       25      // USART3_VCP_RX
#define PA6                       PIN_A6  // A6/MI
#define PA7                       PIN_A5  // A5
#define PA8                       7       // LED_BUILTIN
#define PA9                       19      // TX
#define PA10                      18      // RX
#define PA11                      32      // USB_D_N
#define PA12                      33      // USB_D_P
#define PA13                      23      // SWDIO
#define PA14                      24      // SWCLK
#define PA15                      29      // CHARGE_DETECT
#define PB0                       PIN_A7  // A7/D11
#define PB1                       PIN_A4  // A4/D4
#define PB2                       31      // USB_DETECT
#define PB3                       15      // CK
#define PB4                       13      // D13
#define PB5                       16      // MO
#define PB6                       21      // SCL
#define PB7                       22      // SDA
#define PB8                       5       // D5
#define PB9                       6       // D6
#define PB10                      26      // USART3_VCP_TX
#define PB13                      10      // D10
#define PB14                      9       // D9
#define PB15                      12      // D12
#define PC13                      8       // USER_BTN
#define PC14                      34      // OSC32_IN (LSE)
#define PC15                      35      // OSC32_OUT (LSE)
#define PH0                       27      // ENABLE_3V3
#define PH1                       28      // DISCHARGE_3V3
#define PH3                       20      // B

// Alternate pins number
#define PA0_ALT1                  (PA0  | ALT1)
#define PA1_ALT1                  (PA1  | ALT1)
#define PA1_ALT2                  (PA1  | ALT2)
#define PA2_ALT1                  (PA2  | ALT1)
#define PA2_ALT2                  (PA2  | ALT2)
#define PA3_ALT1                  (PA3  | ALT1)
#define PA3_ALT2                  (PA3  | ALT2)
#define PA4_ALT1                  (PA4  | ALT1)
#define PA5_ALT1                  (PA5  | ALT1)
#define PA6_ALT1                  (PA6  | ALT1)
#define PA7_ALT1                  (PA7  | ALT1)
#define PA7_ALT2                  (PA7  | ALT2)
#define PA7_ALT3                  (PA7  | ALT3)
#define PA15_ALT1                 (PA15 | ALT1)
#define PB0_ALT1                  (PB0  | ALT1)
#define PB0_ALT2                  (PB0  | ALT2)
#define PB1_ALT1                  (PB1  | ALT1)
#define PB1_ALT2                  (PB1  | ALT2)
#define PB3_ALT1                  (PB3  | ALT1)
#define PB4_ALT1                  (PB4  | ALT1)
#define PB5_ALT1                  (PB5  | ALT1)
#define PB6_ALT1                  (PB6  | ALT1)
#define PB7_ALT1                  (PB7  | ALT1)
#define PB8_ALT1                  (PB8  | ALT1)
#define PB9_ALT1                  (PB9  | ALT1)
#define PB10_ALT1                 (PB10 | ALT1)
#define PB13_ALT1                 (PB13 | ALT1)
#define PB14_ALT1                 (PB14 | ALT1)
#define PB14_ALT2                 (PB14 | ALT2)
#define PB15_ALT1                 (PB15 | ALT1)
#define PB15_ALT2                 (PB15 | ALT2)

#define NUM_DIGITAL_PINS          36
#define NUM_ANALOG_INPUTS         9

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN             PA8
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN                PC13
#endif

// Power switch ENABLE and DISCHARGE pins
#ifndef ENABLE_3V3
  #define ENABLE_3V3              PH0
#endif
#ifndef DISCHARGE_3V3
  #define DISCHARGE_3V3           PH1
  #define DISABLE_DISCHARGING     HIGH
  #define ENABLE_DISCHARGING      LOW
#endif
#ifndef BATTERY_VOLTAGE
  #define BATTERY_VOLTAGE         PA4
#endif
#ifndef CHARGE_DETECT
  #define CHARGE_DETECT           PA15
#endif
#ifndef USB_DETECT
  #define USB_DETECT              PB2
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS              PB0  // Shared with D11 (no dedicated CS pin)
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1             PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2             PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3             PNUM_NOT_DEFINED
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI            PB5
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO            PA6
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK             PB3
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA            PB7
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL            PB6
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
  #define SERIAL_UART_INSTANCE    1
#endif

// Default pin used for generic 'Serial' instance
// Required for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX           PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX           PA9
#endif

// Default pin used for generic 'Serial3' instance
// Required for Virtual COM Port (VCP)
#ifndef PIN_SERIAL3_RX
  #define PIN_SERIAL3_RX          PA5
#endif
#ifndef PIN_SERIAL3_TX
  #define PIN_SERIAL3_TX          PB10
#endif

// LPUART1
#ifndef PIN_SERIAL_LP1_RX
  #define PIN_SERIAL_LP1_RX       PA3
#endif
#ifndef PIN_SERIAL_LP1_TX
  #define PIN_SERIAL_LP1_TX       PA2
#endif

// Virtual COM Port for Heron with a 14-pin STLink Connector mounted.
// To use the STLINK's Virtual COM port, add the following line to an Arduino project:
//     HardwareSerial SerialVCP(PIN_VCP_RX, PIN_VCP_TX);
#ifndef PIN_VCP_RX
  #define PIN_VCP_RX              PIN_SERIAL3_RX
#endif
#ifndef PIN_VCP_TX
  #define PIN_VCP_TX              PIN_SERIAL3_TX
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_OSPI_MODULE_DISABLED)
  #define HAL_OSPI_MODULE_ENABLED
#endif

// Alternate SYS_WKUP definition
#define PWR_WAKEUP_PIN1_1
#define PWR_WAKEUP_PIN2_1
#define PWR_WAKEUP_PIN3_1
#define PWR_WAKEUP_PIN4_1
#define PWR_WAKEUP_PIN4_2
#define PWR_WAKEUP_PIN5_1
#define PWR_WAKEUP_PIN6_1
#define PWR_WAKEUP_PIN7_1
#define PWR_WAKEUP_PIN8_1

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
