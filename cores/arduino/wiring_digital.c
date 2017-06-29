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


//This is the list of the IOs configured
uint32_t g_digPinConfigured[MAX_NB_PORT] = {0};
extern uint32_t g_anOutputPinConfigured[MAX_NB_PORT];


void pinMode( uint32_t ulPin, uint32_t ulMode )
{
  PinName p = digitalPinToPinName(ulPin);

  if(p != NC) {
    // If the pin that support PWM or DAC output, we need to turn it off
    if(is_pin_configured(p, g_anOutputPinConfigured)) {
#ifdef HAL_DAC_MODULE_ENABLED
      if(pin_in_pinmap(p, PinMap_DAC)) {
        dac_stop(p);
      } else
#endif //HAL_DAC_MODULE_ENABLED
      if(pin_in_pinmap(p, PinMap_PWM)) {
        pwm_stop(p);
      }
      reset_pin_configured(p, g_anOutputPinConfigured);
    }

    switch ( ulMode )
    {
      case INPUT:
        digital_io_init(p, GPIO_MODE_INPUT, GPIO_NOPULL);
      break;
      case INPUT_PULLUP:
        digital_io_init(p, GPIO_MODE_INPUT, GPIO_PULLUP);
      break;
      case INPUT_PULLDOWN:
        digital_io_init(p, GPIO_MODE_INPUT, GPIO_PULLDOWN);
      break;
      case OUTPUT:
        digital_io_init(p, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL);
      break;
      default:
      break;
    }
    set_pin_configured(p, g_digPinConfigured);
  }
}

void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
  PinName p = digitalPinToPinName(ulPin);
  if(p != NC) {
    if(is_pin_configured(p, g_digPinConfigured)) {
      digital_io_write(get_GPIO_Port(STM_PORT(p)), STM_GPIO_PIN(p), ulVal);
    }
  }
}

int digitalRead( uint32_t ulPin )
{
  uint8_t level = 0;
  PinName p = digitalPinToPinName(ulPin);
  if(p != NC) {
    if(is_pin_configured(p, g_digPinConfigured)) {
      level = digital_io_read(get_GPIO_Port(STM_PORT(p)), STM_GPIO_PIN(p));
    }
  }
  return (level)? HIGH : LOW;
}

#ifdef __cplusplus
}
#endif
