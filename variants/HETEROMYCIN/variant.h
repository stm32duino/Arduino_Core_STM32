/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
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
extern "C"{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
extern const PinName digitalPin[];

// Define pin names to match digital pin number --> Dx
// USART1
#define PA10 0 // D0 - RX
#define PA9  1 // D1 - TX

// USART3
#define PC11 2 // D2 - RX
#define PC10 3 // D3 - TX

// SWD
#define PA13 4 // D4 - SWDIO
#define PA14 5 // D5 - SWCLK
#define PB3  6 // D6 - SWO

// MISC
#define PA15 7 // D7 - Status LED
#define PD11 8 // D8 - SD_DETECT
#define PA4  9 // D9 - MCU_SS

// SPI4
#define PD10 10 // D10 - SS_SD
#define PE14 11 // D11 - MOSI
#define PE13 12 // D12 - MISO
#define PE12 13 // D13 - SCK

// I2C
#define PB9 14 // D14 - SDA
#define PB6 15 // D15 - SCL

// SPI1
#define PA7 16 // D16 - MOSI
#define PA6 17 // D17 - MISO
#define PA5 18 // D18 - SCK

// Stepper
#define PA3  19 // D19 - STEP_X
#define PE7  20 // D20 - DIR_X
#define PE8  21 // D21 - SS_X
#define PA2  22 // D22 - STEP_Y
#define PB1  23 // D23 - DIR_Y
#define PB2  24 // D24 - SS_Y
#define PA1  25 // D25 - STEP_Z
#define PC5  26 // D26 - DIR_Z
#define PB0  27 // D27 - SS_Z
#define PB15 28 // D28 - STEP_E0
#define PB13 29 // D29 - DIR_E0
#define PD9  30 // D30 - SS_E0
#define PB14 31 // D31 - STEP_E1
#define PB10 32 // D32 - DIR_E1
#define PB12 33 // D33 - SS_E1

// PWM
#define PE5 34  // D34 - PWM_BED
#define PA0 35  // D35 - PWM_HEAT1
#define PE6 36  // D36 - PWM_HEAT2
#define PD12 37 // D37 - PWM_FAN1
#define PD13 38 // D38 - PWM_FAN2
#define PD14 39 // D39 - PWM_FAN3
#define PD15 40 // D40 - PWM_FAN4
#define PC9 41  // D41 - PWM_EXT1
#define PC8 42  // D42 - PWM_EXT2
#define PC7 43  // D43 - PWM_EXT3
#define PC6 44  // D44 - PWM_EXT4

// Endstops
#define PE4 45 // D45 - X_MIN
#define PE3 46 // D46 - Y_MIN
#define PE2 47 // D47 - Z_MIN

// GPIO
#define PD6 48 // D48 - D1
#define PD5 49 // D49 - D2
#define PD4 50 // D50 - D3
#define PD3 51 // D51 - D4
#define PD2 52 // D52 - D5

// ADC
#define PC3 53 // D53/A0 - TEMP1
#define PC2 54 // D54/A1 - TEMP2
#define PC1 55 // D55/A2 - TEMP3
#define PC0 56 // D56/A3 - TEMP4

#define NUM_DIGITAL_PINS       57
#define NUM_ANALOG_INPUTS       4
#define NUM_ANALOG_FIRST       53

// PWM resolution
#define PWM_RESOLUTION          8
#define PWM_FREQUENCY           20000 // >= 20 Khz => inaudible noise for fans
#define PWM_MAX_DUTY_CYCLE      255

// On-board LED pin number
#define LED_BUILTIN             PA15
#define LED_YELLOW              LED_BUILTIN

// Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM in PeripheralPins.c
#define TIMER_TONE              TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM17  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    1 //ex: 1 for Serial1 (USART1)
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9

#define PIN_SERIAL3_RX          PC11 // For USART3 RX
#define PIN_SERIAL3_TX          PC10 // For USART3 TX

// MISC
#define SD_DETECT_PIN           PD11

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
#define SERIAL_PORT_MONITOR     Serial
#define SERIAL_PORT_HARDWARE    Serial
#define SERIAL_PORT_LINUXBRIDGE Serial
#define SERIAL_PORT_HARDWARE_OPEN Serial3
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
