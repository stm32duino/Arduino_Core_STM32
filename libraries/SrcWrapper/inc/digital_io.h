/**
  ******************************************************************************
  * @file    digital_io.h
  * @brief   Header for digital_io module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DIGITAL_IO_H
#define __DIGITAL_IO_H

/* Includes ------------------------------------------------------------------*/
#include "wiring_constants.h"
#include "PinNames.h"
#include "pinmap.h"
#include "stm32yyxx_ll_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  This function set a value to an IO
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  * @param  val : 0 to set to low, any other value to set to high
  * @retval None
  */
static inline void digital_io_write(GPIO_TypeDef *port, uint32_t pin, uint32_t val)
{
  if (val) {
    LL_GPIO_SetOutputPin(port, pin);
  } else {
    LL_GPIO_ResetOutputPin(port, pin);
  }
}

/**
  * @brief  This function read the value of an IO
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  * @retval The pin state (LOW or HIGH)
  */
static inline uint32_t digital_io_read(GPIO_TypeDef *port, uint32_t pin)
{
  return LL_GPIO_IsInputPinSet(port, pin);
}

/**
  * @brief  This function toggle value of an IO
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  * @retval None
  */
static inline void digital_io_toggle(GPIO_TypeDef *port, uint32_t pin)
{
  LL_GPIO_TogglePin(port, pin);
}

/**
  * @brief  This function set a value to an IO
  * @param  pn : Pin name
  * @param  val : 0 to set to low, any other value to set to high
  * @retval None
  */
static inline void digitalWriteFast(PinName pn, uint32_t ulVal)
{
  digital_io_write(get_GPIO_Port(STM_PORT(pn)), STM_LL_GPIO_PIN(pn), ulVal);
}

/**
  * @brief  This function read the value of an IO
  * @param  pn : Pin name
  * @retval The pin state (LOW or HIGH)
  */
static inline int digitalReadFast(PinName pn)
{
  uint8_t level = 0;
  level = digital_io_read(get_GPIO_Port(STM_PORT(pn)), STM_LL_GPIO_PIN(pn));
  return (level) ? HIGH : LOW;
}

/**
  * @brief  This function toggle value of an IO
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  * @retval None
  */
static inline void digitalToggleFast(PinName pn)
{
  digital_io_toggle(get_GPIO_Port(STM_PORT(pn)), STM_LL_GPIO_PIN(pn));
}

#ifdef __cplusplus
}
#endif

#endif /* __DIGITAL_IO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
