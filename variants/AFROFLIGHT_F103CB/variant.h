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

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

#define PB9  0
#define PB8  1
#define PB7  2
#define PB6  3
#define PB5  4
#define PB4  5  // LED0
#define PB3  6  // LED1
#define PA15 7
#define PA12 8
#define PA11 9
#define PA10 10
#define PA9  11
#define PA8  12
#define PB15 13
#define PB14 14
#define PB13 15
#define PB12 16
#define PC13 17
#define PC14 18
#define PC15 19
#define PA0  20 // A0
#define PA1  21 // A1
#define PA2  22 // A2
#define PA3  23 // A3
#define PA4  24 // A4 Board voltage ADC
#define PA5  25 // A5
#define PA6  26 // A6
#define PA7  27 // A7
#define PB0  28 // A8
#define PB1  29 // A9
#define PB10 30
#define PB11 31
// Other
#define PB2  32 // BOOT1
#define PA13 33 // SWDI0
#define PA14 34 // SWCLK

// This must be a literal
#define NUM_DIGITAL_PINS        35
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       10
#define NUM_ANALOG_FIRST        20

// On-board LED pin number
#define LED0                    PB4
#define LED1                    PB3

#define LED_BUILTIN             LED0

// SPI Definitions
#define PIN_SPI_SS              PA4
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5

// I2C Definitions
//On afroflight Rev 5 it's on i2c port 2 that MPU6050 is connected too
#define PIN_WIRE_SDA            PB11
#define PIN_WIRE_SCL            PB10

// Timer Definitions
#define TIMER_TONE              TIM3
#define TIMER_SERVO             TIM2

// UART Definitions
#define SERIAL_UART_INSTANCE    1
// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9

#define MPU_I2C_SDA             PB11
#define MPU_I2C_SCL             PB10
#define MPU_ADDR                0x68
#define MPU_INT                 PB13
/*
 * RC_CH1 T2C1                    PA0
 * RC_CH2 T2C2                    PA1
 * RC_CH3 T2C3/UA2_TX             PA2
 * RC_CH4 T2C4/UA2_RX             PA3
 * RC_CH5 T3C1                    PA6
 * RC_CH6 T3C2                    PA7
 * RC_CH7 T3C3                    PB0
 * RC_CH8 T3C4                    PB1
 *
 * PWM1 T1C1                      PA8
 * PMW2 T1C4                      PA11
 * PMW3 T4C1                      PB6
 * PMW4 T4C2                      PB7
 * PMW5 T4C3                      PB8
 * PMW6 T4C4                      PB9
 * SONAR_INT                      PA15
 * GPIO_BOTTOM                    PB5
 * TELEM_OUT                      PA13 // Warning, SWD access is lost when using this pin, bootloader via uart is required after
 *
 * BAT_ADC                        PA4 // Connected to 6 pin header Battery voltage in via resistor divider
 * ACC_INT                        PA5 // Connected to Intterupt pin of MMA84520 accelerometer I2C
 *
 * MAG_DRD                        PB12 //Connected to HMC5883L compass I2C
 * BEEP                           PA12 //Connected to Beep out transistor on 6 pin header
 *
 */

#ifdef ARDUINO_AFROFLIGHT_F103CB_12M
#define HSE_VALUE    12000000U /*!< Value of the External oscillator in Hz */
#endif

#ifdef __cplusplus
} // extern "C"
#endif
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
#define SERIAL_PORT_HARDWARE    Serial1
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
