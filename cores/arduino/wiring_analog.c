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

#include "Arduino.h"
#include "PinConfigured.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(HAL_DAC_MODULE_ENABLED) || defined(HAL_TIM_MODULE_ENABLED)
//This is the list of the IOs configured
uint32_t g_anOutputPinConfigured[MAX_NB_PORT] = {0};
#endif

static int _readResolution = 10;
static int _writeResolution = 8;
static uint32_t _writeFreq = PWM_FREQUENCY;

void analogReadResolution(int res)
{
  _readResolution = res;
}

void analogWriteResolution(int res)
{
  _writeResolution = res;
}

void analogWriteFrequency(uint32_t freq)
{
  _writeFreq = freq;
}

static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to)
{
  if (from == to) {
    return value;
  }
  if (value == 0) {
    return value;
  }
  if (from > to) {
    return (((value + 1) >> (from - to)) - 1);
  } else {
    return (((value + 1) << (to - from)) - 1);
  }
}

void analogReference(eAnalogReference ulMode)
{
  UNUSED(ulMode);
}

//perform the read operation on the selected analog pin.
//the initialization of the analog PIN is done through this function
uint32_t analogRead(uint32_t ulPin)
{
  uint32_t value = 0;
#ifdef HAL_ADC_MODULE_ENABLED
  PinName p = analogInputToPinName(ulPin);
  if (p != NC) {
    value = adc_read_value(p);
    value = mapResolution(value, ADC_RESOLUTION, _readResolution);
  }
#else
  UNUSED(ulPin);
#endif
  return value;
}


void analogOutputInit(void)
{
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// variant.cpp file.  For the rest of the pins, we default
// to digital output.
void analogWrite(uint32_t ulPin, uint32_t ulValue)
{
#if defined(HAL_DAC_MODULE_ENABLED)
  uint8_t do_init = 0;
#endif
  PinName p = digitalPinToPinName(ulPin);
  if (p != NC) {
#ifdef HAL_DAC_MODULE_ENABLED
    if (pin_in_pinmap(p, PinMap_DAC)) {
      if (is_pin_configured(p, g_anOutputPinConfigured) == false) {
        do_init = 1;
        set_pin_configured(p, g_anOutputPinConfigured);
      }
      ulValue = mapResolution(ulValue, _writeResolution, DACC_RESOLUTION);
      dac_write_value(p, ulValue, do_init);
    } else
#endif //HAL_DAC_MODULE_ENABLED
#ifdef HAL_TIM_MODULE_ENABLED
      if (pin_in_pinmap(p, PinMap_PWM)) {
        if (is_pin_configured(p, g_anOutputPinConfigured) == false) {
          set_pin_configured(p, g_anOutputPinConfigured);
        }
        ulValue = mapResolution(ulValue, _writeResolution, PWM_RESOLUTION);
        pwm_start(p, _writeFreq, ulValue);
      } else
#endif /* HAL_TIM_MODULE_ENABLED */
      {
        //DIGITAL PIN ONLY
        // Defaults to digital write
        pinMode(ulPin, OUTPUT);
        ulValue = mapResolution(ulValue, _writeResolution, 8);
        if (ulValue < 128) {
          digitalWrite(ulPin, LOW);
        } else {
          digitalWrite(ulPin, HIGH);
        }
      }
  }
}

#ifdef __cplusplus
}
#endif
