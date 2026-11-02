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
 * @file wiring_digital.c
 * @brief Digital I/O functions: pinMode(), digitalWrite(), digitalRead() and digitalToggle().
 */

#include "Arduino.h"
#include "PinConfigured.h"

#ifdef __cplusplus
extern "C" {
#endif


extern pin_size_t g_anOutputPinConfigured[MAX_NB_PORT];

/**
 * @brief Set the mode of a pin.
 *
 * If the pin was used for PWM or DAC output (analogWrite()), the output is
 * stopped first. Any unsupported mode calls Error_Handler().
 *
 * @param pinNumber Pin number, Dx or x.
 * @param pinMode INPUT, INPUT_PULLUP, INPUT_PULLDOWN, INPUT_ANALOG, OUTPUT or OUTPUT_OPEN_DRAIN.
 */
void pinMode(pin_size_t pinNumber, PinMode pinMode)
{
  PinName p = digitalPinToPinName(pinNumber);

  if (p != NC) {
    // If the pin that support PWM or DAC output, we need to turn it off
#if !defined(HAL_DAC_MODULE_ONLY) &&\
    (defined(HAL_DAC_MODULE_ENABLED) || (defined(USE_HAL_DAC_MODULE) && (USE_HAL_DAC_MODULE == 1))) ||\
    (defined(HAL_TIM_MODULE_ENABLED) && !defined(HAL_TIM_MODULE_ONLY))
    if (is_pin_configured(p, g_anOutputPinConfigured)) {
#if !defined(HAL_DAC_MODULE_ONLY) &&\
    (defined(HAL_DAC_MODULE_ENABLED) || (defined(USE_HAL_DAC_MODULE) && (USE_HAL_DAC_MODULE == 1)))
      if (pin_in_pinmap(p, PinMap_DAC)) {
        dac_stop(p);
      } else
#endif
      {
#if defined(HAL_TIM_MODULE_ENABLED) && !defined(HAL_TIM_MODULE_ONLY)
        if (pin_in_pinmap(p, PinMap_TIM)) {
          pwm_stop(p);
        }
#endif //HAL_TIM_MODULE_ENABLED && !HAL_TIM_MODULE_ONLY
      }
      /* Unconditionally reset the pin configuration */
      reset_pin_configured(p, g_anOutputPinConfigured);
    }
#endif
    switch (pinMode) {
      case INPUT: /* INPUT_FLOATING */
        pin_function(p, STM_PIN_DATA(STM_MODE_INPUT, LL_GPIO_PULL_NO, 0));
        break;
      case INPUT_PULLUP:
        pin_function(p, STM_PIN_DATA(STM_MODE_INPUT, LL_GPIO_PULL_UP, 0));
        break;
      case INPUT_PULLDOWN:
        pin_function(p, STM_PIN_DATA(STM_MODE_INPUT, LL_GPIO_PULL_DOWN, 0));
        break;
      case INPUT_ANALOG:
        pin_function(p, STM_PIN_DATA(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0));
        break;
      case OUTPUT:
        pin_function(p, STM_PIN_DATA(STM_MODE_OUTPUT_PP, LL_GPIO_PULL_NO, 0));
        break;
      case OUTPUT_OPEN_DRAIN:
        pin_function(p, STM_PIN_DATA(STM_MODE_OUTPUT_OD, LL_GPIO_PULL_NO, 0));
        break;
      default:
        Error_Handler();
        break;
    }
  }
}

/**
 * @brief Write a HIGH or LOW value to a digital pin.
 *
 * @param pinNumber Pin number, Dx or x.
 * @param status HIGH or LOW.
 */
void digitalWrite(pin_size_t pinNumber, PinStatus status)
{
  PinName p = digitalPinToPinName(pinNumber);
  if (p != NC) {
    digitalWriteFast(p, status);
  }
}

/**
 * @brief Read the value of a digital pin.
 *
 * @param pinNumber Pin number, Dx or x.
 * @return HIGH or LOW. LOW if the pin is invalid.
 */
PinStatus digitalRead(pin_size_t pinNumber)
{
  PinName p = digitalPinToPinName(pinNumber);

  return (p == NC) ? LOW : digitalReadFast(p);
}

void digitalToggle(pin_size_t pinNumber)
{
  PinName p = digitalPinToPinName(pinNumber);
  if (p != NC) {
    digitalToggleFast(p);
  }
}

#ifdef __cplusplus
}
#endif
