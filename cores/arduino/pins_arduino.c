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

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

WEAK uint32_t pinNametoDigitalPin(PinName p)
{
  uint32_t i = NUM_DIGITAL_PINS;
  if (STM_VALID_PINNAME(p)) {
    for (i = 0; i < NUM_DIGITAL_PINS; i++) {
      if (digitalPin[i] == (p & PNAME_MASK)) {
        i |= ((uint32_t)(p) & ALTX_MASK);
        break;
      }
    }
  }
  return i;
}

PinName analogInputToPinName(uint32_t pin)
{
  PinName pn = digitalPinToPinName(analogInputToDigitalPin(pin));
  if (pn == NC) {
    switch (pin) {
#if defined(ADC_CHANNEL_TEMPSENSOR) || defined(ADC_CHANNEL_TEMPSENSOR_ADC1)
      case ATEMP:
        pn = PADC_TEMP;
        break;
#endif
#if defined(ADC5) && defined(ADC_CHANNEL_TEMPSENSOR_ADC5)
      case ATEMP_ADC5:
        pn = PADC_TEMP_ADC5;
        break;
#endif
#ifdef AVREF
      case AVREF:
        pn = PADC_VREF;
        break;
#endif
#ifdef AVBAT
      case AVBAT:
        pn = PADC_VBAT;
        break;
#endif
      default:
        break;
    }
  }
  return pn;
}

/**
  * @brief  Return true if a digital pin is an analog input
  * @param  pin Dx, x or PYn
  * @retval boolean true if analog or false
  */
bool digitalpinIsAnalogInput(uint32_t pin)
{
  bool ret = false;
#if NUM_ANALOG_INPUTS > 0
  if ((pin & PNUM_ANALOG_BASE) == PNUM_ANALOG_BASE) {
    ret = true;
  } else {
    for (uint32_t i = 0; i < NUM_ANALOG_INPUTS; i++) {
      if (analogInputPin[i] == (pin & PNUM_MASK)) {
        ret = true;
        break;
      }
    }
  }
#endif /* NUM_ANALOG_INPUTS > 0 */
  return ret;
}

/**
  * @brief  Return the analog input linked to a digital pin
  * @param  pin Dx, x or PYn
  * @retval analogInput valid analog input or NUM_ANALOG_INPUTS
  */
uint32_t digitalPinToAnalogInput(uint32_t pin)
{
  uint32_t ret = NUM_ANALOG_INPUTS;
#if NUM_ANALOG_INPUTS > 0
  if ((pin & PNUM_ANALOG_BASE) == PNUM_ANALOG_BASE) {
    /* PYn = Ax */
    ret = (pin & PNUM_ANALOG_INDEX) | (pin & ALTX_MASK);
  } else {
    for (uint32_t i = 0; i < NUM_ANALOG_INPUTS; i++) {
      if (analogInputPin[i] == (pin & PNUM_MASK)) {
        ret = i | (pin & ALTX_MASK);
        break;
      }
    }
  }
#endif /* NUM_ANALOG_INPUTS > 0 */
  return ret;
}

#ifdef __cplusplus
}
#endif
