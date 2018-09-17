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

  // Enum defining pin names to match digital pin number --> Dx
  enum
  {
    // USART
    PA10, // D0 - RX
    PA9,  // D1 - TX

    // SWD
    PA14, // D2 - SWCLK
    PA13, // D3 - SWDIO

    // EXT3
    PE5, // D4 - EXT_D1
    PE4, // D5 - EXT_D2
    PE3, // D6 - EXT_D3
    PE2, // D7 - EXT_D4
    PE1, // D8 - EXT_D5

    // SPI
    PB2, // D9 - SS_SD
    PC4, // D10 - SS_E
    PA7, // D11 - MOSI
    PA6, // D12 - MISO
    PA5, // D13 - SCK
    PB1, // D14 - SS_X
    PB0, // D15 - SS_Y
    PC5, // D16 - SS_Z

    // I2C
    PB6, // D17 - SCL
    PB7, // D18 - SDA

    // USB
    PA12, // D19 - DD+
    PA11, // D20 - DD-

    // LED
    PD0, // D21 - STATUS_LED

    // PWM
    // TIM2
    PA15, // D22 - X_STEP
    PB3,  // D23 - Y_STEP
    PB10, // D24 - Z_STEP
    PB11, // D25 - E_STEP
    // TIM3
    PB5, // D26 - PWM_EXT1
    PB4, // D27 - PWM_EXT2
    PC8, // D28 - PWM_EXT3
    PC9, // D29 - PWM_EXT4
    // TIM5
    PA0, // D30 - PWM_FAN1
    PA1, // D31 - PWM_BED
    PA2, // D32 - PWM_FAN2
    PA3, // D33 - PWM_HEAT

    // Stepper
    PC12, // D34 - X_EN
    PC10, // D35 - X_DIR
    PC11, // D36 - X_DIAG
    PD4,  // D37 - Y_EN
    PD6,  // D38 - Y_DIR
    PD5,  // D39 - Y_DIAG
    PE15, // D40 - Z_EN
    PE13, // D41 - Z_DIR
    PE14, // D42 - Z_DIAG
    PE11, // D43 - E_EN
    PE10, // D44 - E_DIR
    PE12, // D45 - E_DIAG

    // EXT3
    PC6,  // D46 - LCD_BEEPER
    PC7,  // D47 - BTN_ENC
    PD14, // D48 - LCD_EN
    PD15, // D49 - LCD_RS
    PD13, // D50 - LCD_D4
    PD12, // D51 - LCD_D5
    PD11, // D52 - LCD_D6
    PD10, // D53 - LCD_D7

    // EXT2
    PC14, // D54 - BTN_EN1
    PC15, // D55 - BTN_EN2
    PC13, // D56 - SD_CARD_DET
    PE6,  // D57 - KILL_PIN

    // Endstops
    PB12, // D58 - X_MIN
    PB13, // D59 - X_MAX
    PB14, // D60 - Y_MIN
    PB15, // D61 - Y_MAX
    PD8,  // D62 - Z_MIN
    PD9,  // D63 - Z_MAX

    // ADC
    PC0, // D64 - THERM_1
    PC1, // D65 - THERM_2
    PC2, // D66 - THERM_3
    PA4, // D67 - FAN_SPEED1
    PC3, // D68 - FAN_SPEED2

    PEND
  };

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
