/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 *
 * Author: Sergey Shcherbakov 2020
 * As a base used board_template/variant.h
 */

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

/* Test pins */
#define PC2  0  // TP2
#define PE6  1  // TP3
#define PC13 2  // TP4
#define PA3  3  // TP5
#define PE5  4  // TP6
#define PD6  5  // TP7
#define PD3  6  // TP8
#define PD2  7  // TP9
#define PB14 8  // TP10
#define PB15 9  // TP11
#define PA8  10 // TP12

/* Button switches */
#define PC11 11 // SW1
#define PA15 12 // SW2
#define PC9  13 // SW3
#define PC6  14 // SW4
#define PC8  15 // SW5

/* WH1602 Char Display */
#define PE7  16 // DISP_RS
#define PE10 17 // DISP_RW
#define PE11 18 // DISP_ENA
#define PE12 19 // DISP_DB4
#define PE13 20 // DISP_DB5
#define PE14 21 // DISP_DB6
#define PE15 22 // DISP_DB7
#define PE9  23 // Display backlight open-drain output

/* Ethernet */
#define PB0  24 // ETH_UP_LED#, it's should be used by Ethernet driver
#define PE8  25 // RMII_PHY_INT#, it's should be used by Ethernet driver _ONLY_
#define PD10 26 // RMII_PHY_RST#, it's should be used by Ethernet driver _ONLY_

/* MEMS */
#define PE4  27 // MEMS_INT1#_A/G
#define PE2  28 // MEMS_INT2#_A/G
#define PB8  29 // MEMS_INT#_M

/* USART3 */
#define PD9  30  // USART3_RX
#define PD8  31  // USART3_TX

/* I2C */
#define PB6  32  // I2C1_SCL
#define PB9  33  // I2C1_SDA

/* SPI */
#define PA5  34  // SPI1_SCK
#define PB5  35  // SPI1_MOSI
#define PB4  36  // SPI1_MISO
#define PD7  37  // SPI1_CS0#

/* CAN */
#define PD0  38  // CAN1_RX
#define PD1  39  // CAN1_TX

/* Other */
#define PB7  40  // PWM_EN
#define PB1  A0  // ADC only, i.e. it's connected to Temperature Sensor

/* LEDs */
#define PD12 42  // Green LED
#define PD13 43  // Orange LED
#define PD14 44  // Red LED
#define PD15 45  // Blue LED

/* DHT11 */
#define PD11 46  // DHT11 sensor input

// This must be a literal
#define NUM_DIGITAL_PINS        47
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       3

// On-board LED pin number
#define LED_GREEN               PD12
#define LED_BLUE                PD15
#define LED_RED                 PD14
#define LED_ORANGE              PD13
#define LED_BUILTIN             LED_GREEN

// On-board user button
#define USER_BTN                2 /* PA0 */

// SPI Definitions
#define PIN_SPI_SS              NC // No HW SS is available, PD7 pin will be used
#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PA5

// I2C Definitions
#define PIN_WIRE_SDA            PB9
#define PIN_WIRE_SCL            PB6

// CAN Definitions
#define PIN_CAN_RX              PD0 // CAN1_RX
#define PIN_CAN_TX              PD1 // CAN1_TX

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    3

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PD9
#define PIN_SERIAL_TX           PD8

/* Extra HAL modules */
#define HAL_ETH_MODULE_ENABLED
#define HAL_CAN_MODULE_ENABLED

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

#define HSE_VALUE               8000000U  /*!< Value of the External oscillator in Hz */

#endif /* _VARIANT_ARDUINO_STM32_ */
