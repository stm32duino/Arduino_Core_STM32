/*
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
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

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "PeripheralPins.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  /*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
  extern const PinName digitalPin[];

// USART
#define PA10 0  // RX
#define PA9  1  // TX

// SWD
#define PA14 2  // SWCLK
#define PA13 3  // SWDIO

// EXT3
#define PE5  4  // EXT_D1
#define PE4  5  // EXT_D2
#define PE3  6  // EXT_D3
#define PE2  7  // EXT_D4
#define PE1  8  // EXT_D5

// SPI
#define PB2  9  // SS_SDLCD
#define PC4  10 // SS_E
#define PA7  11 // MOSI
#define PA6  12 // MISO
#define PA5  13 // SCK
#define PB1  14 // SS_X
#define PB0  15 // SS_Y
#define PC5  16 // SS_Z

// I2C
#define PB6  17 // SCL
#define PB7  18 // SDA

// USB
#define PA12 19 // DD+
#define PA11 20 // DD//

// LED
#define PD0  21 // STATUS_LED

// PWM
// TIM2
#define PA15 22 // X_STEP
#define PB3  23 // Y_STEP
#define PB10 24 // Z_STEP
#define PB11 25 // E_STEP
// TIM3
#define PB5  26 // PWM_EXT1
#define PB4  27 // PWM_EXT2
#define PC8  28 // PWM_EXT3
#define PC9  29 // PWM_EXT4
// TIM5
#define PA0  30 // PWM_FAN1
#define PA1  31 // PWM_BED
#define PA2  32 // PWM_FAN2
#define PA3  33 // PWM_HEAT

// Stepper
#define PC12 34 // X_EN
#define PC10 35 // X_DIR
#define PC11 36 // X_DIAG
#define PD4  37 // Y_EN
#define PD6  38 // Y_DIR
#define PD5  39 // Y_DIAG
#define PE15 40 // Z_EN
#define PE13 41 // Z_DIR
#define PE14 42 // Z_DIAG
#define PE11 43 // E_EN
#define PE10 44 // E_DIR
#define PE12 45 // E_DIAG

// EXT3
#define PC6  46 // LCD_BEEPER
#define PC7  47 // BTN_ENC
#define PD14 48 // LCD_EN
#define PD15 49 // LCD_RS
#define PD13 50 // LCD_D4
#define PD12 51 // LCD_D5
#define PD11 52 // LCD_D6
#define PD10 53 // LCD_D7

// EXT2
#define PC14 54 // BTN_EN1
#define PC15 55 // BTN_EN2
#define PC13 56 // SD_CARD_DET

// SD Card Reader
#define PE7  57 // SS_SD

// Endstops
#define PB12 58 // X_MIN
#define PB13 59 // X_MAX
#define PB14 60 // Y_MIN
#define PB15 61 // Y_MAX
#define PD8  62 // Z_MIN
#define PD9  63 // Z_MAX

// ADC
#define PC0  64 // THERM_1
#define PC1  65 // THERM_2
#define PC2  66 // THERM_3
#define PA4  67 // FAN_SPEED1
#define PC3  68 // FAN_SPEED2

// PIN definition
#define NUM_DIGITAL_PINS 69
#define NUM_ANALOG_INPUTS 5
#define NUM_ANALOG_FIRST 64

// PWM resolution
#define PWM_RESOLUTION          8
#define PWM_FREQUENCY           20000 // >= 20 Khz => inaudible noise for fans
#define PWM_MAX_DUTY_CYCLE      255

// On-board LED pin number
#define LED_YELLOW PD0
#define LED_BUILTIN LED_YELLOW

// Timer Definitions

// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO TIM3 //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE 1

// I2C Definitions
#define PIN_WIRE_SDA PB7
#define PIN_WIRE_SCL PB6

// Default pin used for 'Serial' instance
#define PIN_SERIAL_RX 0
#define PIN_SERIAL_TX 1

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
#define SERIAL_PORT_MONITOR Serial
#define SERIAL_PORT_HARDWARE Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
