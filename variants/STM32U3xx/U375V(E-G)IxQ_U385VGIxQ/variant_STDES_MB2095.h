/*
 *******************************************************************************
 * Copyright (c) 2025, STMicroelectronics
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
/* J1 M.2 connector */
/* Odd part */
#define PA12                    0       /* USB_P */
#define PA11                    1       /* USB_N */
#define PH3                     2       /* BOOT0 */
#define PB1                     PIN_A11 /* Also on CN3 */
#define PB13                    4       /* LED5 Green */
#define PB10                    5       /* LED4 Red also on CN3 */
#define PB11                    6
#define PA14                    7       /* SWCLK */
#define PA13                    8       /* SWDIO */
#define PD0                     9       /* FDCAN1_RX */
#define PD1                     10      /* FDCAN1_TX */
#define PD15                    11      /* TIM4_CH4*/
#define PB9                     12      /* I2C1_SDA also on CN3 */
#define PB6                     13      /* I2C1_SCL also on CN3 */
#define PA15                    14      /* SPI1_NSS */
#define PE13                    15      /* SPI1_SCK */
#define PE15                    16      /* SPI1_MOSI */
#define PE14                    17      /* SPI1_MISO */
/* Even part */
#define PB3                     18      /* SWO */
#define PD5                     19
#define PA6                     PIN_A12 /* I2C2_SDA */
#define PB2                     PIN_A13 /* I2C2_SCL */
#define PA9                     22      /* USART1_TX CN5: HC-06 module connector */
#define PA10                    23      /* USART1_RX CN5: HC-06 module connector */
#define PD14                    24      /* TIM4_CH3 */
#define PC0                     PIN_A14 /* Also on CN3 */
#define PC1                     PIN_A15 /* Also on CN3 */
#define PA2                     PIN_A16
#define PE0                     28
#define PC7                     29
#define PE8                     30
#define PB8                     31      /* Also on CN3 */
#define PE9                     32      /* J1_50 LNK4 ADF1_CCK0 */
#define PB4                     33      /* J1_52 LNK2 ADF1_SDI0 */
#define PE5                     34      /* J1_50 LNK5 SAI1_SCK_A */
#define PE4                     35      /* J1_52 LNK3 SAI1_FS_A */
#define PE7                     36      /* SAI1_SD_B */
#define PE6                     37      /* SAI1_SD_A */
#define PE2                     38      /* SAI1_MCLK_A */
#define PC12                    39      /* SDMMC1_CK */
#define PD2                     40      /* SDMMC1_CMD */
#define PC8                     41      /* SDMMC1_D0 */
#define PC9                     42      /* SDMMC1_D1 */
#define PC10                    43      /* SDMMC1_D2 */
#define PC11                    44      /* SDMMC1_D3 */
/* J2 M.2 connector */
/* Odd part */
#define PH0                     45
/* Even part */
#define PA4                     PIN_A0  /* DAC1_OUT1 also on CN3 */
#define PA5                     PIN_A1  /* DAC1_OUT2 also on CN3 */
#define PA3                     PIN_A2  /* OP1_VOUT */
#define PA0                     PIN_A3  /* OP1_VINP */
#define PA1                     PIN_A4  /* OP1_VINM */
#define PD13                    PIN_A5  /* I3C1_SDA */
#define PD12                    PIN_A6  /* I3C1_SCL */
#define PE10                    53      /* OSPI1_CLK */
#define PE12                    54      /* OSPI1_IO0 */
#define PB0                     PIN_A7  /* OSPI1_IO1 */
#define PA7                     PIN_A8  /* OSPI1_IO2 */
#define PC6                     57      /* OSPI1_IO3 */
#define PD4                     58      /* OSPI1_IO4 */
#define PC2                     PIN_A9  /* OSPI1_IO5 */
#define PC3                     PIN_A10 /* OSPI1_IO6 */
#define PD7                     61      /* OSPI1_IO7 */
#define PE3                     62      /* OSPI1_DQS */
#define PE11                    63      /* OSPI1_NCS */
#define PB5                     64      /* OSPI1_NCLK */
/* CN3: 16-pin header to breadboard */
/* Most of them already defined on J1 or J2 */
#define PB7                     65
/* Joystick */
#define PD11                    PIN_A17 /* USER_BTN */
/* LEDs */
#define PB15                    67      /* LED1 Green */
#define PB14                    68      /* LED2 Red */
#define PA8                     69      /* LED3 Orange */
/* Debug */
#define PD8                     70      /* UART3_TX */
#define PD9                     71      /* USART3_RX */
/* Other */
#define PC14                    72      /* OSC32_IN */
#define PC15                    73      /* OSC32_OUT */
/* Not connected
 * PC13
 * PD3 LEDMCU connected to VDD
 * PD6
 * PD10
 * PH1 OSC_OUT
 */

// Alternate pins number
#define PA1_ALT1                (PA1  | ALT1)
#define PA2_ALT1                (PA2  | ALT1)
#define PA3_ALT1                (PA3  | ALT1)
#define PA4_ALT1                (PA4  | ALT1)
#define PA5_ALT1                (PA5  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA9_ALT1                (PA9  | ALT1)
#define PA10_ALT1               (PA10 | ALT1)
#define PA15_ALT1               (PA15 | ALT1)
#define PB0_ALT1                (PB0  | ALT1)
#define PB1_ALT1                (PB1  | ALT1)
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
#define PB15_ALT1               (PB15 | ALT1)
#define PC1_ALT1                (PC1  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)
#define PH3_ALT1                (PH3  | ALT1)

#define NUM_DIGITAL_PINS        74
#define NUM_ANALOG_INPUTS       18

// On-board LED pin number
#define LED1                    PB15
#define LED2                    PB14
#define LED3                    PA8
#define LED4                    PB10
#define LED5                    PB13
#define LED_GREEN               LED1
#define LED_RED                 LED2
#define LED_ORANGE              LED3
#define LED_RED2                LED4
#define LED_GREEN2              LED5
#ifndef LED_BUILTIN
  #define LED_BUILTIN           LED_GREEN
#endif

// On-board user button
#define JOYSTICK                PD11
#ifndef USER_BTN
  #define USER_BTN              JOYSTICK
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PA4
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           PA15
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           PB0
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3           PE12
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PA7
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PA6
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PA1
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PA6
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PB2
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
  #define PIN_SERIAL_RX         PD9
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PD8
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_OSPI_MODULE_DISABLED)
  #define HAL_OSPI_MODULE_ENABLED
#endif
#if !defined(HAL_SD_MODULE_DISABLED)
  #define HAL_SD_MODULE_ENABLED
#endif

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
