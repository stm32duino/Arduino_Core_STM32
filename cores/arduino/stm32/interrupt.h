/**
  ******************************************************************************
  * @file    interrupt.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   Header for interrupt module
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
#ifndef __INTERRUPT_H
#define __INTERRUPT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"

#if !defined(HAL_EXTI_MODULE_DISABLED)

  #if defined(STM32F3xx)
    #define EXTI2_IRQn    EXTI2_TSC_IRQn
  #endif

  #ifndef EXTI_IRQ_PRIO
    #if (__CORTEX_M == 0x00U)
      #define EXTI_IRQ_PRIO       3
    #else
      #define EXTI_IRQ_PRIO       6
    #endif /* __CORTEX_M */
  #endif /* EXTI_IRQ_PRIO */
  #ifndef EXTI_IRQ_SUBPRIO
    #define EXTI_IRQ_SUBPRIO    0
  #endif

  #ifdef __cplusplus
    #include <functional>

    typedef std::function<void(void)> callback_function_t;
    void stm32_interrupt_enable(GPIO_TypeDef *port, uint16_t pin, callback_function_t callback, uint32_t mode);
  #endif

  /* Exported functions ------------------------------------------------------- */
  void stm32_interrupt_enable(GPIO_TypeDef *port, uint16_t pin, void (*callback)(void), uint32_t mode);
  void stm32_interrupt_disable(GPIO_TypeDef *port, uint16_t pin);
#endif /* !HAL_EXTI_MODULE_DISABLED */

#endif /* __INTERRUPT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
