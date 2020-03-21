/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 *******************************************************************************
 */
#include "PortNames.h"

GPIO_TypeDef *GPIOPort[MAX_NB_PORT] = {
  (GPIO_TypeDef *)GPIOA_BASE,
  (GPIO_TypeDef *)GPIOB_BASE
#if defined GPIOC_BASE
  , (GPIO_TypeDef *)GPIOC_BASE
#endif
#if defined GPIOD_BASE
  , (GPIO_TypeDef *)GPIOD_BASE
#endif
#if defined GPIOE_BASE
  , (GPIO_TypeDef *)GPIOE_BASE
#endif
#if defined GPIOF_BASE
  , (GPIO_TypeDef *)GPIOF_BASE
#endif
#if defined GPIOG_BASE
  , (GPIO_TypeDef *)GPIOG_BASE
#endif
#if defined GPIOH_BASE
  , (GPIO_TypeDef *)GPIOH_BASE
#endif
#if defined GPIOI_BASE
  , (GPIO_TypeDef *)GPIOI_BASE
#endif
#if defined GPIOJ_BASE
  , (GPIO_TypeDef *)GPIOJ_BASE
#endif
#if defined GPIOK_BASE
  , (GPIO_TypeDef *)GPIOK_BASE
#endif
#if defined GPIOZ_BASE
  , (GPIO_TypeDef *)GPIOZ_BASE
#endif
};

/* Enable GPIO clock and return GPIO base address */
GPIO_TypeDef *set_GPIO_Port_Clock(uint32_t port_idx)
{
  GPIO_TypeDef *gpioPort = 0;
  switch (port_idx) {
    case PortA:
      gpioPort = (GPIO_TypeDef *)GPIOA_BASE;
      __HAL_RCC_GPIOA_CLK_ENABLE();
      break;
    case PortB:
      gpioPort = (GPIO_TypeDef *)GPIOB_BASE;
      __HAL_RCC_GPIOB_CLK_ENABLE();
      break;
#if defined GPIOC_BASE
    case PortC:
      gpioPort = (GPIO_TypeDef *)GPIOC_BASE;
      __HAL_RCC_GPIOC_CLK_ENABLE();
      break;
#endif
#if defined GPIOD_BASE
    case PortD:
      gpioPort = (GPIO_TypeDef *)GPIOD_BASE;
      __HAL_RCC_GPIOD_CLK_ENABLE();
      break;
#endif
#if defined GPIOE_BASE
    case PortE:
      gpioPort = (GPIO_TypeDef *)GPIOE_BASE;
      __HAL_RCC_GPIOE_CLK_ENABLE();
      break;
#endif
#if defined GPIOF_BASE
    case PortF:
      gpioPort = (GPIO_TypeDef *)GPIOF_BASE;
      __HAL_RCC_GPIOF_CLK_ENABLE();
      break;
#endif
#if defined GPIOG_BASE
    case PortG:
#if defined(STM32L4xx) && defined(PWR_CR2_IOSV)
      // Enable VDDIO2 supply for 14 I/Os (Port G[15:2])
      __HAL_RCC_PWR_CLK_ENABLE();
      HAL_PWREx_EnableVddIO2();
#endif
      gpioPort = (GPIO_TypeDef *)GPIOG_BASE;
      __HAL_RCC_GPIOG_CLK_ENABLE();
      break;
#endif
#if defined GPIOH_BASE
    case PortH:
      gpioPort = (GPIO_TypeDef *)GPIOH_BASE;
      __HAL_RCC_GPIOH_CLK_ENABLE();
      break;
#endif
#if defined GPIOI_BASE
    case PortI:
      gpioPort = (GPIO_TypeDef *)GPIOI_BASE;
      __HAL_RCC_GPIOI_CLK_ENABLE();
      break;
#endif
#if defined GPIOJ_BASE
    case PortJ:
      gpioPort = (GPIO_TypeDef *)GPIOJ_BASE;
      __HAL_RCC_GPIOJ_CLK_ENABLE();
      break;
#endif
#if defined GPIOK_BASE
    case PortK:
      gpioPort = (GPIO_TypeDef *)GPIOK_BASE;
      __HAL_RCC_GPIOK_CLK_ENABLE();
      break;
#endif
#if defined GPIOZ_BASE
    case PortZ:
      gpioPort = (GPIO_TypeDef *)GPIOZ_BASE;
      __HAL_RCC_GPIOZ_CLK_ENABLE();
      break;
#endif
    default:
      // wrong port number
      //TBD: error management
      gpioPort = 0;
      break;
  }
  return gpioPort;
}
