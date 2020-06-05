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

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

#define PE7   0 // - USART7_RX
#define PE8   1 // - USART7_TX and TIM1_CH1N
#define PE1   2
#define PD14  3 // - TIM4_CH3
#define PE10  4 // - TIM1_CH2N
#define PD15  5 // - TIM4_CH4
#define PE9   6 // - TIM1_CH1
#define PD1   7
#define PG3   8
#define PH6   9 // - TIM12_CH1
#define PE11  10 // - SPI4_NSS and TIM1_CH2
#define PE14  11 // - SPI4_MOSI and TIM1_CH4
#define PE13  12 // - SPI4_MISO and TIM1_CH3
#define PE12  13 // - SPI4_SCK and TIM1_CH3N
#define PA12  14 // - I2C5_SDA
#define PA11  15 // - I2C5_SCL and TIM1_CH4
// CN2 Raspberry Pi GPIO connectors
// #define PA12  16  // RPI_3 - GPIO2 / I2C5_SDA
// #define PA11  17  // RPI_5 - GPIO3 / I2C5_SCL
// #define PA8   18  // RPI_7 - GPIO4 / MCO1
// #define PB10  19  // RPI_8 - GPIO14 / USART3_TX
// #define PB12  20  // RPI_10 - GPIO15 / USART3_RX
// #define PG8   21  // RPI_11 - GPIO17 / USART3_RTS
// #define PI5   22  // RPI_12 - GPIO18 / SAI2_SCKA
// #define PD7   23  // RPI_13 - GPIO27 / SDMMC3_D3
// #define PG15  24  // RPI_15 - GPIO22 / SDMMC3_CK
// #define PF1   25  // RPI_16 - GPIO23 / SDMMC3_CMD
// #define PF0   26  // RPI_18 - GPIO24 / SDMMC3_D0
// #define PF9   27  // RPI_19 - GPIO10 / SPI5_MOSI
// #define PF8   28  // RPI_21 - GPIO9 / SPI5_MISO
// #define PF4   29  // RPI_22 - GPIO25 / SDMMC3_D1
// #define PF7   30  // RPI_23 - GPIO11 / SPI5_SCK
// #define PF6   31  // RPI_24 - GPIO8 / SPI5_NSS
// #define PF3   32  // RPI_26 - GPIO7
// #define PF15  33  // RPI_27 - I2C1_SDA
// #define PD12  34  // RPI_28 - I2C1_SCL
// #define PG2   35  // RPI_29 - GPIO5 / MCO2
// #define PH11  36  // RPI_31 - GPIO6 / TIM5_CH2
// #define PD13  37  // RPI_32 - GPIO12 / TIM4_CH2
// #define PC7   38  // RPI_33 - GPIO13 /TIM3_CH2
// #define PI7   39  // RPI_35 - GPIO19 / SAI2_FSA
// #define PB13  40  // RPI_36 - GPIO16 / USART3_CTS
// #define PF5   41  // RPI_37 - GPIO26 / SDMMC3_D2
// #define PI6   42  // RPI_38 - GPIO20 / SAI2_SDA
// #define PF11  43  // RPI_40 - GPIO21 / SAI2_SDB
#define PA14  16 // 44  // LED LD5, Green, Active Low, Connected to B3 (USER1 Button)
#define PA13  17 // 45  // LED LD6, Red, Active Low, Connected to B4 (USER2 Button)
#define PH7   18 // 46  // LED LD7, Orange, Active High
// CN17  CN17 Left Arduino Analog Pins
#define PF14  19 // 47  // A0 - ADC1_IN0
#define PF13  20 // 48  // A1 - ADC1_IN1
#define ANA0  21 // 49  // A2 - ADC1_IN6
#define ANA1  22 // 50  // A3 - ADC1_IN2
#define PC3   23 // 51  // A4 - ADC1_IN13, or PA_12 (D14) with SB23 ON / SB24 OFF
#define PF12  24 // 52  // A5 - ADC1_IN14, or PA_11 (D15) with SB25 ON / SB26 OFF

// This must be a literal
#define NUM_DIGITAL_PINS        25 // 53
#define NUM_ANALOG_INPUTS       6
#define NUM_ANALOG_FIRST        19 // 47

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
//Do not use timer used by PWM pins when possible. See PinMap_PWM in PeripheralPins.c
// Unused Timers: TIM6, TIM7 (Those are basic timers usually for DACs, not capable to PWM)
//                LPTIM[1:5]
#define TIMER_TONE              TIM7

// Do not use basic timer: OC is required
// Basic timers are TIM6 and TIM7
#define TIMER_SERVO             TIM2

// UART Definitions
// Define here Serial instance number to map on Serial generic name
#define SERIAL_UART_INSTANCE    7 // Arduino TX/RX pins
// DEBUG_UART could be redefined to print on another instance than 'Serial'
// #define DEBUG_UART              ((USART_TypeDef *) USART3) // ex: USART3
// DEBUG_UART baudrate, default: 9600 if not defined
// #define DEBUG_UART_BAUDRATE     115200
// DEBUG_UART Tx pin name, default: the first one found in PinMap_UART_TX for DEBUG_UART
// #define DEBUG_PINNAME_TX        PB10 // This is RPi_8 pin

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PE7 // USART7_RX
#define PIN_SERIAL_TX           PE8 // USART7_TX

// Optional PIN_SERIALn_RX and PIN_SERIALn_TX where 'n' is the U(S)ART number
// Used when user instanciate a hardware Serial using its peripheral name.
// Example: HardwareSerial mySerial(USART3);
// will use PIN_SERIAL3_RX and PIN_SERIAL3_TX if defined.
// #define PIN_SERIAL3_RX          PB10 // RPi Serial RX
// #define PIN_SERIAL3_TX          PB12 // RPi Serial TX

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
  #define SERIAL_PORT_HARDWARE    Serial
  #define SERIAL_PORT_LINUXBRIDGE SerialVirtIO
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
