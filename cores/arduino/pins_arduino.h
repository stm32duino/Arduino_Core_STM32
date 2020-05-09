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
#include <stdbool.h>
#include <stdlib.h> /* Required for static_assert */
// Include board variant
#include "variant.h"
#include "PinNames.h"


// Avoid PortName issue
_Static_assert(LastPort <= 0x0F, "PortName must be less than 16");

// Arduino digital pins alias
// GPIO port (A to K) * 16 pins: 176
enum {
  D0,   D1,   D2,   D3,   D4,   D5,   D6,   D7,   D8,   D9,
  D10,  D11,  D12,  D13,  D14,  D15,  D16,  D17,  D18,  D19,
  D20,  D21,  D22,  D23,  D24,  D25,  D26,  D27,  D28,  D29,
  D30,  D31,  D32,  D33,  D34,  D35,  D36,  D37,  D38,  D39,
  D40,  D41,  D42,  D43,  D44,  D45,  D46,  D47,  D48,  D49,
  D50,  D51,  D52,  D53,  D54,  D55,  D56,  D57,  D58,  D59,
  D60,  D61,  D62,  D63,  D64,  D65,  D66,  D67,  D68,  D69,
  D70,  D71,  D72,  D73,  D74,  D75,  D76,  D77,  D78,  D79,
  D80,  D81,  D82,  D83,  D84,  D85,  D86,  D87,  D88,  D89,
  D90,  D91,  D92,  D93,  D94,  D95,  D96,  D97,  D98,  D99,
  D100, D101, D102, D103, D104, D105, D106, D107, D108, D109,
  D110, D111, D112, D113, D114, D115, D116, D117, D118, D119,
  D120, D121, D122, D123, D124, D125, D126, D127, D128, D129,
  D130, D131, D132, D133, D134, D135, D136, D137, D138, D139,
  D140, D141, D142, D143, D144, D145, D146, D147, D148, D149,
  D150, D151, D152, D153, D154, D155, D156, D157, D158, D159,
  D160, D161, D162, D163, D164, D165, D166, D167, D168, D169,
  D170, D171, D172, D173, D174, D175,
  DMAX
};

// Arduino analog pins

#ifndef NUM_ANALOG_INPUTS
  #define NUM_ANALOG_INPUTS 0
#endif

// If NUM_ANALOG_FIRST is not defined:
// - Ax are not contiguous in the digitalPin array
// - analogInputPin array is available
#ifndef NUM_ANALOG_FIRST
  #define NUM_ANALOG_FIRST          (NUM_DIGITAL_PINS + 1)
  #define NUM_ANALOG_LAST           (NUM_DIGITAL_PINS + NUM_ANALOG_INPUTS)
  #define NUM_ANALOG_INTERNAL_FIRST (NUM_ANALOG_LAST + 1)
#else
  #define NUM_ANALOG_INTERNAL_FIRST (NUM_DIGITAL_PINS + 1)
#endif

// If NUM_ANALOG_INPUTS is not defined there is no analog pins defined.
// Anyway ADC internal channels are always avaialable.
#if NUM_ANALOG_INPUTS > 0
// Analog pins must be contiguous to be able to loop on each value
#define MAX_ANALOG_INPUTS 24
_Static_assert(NUM_ANALOG_INPUTS <= MAX_ANALOG_INPUTS,
               "Core NUM_ANALOG_INPUTS limited to MAX_ANALOG_INPUTS");

_Static_assert(NUM_ANALOG_FIRST >= NUM_ANALOG_INPUTS,
               "First analog pin value (A0) must be greater than or equal to NUM_ANALOG_INPUTS");

#if NUM_ANALOG_INPUTS > 0
  #define PIN_A0       NUM_ANALOG_FIRST
  static const uint8_t A0 = PIN_A0;
#endif
#if NUM_ANALOG_INPUTS > 1
  #define PIN_A1       (PIN_A0 + 1)
  static const uint8_t A1 = PIN_A1;
#endif
#if NUM_ANALOG_INPUTS > 2
  #define PIN_A2       (PIN_A1 + 1)
  static const uint8_t A2 = PIN_A2;
#endif
#if NUM_ANALOG_INPUTS > 3
  #define PIN_A3       (PIN_A2 + 1)
  static const uint8_t A3 = PIN_A3;
#endif
#if NUM_ANALOG_INPUTS > 4
  #define PIN_A4       (PIN_A3 + 1)
  static const uint8_t A4 = PIN_A4;
#endif
#if NUM_ANALOG_INPUTS > 5
  #define PIN_A5       (PIN_A4 + 1)
  static const uint8_t A5 = PIN_A5;
#endif
#if NUM_ANALOG_INPUTS > 6
  #define PIN_A6       (PIN_A5 + 1)
  static const uint8_t A6 = PIN_A6;
#endif
#if NUM_ANALOG_INPUTS > 7
  #define PIN_A7       (PIN_A6 + 1)
  static const uint8_t A7 = PIN_A7;
#endif
#if NUM_ANALOG_INPUTS > 8
  #define PIN_A8       (PIN_A7 + 1)
  static const uint8_t A8 = PIN_A8;
#endif
#if NUM_ANALOG_INPUTS > 9
  #define PIN_A9       (PIN_A8 + 1)
  static const uint8_t A9 = PIN_A9;
#endif
#if NUM_ANALOG_INPUTS > 10
  #define PIN_A10      (PIN_A9 + 1)
  static const uint8_t A10 = PIN_A10;
#endif
#if NUM_ANALOG_INPUTS > 11
  #define PIN_A11      (PIN_A10 + 1)
  static const uint8_t A11 = PIN_A11;
#endif
#if NUM_ANALOG_INPUTS > 12
  #define PIN_A12      (PIN_A11 + 1)
  static const uint8_t A12 = PIN_A12;
#endif
#if NUM_ANALOG_INPUTS > 13
  #define PIN_A13      (PIN_A12 + 1)
  static const uint8_t A13 = PIN_A13;
#endif
#if NUM_ANALOG_INPUTS > 14
  #define PIN_A14      (PIN_A13 + 1)
  static const uint8_t A14 = PIN_A14;
#endif
#if NUM_ANALOG_INPUTS > 15
  #define PIN_A15      (PIN_A14 + 1)
  static const uint8_t A15 = PIN_A15;
#endif
#if NUM_ANALOG_INPUTS > 16
  #define PIN_A16      (PIN_A15 + 1)
  static const uint8_t A16 = PIN_A16;
#endif
#if NUM_ANALOG_INPUTS > 17
  #define PIN_A17      (PIN_A16 + 1)
  static const uint8_t A17 = PIN_A17;
#endif
#if NUM_ANALOG_INPUTS > 18
  #define PIN_A18      (PIN_A17 + 1)
  static const uint8_t A18 = PIN_A18;
#endif
#if NUM_ANALOG_INPUTS > 19
  #define PIN_A19      (PIN_A18 + 1)
  static const uint8_t A19 = PIN_A19;
#endif
#if NUM_ANALOG_INPUTS > 20
  #define PIN_A20      (PIN_A19 + 1)
  static const uint8_t A20 = PIN_A20;
#endif
#if NUM_ANALOG_INPUTS > 21
  #define PIN_A21      (PIN_A20 + 1)
  static const uint8_t A21 = PIN_A21;
#endif
#if NUM_ANALOG_INPUTS > 22
  #define PIN_A22      (PIN_A21 + 1)
  static const uint8_t A22 = PIN_A22;
#endif
#if NUM_ANALOG_INPUTS > 23
  #define PIN_A23      (PIN_A22 + 1)
  static const uint8_t A23 = PIN_A23;
#endif
#endif /* NUM_ANALOG_INPUTS > 0 */

// Default for Arduino connector compatibility
// SPI Definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS                  10
#endif
#ifndef PIN_SPI_SS1
  #define PIN_SPI_SS1                 4
#endif
#ifndef PIN_SPI_SS2
  #define PIN_SPI_SS2                 7
#endif
#ifndef PIN_SPI_SS3
  #define PIN_SPI_SS3                 8
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI                11
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO                12
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK                 13
#endif

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t SS1  = PIN_SPI_SS1;
static const uint8_t SS2  = PIN_SPI_SS2;
static const uint8_t SS3  = PIN_SPI_SS3;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

// I2C Definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA                14
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL                15
#endif

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// ADC internal channels (not a pins)
// Only used for analogRead()
#if defined(ADC_CHANNEL_TEMPSENSOR) || defined(ADC_CHANNEL_TEMPSENSOR_ADC1)
  #define ATEMP        (NUM_ANALOG_INTERNAL_FIRST)
#endif
#ifdef ADC_CHANNEL_VREFINT
  #define AVREF        (NUM_ANALOG_INTERNAL_FIRST + 2)
#endif
#ifdef ADC_CHANNEL_VBAT
  #define AVBAT        (NUM_ANALOG_INTERNAL_FIRST + 3)
#endif
#if defined(ADC5) && defined(ADC_CHANNEL_TEMPSENSOR_ADC5)
  #define ATEMP_ADC5   (NUM_ANALOG_INTERNAL_FIRST + 4)
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern const PinName digitalPin[];
extern const uint32_t analogInputPin[];

#define NOT_AN_INTERRUPT            NC // -1

// Convert a digital pin number Dxx to a PinName PX_n
// Note: Analog pin is also a digital pin.
#ifndef NUM_ANALOG_LAST
#define digitalPinToPinName(p)      (((uint32_t)p < NUM_DIGITAL_PINS) ? digitalPin[p] : NC)
#else
#define digitalPinToPinName(p)      (((uint32_t)p < NUM_DIGITAL_PINS) ? digitalPin[p] : \
            ((uint32_t)p >= NUM_ANALOG_FIRST) && ((uint32_t)p <= NUM_ANALOG_LAST) ? \
                                                digitalPin[analogInputPin[p-NUM_ANALOG_FIRST]] : NC)
#endif
// Convert a PinName PX_n to a digital pin number
uint32_t pinNametoDigitalPin(PinName p);

// Convert an analog pin number to a digital pin number
#if NUM_ANALOG_INPUTS > 0
// Used by analogRead api to have A0 == 0
// For contiguous analog pins definition in digitalPin array
#ifndef NUM_ANALOG_LAST
#define analogInputToDigitalPin(p)  (((uint32_t)p < NUM_ANALOG_INPUTS) ? (p+A0) : p)
#else
// For non contiguous analog pins definition in digitalPin array
#define analogInputToDigitalPin(p)  ( \
            ((uint32_t)p < NUM_ANALOG_INPUTS) ? analogInputPin[p] : \
            ((uint32_t)p >= NUM_ANALOG_FIRST) && ((uint32_t)p <= NUM_ANALOG_LAST) ? \
                                                analogInputPin[p-NUM_ANALOG_FIRST] : p)
#endif // !NUM_ANALOG_LAST
#else
// No analog pin defined
#define analogInputToDigitalPin(p)  (NUM_DIGITAL_PINS)
#endif // NUM_ANALOG_INPUTS > 0

// Convert an analog pin number Axx to a PinName PX_n
PinName analogInputToPinName(uint32_t pin);

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

#define analogInPinToBit(p)         (STM_GPIO_PIN(digitalPinToPinName(p)))
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

// Specific for Firmata.
// Some pins could be duplicated, ensure 'p' is not one of the serial pins
#if defined(PIN_SERIAL_RX) && defined(PIN_SERIAL_TX)
#define pinIsSerial(p)              ((digitalPinFirstOccurence(p) == PIN_SERIAL_RX) ||\
                                     (digitalPinFirstOccurence(p) == PIN_SERIAL_TX))
#endif
// Convenient macro to handle Analog
bool pinIsAnalogInput(uint32_t pin);
uint32_t digitalPinToAnalogInput(uint32_t pin);

#ifdef __cplusplus
}
#endif

// Default Definitions, could be redefined in variant.h
#ifndef ADC_RESOLUTION
  #define ADC_RESOLUTION              10
#endif

#define DACC_RESOLUTION             12

#ifndef PWM_RESOLUTION
  #define PWM_RESOLUTION              8
#endif

_Static_assert((ADC_RESOLUTION > 0) &&(ADC_RESOLUTION <= 32),
               "ADC_RESOLUTION must be 0 < x <= 32!");
_Static_assert((PWM_RESOLUTION > 0) &&(PWM_RESOLUTION <= 32),
               "PWM_RESOLUTION must be 0 < x <= 32!");

#ifndef PWM_FREQUENCY
  #define PWM_FREQUENCY               1000
#endif
#ifndef PWM_MAX_DUTY_CYCLE
  #define PWM_MAX_DUTY_CYCLE          4095
#endif

#endif /*_PINS_ARDUINO_H_*/
