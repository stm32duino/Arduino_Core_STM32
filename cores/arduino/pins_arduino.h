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

#define NOT_AN_INTERRUPT            NC // -1
#define DEND                        PEND
#define NUM_DIGITAL_PINS            ((uint32_t)DEND)
#define NUM_ANALOG_INPUTS           ((uint32_t)(AEND-A0))

// Convert a digital pin number Dxx to a PinName PX_n
// Note: Analog pin is also a digital pin.
#define digitalPinToPinName(p)      (((uint32_t)p < NUM_DIGITAL_PINS) ? digitalPin[p] : NC)
// Convert a PinName PX_n to a digital pin number
uint32_t pinNametoDigitalPin(PinName p);

// Convert an analog pin number to a digital pin number
// Used by analogRead api to have A0 == 0
#define analogInputToDigitalPin(p)  (((uint32_t)p < NUM_ANALOG_INPUTS) ? (p+A0) : p)
// Convert an analog pin number Axx to a PinName PX_n
#define analogInputToPinName(p)     (digitalPinToPinName(analogInputToDigitalPin(p)))
// All pins could manage EXTI
#define digitalPinToInterrupt(p)    (digitalPinIsValid(p) ? p : NOT_AN_INTERRUPT)

#define digitalPinHasI2C(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SDA) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SCL))
#define digitalPinHasPWM(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_PWM))
#define digitalPinHasSerial(p)      (pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_RX) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_TX))
#define digitalPinHasSPI(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MOSI) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MISO) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SCLK) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SSEL))


#define digitalPinToPort(p)         (get_GPIO_Port(STM_PORT(digitalPinToPinName(p))))
#define digitalPinToBitMask(p)      (STM_GPIO_PIN(digitalPinToPinName(p)))

#define analogInPinToBit(p)         (STM_PIN(digitalPinToPinName(p)))
#define portOutputRegister(P)       (&(P->ODR))
#define portInputRegister(P)        (&(P->IDR))

#define portSetRegister(P)          (&(P->BSRR))
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
// For those series reset are in the high part so << 16U needed
#define portClearRegister(P)        (&(P->BSRR))
#else
#define portClearRegister(P)        (&(P->BRR))
#endif


#if defined(STM32F1xx)
// Config registers split in 2 registers:
// CRL: pin 0..7
// CRH: pin 8..15
// Return only CRL
#define portModeRegister(P)         (&(P->CRL))
#else
#define portModeRegister(P)         (&(P->MODER))
#endif
#define portConfigRegister(P)       (portModeRegister(P))


#define digitalPinIsValid(p)        (digitalPinToPinName(p) != NC)

// As some pin could be duplicated in digitalPin[]
// return first occurence of linked PinName (PYx)
#define digitalPinFirstOccurence(p) (pinNametoDigitalPin(digitalPinToPinName(p)))

// Specific for Firmata. As some pins could be duplicated,
// ensure 'p' is not one of the serial pins
#if defined(PIN_SERIAL_RX) && defined(PIN_SERIAL_TX)
#define pinIsSerial(p)              ((digitalPinFirstOccurence(p) == PIN_SERIAL_RX) ||\
                                     (digitalPinFirstOccurence(p) == PIN_SERIAL_TX))
#endif

#ifdef __cplusplus
}
#endif

#endif /*_PINS_ARDUINO_H_*/
