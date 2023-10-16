/*
 *******************************************************************************
 * Copyright (c) 2023, STMicroelectronics
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
#define PA2                     0
#define PA3                     1
#define PA0                     PIN_A0
#define PA1                     PIN_A1
#define PA6                     PIN_A2
#define PB10                    5
#define PB14                    6
#define PB0                     PIN_A3
#define PB1                     PIN_A4
#define PB15                    9
#define PA8                     10
#define PA11                    11
#define PB13                    12
#define PB2                     PIN_A5
#define PB3                     14
#define PB4                     15
#define PB5                     16
#define PB6                     17
#define PB7                     18
#define PA4                     PIN_A6
#define PA5                     20
#define PA7                     21
#define PA9                     22
#define PA10                    23
#define PA12                    24
#define PA13                    25
#define PA14                    26
#define PA15                    27
#define PB8                     28
#define PB9                     29
#define PB12                    30
#define PC13                    31
#define PC14                    32
#define PC15                    33
#define PH0                     34
#define PH1                     35
#define PH3                     36

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA1_ALT1                (PA1  | ALT1)
#define PA1_ALT2                (PA1  | ALT2)
#define PA2_ALT1                (PA2  | ALT1)
#define PA2_ALT2                (PA2  | ALT2)
#define PA3_ALT1                (PA3  | ALT1)
#define PA3_ALT2                (PA3  | ALT2)
#define PA4_ALT1                (PA4  | ALT1)
#define PA5_ALT1                (PA5  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB4_ALT1                (PB4  | ALT1)
#define PB5_ALT1                (PB5  | ALT1)
#define PB6_ALT1                (PB6  | ALT1)
#define PB7_ALT1                (PB7  | ALT1)
#define PB8_ALT1                (PB8  | ALT1)
#define PB9_ALT1                (PB9  | ALT1)
#define PB10_ALT1               (PB10 | ALT1)
#define PB13_ALT1               (PB13 | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)

#define NUM_DIGITAL_PINS        37
#define NUM_ANALOG_INPUTS       7

// User button
#ifndef USER_BTN
  #define USER_BTN              PA12
#endif

// Switch to HL7812
#ifndef SWITCH_TO_HL7812
  #define SWITCH_TO_HL7812      PB8
#endif

// WAKE UP HL721
#ifndef WAKE_UP_HL7812
  #define WAKE_UP_HL7812        PA15
#endif

// Battery level
#ifndef BAT_LEVEL
  #define BAT_LEVEL             PA4
#endif

// Accelerator interrupt
#ifndef INT_ACCEL
  #define INT_ACCEL             PB9
#endif

// reset HL7812
#ifndef RESET_HL7812
  #define RESET_HL7812          PB12
#endif

// VGPIO_SHIFT
#ifndef VGPIO
  #define VGPIO                 PC13
#endif

#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PB5
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PB4
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PB3
#endif

// GPIO Expander (warning: not a pin number)
#ifndef RED_LED
  #define RED_LED               3
#endif

#ifndef GREEN_LED
  #define GREEN_LED             4
#endif

#ifndef BLUE_LED
  #define BLUE_LED              5
#endif

#ifndef IO4
  #define IO4                   1
#endif

#ifndef IO13
  #define IO13                  6
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
  #define SERIAL_UART_INSTANCE  3
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA5
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA7
#endif

#ifndef PIN_SERIALLP1_RX
  #define PIN_SERIALLP1_RX      PA3
#endif
#ifndef PIN_SERIALLP1_TX
  #define PIN_SERIALLP1_TX      PA2
#endif

#ifndef PIN_SERIAL3_RX
  #define PIN_SERIAL3_RX        PA10
#endif
#ifndef PIN_SERIAL3_TX
  #define PIN_SERIAL3_TX        PA9
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// Extra HAL modules
// #if !defined(HAL_DAC_MODULE_DISABLED)
//   #define HAL_DAC_MODULE_ENABLED
// #endif
// #if !defined(HAL_OSPI_MODULE_DISABLED)
//   #define HAL_OSPI_MODULE_ENABLED
// #endif

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
