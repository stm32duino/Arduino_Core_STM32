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
  timerPinInfo_t pinInfo;
};

/* Exported constants --------------------------------------------------------*/
#define MAX_FREQ  65535

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

void attachIntHandle(stimer_t *obj, void (*irqHandle)(stimer_t *));

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
