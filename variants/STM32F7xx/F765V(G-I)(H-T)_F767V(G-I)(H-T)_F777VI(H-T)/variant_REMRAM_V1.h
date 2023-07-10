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
*        Pins
*----------------------------------------------------------------------------*/

// USART
#define PA10                    0  // RX
#define PA9                     1  // TX

// SWD
#define PA14                    2  // SWCLK
#define PA13                    3  // SWDIO

// EXT3
#define PE5                     4  // EXT_D1
#define PE4                     5  // EXT_D2
#define PE3                     6  // EXT_D3
#define PE2                     7  // EXT_D4
#define PE1                     8  // EXT_D5

// SPI
#define PB2                     9  // SS_SDLCD
#define PC4                     10 // SS_E
#define PA7                     11 // MOSI
#define PA6                     12 // MISO
#define PA5                     13 // SCK
#define PB1                     14 // SS_X
#define PB0                     15 // SS_Y
#define PC5                     16 // SS_Z

// I2C
#define PB6                     17 // SCL
#define PB7                     18 // SDA

// USB
#define PA12                    19 // DD+
#define PA11                    20 // DD//

// LED
#define PD0                     21 // STATUS_LED

// PWM
// TIM2
#define PA15                    22 // X_STEP
#define PB3                     23 // Y_STEP
#define PB10                    24 // Z_STEP
#define PB11                    25 // E_STEP
// TIM3
#define PB5                     26 // PWM_EXT1
#define PB4                     27 // PWM_EXT2
#define PC8                     28 // PWM_EXT3
#define PC9                     29 // PWM_EXT4
// TIM5
#define PA0                     30 // PWM_FAN1
#define PA1                     31 // PWM_BED
#define PA2                     32 // PWM_FAN2
#define PA3                     33 // PWM_HEAT

// Stepper
#define PC12                    34 // X_EN
#define PC10                    35 // X_DIR
#define PC11                    36 // X_DIAG
#define PD4                     37 // Y_EN
#define PD6                     38 // Y_DIR
#define PD5                     39 // Y_DIAG
#define PE15                    40 // Z_EN
#define PE13                    41 // Z_DIR
#define PE14                    42 // Z_DIAG
#define PE11                    43 // E_EN
#define PE10                    44 // E_DIR
#define PE12                    45 // E_DIAG

// EXT3
#define PC6                     46 // LCD_BEEPER
#define PC7                     47 // BTN_ENC
#define PD14                    48 // LCD_EN
#define PD15                    49 // LCD_RS
#define PD13                    50 // LCD_D4
#define PD12                    51 // LCD_D5
#define PD11                    52 // LCD_D6
#define PD10                    53 // LCD_D7

// EXT2
#define PC14                    54 // BTN_EN1
#define PC15                    55 // BTN_EN2
#define PC13                    56 // SD_CARD_DET

// SD Card Reader
#define PE7                     57 // SS_SD

// Endstops
#define PB12                    58 // X_MIN
#define PB13                    59 // X_MAX
#define PB14                    60 // Y_MIN
#define PB15                    61 // Y_MAX
#define PD8                     62 // Z_MIN
#define PD9                     63 // Z_MAX

// ADC
#define PC0                     PIN_A0 // THERM_1
#define PC1                     PIN_A1 // THERM_2
#define PC2                     PIN_A2 // THERM_3
#define PA4                     PIN_A3 // FAN_SPEED1
#define PC3                     PIN_A4 // FAN_SPEED2

// Alternate pins number
#define PA0_ALT1                (PA0  | ALT1)
#define PA0_ALT2                (PA0  | ALT2)
#define PA1_ALT1                (PA1  | ALT1)
#define PA1_ALT2                (PA1  | ALT2)
#define PA2_ALT1                (PA2  | ALT1)
#define PA2_ALT2                (PA2  | ALT2)
#define PA3_ALT1                (PA3  | ALT1)
#define PA3_ALT2                (PA3  | ALT2)
#define PA4_ALT1                (PA4  | ALT1)
#define PA4_ALT2                (PA4  | ALT2)
#define PA5_ALT1                (PA5  | ALT1)
#define PA6_ALT1                (PA6  | ALT1)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PA7_ALT3                (PA7  | ALT3)
#define PA15_ALT1               (PA15 | ALT1)
#define PA15_ALT2               (PA15 | ALT2)
#define PB0_ALT1                (PB0  | ALT1)
#define PB0_ALT2                (PB0  | ALT2)
#define PB1_ALT1                (PB1  | ALT1)
#define PB1_ALT2                (PB1  | ALT2)
#define PB3_ALT1                (PB3  | ALT1)
#define PB3_ALT2                (PB3  | ALT2)
#define PB4_ALT1                (PB4  | ALT1)
#define PB4_ALT2                (PB4  | ALT2)
#define PB5_ALT1                (PB5  | ALT1)
#define PB5_ALT2                (PB5  | ALT2)
#define PB6_ALT1                (PB6  | ALT1)
#define PB7_ALT1                (PB7  | ALT1)
//#define PB8_ALT1                (PB8  | ALT1)
//#define PB9_ALT1                (PB9  | ALT1)
#define PB14_ALT1               (PB14 | ALT1)
#define PB14_ALT2               (PB14 | ALT2)
#define PB15_ALT1               (PB15 | ALT1)
#define PB15_ALT2               (PB15 | ALT2)
#define PC0_ALT1                (PC0  | ALT1)
#define PC0_ALT2                (PC0  | ALT2)
#define PC1_ALT1                (PC1  | ALT1)
#define PC1_ALT2                (PC1  | ALT2)
#define PC2_ALT1                (PC2  | ALT1)
#define PC2_ALT2                (PC2  | ALT2)
#define PC3_ALT1                (PC3  | ALT1)
#define PC3_ALT2                (PC3  | ALT2)
#define PC4_ALT1                (PC4  | ALT1)
#define PC5_ALT1                (PC5  | ALT1)
#define PC6_ALT1                (PC6  | ALT1)
#define PC7_ALT1                (PC7  | ALT1)
#define PC8_ALT1                (PC8  | ALT1)
#define PC9_ALT1                (PC9  | ALT1)
#define PC10_ALT1               (PC10 | ALT1)
#define PC11_ALT1               (PC11 | ALT1)

// PIN definition
#define NUM_DIGITAL_PINS        69
#define NUM_ANALOG_INPUTS       5

// PWM resolution
#define PWM_FREQUENCY           20000 // >= 20 Khz => inaudible noise for fans
#define PWM_MAX_DUTY_CYCLE      255

// On-board LED pin number
#define LED_YELLOW PD0
#define LED_BUILTIN             LED_YELLOW

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            TIM6
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           TIM7
#endif

// UART Definitions
#define SERIAL_UART_INSTANCE    1

// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6

// Default pin used for 'Serial' instance
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9

// SDMMC signals not available
#define SDMMC_CKIN_NA
#define SDMMC_CDIR_NA
#define SDMMC_D0DIR_NA
#define SDMMC_D123DIR_NA

/* HAL configuration */
#define HSE_VALUE               24000000U

// Last Flash sector used for EEPROM emulation, address/sector depends on single/dual bank configuration.
// By default 2MB single bank
#define FLASH_BASE_ADDRESS      0x081C0000
#define FLASH_DATA_SECTOR       11

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
  #define SERIAL_PORT_MONITOR   Serial
  #define SERIAL_PORT_HARDWARE  Serial
#endif
