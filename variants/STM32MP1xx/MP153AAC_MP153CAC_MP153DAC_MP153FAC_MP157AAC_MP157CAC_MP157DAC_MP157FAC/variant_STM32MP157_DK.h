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
 *----------------------------------------------------------------------------*/
#define PE7                     0 // - USART7_RX
#define PE8                     1 // - USART7_TX and TIM1_CH1N
#define PE1                     2
#define PD14                    3 // - TIM4_CH3
#define PE10                    4 // - TIM1_CH2N
#define PD15                    5 // - TIM4_CH4
#define PE9                     6 // - TIM1_CH1
#define PD1                     7
#define PG3                     8
#define PH6                     9 // - TIM12_CH1
#define PE11                    10 // - SPI4_NSS and TIM1_CH2
#define PE14                    11 // - SPI4_MOSI and TIM1_CH4
#define PE13                    12 // - SPI4_MISO and TIM1_CH3
#define PE12                    13 // - SPI4_SCK and TIM1_CH3N
#define PA12                    14 // - I2C5_SDA
#define PA11                    15 // - I2C5_SCL and TIM1_CH4
// CN2 Raspberry Pi GPIO connectors
// #define PA12                    16  // RPI_3 - GPIO2 / I2C5_SDA
// #define PA11                    17  // RPI_5 - GPIO3 / I2C5_SCL
// #define PA8                     18  // RPI_7 - GPIO4 / MCO1
// #define PB10                    19  // RPI_8 - GPIO14 / USART3_TX
// #define PB12                    20  // RPI_10 - GPIO15 / USART3_RX
// #define PG8                     21  // RPI_11 - GPIO17 / USART3_RTS
// #define PI5                     22  // RPI_12 - GPIO18 / SAI2_SCKA
// #define PD7                     23  // RPI_13 - GPIO27 / SDMMC3_D3
// #define PG15                    24  // RPI_15 - GPIO22 / SDMMC3_CK
// #define PF1                     25  // RPI_16 - GPIO23 / SDMMC3_CMD
// #define PF0                     26  // RPI_18 - GPIO24 / SDMMC3_D0
// #define PF9                     27  // RPI_19 - GPIO10 / SPI5_MOSI
// #define PF8                     28  // RPI_21 - GPIO9 / SPI5_MISO
// #define PF4                     29  // RPI_22 - GPIO25 / SDMMC3_D1
// #define PF7                     30  // RPI_23 - GPIO11 / SPI5_SCK
// #define PF6                     31  // RPI_24 - GPIO8 / SPI5_NSS
// #define PF3                     32  // RPI_26 - GPIO7
// #define PF15                    33  // RPI_27 - I2C1_SDA
// #define PD12                    34  // RPI_28 - I2C1_SCL
// #define PG2                     35  // RPI_29 - GPIO5 / MCO2
// #define PH11                    36  // RPI_31 - GPIO6 / TIM5_CH2
// #define PD13                    37  // RPI_32 - GPIO12 / TIM4_CH2
// #define PC7                     38  // RPI_33 - GPIO13 /TIM3_CH2
// #define PI7                     39  // RPI_35 - GPIO19 / SAI2_FSA
// #define PB13                    40  // RPI_36 - GPIO16 / USART3_CTS
// #define PF5                     41  // RPI_37 - GPIO26 / SDMMC3_D2
// #define PI6                     42  // RPI_38 - GPIO20 / SAI2_SDA
// #define PF11                    43  // RPI_40 - GPIO21 / SAI2_SDB
#define PA14                    16 // 44  // LED LD5, Green, Active Low, Connected to B3 (USER1 Button)
#define PA13                    17 // 45  // LED LD6, Red, Active Low, Connected to B4 (USER2 Button)
#define PH7                     18 // 46  // LED LD7, Orange, Active High
// CN17  CN17 Left Arduino Analog Pins
#define PF14                    PIN_A0 // 47  // ADC1_IN0
#define PF13                    PIN_A1 // 48  // ADC1_IN1
#define ANA0                    PIN_A2 // 49  // ADC1_IN6
#define ANA1                    PIN_A3 // 50  // ADC1_IN2
#define PC3                     PIN_A4 // 51  // ADC1_IN13, or PA_12 (D14) with SB23 ON / SB24 OFF
#define PF12                    PIN_A5 // 52  // ADC1_IN14, or PA_11 (D15) with SB25 ON / SB26 OFF

// No Alternate pins number provided

#define NUM_DIGITAL_PINS        25 // 53
#define NUM_ANALOG_INPUTS       6

// On-board LED pin number
#define LED_GREEN               PA14
#define LED_RED                 PA13
#define LED_ORANGE              PH7
#define LED_BUILTIN             LED_ORANGE

// On-board user button
// The STM32MP157A-DK1 and STM32MP157C-DK2 Discovery kits provide four types of buttons:
// * Wake-up button (B1)
//   – Allows the platform to be woken up from any low-power mode
//   – Connected to STPMIC1 PONKEY, which generates a wake up signal on STM32MP157x PA0
// * Reset button (B2)
//   – Used to reset the Discovery kit
// * USER1 button (B3)
//   – Used at boot time by U-Boot to enter the USB programming mode
// * USER2 button (B4)
//   – Used at boot time by U-Boot to enter the Android® Fastboot mode
#define USER1_BTN               LED_GREEN
#define USER2_BTN               LED_RED
#define USER_BTN                USER1_BTN

// Timer Definitions (optional)
//Do not use timer used by PWM pins when possible. See PinMap_TIM in PeripheralPins.c
// Unused Timers: TIM6, TIM7 (Those are basic timers usually for DACs, not capable to PWM)
//                LPTIM[1:5]
#define TIMER_TONE              TIM7

// Do not use basic timer: OC is required
// Basic timers are TIM6 and TIM7
#define TIMER_SERVO             TIM2

// UART Definitions
#define SERIAL_UART_INSTANCE    7 // Arduino TX/RX pins

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PE7 // USART7_RX
#define PIN_SERIAL_TX           PE8 // USART7_TX

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
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_HARDWARE    Serial
  #define SERIAL_PORT_LINUXBRIDGE SerialVirtIO
#endif
