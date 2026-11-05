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
 *----------------------------------------------------------------------------
 *        Arduino digital pin numbers on the right (indexes into the digitalPin[] array)
 *        and the STM32 pins they correspond to on the left.  The only apparent
 *        function I can see is to reference a pin in a sketch in something
 *        like digitalWrite() and have it index into digitalPin[] to find the
 *        actual pin.  On the other hand, PIN_A* are numbers offset by PNUM_ANALOG_BASE,
 *        which serves to say that this IS an analog pin and which tells analogWrite
 *        to index into the digitalPin[] array to find the actual pin.
 *----------------------------------------------------------------------------*/
#define PA0                       PIN_A8  // A8/BATTERY_VOLTAGE (STAT)
#define PA1                       PIN_A1  // A1
#define PA2                       PIN_A9  // A9/TX2
#define PA3                       PIN_A0  // A0
#define PA4                       PIN_A10 // A10/D10
#define PA5                       PIN_A13 // A13/D13
#define PA6                       PIN_A12 // A12/D12
#define PA7                       PIN_A11 // A11/D11
#define PA9                       30      // TX
#define PA10                      28      // RX
#define PA11                      66      // USB_DM
#define PA12                      67      // USB_DP
#define PA13                      56      // SWDIO
#define PA14                      57      // SWCLK
#define PA15                      59      // JTDI
#define PB0                       PIN_A15 // A15/QIO1
#define PB1                       PIN_A6  // A6
#define PB2                       74      // BOOT1 (Do not connect to VDD)
#define PB3                       58      // JTDO
#define PB4                       31      // CTS
#define PB6                       42      // SCL
#define PB7                       44      // SDA
#define PB9                       14      // D14
#define PB10                      39      // TX3
#define PB11                      38      // RX3
#define PB13                      41      // CTS3
#define PB14                      27      // MI
#define PB15                      26      // MO
#define PC0                       PIN_A14 // A14/SCL3
#define PC1                       PIN_A3  // A3
#define PC2                       PIN_A7  // A7
#define PC3                       PIN_A2  // A2
#define PC4                       PIN_A4  // A4
#define PC5                       PIN_A5  // A5
#define PC6                       65      // USB_DETECT
#define PC9                       46      // SDA3
#define PC11                      48      // QCS
#define PC13                      55      // USER_BTN
#define PC14                      68      // OSC32 IN (LSE)
#define PC15                      69      // OSC32 OUT (LSE)
#define PD0                       16      // CS
#define PD1                       24      // SCK
#define PD2                       40      // RTS3
#define PD3                       37      // CTS2
#define PD4                       36      // RTS2
#define PD5                       33      // QEN
#define PD6                       34      // RX2
#define PD8                       1       // D1
#define PD9                       0       // D0
#define PD15                      9       // D9
#define PE1                       15      // D15
#define PE2                       54      // LED_BUILTIN
#define PE3                       4       // D4
#define PE4                       62      // ENABLE_3V3
#define PE6                       63      // DISCHARGE_3V3
#define PE9                       6       // D6
#define PE10                      49      // QCLK
#define PE11                      5       // D5
#define PE12                      53      // QIO0
#define PE13                      3       // D3
#define PE14                      51      // QIO2
#define PE15                      50      // QIO3
#define PF0                       45      // SDA2
#define PF1                       43      // SCL2
#define PF12                      8       // D8
#define PF13                      7       // D7
#define PF15                      2       // D2
#define PG0                       70      // VERSION BIT 0
#define PG1                       71      // VERSION BIT 1
#define PG2                       72      // VERSION BIT 2
#define PG3                       73      // VERSION BIT 3
#define PG7                       60      // LPUART1_VCP_TX (TX0)
#define PG8                       61      // LPUART1_VCP_RX (RX0)
#define PG12                      29      // RTS
#define PH3                       32      // B

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
#define PB6_ALT1                  (PB6  | ALT1)
#define PB7_ALT1                  (PB7  | ALT1)
#define PB9_ALT1                  (PB9  | ALT1)
#define PB10_ALT1                 (PB10 | ALT1)
#define PB11_ALT1                 (PB11 | ALT1)
#define PB13_ALT1                 (PB13 | ALT1)
#define PB14_ALT1                 (PB14 | ALT1)
#define PB14_ALT2                 (PB14 | ALT2)
#define PB15_ALT1                 (PB15 | ALT1)
#define PB15_ALT2                 (PB15 | ALT2)
#define PC6_ALT1                  (PC6  | ALT1)
#define PC9_ALT1                  (PC9  | ALT1)
#define PC11_ALT1                 (PC11 | ALT1)

#define NUM_DIGITAL_PINS          75
#define NUM_ANALOG_INPUTS         16

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN             PE2
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN                PC13
#endif

// Power switch ENABLE and DISCHARGE pins
#ifndef ENABLE_3V3
  #define ENABLE_3V3              PE4
#endif
#ifndef DISCHARGE_3V3
  #define DISCHARGE_3V3           PE6
  #define DISABLE_DISCHARGING     HIGH
  #define ENABLE_DISCHARGING      LOW
#endif

// Macro functions for 3V3 regulator management
#ifndef ENABLE_3V3_REGULATOR
#  define ENABLE_3V3_REGULATOR()  do { \
     digitalWrite(DISCHARGE_3V3, DISABLE_DISCHARGING); \
     digitalWrite(ENABLE_3V3, HIGH); \
   } while (0)
#endif
#ifndef DISABLE_3V3_REGULATOR
#  define DISABLE_3V3_REGULATOR() do { \
     digitalWrite(ENABLE_3V3, LOW); \
   } while (0)
#endif
#ifndef DRAIN_3V3_REGULATOR_MS
#  define DRAIN_3V3_REGULATOR_MS(ms) do { \
     if (digitalRead(ENABLE_3V3)) { break; } \
     digitalWrite(DISCHARGE_3V3, ENABLE_DISCHARGING); \
     delay(ms); \
     digitalWrite(DISCHARGE_3V3, DISABLE_DISCHARGING); \
   } while (0)
#endif

// Dedicated board pins
#ifndef VMAIN_ADC
  #define VMAIN_ADC               PA0
  #define VMAIN_ADC_DIV_BOT_R     4.3f
  #define VMAIN_ADC_DIV_TOP_R     10.0f
  #define VMAIN_ADC_DIV_K         ((double)((VMAIN_ADC_DIV_TOP_R + VMAIN_ADC_DIV_BOT_R) / VMAIN_ADC_DIV_BOT_R))
#endif
#ifndef VMAIN_MV
#  define VMAIN_MV() ({ \
     __HAL_ADC_CALC_DATA_TO_VOLTAGE(__LL_ADC_CALC_VREFANALOG_VOLTAGE(analogRead(AVREF), LL_ADC_GetResolution(ADC1)), analogRead(VMAIN_ADC), LL_ADC_GetResolution(ADC1)) * VMAIN_ADC_DIV_K; \
   })
#endif
// Charge detection is not implemented on the Swan hardware
// #ifndef CHARGE_DETECT
//   #define CHARGE_DETECT
// #endif
#ifndef USB_DETECT
  #define USB_DETECT              PC6
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS              PD0
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI            PB15
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO            PB14
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK             PD1
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
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX           PA10
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX           PA9
#endif

// Default pin used for generic 'Serial3' instance
#ifndef PIN_SERIAL3_RX
  #define PIN_SERIAL3_RX          PC5
#endif
#ifndef PIN_SERIAL3_TX
  #define PIN_SERIAL3_TX          PC4
#endif

// LPUART1
#ifndef PIN_SERIAL_LP1_RX
  #define PIN_SERIAL_LP1_RX       PG8
#endif
#ifndef PIN_SERIAL_LP1_TX
  #define PIN_SERIAL_LP1_TX       PG7
#endif

// Virtual COM Port for Swans with a 14-pin STLink Connector mounted.
// To use the STLINK's Virtual COM port, this would be added to an Arduino project:
//     Uart SerialVCP(PIN_VCP_RX, PIN_VCP_TX);
#ifndef PIN_VCP_RX
  #define PIN_VCP_RX              PIN_SERIAL_LP1_RX
#endif
#ifndef PIN_VCP_TX
  #define PIN_VCP_TX              PIN_SERIAL_LP1_TX
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_OSPI_MODULE_DISABLED)
  #define HAL_OSPI_MODULE_ENABLED
#endif
// Disabled as some SDMMC pins are NC
// #if !defined(HAL_SD_MODULE_DISABLED)
//   #define HAL_SD_MODULE_ENABLED
// #endif

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
