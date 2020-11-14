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

//P1 connector Right side
#define PC0  A0
#define PC2  A1
#define PF2  A2
#define PA0  3
#define PA2  4
#define PA4  5
#define PA6  6
#define PC4  A3
#define PB0  A4
#define PB2  A5
#define PE8  10
#define PE10 11
#define PE12 12
#define PE14 13
#define PB10 14
#define PB12 A6
#define PB14 A7
#define PD8  A8
#define PD10 A9
#define PD12 A10
#define PD14 A11
#define PC7  21
//P2 connector Left side
#define PF9  22
#define PF0  23
#define PC14 24
#define PE6  25
#define PE4  26
#define PE2  27
#define PE0  28
#define PB8  29
#define PB6  30
#define PB4  31
#define PD7  32
#define PD5  33
#define PD3  34
#define PD1  35
#define PC12 36
#define PC10 37
#define PA14 38
#define PF6  39
#define PA12 40
#define PA10 41
#define PA8  42
#define PC8  43
//P1 Connector Left Side
#define PC1  A12
#define PC3  A13
#define PA1  46
#define PA3  47
#define PF4  A14
#define PA5  49
#define PA7  50
#define PC5  A15
#define PB1  A16
#define PE7  A17
#define PE9  54
#define PE11 55
#define PE13 56
#define PE15 57
#define PB11 58
#define PB13 A18
#define PB15 A19
#define PD9  A20
#define PD11 A21
#define PD13 A22
#define PD15 64
#define PC6  65
//P2 connector Right side
#define PF10 66
#define PF1  67
#define PC15 68
#define PC13 69
#define PE5  70
#define PE3  71
#define PE1  72
#define PB9  73
#define PB7  74
#define PB5  75
#define PB3  76
#define PD6  77
#define PD4  78
#define PD2  79
#define PD0  80
#define PC11 81
#define PA15 82
#define PA13 83
#define PA11 84
#define PA9  85
#define PC9  86

// This must be a literal
#define NUM_DIGITAL_PINS        87
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       23

// On-board LED pin number
#define LED_BLUE                PE8
#define LED_RED                 PE9
#define LED_ORANGE              PE10
#define LED_GREEN               PE11
#define LED_BLUE2               PE12
#define LED_RED2                PE13
#define LED_ORANGE2             PE14
#define LED_GREEN2              PE15
#define LED_BUILTIN             LED_BLUE

// On-board user button
#define USER_BTN                PA0

// SPI Definitions
#define PIN_SPI_SS2             PA4
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5

// I2C Definitions
#define PIN_WIRE_SDA            PB6
#define PIN_WIRE_SCL            PB7

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA3
#define PIN_SERIAL_TX           PA2

/* Extra HAL modules */
#define HAL_DAC_MODULE_ENABLED

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
  #define SERIAL_PORT_MONITOR     Serial // Require connections for ST-LINK VCP on U2 pin 12 and 13.
  // See UM §6.1.3 ST-LINK/V2-A VCP configuration)
  #define SERIAL_PORT_HARDWARE_OPEN  Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
