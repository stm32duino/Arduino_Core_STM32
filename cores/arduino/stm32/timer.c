/**
  ******************************************************************************
  * @file    timer.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide timer services
  *
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
/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f4xx_system
  * @{
  */

/** @addtogroup STM32F4xx_System_Private_Includes
  * @{
  */
#include "core_debug.h"
#include "timer.h"
#include "board.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_FunctionPrototypes
* @{
*/

static void HAL_TIMx_PeriodElapsedCallback(stimer_t *obj);

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F4xx_System_Private_Variables
  * @{
  */

#define TIMER_NUM (22)
static TIM_HandleTypeDef* timer_handles[TIMER_NUM] = {NULL};


/**
  * @}
  */

/**
  * @brief  Enable the timer clock
  * @param  htim : one of the defined timer
  * @retval None
  */
void timer_enable_clock(TIM_HandleTypeDef *htim)
{
// Enable TIM clock
#if defined(TIM1_BASE)
  if (htim->Instance == TIM1){
      __HAL_RCC_TIM1_CLK_ENABLE();
      timer_handles[0] = htim;
  }
#endif
#if defined(TIM2_BASE)
  if (htim->Instance == TIM2) {
      __HAL_RCC_TIM2_CLK_ENABLE();
      timer_handles[1] = htim;
  }
#endif
#if defined(TIM3_BASE)
  if (htim->Instance == TIM3) {
      __HAL_RCC_TIM3_CLK_ENABLE();
      timer_handles[2] = htim;
  }
#endif
#if defined(TIM4_BASE)
  if (htim->Instance == TIM4) {
      __HAL_RCC_TIM4_CLK_ENABLE();
      timer_handles[3] = htim;
  }
#endif
#if defined(TIM5_BASE)
  if (htim->Instance == TIM5) {
      __HAL_RCC_TIM5_CLK_ENABLE();
      timer_handles[4] = htim;
  }
#endif
#if defined(TIM6_BASE)
  if (htim->Instance == TIM6) {
      __HAL_RCC_TIM6_CLK_ENABLE();
      timer_handles[5] = htim;
  }
#endif
#if defined(TIM7_BASE)
  if (htim->Instance == TIM7) {
      __HAL_RCC_TIM7_CLK_ENABLE();
      timer_handles[6] = htim;
  }
#endif
#if defined(TIM8_BASE)
  if (htim->Instance == TIM8) {
      __HAL_RCC_TIM8_CLK_ENABLE();
      timer_handles[7] = htim;
  }
#endif
#if defined(TIM9_BASE)
  if (htim->Instance == TIM9) {
      __HAL_RCC_TIM9_CLK_ENABLE();
      timer_handles[8] = htim;
  }
#endif
#if defined(TIM10_BASE)
  if (htim->Instance == TIM10) {
      __HAL_RCC_TIM10_CLK_ENABLE();
      timer_handles[9] = htim;
  }
#endif
#if defined(TIM11_BASE)
  if (htim->Instance == TIM11) {
      __HAL_RCC_TIM11_CLK_ENABLE();
      timer_handles[10] = htim;
  }
#endif
#if defined(TIM12_BASE)
  if (htim->Instance == TIM12) {
      __HAL_RCC_TIM12_CLK_ENABLE();
      timer_handles[11] = htim;
  }
#endif
#if defined(TIM13_BASE)
  if (htim->Instance == TIM13) {
      __HAL_RCC_TIM13_CLK_ENABLE();
      timer_handles[12] = htim;
  }
#endif
#if defined(TIM14_BASE)
  if (htim->Instance == TIM14) {
      __HAL_RCC_TIM14_CLK_ENABLE();
      timer_handles[13] = htim;
  }
#endif
#if defined(TIM15_BASE)
  if (htim->Instance == TIM15) {
      __HAL_RCC_TIM15_CLK_ENABLE();
      timer_handles[14] = htim;
  }
#endif
#if defined(TIM16_BASE)
  if (htim->Instance == TIM16) {
      __HAL_RCC_TIM16_CLK_ENABLE();
      timer_handles[15] = htim;
  }
#endif
#if defined(TIM17_BASE)
  if (htim->Instance == TIM17) {
      __HAL_RCC_TIM17_CLK_ENABLE();
      timer_handles[16] = htim;
  }
#endif
#if defined(TIM18_BASE)
  if (htim->Instance == TIM18) {
      __HAL_RCC_TIM18_CLK_ENABLE();
      timer_handles[17] = htim;
  }
#endif
#if defined(TIM19_BASE)
  if (htim->Instance == TIM19) {
      __HAL_RCC_TIM19_CLK_ENABLE();
      timer_handles[18] = htim;
  }
#endif
#if defined(TIM20_BASE)
  if (htim->Instance == TIM20) {
      __HAL_RCC_TIM20_CLK_ENABLE();
      timer_handles[19] = htim;
  }
#endif
#if defined(TIM21_BASE)
  if (htim->Instance == TIM21) {
      __HAL_RCC_TIM21_CLK_ENABLE();
      timer_handles[20] = htim;
  }
#endif
#if defined(TIM22_BASE)
  if (htim->Instance == TIM22) {
      __HAL_RCC_TIM22_CLK_ENABLE();
      timer_handles[21] = htim;
  }
#endif
}

/**
  * @brief  Disable the timer clock
  * @param  htim : one of the defined timer
  * @retval None
  */
void timer_disable_clock(TIM_HandleTypeDef *htim)
{
// Enable TIM clock
#if defined(TIM1_BASE)
  if (htim->Instance == TIM1){
      __HAL_RCC_TIM1_CLK_DISABLE();
  }
#endif
#if defined(TIM2_BASE)
  if (htim->Instance == TIM2) {
      __HAL_RCC_TIM2_CLK_DISABLE();
  }
#endif
#if defined(TIM3_BASE)
  if (htim->Instance == TIM3) {
      __HAL_RCC_TIM3_CLK_DISABLE();
  }
#endif
#if defined(TIM4_BASE)
  if (htim->Instance == TIM4) {
      __HAL_RCC_TIM4_CLK_DISABLE();
  }
#endif
#if defined(TIM5_BASE)
  if (htim->Instance == TIM5) {
      __HAL_RCC_TIM5_CLK_DISABLE();
  }
#endif
#if defined(TIM6_BASE)
  if (htim->Instance == TIM6) {
      __HAL_RCC_TIM6_CLK_DISABLE();
  }
#endif
#if defined(TIM7_BASE)
  if (htim->Instance == TIM7) {
      __HAL_RCC_TIM7_CLK_DISABLE();
  }
#endif
#if defined(TIM8_BASE)
  if (htim->Instance == TIM8) {
      __HAL_RCC_TIM8_CLK_DISABLE();
  }
#endif
#if defined(TIM9_BASE)
  if (htim->Instance == TIM9) {
      __HAL_RCC_TIM9_CLK_DISABLE();
  }
#endif
#if defined(TIM10_BASE)
  if (htim->Instance == TIM10) {
      __HAL_RCC_TIM10_CLK_DISABLE();
  }
#endif
#if defined(TIM11_BASE)
  if (htim->Instance == TIM11) {
      __HAL_RCC_TIM11_CLK_DISABLE();
  }
#endif
#if defined(TIM12_BASE)
  if (htim->Instance == TIM12) {
      __HAL_RCC_TIM12_CLK_DISABLE();
  }
#endif
#if defined(TIM13_BASE)
  if (htim->Instance == TIM13) {
      __HAL_RCC_TIM13_CLK_DISABLE();
  }
#endif
#if defined(TIM14_BASE)
  if (htim->Instance == TIM14) {
      __HAL_RCC_TIM14_CLK_DISABLE();
  }
#endif
#if defined(TIM15_BASE)
  if (htim->Instance == TIM15) {
      __HAL_RCC_TIM15_CLK_DISABLE();
  }
#endif
#if defined(TIM16_BASE)
  if (htim->Instance == TIM16) {
      __HAL_RCC_TIM16_CLK_DISABLE();
  }
#endif
#if defined(TIM17_BASE)
  if (htim->Instance == TIM17) {
      __HAL_RCC_TIM17_CLK_DISABLE();
  }
#endif
#if defined(TIM18_BASE)
  if (htim->Instance == TIM18) {
      __HAL_RCC_TIM18_CLK_DISABLE();
  }
#endif
#if defined(TIM19_BASE)
  if (htim->Instance == TIM19) {
      __HAL_RCC_TIM19_CLK_DISABLE();
  }
#endif
#if defined(TIM20_BASE)
  if (htim->Instance == TIM20) {
      __HAL_RCC_TIM20_CLK_DISABLE();
  }
#endif
#if defined(TIM21_BASE)
  if (htim->Instance == TIM21) {
      __HAL_RCC_TIM21_CLK_DISABLE();
  }
#endif
#if defined(TIM22_BASE)
  if (htim->Instance == TIM22) {
      __HAL_RCC_TIM22_CLK_DISABLE();
  }
#endif
}

/**
  * @brief  TIMER Initialization - clock init and nvic init
  * @param  htim_base : one of the defined timer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim_base)
{
  timer_enable_clock(htim_base);

  HAL_NVIC_SetPriority(getTimerIrq(htim_base->Instance), 15 ,0);
  HAL_NVIC_EnableIRQ(getTimerIrq(htim_base->Instance));
}

/**
  * @brief  TIMER Deinitialization - clock and nvic
  * @param  htim_base : one of the defined timer
  * @retval None
  */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim_base)
{
  timer_disable_clock(htim_base);
  HAL_NVIC_DisableIRQ(getTimerIrq(htim_base->Instance));
}

/**
  * @brief  This function will set the timer to the required value
  * @param  timer_id : timer_id_e
  * @param  period : Timer period in milliseconds
  * @param  prescaler : clock divider
  * @retval None
  */
void TimerHandleInit(stimer_t *obj, uint16_t period, uint16_t prescaler)
{
  if(obj == NULL)
    return;

  TIM_HandleTypeDef *handle = &(obj->handle);

  handle->Instance               = obj->timer;
  handle->Init.Prescaler         = prescaler;
  handle->Init.CounterMode       = TIM_COUNTERMODE_UP;
  handle->Init.Period            = period;
  handle->Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
#if !defined(STM32L0xx) && !defined(STM32L1xx)
  handle->Init.RepetitionCounter = 0x0000;
#endif
  if(HAL_TIM_Base_Init(handle) != HAL_OK){
    return;
  }

  if(HAL_TIM_Base_Start_IT(handle) != HAL_OK){
    return;
  }
}

/**
  * @brief  This function return the timer clock source.
  * @param  tim: timer instance
  * @retval 1 = PCLK1 or 2 = PCLK2 or 0 = unknown
  */
uint32_t getTimerIrq(TIM_TypeDef* tim)
{
  uint32_t IRQn = 0;

  if(tim != (TIM_TypeDef *)NC) {
    /* Get IRQn depending on TIM instance */
    switch ((uint32_t)tim) {
#if defined(TIM1_BASE)
       case (uint32_t)TIM1:
         IRQn = TIM1_IRQn;
         break;
#endif
#if defined(TIM2_BASE)
       case (uint32_t)TIM2:
         IRQn = TIM2_IRQn;
         break;
#endif
#if defined(TIM3_BASE)
       case (uint32_t)TIM3:
         IRQn = TIM3_IRQn;
         break;
#endif
#if defined(TIM4_BASE)
       case (uint32_t)TIM4:
         IRQn = TIM4_IRQn;
         break;
#endif
#if defined(TIM5_BASE)
       case (uint32_t)TIM5:
         IRQn = TIM5_IRQn;
         break;
#endif
#if defined(TIM6_BASE)
       case (uint32_t)TIM6:
         IRQn = TIM6_IRQn;
         break;
#endif
#if defined(TIM7_BASE)
       case (uint32_t)TIM7:
         IRQn = TIM7_IRQn;
         break;
#endif
#if defined(TIM8_BASE)
       case (uint32_t)TIM8:
         IRQn = TIM8_IRQn;
         break;
#endif
#if defined(TIM9_BASE)
       case (uint32_t)TIM9:
         IRQn = TIM9_IRQn;
         break;
#endif
#if defined(TIM10_BASE)
       case (uint32_t)TIM10:
         IRQn = TIM10_IRQn;
         break;
#endif
#if defined(TIM11_BASE)
       case (uint32_t)TIM11:
         IRQn = TIM11_IRQn;
         break;
#endif
#if defined(TIM12_BASE)
       case (uint32_t)TIM12:
         IRQn = TIM12_IRQn;
         break;
#endif
#if defined(TIM13_BASE)
       case (uint32_t)TIM13:
         IRQn = TIM13_IRQn;
         break;
#endif
#if defined(TIM14_BASE)
       case (uint32_t)TIM14:
         IRQn = TIM14_IRQn;
         break;
#endif
#if defined(TIM15_BASE)
       case (uint32_t)TIM15:
         IRQn = TIM15_IRQn;
         break;
#endif
#if defined(TIM16_BASE)
       case (uint32_t)TIM16:
         IRQn = TIM16_IRQn;
         break;
#endif
#if defined(TIM17_BASE)
       case (uint32_t)TIM17:
         IRQn = TIM17_IRQn;
         break;
#endif
#if defined(TIM18_BASE)
       case (uint32_t)TIM18:
         IRQn = TIM18_IRQn;
         break;
#endif
#if defined(TIM19_BASE)
       case (uint32_t)TIM19:
         IRQn = TIM19_IRQn;
         break;
#endif
#if defined(TIM20_BASE)
       case (uint32_t)TIM20:
         IRQn = TIM20_IRQn;
         break;
#endif
#if defined(TIM21_BASE)
       case (uint32_t)TIM21:
         IRQn = TIM21_IRQn;
         break;
#endif
#if defined(TIM22_BASE)
       case (uint32_t)TIM22:
         IRQn = TIM22_IRQn;
         break;
#endif
         break;
     default:
        core_debug("TIM: Unknown timer IRQn");
        break;
    }
  }
  return IRQn;
}

/**
  * @brief  This function will reset the timer
  * @param  timer_id : timer_id_e
  * @retval None
  */
void TimerHandleDeinit(stimer_t *obj)
{
  if(obj != NULL) {
    HAL_TIM_Base_DeInit(&(obj->handle));
    HAL_TIM_Base_Stop_IT(&(obj->handle));
  }
}

/**
  * @brief  This function return the timer clock source.
  * @param  tim: timer instance
  * @retval 1 = PCLK1 or 2 = PCLK2 or 0 = unknown
  */
uint8_t getTimerClkSrc(TIM_TypeDef* tim)
{
  uint8_t clkSrc = 0;

  if(tim != (TIM_TypeDef *)NC)
#ifdef STM32F0xx
    /* TIMx source CLK is PCKL1 */
    clkSrc = 1;
#else
  {
    /* Get source clock depending on TIM instance */
    switch ((uint32_t)tim) {
#if defined(TIM2_BASE)
       case (uint32_t)TIM2:
#endif
#if defined(TIM3_BASE)
       case (uint32_t)TIM3:
#endif
#if defined(TIM4_BASE)
       case (uint32_t)TIM4:
#endif
#if defined(TIM5_BASE)
       case (uint32_t)TIM5:
#endif
#if defined(TIM6_BASE)
       case (uint32_t)TIM6:
#endif
#if defined(TIM7_BASE)
       case (uint32_t)TIM7:
#endif
#if defined(TIM12_BASE)
       case (uint32_t)TIM12:
#endif
#if defined(TIM13_BASE)
       case (uint32_t)TIM13:
#endif
#if defined(TIM14_BASE)
       case (uint32_t)TIM14:
#endif
#if defined(TIM18_BASE)
       case (uint32_t)TIM18:
#endif
         clkSrc = 1;
         break;
#if defined(TIM1_BASE)
       case (uint32_t)TIM1:
#endif
#if defined(TIM8_BASE)
       case (uint32_t)TIM8:
#endif
#if defined(TIM9_BASE)
       case (uint32_t)TIM9:
#endif
#if defined(TIM10_BASE)
       case (uint32_t)TIM10:
#endif
#if defined(TIM11_BASE)
       case (uint32_t)TIM11:
#endif
#if defined(TIM15_BASE)
       case (uint32_t)TIM15:
#endif
#if defined(TIM16_BASE)
       case (uint32_t)TIM16:
#endif
#if defined(TIM17_BASE)
       case (uint32_t)TIM17:
#endif
#if defined(TIM19_BASE)
       case (uint32_t)TIM19:
#endif
#if defined(TIM20_BASE)
       case (uint32_t)TIM20:
#endif
#if defined(TIM21_BASE)
       case (uint32_t)TIM21:
#endif
#if defined(TIM22_BASE)
       case (uint32_t)TIM22:
#endif
         clkSrc = 2;
         break;
     default:
        core_debug("TIM: Unknown timer instance");
        break;
    }
  }
#endif
  return clkSrc;
}

/**
  * @brief  This function return the timer clock frequency.
  * @param  tim: timer instance
  * @retval frequency in Hz
  */
uint32_t getTimerClkFreq(TIM_TypeDef* tim)
{
  RCC_ClkInitTypeDef    clkconfig = {};
  uint32_t              pFLatency = 0U;
  uint32_t              uwTimclock = 0U, uwAPBxPrescaler = 0U;

  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  switch(getTimerClkSrc(tim)) {
    case 1:
      uwAPBxPrescaler = clkconfig.APB1CLKDivider;
      uwTimclock = HAL_RCC_GetPCLK1Freq();
      break;
#ifndef STM32F0xx
    case 2:
      uwAPBxPrescaler = clkconfig.APB2CLKDivider;
      uwTimclock = HAL_RCC_GetPCLK2Freq();
      break;
#endif
    default:
    case 0:
      core_debug("TIM: Unknown clock source");
      break;
  }

#if defined(STM32H7xx)
/* When TIMPRE bit of the RCC_CFGR register is reset,
 *   if APBx prescaler is 1 or 2 then TIMxCLK = HCLK,
 *   otherwise TIMxCLK = 2x PCLKx.
 * When TIMPRE bit in the RCC_CFGR register is set,
 *   if APBx prescaler is 1,2 or 4, then TIMxCLK = HCLK,
 *   otherwise TIMxCLK = 4x PCLKx
 */
  RCC_PeriphCLKInitTypeDef PeriphClkConfig = {};
  HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkConfig);

  if (PeriphClkConfig.TIMPresSelection == RCC_TIMPRES_ACTIVATED) {
    switch (uwAPBxPrescaler) {
      default:
	  case RCC_APB1_DIV1:
      case RCC_APB1_DIV2:
      case RCC_APB1_DIV4:
	  /* case RCC_APB2_DIV1: */
      case RCC_APB2_DIV2:
      case RCC_APB2_DIV4:
        uwTimclock=HAL_RCC_GetHCLKFreq();
        break;
      case RCC_APB1_DIV8:
      case RCC_APB1_DIV16:
      case RCC_APB2_DIV8:
      case RCC_APB2_DIV16:
        uwTimclock*=4;
        break;
    }
  } else {
    switch (uwAPBxPrescaler) {
      default:
	  case RCC_APB1_DIV1:
      case RCC_APB1_DIV2:
	  /* case RCC_APB2_DIV1: */
      case RCC_APB2_DIV2:
        // uwTimclock*=1;
        uwTimclock=HAL_RCC_GetHCLKFreq();
        break;
      case RCC_APB1_DIV4:
      case RCC_APB1_DIV8:
      case RCC_APB1_DIV16:
      case RCC_APB2_DIV4:
      case RCC_APB2_DIV8:
      case RCC_APB2_DIV16:
        uwTimclock*=2;
        break;
    }
  }
#else
/* When TIMPRE bit of the RCC_DCKCFGR register is reset,
 *   if APBx prescaler is 1, then TIMxCLK = PCLKx,
 *   otherwise TIMxCLK = 2x PCLKx.
 * When TIMPRE bit in the RCC_DCKCFGR register is set,
 *   if APBx prescaler is 1,2 or 4, then TIMxCLK = HCLK,
 *   otherwise TIMxCLK = 4x PCLKx
 */
#if defined(STM32F4xx) || defined(STM32F7xx)
#if !defined(STM32F405xx) && !defined(STM32F415xx) &&\
    !defined(STM32F407xx) && !defined(STM32F417xx)
  RCC_PeriphCLKInitTypeDef PeriphClkConfig = {};
  HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkConfig);

  if (PeriphClkConfig.TIMPresSelection == RCC_TIMPRES_ACTIVATED)
    switch (uwAPBxPrescaler) {
      default:
      case RCC_HCLK_DIV1:
      case RCC_HCLK_DIV2:
      case RCC_HCLK_DIV4:
        uwTimclock=HAL_RCC_GetHCLKFreq();
        break;
      case RCC_HCLK_DIV8:
      case RCC_HCLK_DIV16:
        uwTimclock*=4;
        break;
    }
  else
#endif
#endif
    switch (uwAPBxPrescaler) {
      default:
      case RCC_HCLK_DIV1:
        // uwTimclock*=1;
        break;
      case RCC_HCLK_DIV2:
      case RCC_HCLK_DIV4:
      case RCC_HCLK_DIV8:
      case RCC_HCLK_DIV16:
        uwTimclock*=2;
        break;
    }
#endif /* STM32H7xx */
  return uwTimclock;
}

/**
  * @brief  This function will set the timer to generate pulse in interrupt mode with a particular duty cycle
  * @param  timer_id : timer_id_e
  * @param  period : timer period in microseconds
  * @param  pulseWidth : pulse width in microseconds
  * @param  irqHandle : interrupt routine to call
  * @retval None
  */
void TimerPulseInit(stimer_t *obj, uint16_t period, uint16_t pulseWidth, void (*irqHandle)(stimer_t*, uint32_t))
{
  TIM_OC_InitTypeDef sConfig = {};
  TIM_HandleTypeDef *handle = &(obj->handle);

  obj->timer = TIMER_SERVO;

  //min pulse = 1us - max pulse = 65535us
  handle->Instance               = obj->timer;
  handle->Init.Period            = period;
  handle->Init.Prescaler         = (uint32_t)(getTimerClkFreq(obj->timer) / (1000000)) - 1;
  handle->Init.ClockDivision     = 0;
  handle->Init.CounterMode       = TIM_COUNTERMODE_UP;
#if !defined(STM32L0xx) && !defined(STM32L1xx)
  handle->Init.RepetitionCounter = 0;
#endif
  obj->irqHandleOC = irqHandle;

  sConfig.OCMode        = TIM_OCMODE_TIMING;
  sConfig.Pulse         = pulseWidth;
  sConfig.OCPolarity    = TIM_OCPOLARITY_HIGH;
  sConfig.OCFastMode    = TIM_OCFAST_DISABLE;
#if !defined(STM32L0xx) && !defined(STM32L1xx)
  sConfig.OCNPolarity   = TIM_OCNPOLARITY_HIGH;
  sConfig.OCIdleState   = TIM_OCIDLESTATE_RESET;
  sConfig.OCNIdleState  = TIM_OCNIDLESTATE_RESET;
#endif
  HAL_NVIC_SetPriority(getTimerIrq(obj->timer), 14, 0);
  HAL_NVIC_EnableIRQ(getTimerIrq(obj->timer));

  if(HAL_TIM_OC_Init(handle) != HAL_OK) return;

  if(HAL_TIM_OC_ConfigChannel(handle, &sConfig, TIM_CHANNEL_1) != HAL_OK) return;
  if(HAL_TIM_OC_Start_IT(handle, TIM_CHANNEL_1) != HAL_OK) return;
}

/**
  * @brief  This function will reset the pulse generation
  * @param  timer_id : timer_id_e
  * @retval None
  */
void TimerPulseDeinit(stimer_t *obj)
{
  TIM_HandleTypeDef *handle = &(obj->handle);

  obj->irqHandleOC = NULL;

  HAL_NVIC_DisableIRQ(getTimerIrq(obj->timer));

  if(HAL_TIM_OC_DeInit(handle) != HAL_OK) return;
  if(HAL_TIM_OC_Stop_IT(handle, TIM_CHANNEL_1) != HAL_OK) return;
}

/**
  * @brief  Initializes the TIM Output Compare MSP.
  * @param  htim: TIM handle
  * @retval None
  */
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
  timer_enable_clock(htim);
}

/**
  * @brief  DeInitialize TIM Output Compare MSP.
  * @param  htim: TIM handle
  * @retval None
  */
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim)
{
  timer_disable_clock(htim);
}

/* Aim of the function is to get timer_s pointer using htim pointer */
/* Highly inspired from magical linux kernel's "container_of" */
/* (which was not directly used since not compatible with IAR toolchain) */
stimer_t *get_timer_obj(TIM_HandleTypeDef *htim){
    struct timer_s *obj_s;
    stimer_t *obj;

    obj_s = (struct timer_s *)( (char *)htim - offsetof(struct timer_s,handle));
    obj = (stimer_t *)( (char *)obj_s - offsetof(stimer_t,timer));

    return (obj);
}

/**
  * @brief  Output Compare callback in non-blocking mode
  * @param  htim : TIM OC handle
  * @retval None
  */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  uint32_t channel = 0;
  stimer_t *obj = get_timer_obj(htim);

  if(obj->irqHandleOC != NULL) {
    switch(htim->Channel) {
      case HAL_TIM_ACTIVE_CHANNEL_1:
        channel = TIM_CHANNEL_1 / 4;
      break;
      default:
        return;
      break;
    }
      obj->irqHandleOC(obj, channel);
  }
}

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  timer_id : id of the timer
  * @retval None
  */
void HAL_TIMx_PeriodElapsedCallback(stimer_t *obj)
{
  GPIO_TypeDef* port = get_GPIO_Port(STM_PORT(obj->pin));

  if(port != NULL) {
    if(obj->pinInfo.count != 0){
      if (obj->pinInfo.count > 0) obj->pinInfo.count--;
      obj->pinInfo.state = (obj->pinInfo.state == 0)? 1 : 0;
      digital_io_write(port, STM_LL_GPIO_PIN(obj->pin), obj->pinInfo.state);
    }
    else {
      digital_io_write(port, STM_LL_GPIO_PIN(obj->pin), 0);
    }
  }
}

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  stimer_t *obj = get_timer_obj(htim);

  if(obj->irqHandle != NULL) {
      obj->irqHandle(obj);
  }
}

/**
  * @brief  This function will set the tone timer to the required value and
  *         configure the pin to toggle.
  * @param  port : pointer to GPIO_TypeDef
  * @param  pin : pin number to toggle
  * @param  frequency : toggle frequency (in hertz)
  * @param  duration : toggle time
  * @retval None
  */
void TimerPinInit(stimer_t *obj, uint32_t frequency, uint32_t duration)
{
  uint8_t end = 0;
  uint32_t timClkFreq = 0;
  // TIMER_TONE freq is twice frequency
  uint32_t timFreq = 2*frequency;
  uint32_t prescaler = 1;
  uint32_t period = 0;
  uint32_t scale = 0;

  if(frequency > MAX_FREQ)
    return;

  obj->timer = TIMER_TONE;
  obj->pinInfo.state = 0;

  if(frequency == 0) {
    TimerPinDeinit(obj);
    return;
  }

  //Calculate the toggle count
  if (duration > 0) {
    obj->pinInfo.count = ((timFreq * duration) / 1000);
  }
  else {
    obj->pinInfo.count = -1;
  }

  pin_function(obj->pin, STM_PIN_DATA(STM_MODE_OUTPUT_PP, GPIO_NOPULL, 0));
  timClkFreq = getTimerClkFreq(obj->timer);

  // Do this once
  scale = timClkFreq / timFreq;
  while(end == 0) {
    period = ((uint32_t)( scale / prescaler)) - 1;

    if((period >= 0xFFFF) && (prescaler < 0xFFFF))
      prescaler++; //prescaler *= 2;

    else
      end = 1;
  }

  if((period < 0xFFFF) && (prescaler < 0xFFFF)) {
    obj->irqHandle = HAL_TIMx_PeriodElapsedCallback;
    TimerHandleInit(obj, period, prescaler-1);
  }
  else {
    TimerHandleDeinit(obj);
  }
}

/**
  * @brief  This function will reset the tone timer
  * @param  port : pointer to port
  * @param  pin : pin number to toggle
  * @retval None
  */
void TimerPinDeinit(stimer_t *obj)
{
  TimerHandleDeinit(obj);
  pin_function(obj->pin, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
}

/**
  * @brief  Get the counter value.
  * @param  timer_id : id of the timer
  * @retval Counter value
  */
uint32_t getTimerCounter(stimer_t *obj)
{
  return __HAL_TIM_GET_COUNTER(&(obj->handle));
}

/**
  * @brief  Set the counter value.
  * @param  timer_id : id of the timer
  * @param  value : counter value
  * @retval None
  */
void setTimerCounter(stimer_t *obj, uint32_t value)
{
  __HAL_TIM_SET_COUNTER(&(obj->handle), value);
}

/**
  * @brief  Set the TIM Capture Compare Register value.
  * @param  timer_id : id of the timer
  * @param  channel : TIM Channels to be configured.
  * @param  value : register new register.
  * @retval None
  */
void setCCRRegister(stimer_t *obj, uint32_t channel, uint32_t value)
{
  __HAL_TIM_SET_COMPARE(&(obj->handle), channel*4, value);
}

/**
  * @brief  Set the TIM Capture Compare Register value.
  * @param  timer_id : id of the timer
  * @param  channel : TIM Channels to be configured.
  * @retval CRR value.
  */
uint32_t getCCRRegister(stimer_t *obj, uint32_t channel)
{
  return __HAL_TIM_GET_COMPARE(&(obj->handle), channel);
}

/**
  * @brief  Attached an interrupt handler
  * @param  timer_id : id of the timer
  * @param  irqHandle : interrupt handler
  * @retval none
  */
void attachIntHandle(stimer_t *obj, void (*irqHandle)(stimer_t *))
{
  obj->irqHandle = irqHandle;
}


/******************************************************************************/
/*                            TIMx IRQ HANDLER                                */
/******************************************************************************/

#if defined(TIM1_BASE)
/**
  * @brief  TIM1 IRQHandler common with TIM10 and TIM16 on some STM32F1xx
  * @param  None
  * @retval None
  */
void TIM1_IRQHandler(void)
{
  if(timer_handles[0] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[0]);
  }

#if defined(STM32F1xx) || defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
#if defined (TIM10_BASE)
  if(timer_handles[9] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[9]);
  }
#endif
#endif

#if defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32L4xx)
#if defined (TIM16_BASE)
  if(timer_handles[15] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[15]);
  }
#endif
#endif
}
#endif //TIM1_BASE

#if defined(TIM2_BASE)
/**
  * @brief  TIM2 IRQHandler
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
  if(timer_handles[1] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[1]);
  }
}
#endif //TIM2_BASE

#if defined(TIM3_BASE)
/**
  * @brief  TIM3 IRQHandler
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
  if(timer_handles[2] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[2]);
  }
}
#endif //TIM3_BASE

#if defined(TIM4_BASE)
/**
  * @brief  TIM4 IRQHandler
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)
{
  if(timer_handles[3] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[3]);
  }
}
#endif //TIM4_BASE

#if defined(TIM5_BASE)
/**
  * @brief  TIM5 IRQHandler
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{
  if(timer_handles[4] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[4]);
  }
}
#endif //TIM5_BASE

#if defined(TIM6_BASE)
/**
  * @brief  TIM6 IRQHandler
  * @param  None
  * @retval None
  */
void TIM6_IRQHandler(void)
{
  if(timer_handles[5] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[5]);
  }
}
#endif //TIM6_BASE

#if defined(TIM7_BASE)
/**
  * @brief  TIM7 IRQHandler
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void)
{
  if(timer_handles[6] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[6]);
  }
}
#endif //TIM7_BASE

#if defined(TIM8_BASE)
/**
  * @brief  TIM8 IRQHandler
  * @param  None
  * @retval None
  */
void TIM8_IRQHandler(void)
{
  if(timer_handles[7] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[7]);
  }

#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
  if(timer_handles[12] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[12]);
  }
#endif
}
#endif //TIM8_BASE

#if defined(TIM9_BASE)
/**
  * @brief  TIM9 IRQHandler
  * @param  None
  * @retval None
  */
void TIM9_IRQHandler(void)
{
  if(timer_handles[8] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[8]);
  }
}
#endif //TIM9_BASE

#if defined(TIM10_BASE)
#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32F4xx) && !defined(STM32F7xx)
/**
  * @brief  TIM10 IRQHandler
  * @param  None
  * @retval None
  */
void TIM10_IRQHandler(void)
{
  if(timer_handles[9] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[9]);
  }
}
#endif
#endif //TIM10_BASE

#if defined(TIM11_BASE)
/**
  * @brief  TIM11 IRQHandler
  * @param  None
  * @retval None
  */
void TIM11_IRQHandler(void)
{
  if(timer_handles[10] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[10]);
  }
}
#endif //TIM11_BASE

#if defined(TIM12_BASE)
/**
  * @brief  TIM12 IRQHandler
  * @param  None
  * @retval None
  */
void TIM12_IRQHandler(void)
{
  if(timer_handles[11] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[11]);
  }
}
#endif //TIM12_BASE

#if defined(TIM13_BASE)
#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32F4xx) && !defined(STM32F7xx)
/**
  * @brief  TIM13 IRQHandler
  * @param  None
  * @retval None
  */
void TIM13_IRQHandler(void)
{
  if(timer_handles[12] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[12]);
  }
}
#endif
#endif //TIM13_BASE

#if defined(TIM14_BASE)
/**
  * @brief  TIM14 IRQHandler
  * @param  None
  * @retval None
  */
void TIM14_IRQHandler(void)
{
  if(timer_handles[13] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[13]);
  }
}
#endif //TIM14_BASE

#if defined(TIM15_BASE)
/**
  * @brief  TIM15 IRQHandler
  * @param  None
  * @retval None
  */
void TIM15_IRQHandler(void)
{
  if(timer_handles[14] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[14]);
  }
}
#endif //TIM15_BASE

#if defined(TIM16_BASE)
#if !defined(STM32F1xx) && !defined(STM32F3xx) && !defined(STM32L4xx)
/**
  * @brief  TIM16 IRQHandler
  * @param  None
  * @retval None
  */
void TIM16_IRQHandler(void)
{
  if(timer_handles[15] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[15]);
  }
}
#endif
#endif //TIM16_BASE

#if defined(TIM17_BASE)
/**
  * @brief  TIM17 IRQHandler
  * @param  None
  * @retval None
  */
void TIM17_IRQHandler(void)
{
  if(timer_handles[16] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[16]);
  }
}
#endif //TIM17_BASE

#if defined(TIM18_BASE)
/**
  * @brief  TIM18 IRQHandler
  * @param  None
  * @retval None
  */
void TIM18_IRQHandler(void)
{
  if(timer_handles[17] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[17]);
  }
}
#endif //TIM18_BASE

#if defined(TIM19_BASE)
/**
  * @brief  TIM19 IRQHandler
  * @param  None
  * @retval None
  */
void TIM19_IRQHandler(void)
{
  if(timer_handles[18] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[18]);
  }
}
#endif //TIM19_BASE

#if defined(TIM20_BASE)
/**
  * @brief  TIM20 IRQHandler
  * @param  None
  * @retval None
  */
void TIM20_IRQHandler(void)
{
  if(timer_handles[19] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[19]);
  }
}
#endif //TIM20_BASE

#if defined(TIM21_BASE)
/**
  * @brief  TIM21 IRQHandler
  * @param  None
  * @retval None
  */
void TIM21_IRQHandler(void)
{
  if(timer_handles[20] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[20]);
  }
}
#endif //TIM21_BASE

#if defined(TIM22_BASE)
/**
  * @brief  TIM22 IRQHandler
  * @param  None
  * @retval None
  */
void TIM22_IRQHandler(void)
{
  if(timer_handles[21] != NULL) {
    HAL_TIM_IRQHandler(timer_handles[21]);
  }
}
#endif //TIM22_BASE

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
