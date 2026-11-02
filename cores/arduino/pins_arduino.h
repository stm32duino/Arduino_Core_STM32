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
/**
 * @file pins_arduino.h
 * @brief Pin number conversion helpers, port register macros and default pin definitions.
 */
#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_
#include <stdbool.h>
#include <stdlib.h> /* Required for static_assert */
#include "api/Common.h"
#include "variant.h"
#include "PinNames.h"

#include "pins_arduino_analog.h"
#include "pins_arduino_digital.h"

/** Pin number mask, allows to retrieve the pin number without ALTx. */
#define PNUM_MASK                   0xFF

/** Pin not defined. */
#define PNUM_NOT_DEFINED            NUM_DIGITAL_PINS

/* Avoid PortName issue */
_Static_assert(LastPort <= 0x0F, "PortName must be less than 16");

_Static_assert(NUM_ANALOG_INPUTS <= MAX_ANALOG_INPUTS,
               "Core NUM_ANALOG_INPUTS limited to MAX_ANALOG_INPUTS");

/* Default for Arduino connector compatibility */
/* SPI Definitions: default pin numbers, could be redefined in the variant */
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS                10
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1               4
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2               7
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3               8
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI              11
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO              12
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK               13
#endif

static const pin_size_t SS   = PIN_SPI_SS;
static const pin_size_t SS1  = PIN_SPI_SS1;
static const pin_size_t SS2  = PIN_SPI_SS2;
static const pin_size_t SS3  = PIN_SPI_SS3;
static const pin_size_t MOSI = PIN_SPI_MOSI;
static const pin_size_t MISO = PIN_SPI_MISO;
static const pin_size_t SCK  = PIN_SPI_SCK;

/* I2C Definitions: default pin numbers, could be redefined in the variant */
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA              14
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL              15
#endif

static const pin_size_t SDA = PIN_WIRE_SDA;
static const pin_size_t SCL = PIN_WIRE_SCL;

/* I3C Definitions: default pin numbers, could be redefined in the variant */
#ifndef PIN_I3C_SDA
  #define PIN_I3C_SDA              14
#endif
#ifndef PIN_I3C_SCL
  #define PIN_I3C_SCL              15
#endif

static const uint32_t I3C_SDA = PIN_I3C_SDA;
static const uint32_t I3C_SCL = PIN_I3C_SCL;

#ifdef __cplusplus
extern "C" {
#endif
extern const PinName digitalPin[];
extern const pin_size_t analogInputPin[];

/**
 * @brief Value returned by digitalPinToInterrupt() when the pin cannot be used
 * as an interrupt.
 */
#define NOT_AN_INTERRUPT            (pin_size_t)NC

/**
 * @brief Convert a digital pin number (Dxx) to a PinName (PX_n).
 *
 * The ALTX bits of the pin number are preserved. An analog pin number (Ax) is also accepted.
 *
 * @param p Digital pin number.
 * @return PinName of the pin. NC if the pin is not valid.
 */
#if NUM_ANALOG_INPUTS > 0
/* Note: Analog pin is also a digital pin */
#define digitalPinToPinName(p)      ((((pin_size_t)(p) & PNUM_MASK) < NUM_DIGITAL_PINS) ? \
            (PinName)(digitalPin[(pin_size_t)(p) & PNUM_MASK] | ((p) & ALTX_MASK)) : \
            (((pin_size_t)(p) & PNUM_ANALOG_BASE) == PNUM_ANALOG_BASE) && \
            (((pin_size_t)(p) & PNUM_MASK) < NUM_ANALOG_INTERNAL_FIRST) ? \
            (PinName)(digitalPin[analogInputPin[(p) & PNUM_ANALOG_INDEX]] | ((p) & ALTX_MASK)) : NC)
#else
#define digitalPinToPinName(p)      ((((pin_size_t)(p) & PNUM_MASK) < NUM_DIGITAL_PINS) ? \
            (PinName)(digitalPin[(pin_size_t)(p) & PNUM_MASK] | ((p) & ALTX_MASK)) : NC)
#endif /* NUM_ANALOG_INPUTS > 0 */
/**
 * @brief Convert a PinName (PX_n) to a digital pin number.
 *
 * @param p PinName to convert.
 * @return Digital pin number, with the ALTX bits preserved.
 * NUM_DIGITAL_PINS if not found.
 */
pin_size_t pinNametoDigitalPin(PinName p);

/**
 * @brief Convert an analog pin number (Ax) to a digital pin number.
 *
 * Used by the analogRead API to have A0 == 0, even if the analog pins are
 * not contiguous in the digitalPin array.
 *
 * @param p Analog pin number.
 * @return Digital pin number, with the ALTX bits preserved. NC if the pin is
 * not valid, or NUM_DIGITAL_PINS when no analog input is defined.
 */
#if NUM_ANALOG_INPUTS > 0
#define analogInputToDigitalPin(p)  ((((pin_size_t)(p) & PNUM_MASK) < NUM_ANALOG_INPUTS) ? \
            analogInputPin[(pin_size_t)(p) & PNUM_MASK] | ((pin_size_t)(p) & ALTX_MASK) : \
            (((pin_size_t)(p) & PNUM_ANALOG_BASE) == PNUM_ANALOG_BASE) && \
            (((pin_size_t)(p) & PNUM_MASK) < NUM_ANALOG_INTERNAL_FIRST) ? \
            analogInputPin[(p) & PNUM_ANALOG_INDEX] | ((pin_size_t)(p) & ALTX_MASK) : (pin_size_t)NC)
#else/* No analog pin defined */
#define analogInputToDigitalPin(p)  (NUM_DIGITAL_PINS)
#endif /* NUM_ANALOG_INPUTS > 0 */

/**
 * @brief Convert an analog pin number (Ax) to a PinName (PX_n).
 *
 * @note The internal channels (ATEMP, ATEMP_ADC5, AVREF, AVBAT) are also
 * handled when defined.
 *
 * @param pin Analog pin number, Ax.
 * @return PinName of the analog input. NC if the pin is not an analog input.
 */
PinName analogInputToPinName(pin_size_t pin);

/**
 * @brief Convert a digital pin number to an interrupt number.
 *
 * All pins could manage EXTI, so the pin number is used as interrupt number.
 *
 * @param p Digital pin number.
 * @return The pin number if it is valid, NOT_AN_INTERRUPT otherwise.
 */
#define digitalPinToInterrupt(p)    (digitalPinIsValid(p) ? p : NOT_AN_INTERRUPT)

/** Check whether a digital pin has an I2C (SDA or SCL) function. */
#define digitalPinHasI2C(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SDA) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SCL))
/** Check whether a digital pin has a PWM (timer) function. */
#define digitalPinHasPWM(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_TIM))
/** Check whether a digital pin has a UART (RX or TX) function. */
#define digitalPinHasSerial(p)      (pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_RX) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_TX))
/**
 * Check whether a digital pin has an SPI (MOSI, MISO, SCLK or SSEL) function.
 */
#define digitalPinHasSPI(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MOSI) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MISO) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SCLK) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SSEL))


/** Get the GPIO port (GPIO_TypeDef pointer) of a digital pin. */
#define digitalPinToPort(p)         (get_GPIO_Port(STM_PORT(digitalPinToPinName(p))))
/** Get the bit mask of a digital pin in its GPIO port registers. */
#define digitalPinToBitMask(p)      (STM_GPIO_PIN(digitalPinToPinName(p)))

/** Get the bit mask of an analog pin in its GPIO port registers. */
#define analogInPinToBit(p)         (STM_GPIO_PIN(digitalPinToPinName(p)))
/** Get the address of the output data register of a GPIO port. */
#define portOutputRegister(P)       (&(P->ODR))
/** Get the address of the input data register of a GPIO port. */
#define portInputRegister(P)        (&(P->IDR))

/** Get the address of the set register of a GPIO port. */
#define portSetRegister(P)          (&(P->BSRR))
/* Get the address of the clear register of a GPIO port */
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
/* For those series reset are in the high part so << 16U needed */
#define portClearRegister(P)        (&(P->BSRR))
#else
#define portClearRegister(P)        (&(P->BRR))
#endif


/* Get the address of the mode register of a GPIO port */
#if defined(STM32F1xx)
/*
 * Config registers split in 2 registers:
 * CRL: pin 0..7
 * CRH: pin 8..15
 * Return only CRL
 */
#define portModeRegister(P)         (&(P->CRL))
#else
#define portModeRegister(P)         (&(P->MODER))
#endif
/**
 * Get the address of the mode register of a GPIO port.
 * Same as portModeRegister().
 */
#define portConfigRegister(P)       (portModeRegister(P))


/** Check whether a digital pin number is valid, i.e. linked to a PinName. */
#define digitalPinIsValid(p)        (digitalPinToPinName(p) != NC)

/**
 * @brief Get the first occurrence of a pin in digitalPin[].
 *
 * Some pins could be duplicated in digitalPin[], this returns the digital pin
 * number of the first occurrence of the linked PinName (PYx).
 *
 * @param p Digital pin number.
 * @return Digital pin number of the first occurrence.
 * NUM_DIGITAL_PINS if not found.
 */
#define digitalPinFirstOccurence(p) (pinNametoDigitalPin(digitalPinToPinName(p)))

/* Specific for Firmata */
#if defined(PIN_SERIAL_RX) && defined(PIN_SERIAL_TX)
/**
 * Check whether a digital pin is the RX or TX pin of the default serial (Firmata).
 */
#define pinIsSerial(p)              ((digitalPinToPinName(p) == \
                                      digitalPinToPinName(PIN_SERIAL_RX & PNUM_MASK)) ||\
                                     (digitalPinToPinName(p) == \
                                      digitalPinToPinName(PIN_SERIAL_TX & PNUM_MASK)))
#endif
/**
 * Convenient macro to handle Analog for Firmata, see digitalpinIsAnalogInput().
 */
#define pinIsAnalogInput digitalpinIsAnalogInput
/**
 * @brief Check whether a digital pin is an analog input.
 *
 * @param pin Dx, x or PYn.
 * @return true if the pin is an analog input, false otherwise.
 */
bool digitalpinIsAnalogInput(pin_size_t pin);
/**
 * @brief Get the analog input linked to a digital pin.
 *
 * @param pin Dx, x or PYn.
 * @return Valid analog input number, or NUM_ANALOG_INPUTS if none.
 */
pin_size_t digitalPinToAnalogInput(pin_size_t pin);

#ifdef __cplusplus
}
#endif

/* Default Definitions, could be redefined in variant.h */
#ifndef ADC_RESOLUTION
  /** Default resolution of analogRead() values, in bits. */
  #define ADC_RESOLUTION            10
#endif

/** Resolution of the DAC, in bits. */
#define DACC_RESOLUTION             12

#ifndef PWM_RESOLUTION
  /** Default resolution of analogWrite() values, in bits. */
  #define PWM_RESOLUTION            8
#endif

_Static_assert((ADC_RESOLUTION > 0) &&(ADC_RESOLUTION <= 32),
               "ADC_RESOLUTION must be 0 < x <= 32!");
_Static_assert((PWM_RESOLUTION > 0) &&(PWM_RESOLUTION <= 32),
               "PWM_RESOLUTION must be 0 < x <= 32!");

#ifndef PWM_FREQUENCY
  /** Default PWM frequency of analogWrite(), in Hertz. */
  #define PWM_FREQUENCY             1000
#endif
#ifndef PWM_MAX_DUTY_CYCLE
  /** Maximum PWM duty cycle value. */
  #define PWM_MAX_DUTY_CYCLE        4095
#endif

#endif /*_PINS_ARDUINO_H_*/
