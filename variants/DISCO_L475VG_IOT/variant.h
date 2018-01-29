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

enum {
// CN3 connector
  PA1,  //D0 - UART4_RX
  PA0,  //D1 - UART4_TX
  PD14, //D2
  PB0,  //D3 - PWM
  PA3,  //D4
  PB4,  //D5 - PWM
  PB1,  //D6 - PWM
  PA4,  //D7
// CN1 connector
  PB2,  //D8
  PA15, //D9 - PWM
  PA2,  //D10 - SPI_SSN/PWM
  PA7,  //D11 - SPI1_MOSI/PWM
  PA6,  //D12 - SPI1_MISO
  PA5,  //D13 - SPI1_SCK/LED1
  PB9,  //D14 - I2C1_SDA
  PB8,  //D15 - I2C1_SCL
// Not on connector
  PB14, //D16 - LED2
  PC13, //D17 - USER_BTN
// ST-LINK
  PB6,  //D18 - ST-LINK-UART1_TX
  PB7,  //D19 - ST-LINK-UART1_RX
// CN9 USB OTG FS connector
  PA9,  //D20 - USB_OTG_FS_VBUS
  PA10, //D21 - USB_OTG_FS_ID
  PA11, //D22 - USB_OTG_FS_DM
  PA12, //D23 - USB_OTG_FS_DP
  PD12, //D24 - USB_OTG_FS_PWR_EN
  PE3,  //D25 - USB_OTG_OVRCR_EXTI3
// CN10 PMOD connector
  PD0,  //D26 - PMOD-RESET
  PD1,  //D27 - PMOD-SPI2_SCK
  PD2,  //D28 - PMOD-IRQ_EXTI2
  PD3,  //D29 - PMOD-UART2_CTS/SPI2_MISO
  PD4,  //D30 - PMOD-UART2_RTS/SPI2_MOSI
  PD5,  //D31 - PMOD-UART2_TX/SPI2_CSN
  PD6,  //D32 - PMOD-UART2_RX
// Sensors / modules pins
  PA8,  //D33 - SPBTLE-RF-RST
  PB5,  //D34 - SPSGRF-915-SPI3_CSN
  PB10, //D35 - INTERNAL-I2C2_SCL
  PB11, //D36 - INTERNAL-I2C2_SDA
  PB12, //D37 - ISM43362-BOOT0
  PB13, //D38 - ISM43362-WAKEUP
  PB15, //D39 - SPSGRF-915-SDN
  PC6,  //D40 - VL53L0X_XSHUT
  PC7,  //D41 - VL53L0X_GPIO1_EXTI7
  PC8,  //D42 - LIS3MDL_DRDY_EXTI8
  PC9,  //D43 - LED3 (WIFI) & LED4 (BLE)
  PC10, //D44 - INTERNAL-SPI3_SCK
  PC11, //D45 - INTERNAL-SPI3_MISO
  PC12, //D46 - INTERNAL-SPI3_MOSI
  PD7,  //D47 - STSAFE-A100-RESET
  PD8,  //D48 - INTERNAL-UART3_TX
  PD9,  //D49 - INTERNAL-UART3_RX
  PD10, //D50 - LPS22HB_INT_DRDY_EXTI10
  PD11, //D51 - LSM6DSL_INT1_EXTI11
  PD13, //D52 - SPBTLE-RF-SPI3_CSN
  PD15, //D53 - HTS221_DRDY_EXTI15
  PE0,  //D54 - ISM43362-SPI3_CSN
  PE1,  //D55 - ISM43362-DRDY_EXTI1
  PE2,  //D56 - M24SR64-Y-RF_DISABLE
  PE4,  //D57 - M24SR64-Y-GPO
  PE5,  //D58 - SPSGRF-915-GPIO3_EXTI5
  PE6,  //D59 - SPBTLE-RF-IRQ_EXTI6
  PE7,  //D60 - DFSDM1_DATIN2
  PE8,  //D61 - ISM43362-RST
  PE9,  //D62 - DFSDM1_CKOUT
  PE10, //D63 - QUADSPI_CLK
  PE11, //D64 - QUADSPI_NCS
  PE12, //D65 - QUADSPI_BK1_IO0
  PE13, //D66 - QUADSPI_BK1_IO1
  PE14, //D67 - QUADSPI_BK1_IO2
  PE15, //D68 - QUADSPI_BK1_IO3
// CN4 connector
  PC5,  //D69/A0
  PC4,  //D70/A1
  PC3,  //D71/A2
  PC2,  //D72/A3
  PC1,  //D73/A4
  PC0,  //D74/A5
// Duplicated pins in order to be aligned with PinMap_ADC
  PA1_2, //D75/A6
  PA0_2, //D76/A7
  PB0_2, //D77/A8
  PA3_2, //D78/A9
  PB1_2, //D79/A10
  PA4_2, //D80/A11
  PA2_2, //D81/A12
  PA7_2, //D82/A13
  PA6_2, //D83/A14
  PA5_2, //D84/A15
  PEND
};

// This must be a literal with the same value as PEND
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
