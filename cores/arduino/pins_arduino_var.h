/*
 * Variant pins Arduino definition
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author: Frederic Pillon for STMicroelectronics.
 *
 * License type: GPLv2
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _PINS_ARDUINO_VAR_H_
#define _PINS_ARDUINO_VAR_H_

// Include board variant
#include "variant.h"

#ifdef __cplusplus
extern "C" {
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

// Default Definitions, could be redefined in variant.h
#ifndef ADC_RESOLUTION
#define ADC_RESOLUTION              12
#endif
#ifndef DACC_RESOLUTION
#define DACC_RESOLUTION             12
#endif
#ifndef PWM_RESOLUTION
#define PWM_RESOLUTION              8
#endif
#ifndef PWM_FREQUENCY
#define PWM_FREQUENCY               1000
#endif
#ifndef PWM_MAX_DUTY_CYCLE
#define PWM_MAX_DUTY_CYCLE          255
#endif

// Default for Arduino connector compatibility
// SPI Definitions
#ifndef SS
#define SS                          10
#endif
#ifndef SS1
#define SS1                         4
#endif
#ifndef SS2
#define SS2                         7
#endif
#ifndef SS3
#define SS3                         8
#endif
#ifndef MOSI
#define MOSI                        11
#endif
#ifndef MISO
#define MISO                        12
#endif
#ifndef SCK
#define SCK                         13
#endif
// I2C Definitions
#ifndef SDA
#define SDA                         14
#endif
#ifndef SCL
#define SCL                         15
#endif

#ifdef __cplusplus
}
#endif

#endif /*_PINS_ARDUINO_VAR_H_*/

