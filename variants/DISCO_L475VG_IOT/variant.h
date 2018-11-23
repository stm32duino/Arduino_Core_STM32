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

// CN3 connector
#define PA1  0  // A6/UART4_RX
#define PA0  1  // A7/UART4_TX
#define PD14 2
#define PB0  3  // A8/PWM
#define PA3  4  // A9
#define PB4  5  // PWM
#define PB1  6  // A10/PWM
#define PA4  7  // A11
// CN1 connector
#define PB2  8
#define PA15 9  // PWM
#define PA2  10 // A12/SPI_SSN/PWM
#define PA7  11 // A13/SPI1_MOSI/PWM
#define PA6  12 // A14/SPI1_MISO
#define PA5  13 // A15/SPI1_SCK/LED1
#define PB9  14 // I2C1_SDA
#define PB8  15 // I2C1_SCL
// Not on connector
#define PB14 16 // LED2
#define PC13 17 // USER_BTN
// ST-LINK
#define PB6  18 // ST-LINK-UART1_TX
#define PB7  19 // ST-LINK-UART1_RX
// CN9 USB OTG FS connector
#define PA9  20 // USB_OTG_FS_VBUS
#define PA10 21 // USB_OTG_FS_ID
#define PA11 22 // USB_OTG_FS_DM
#define PA12 23 // USB_OTG_FS_DP
#define PD12 24 // USB_OTG_FS_PWR_EN
#define PE3  25 // USB_OTG_OVRCR_EXTI3
// CN10 PMOD connector
#define PD0  26 // PMOD-RESET
#define PD1  27 // PMOD-SPI2_SCK
#define PD2  28 // PMOD-IRQ_EXTI2
#define PD3  29 // PMOD-UART2_CTS/SPI2_MISO
#define PD4  30 // PMOD-UART2_RTS/SPI2_MOSI
#define PD5  31 // PMOD-UART2_TX/SPI2_CSN
#define PD6  32 // PMOD-UART2_RX
// Sensors / modules pins
#define PA8  33 // SPBTLE-RF-RST
#define PB5  34 // SPSGRF-915-SPI3_CSN
#define PB10 35 // INTERNAL-I2C2_SCL
#define PB11 36 // INTERNAL-I2C2_SDA
#define PB12 37 // ISM43362-BOOT0
#define PB13 38 // ISM43362-WAKEUP
#define PB15 39 // SPSGRF-915-SDN
#define PC6  40 // VL53L0X_XSHUT
#define PC7  41 // VL53L0X_GPIO1_EXTI7
#define PC8  42 // LIS3MDL_DRDY_EXTI8
#define PC9  43 // LED3 (WIFI) & LED4 (BLE)
#define PC10 44 // INTERNAL-SPI3_SCK
#define PC11 45 // INTERNAL-SPI3_MISO
#define PC12 46 // INTERNAL-SPI3_MOSI
#define PD7  47 // STSAFE-A100-RESET
#define PD8  48 // INTERNAL-UART3_TX
#define PD9  49 // INTERNAL-UART3_RX
#define PD10 50 // LPS22HB_INT_DRDY_EXTI10
#define PD11 51 // LSM6DSL_INT1_EXTI11
#define PD13 52 // SPBTLE-RF-SPI3_CSN
#define PD15 53 // HTS221_DRDY_EXTI15
#define PE0  54 // ISM43362-SPI3_CSN
#define PE1  55 // ISM43362-DRDY_EXTI1
#define PE2  56 // M24SR64-Y-RF_DISABLE
#define PE4  57 // M24SR64-Y-GPO
#define PE5  58 // SPSGRF-915-GPIO3_EXTI5
#define PE6  59 // SPBTLE-RF-IRQ_EXTI6
#define PE7  60 // DFSDM1_DATIN2
#define PE8  61 // ISM43362-RST
#define PE9  62 // DFSDM1_CKOUT
#define PE10 63 // QUADSPI_CLK
#define PE11 64 // QUADSPI_NCS
#define PE12 65 // QUADSPI_BK1_IO0
#define PE13 66 // QUADSPI_BK1_IO1
#define PE14 67 // QUADSPI_BK1_IO2
#define PE15 68 // QUADSPI_BK1_IO3
// CN4 connector
#define PC5  69 // A0
#define PC4  70 // A1
#define PC3  71 // A2
#define PC2  72 // A3
#define PC1  73 // A4
#define PC0  74 // A5

// This must be a literal
#define NUM_DIGITAL_PINS        85
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       16
#define NUM_ANALOG_FIRST        69

// On-board LED pin number
#define LED_BUILTIN             13
#define LED1                    LED_BUILTIN
#define LED2                    PB14
#define LED3                    PC9
#define LED4                    LED3

// On-board user button
#define USER_BTN                PC13

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM6

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    1 //Connected to ST-Link
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PB7
#define PIN_SERIAL_TX           PB6

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
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
