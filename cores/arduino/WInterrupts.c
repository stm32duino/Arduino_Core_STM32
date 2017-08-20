/*
  Copyright (c) 2011-2012 Arduino.  All right reserved.

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

#include "WInterrupts.h"

#ifdef __cplusplus
 extern "C" {
#endif

#include "PinAF_STM32F1.h"

void attachInterrupt(uint32_t pin, void (*callback)(void), uint32_t mode)
{
  uint32_t it_mode;
  PinName p = digitalPinToPinName(pin);
  GPIO_TypeDef* port = set_GPIO_Port_Clock(STM_PORT(p));
  if (!port)
	  return;

  switch(mode) {
    case CHANGE :
      it_mode = GPIO_MODE_IT_RISING_FALLING;
    break;
    case FALLING :
    case LOW :
      it_mode = GPIO_MODE_IT_FALLING;
    break;
    case RISING :
    case HIGH :
      it_mode = GPIO_MODE_IT_RISING;
    break;
    default:
      it_mode = GPIO_MODE_IT_RISING;
    break;
  }

#ifdef STM32F1xx
  pinF1_DisconnectDebug(p);
#endif /* STM32F1xx */

  stm32_interrupt_enable(port, STM_GPIO_PIN(p), callback, it_mode);
}

void detachInterrupt(uint32_t pin)
{
  PinName p = digitalPinToPinName(pin);
  GPIO_TypeDef* port = get_GPIO_Port(STM_PORT(p));
  if (!port)
	  return;
  stm32_interrupt_disable(port, STM_GPIO_PIN(p));
}
