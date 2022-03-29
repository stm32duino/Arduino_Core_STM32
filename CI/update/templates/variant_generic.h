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
 */
#pragma once

/*----------------------------------------------------------------------------
 *        STM32 pins number
 *----------------------------------------------------------------------------*/
{% for pin_number in pins_number_list %}
#define {{"%-23s %s"|format(pin_number.name, pin_number.val)}}
{% endfor %}
{% if alt_pins_list %}

// Alternate pins number
  {% for alt in alt_pins_list %}
#define {{"%-23s (%s | %s)"|format(alt.name, alt.base.ljust(waltpin-5), alt.num)}}
  {% endfor %}
{% endif %}

#define NUM_DIGITAL_PINS        {{num_digital_pins}}
{% if num_dualpad_pins %}
#define NUM_DUALPAD_PINS        {{num_dualpad_pins}}
{% endif %}
{% if num_remap_pins %}
#define NUM_REMAP_PINS          {{num_remap_pins}}
{% endif %}
#define NUM_ANALOG_INPUTS       {{num_analog_inputs}}

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PNUM_NOT_DEFINED
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PNUM_NOT_DEFINED
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            {{spi_pins.ss}}
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1           {{spi_pins.ss1}}
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2           {{spi_pins.ss2}}
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3           {{spi_pins.ss3}}
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          {{spi_pins.mosi}}
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          {{spi_pins.miso}}
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           {{spi_pins.sck}}
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          {{i2c_pins.sda}}
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          {{i2c_pins.scl}}
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
  #define TIMER_TONE            {{timer.tone}}
#endif
#ifndef TIMER_SERVO
  #define TIMER_SERVO           {{timer.servo}}
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  {{serial.instance}}
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         {{serial.rx}}
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         {{serial.tx}}
#endif

{% if hal_modules_list %}
// Extra HAL modules
  {% for hal_module in hal_modules_list %}
#if !defined(HAL_{{hal_module}}_MODULE_DISABLED)
  #define HAL_{{hal_module}}_MODULE_ENABLED
#endif
  {% endfor %}

{% endif %}
{% if alt_syswkup_list %}
// Alternate SYS_WKUP definition
  {% for def in alt_syswkup_list %}
#define PWR_WAKEUP_PIN{{def}}
  {% endfor %}

{% endif %}
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
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
#endif

