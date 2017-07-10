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
#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_

// API compatibility
#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Libc porting layers
 */
#if defined (  __GNUC__  ) /* GCC CS3 */
#    include <syscalls.h> /** RedHat Newlib minimal stub */
#endif

#define NOT_AN_INTERRUPT        NC // -1

#define NUM_DIGITAL_PINS        DEND
#define NUM_ANALOG_INPUTS       (AEND-A0)

// Convert a digital pin number Dxx to a PinName Pxy
// Note: Analog pin is also a digital pin.
#define digitalPinToPinName(p)     ((p < NUM_DIGITAL_PINS) ? digitalPin[p] : NC)
// Convert a PinName Pxy to a digital pin number
uint32_t pinNametoDigitalPin(PinName p);

// Convert an analog pin number to a digital pin number
// Used by analogRead api to have A0 == 0
#define analogInputToDigitalPin(p) ((p < NUM_ANALOG_INPUTS) ? (p+A0) : p)
// Convert an analog pin number Axx to a PinName Pxy
#define analogInputToPinName(p)    (digitalPinToPinName(analogInputToDigitalPin(p)))
// All pins could manage EXTI
#define digitalPinToInterrupt(p)   ((p>=D0) && (p < NUM_DIGITAL_PINS) ? p : NOT_AN_INTERRUPT)

#define digitalPinHasI2C(p)        (pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SDA) ||\
                                    pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SCL))
#define digitalPinHasPWM(p)        (pin_in_pinmap(digitalPinToPinName(p), PinMap_PWM))
#define digitalPinHasSerial(p)     (pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_RX) ||\
                                    pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_TX))
#define digitalPinHasSPI(p)        (pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MOSI) ||\
                                    pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MISO) ||\
                                    pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SCLK) ||\
                                    pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SSEL))


#define digitalPinToPort(p)        ( get_GPIO_Port(digitalPinToPinName(p)) )
#define digitalPinToBitMask(p)     ( STM_GPIO_PIN(digitalPinToPinName(p)) )

#define digitalPinIsValid(p)       (digitalPinToPinName(p) != NC)

#ifdef __cplusplus
}
#endif

#endif /*_PINS_ARDUINO_H_*/
