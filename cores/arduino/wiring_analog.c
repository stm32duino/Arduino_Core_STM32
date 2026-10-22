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

/* DAC/PWM */
#if !defined(HAL_DAC_MODULE_ONLY) &&\
    (defined(HAL_DAC_MODULE_ENABLED) || (defined(USE_HAL_DAC_MODULE) && (USE_HAL_DAC_MODULE == 1))) ||\
    (!defined(HAL_TIM_MODULE_ONLY) &&\
    (defined(HAL_TIM_MODULE_ENABLED) || (defined(USE_HAL_TIM_MODULE) && (USE_HAL_TIM_MODULE == 1))))
//This is the list of the IOs configured
uint32_t g_anOutputPinConfigured[MAX_NB_PORT] = {0};
#endif
#define MAX_PWM_RESOLUTION 16
static int _writeResolution = PWM_RESOLUTION;
static int _internalWriteResolution =
#if PWM_RESOLUTION > MAX_PWM_RESOLUTION
  MAX_PWM_RESOLUTION
#else
  PWM_RESOLUTION
#endif
  ;
static uint32_t _writeFreq = PWM_FREQUENCY;

/* ADC */
#if defined(LL_ADC_RESOLUTION_16B) || defined(LL_ADC_DS_DATA_WIDTH_16_BIT)
#define MAX_ADC_RESOLUTION 16
#elif defined(LL_ADC_DS_DATA_WIDTH_15_BIT)
#define MAX_ADC_RESOLUTION 15
#elif defined(LL_ADC_RESOLUTION_14B) || defined(LL_ADC_DS_DATA_WIDTH_14_BIT)
#define MAX_ADC_RESOLUTION 14
#elif defined(LL_ADC_DS_DATA_WIDTH_13_BIT)
#define MAX_ADC_RESOLUTION 13
#else
#define MAX_ADC_RESOLUTION 12
#endif

static int _readResolution = ADC_RESOLUTION;
static int _internalReadResolution =
#if ADC_RESOLUTION > MAX_ADC_RESOLUTION
  MAX_ADC_RESOLUTION
#else
#if ADC_RESOLUTION <= 6 && defined(LL_ADC_RESOLUTION_6B)
  6
#elif ADC_RESOLUTION <= 8 && defined(LL_ADC_RESOLUTION_8B)
  8
#elif ADC_RESOLUTION <= 10 && defined(LL_ADC_RESOLUTION_10B)
  10
#elif ADC_RESOLUTION <= 12 /* Common for all series */
  12
#elif ADC_RESOLUTION <= 13 && defined(LL_ADC_DS_DATA_WIDTH_13_BIT)
  13
#elif ADC_RESOLUTION <= 14 && (defined(LL_ADC_RESOLUTION_14B) || defined(LL_ADC_DS_DATA_WIDTH_14_BIT))
  14
#elif ADC_RESOLUTION <= 15 && defined(LL_ADC_DS_DATA_WIDTH_15_BIT)
  15
#elif defined(LL_ADC_RESOLUTION_16B) || defined(LL_ADC_DS_DATA_WIDTH_16_BIT)
  16
#endif
#endif /* ADC_RESOLUTION > MAX_ADC_RESOLUTION */
  ;

/**
 * @brief Map a value from one resolution to another.
 *
 * @param value Value to convert.
 * @param from Resolution of value, in bits.
 * @param to Target resolution, in bits.
 * @return Value scaled to the target resolution.
 */
static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to)
{
  if (from != to) {
    if (from > to) {
      value = (value < (uint32_t)(1 << (from - to))) ? 0 : ((value + 1) >> (from - to)) - 1;
    } else {
      if (value != 0) {
        value = ((value + 1) << (to - from)) - 1;
      }
    }
  }
  return value;
}

/* ADC */
void analogReadResolution(int res)
{
  if ((res > 0) && (res <= 32)) {
    _readResolution = res;
    _internalReadResolution = _readResolution;
    if (_readResolution > MAX_ADC_RESOLUTION) {
      _internalReadResolution = MAX_ADC_RESOLUTION;
    } else {
#ifdef LL_ADC_RESOLUTION_6B
      if (_internalReadResolution <= 6) {
        _internalReadResolution = 6;
      } else
#endif
#if defined(LL_ADC_RESOLUTION_8B)
        if (_internalReadResolution <= 8) {
          _internalReadResolution = 8;
        } else
#endif
#if defined(LL_ADC_RESOLUTION_10B)
          if (_internalReadResolution <= 10) {
            _internalReadResolution = 10;
          } else
#endif
#if defined(LL_ADC_DS_DATA_WIDTH_11_BIT)
            else if (_internalReadResolution <= 11) {
              _internalReadResolution = 11;
            }
#endif
      /* Common for all series */
      if (_internalReadResolution <= 12) {
        _internalReadResolution = 12;
      }
#if defined(LL_ADC_DS_DATA_WIDTH_13_BIT)
      else if (_internalReadResolution <= 13) {
        _internalReadResolution = 13;
      }
#endif
#if defined(LL_ADC_RESOLUTION_14B) || defined(LL_ADC_DS_DATA_WIDTH_14_BIT)
      else if (_internalReadResolution <= 14) {
        _internalReadResolution = 14;
      }
#endif
#if defined(LL_ADC_DS_DATA_WIDTH_15_BIT)
      else if (_internalReadResolution <= 15) {
        _internalReadResolution = 15;
      }
#endif
#if defined(LL_ADC_RESOLUTION_16B) || defined(LL_ADC_DS_DATA_WIDTH_16_BIT)
      else if (_internalReadResolution <= 16) {
        _internalReadResolution = 16;
      }
#endif
    }
  } else {
    Error_Handler();
  }
}

/**
 * @brief Set the analog reference voltage. Not supported on this core, the call has no effect.
 *
 * @param mode Reference mode, ignored.
 */
void analogReference(uint8_t mode)
{
  (void)mode;
}

/**
 * @brief Read the analog value of a pin, scaled to the resolution set by analogReadResolution().
 *
 * @param pinNumber Analog pin number, e.g. A0 or PA0.
 * @return Converted value, between 0 and 2^resolution - 1. 0 if the pin has no ADC.
 */
int analogRead(pin_size_t pinNumber)
{
  pin_size_t value = 0;
#if !defined(HAL_ADC_MODULE_ONLY) &&\
    (defined(HAL_ADC_MODULE_ENABLED) || (defined(USE_HAL_ADC_MODULE) && (USE_HAL_ADC_MODULE == 1)))

  PinName p = analogInputToPinName(pinNumber);
  if (p != NC) {
    value = adc_read_value(p, _internalReadResolution);
    value = mapResolution(value, _internalReadResolution, _readResolution);
  }
#else
  (void)pinNumber;
#endif
  return value;
}

/* DAC/PWM */
void analogWriteResolution(int res)
{
  if ((res > 0) && (res <= 32)) {
    _writeResolution = res;
    if (_writeResolution > MAX_PWM_RESOLUTION) {
      _internalWriteResolution = MAX_PWM_RESOLUTION;
    } else {
      _internalWriteResolution = _writeResolution;
    }
  } else {
    Error_Handler();
  }
}

void analogWriteFrequency(uint32_t freq)
{
  _writeFreq = freq;
}

/**
 * @brief Write an analog value to a pin, using PWM or DAC if the pin supports it.
 *
 * Pins without a timer or DAC output fall back to digital output.
 *
 * @param pinNumber Pin number to write to.
 * @param value Value to write, scaled to the resolution set by analogWriteResolution().
 */
void analogWrite(pin_size_t pinNumber, int value)
{
  PinName p = digitalPinToPinName(pinNumber);
  if (p != NC) {
#if !defined(HAL_DAC_MODULE_ONLY) &&\
    (defined(HAL_DAC_MODULE_ENABLED) || (defined(USE_HAL_DAC_MODULE) && (USE_HAL_DAC_MODULE == 1)))
    bool do_init = false;
    if (pin_in_pinmap(p, PinMap_DAC)) {
      if (is_pin_configured(p, g_anOutputPinConfigured) == false) {
        do_init = true;
        set_pin_configured(p, g_anOutputPinConfigured);
      }
      value = mapResolution(value, _writeResolution, DACC_RESOLUTION);
      dac_write_value(p, value, do_init);
    } else
#endif //HAL_DAC_MODULE_ENABLED && !HAL_DAC_MODULE_ONLY
#if !defined(HAL_TIM_MODULE_ONLY) &&\
    (defined(HAL_TIM_MODULE_ENABLED) || (defined(USE_HAL_TIM_MODULE) && (USE_HAL_TIM_MODULE == 1)))
      if (pin_in_pinmap(p, PinMap_TIM)) {
        if (is_pin_configured(p, g_anOutputPinConfigured) == false) {
          set_pin_configured(p, g_anOutputPinConfigured);
        }
        value = mapResolution(value, _writeResolution, _internalWriteResolution);
        pwm_start(p, _writeFreq, value, _internalWriteResolution);
      } else
#endif /* HAL_TIM_MODULE_ENABLED && !HAL_TIM_MODULE_ONLY */
      {
        // DIGITAL PIN ONLY
        // Defaults to digital write
        pinMode(pinNumber, OUTPUT);
        value = mapResolution(value, _writeResolution, 8);
        if (value < 128) {
          digitalWrite(pinNumber, LOW);
        } else {
          digitalWrite(pinNumber, HIGH);
        }
      }
  }
}

#ifdef __cplusplus
}
#endif
