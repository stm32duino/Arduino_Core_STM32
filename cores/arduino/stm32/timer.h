/**
  ******************************************************************************
  * @file    timer.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   Header for timer module
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
#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#include "PeripheralPins.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
#define OFFSETOF(type, member) ((uint32_t) (&(((type *)(0))->member)))

typedef struct{
  int32_t count;
  uint8_t state;
}timerPinInfo_t;

typedef struct timer_s stimer_t;

struct timer_s{
  /*  The 1st 2 members TIM_TypeDef *timer
     *  and TIM_HandleTypeDef handle should
     *  be kept as the first members of this struct
     *  to have get_timer_obj() function work as expected
     */
  TIM_TypeDef *timer;
  TIM_HandleTypeDef handle;
  uint8_t idx;
  void (*irqHandle)(stimer_t *);
  void (*irqHandleOC)(stimer_t *, uint32_t);
  PinName pin;
  volatile timerPinInfo_t pinInfo;
};

/* Exported constants --------------------------------------------------------*/
#define MAX_FREQ  65535

#if defined(TIM1_BASE) && !defined(TIM1_IRQn)
#if defined(STM32F0xx)
#define TIM1_IRQn TIM1_BRK_UP_TRG_COM_IRQn
#elif defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32L4xx)
#define TIM1_IRQn TIM1_UP_TIM16_IRQn
#elif defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
#define TIM1_IRQn TIM1_UP_TIM10_IRQn
#endif
#endif
#if defined(TIM6_BASE) && !defined(TIM6_IRQn)
#if !defined(STM32F1xx) && !defined(STM32L1xx)
#define TIM6_IRQn TIM6_DAC_IRQn
#endif
#endif
#if defined(TIM8_BASE) && !defined(TIM8_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
#define TIM8_IRQn TIM8_UP_TIM13_IRQn
#elif  defined(STM32F3xx) || defined(STM32L4xx)
#define TIM8_IRQn TIM8_UP_IRQn
#endif
#endif
#if defined(TIM9_BASE) && !defined(TIM9_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
#define TIM9_IRQn TIM1_BRK_TIM9_IRQn
#endif
#endif
#if defined(TIM10_BASE) && !defined(TIM10_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
#define TIM10_IRQn TIM1_UP_TIM10_IRQn
#endif
#endif
#if defined(TIM11_BASE) && !defined(TIM11_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
#define TIM11_IRQn TIM1_TRG_COM_TIM11_IRQn
#endif
#endif
#if defined(TIM12_BASE) && !defined(TIM12_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
#define TIM12_IRQn TIM8_BRK_TIM12_IRQn
#endif
#endif
#if defined(TIM13_BASE) && !defined(TIM13_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
#define TIM13_IRQn TIM8_UP_TIM13_IRQn
#endif
#endif
#if defined(TIM14_BASE) && !defined(TIM14_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
#define TIM14_IRQn TIM8_TRG_COM_TIM14_IRQn
#endif
#endif
#if defined(TIM15_BASE) && !defined(TIM15_IRQn)
#if defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32L4xx)
#define TIM15_IRQn TIM1_BRK_TIM15_IRQn
#endif
#endif
#if defined(TIM16_BASE) && !defined(TIM16_IRQn)
#if defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32L4xx)
#define TIM16_IRQn TIM1_UP_TIM16_IRQn
#endif
#endif
#if defined(TIM17_BASE) && !defined(TIM17_IRQn)
#if defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32L4xx)
#define TIM17_IRQn TIM1_TRG_COM_TIM17_IRQn
#endif
#endif
#if defined(TIM18_BASE) && !defined(TIM18_IRQn)
#if defined(STM32F3xx)
#define TIM18_IRQn TIM18_DAC2_IRQn
#endif
#endif
#if defined(TIM20_BASE) && !defined(TIM20_IRQn)
#if defined(STM32F3xx)
#define TIM20_IRQn TIM20_UP_IRQn
#endif
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void timer_enable_clock(TIM_HandleTypeDef *htim);
void timer_disable_clock(TIM_HandleTypeDef *htim);

void TimerHandleInit(stimer_t *obj, uint16_t period, uint16_t prescaler);
void TimerHandleDeinit(stimer_t *obj);

void TimerPinInit(stimer_t *obj, uint32_t frequency, uint32_t duration);
void TimerPinDeinit(stimer_t *obj);

void TimerPulseInit(stimer_t *obj, uint16_t period, uint16_t pulseWidth, void (*irqHandle)(stimer_t *, uint32_t));
void TimerPulseDeinit(stimer_t *obj);

uint32_t getTimerCounter(stimer_t *obj);
void setTimerCounter(stimer_t *obj, uint32_t value);
void setCCRRegister(stimer_t *obj, uint32_t channel, uint32_t value);
uint32_t getCCRRegister(stimer_t *obj, uint32_t channel);

uint32_t getTimerIrq(TIM_TypeDef* tim);
uint8_t getTimerClkSrc(TIM_TypeDef* tim);
uint32_t getTimerClkFreq(TIM_TypeDef* tim);

void attachIntHandle(stimer_t *obj, void (*irqHandle)(stimer_t *));

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
