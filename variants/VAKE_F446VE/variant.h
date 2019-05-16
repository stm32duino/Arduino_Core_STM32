/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

#define PA3   0 // Z_PROBE_A    ADC
#define PA2   1 // PWRMON ADC   ADC
#define PA10  2 // USART1_RX
#define PB3   3 // E1_DIAG
#define PB5   4 // N.C.
#define PB4   5 // N.C.
#define PB10  6 // Z_DIR
#define PA8   7 // USD_CD (card detect)
#define PA9   8 // USART1_TX
#define PC7   9 // X_DIR
#define PB6   10 // SD_CS
#define PA7   11 // SPI1_MOSI   EXP2 OR onboard SD
#define PA6   12 // SPI1_MISO
#define PA5   13 // SPI1_SCK
#define PB9   14 // SDA1
#define PB8   15 // SCL1
#define PC10  16 // USER BTN
#define PC12  17
// 18 is NC - BOOT0
#define PA13  19 // SWDIO
#define PA14  20 // SWCLK
#define PA15  21 // SERVO
#define PB7   22 // SD_CD
#define PC13  23 // E2_STEP
#define PC14  24 // E2_DIR
#define PC15  25 // E2_CS
#define PH0   26 // OSC_IN
#define PH1   27 // OSC_OUT
#define PC2   28 // THERM2_ADC  ADC
#define PC3   29 // THERM3_ADC  ADC
#define PC11  30 // LCD_RS
#define PD2   31 // LCD_D6
#define PC9   32 // BEEPER
#define PC8   33 // X_CS
#define PC6   34 // X_STEP
#define PC5   35 // E1_DIR
#define PA12  36 // USB_DP
#define PA11  37 // USB_DM
#define PB12  38      // USED FOR ??
// 39 is NC
#define PB2   40 // E0_DIR
#define PB1   41 // E0_STEP
#define PB15  42
#define PB14  43 // STAT_LED
#define PB13  44      // USED FOR ??
#define PC4   45 // E1_STEP
#define PB11  46
#define PD0   47 // BTN_EN2
#define PD1   48 // LCD_D4
#define PD3   49 // LCD_D5
#define PD4   50 // LCD_D7
#define PD5   51 // KILL
#define PD6   52 // BTN_EN1
#define PD7   53 // LCD_EN
#define PD8   54 // Z_CS
#define PD9   55 // Y_STEP
#define PD10  56 // Y_DIR
#define PD11  57 // Y_CS
#define PD12  58 // HB_PWM
#define PD13  59 // F0_PWM
#define PD14  60 // H1_PWM
#define PD15  61 // H0_PWM
#define PE0   62 // PS_ON
#define PE1   63 // E4_STEP
#define PE2   64 // E4_DIR
#define PE3   65 // E4_CS
#define PE4   66 // E3_DIR
#define PE5   67 // E3_STEP
#define PE6   68 // E3_CS
#define PE7   69 // E_STOP
#define PE8   70 // Z_STOP
#define PE9   71 // Y_STOP
#define PE10  72 // X_STOP
#define PE11  73 // E0_CS
#define PE12  74 // SPI4_SCK
#define PE13  75 // SPI4_MISO
#define PE14  76 // SPI4_MOSI
#define PE15  77 // Z_STEP
#define PA0   78 // F1_PWM  or serial
#define PA1   79 // F2_PWM  or serial
#define PA4   80 // Z_PROBE_D
#define PB0   81 // E1_CS
#define PC1   82 // THERM1_ADC  ADC
#define PC0   83 // THERM0_ADC  ADC

// This must be a literal
#define NUM_DIGITAL_PINS        98
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       6
#define NUM_ANALOG_FIRST        84

// On-board LED pin number
#define LED_BUILTIN             PB14
#define LED_LD2                 LED_BUILTIN
#define LED_GREEN               LED_BUILTIN

// On-board user button
#define USER_BTN                PC10

// UART Definitions
#define SERIAL_UART_INSTANCE    4
/* Enable Serial 1 */
#define HAVE_HWSERIAL1

/* HAL configuration */
#define HSE_VALUE               12000000U

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
#define SERIAL_PORT_MONITOR     Serial4
#define SERIAL_PORT_HARDWARE    Serial1
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
