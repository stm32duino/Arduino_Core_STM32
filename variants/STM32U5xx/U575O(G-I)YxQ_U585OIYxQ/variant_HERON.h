/*
 *******************************************************************************
 * Copyright (c) 2020-2026, STMicroelectronics
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
 *        The pin number definitions below are used to provide a named index
 *        into the digitalPin array defined in variant_CYGNET.cpp. The analog
 *        pins (i.e. PIN_A*) are defined as offset from PNUM_ANALOG_BASE, which
 *        is defined in pin_arduino_analog.h. The index of the analog pin in the
 *        digitalPin array can be retrieved from the analogInputPin array by
 *        masking the pin number against PNUM_ANALOG_BASE (resulting in the
 *        bottom 6 bits) and using that value as an index into the analog array.
 *----------------------------------------------------------------------------*/
#define PA0                       PIN_A0  // A0/D0
#define PA1                       PIN_A1  // A1/D1
#define PA2                       PIN_A2  // A2/D2
#define PA3                       PIN_A3  // A3/D3
#define PA4                       PIN_A8  // A8/BATTERY_VOLTAGE (STAT)
#define PA5                       25      // A9/USART3_VCP_RX
#define PA6                       PIN_A6  // A6/MI
#define PA7                       PIN_A5  // A5
#define PA8                        7      // LED_BUILTIN
#define PA9                       19      // TX
#define PA10                      18      // RX
#define PA11                      32      // USB_D_N
#define PA12                      33      // USB_D_P
#define PA13                      23      // SWDIO
#define PA14                      24      // SWCLK
#define PA15                      29      // CHARGE_DETECT
#define PB0                       PIN_A7  // A7/D11
#define PB1                       PIN_A4  // A4/D4
#define PB2                       31      // A10/USB_DETECT
#define PB3                       15      // CK
#define PB4                       13      // D13
#define PB5                       16      // MO
#define PB6                       21      // SCL
#define PB7                       22      // SDA
#define PB8                        5      // D5
#define PB9                        6      // D6
#define PB10                      26      // USART3_VCP_TX
#define PB13                      10      // D10
#define PB14                       9      // D9
#define PB15                      12      // D12
// #define PC0                       PIN_A11
// #define PC1                       PIN_A12
// #define PC2                       PIN_A13
// #define PC3                       PIN_A14
// #define PC5                       PIN_A15
// #define PC6                       35
// #define PC7                       36
// #define PC8                       37
// #define PC9                       38
// #define PC10                      39
// #define PC11                      40
// #define PC12                      41
#define PC13                       8      // USER_BTN
#define PC14                      34      // OSC32_IN (LSE)
#define PC15                      35      // OSC32_OUT (LSE)
// #define PD0                       45
// #define PD1                       46
// #define PD2                       47
// #define PD4                       48
// #define PD5                       49
// #define PD14                      50
// #define PD15                      51
// #define PE3                       52
// #define PE4                       53
// #define PE5                       54
// #define PE6                       55
// #define PE7                       56
// #define PE8                       57
// #define PE9                       58
// #define PE10                      59
// #define PG9                       60
// #define PG10                      61
// #define PG11                      62
// #define PG12                      63
// #define PG13                      64
// #define PG14                      65
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
// #define PC0_ALT1                  (PC0  | ALT1)
// #define PC1_ALT1                  (PC1  | ALT1)
// #define PC2_ALT1                  (PC2  | ALT1)
// #define PC3_ALT1                  (PC3  | ALT1)
// #define PC5_ALT1                  (PC5  | ALT1)
// #define PC6_ALT1                  (PC6  | ALT1)
// #define PC7_ALT1                  (PC7  | ALT1)
// #define PC8_ALT1                  (PC8  | ALT1)
// #define PC9_ALT1                  (PC9  | ALT1)
// #define PC10_ALT1                 (PC10 | ALT1)
// #define PC11_ALT1                 (PC11 | ALT1)

#define NUM_DIGITAL_PINS          36
#define NUM_ANALOG_INPUTS          9

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
  #define VMAIN_ADC               PA4
  #define VMAIN_ADC_DIV_BOT_R     4.3f
  #define VMAIN_ADC_DIV_TOP_R     10.0f
  #define VMAIN_ADC_DIV_K         ((double)((VMAIN_ADC_DIV_TOP_R + VMAIN_ADC_DIV_BOT_R) / VMAIN_ADC_DIV_BOT_R))
#endif
#ifndef VMAIN_MV
#  define VMAIN_MV() ({ \
     __HAL_ADC_CALC_DATA_TO_VOLTAGE(ADC1, __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC1, analogRead(AVREF), LL_ADC_GetResolution(ADC1)), analogRead(VMAIN_ADC), LL_ADC_GetResolution(ADC1)) * VMAIN_ADC_DIV_K; \
   })
#endif
#ifndef CHARGE_DETECT
  #define CHARGE_DETECT           PA15
  #define CHARGING                LOW
  #define NOT_CHARGING            HIGH
#endif
#ifndef USB_DETECT
  #define USB_DETECT              PB2
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS              PB0  // Shared with D11 (no dedicated CS pin)
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1             PA15
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2             PB0
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
// Mandatory for Firmata
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
//     Uart SerialVCP(PIN_VCP_RX, PIN_VCP_TX);
#ifndef PIN_VCP_RX
  #define PIN_VCP_RX              PIN_SERIAL3_RX
#endif
#ifndef PIN_VCP_TX
  #define PIN_VCP_TX              PIN_SERIAL3_TX
#endif

// Extra HAL modules
// #if !defined(HAL_DAC_MODULE_DISABLED)
//   #define HAL_DAC_MODULE_ENABLED
// #endif
// #if !defined(HAL_OSPI_MODULE_DISABLED)
//   #define HAL_OSPI_MODULE_ENABLED
// #endif
// #if !defined(HAL_SD_MODULE_DISABLED)
//   #define HAL_SD_MODULE_ENABLED
// #endif

// Alternate SYS_WKUP definition
#define PWR_WAKEUP_PIN1_1
#define PWR_WAKEUP_PIN1_2
#define PWR_WAKEUP_PIN2_1
#define PWR_WAKEUP_PIN2_2
#define PWR_WAKEUP_PIN3_1
#define PWR_WAKEUP_PIN3_2
#define PWR_WAKEUP_PIN4_1
#define PWR_WAKEUP_PIN4_2
#define PWR_WAKEUP_PIN5_1
#define PWR_WAKEUP_PIN5_2
#define PWR_WAKEUP_PIN6_1
#define PWR_WAKEUP_PIN6_2
#define PWR_WAKEUP_PIN7_1
#define PWR_WAKEUP_PIN7_2
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
