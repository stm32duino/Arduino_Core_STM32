/*
 *******************************************************************************
 * Copyright (c) 2019, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"
#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif
#if defined(HAL_TIM_MODULE_ENABLED) && !defined(HAL_TIM_MODULE_ONLY)

/* Exported constants --------------------------------------------------------*/
#ifndef TIM_IRQ_PRIO
#if (__CORTEX_M == 0x00U)
#define TIM_IRQ_PRIO       3
#else
#define TIM_IRQ_PRIO       14
#endif /* __CORTEX_M */
#endif /* TIM_IRQ_PRIO */
#ifndef TIM_IRQ_SUBPRIO
#define TIM_IRQ_SUBPRIO    0
#endif

#if defined(TIM1_BASE) && !defined(TIM1_IRQn)
#if defined(STM32F0xx) || defined(STM32G0xx)
#define TIM1_IRQn TIM1_BRK_UP_TRG_COM_IRQn
#define TIM1_IRQHandler TIM1_BRK_UP_TRG_COM_IRQHandler
#elif defined(STM32F1xx) ||defined(STM32G4xx)
#define TIM1_IRQn TIM1_UP_TIM16_IRQn
#if !defined (TIM10_BASE)
#define TIM1_IRQHandler TIM1_UP_TIM16_IRQHandler
#elif defined (TIM10_BASE)
#define TIM1_IRQHandler TIM1_UP_TIM10_IRQHandler
#endif
#elif defined(STM32F3xx) || defined(STM32L4xx) || defined(STM32WBxx)
#define TIM1_IRQn TIM1_UP_TIM16_IRQn
#define TIM1_IRQHandler TIM1_UP_TIM16_IRQHandler
#elif defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
#if !defined (TIM10_BASE)
#define TIM1_IRQn TIM1_UP_IRQn
#define TIM1_IRQHandler TIM1_UP_IRQHandler
#else
#define TIM1_IRQn TIM1_UP_TIM10_IRQn
#define TIM1_IRQHandler TIM1_UP_TIM10_IRQHandler
#endif
#elif defined(STM32H7xx) || defined(STM32MP1xx)
#define TIM1_IRQn TIM1_UP_IRQn
#define TIM1_IRQHandler TIM1_UP_IRQHandler
#endif
#endif
#if defined(TIM6_BASE) && !defined(TIM6_IRQn)
#if defined(DAC_BASE) || defined(DAC1_BASE)
#if defined(STM32G0xx)
#define TIM6_IRQn TIM6_DAC_LPTIM1_IRQn
#define TIM6_IRQHandler TIM6_DAC_LPTIM1_IRQHandler
#elif !defined(STM32F1xx) && !defined(STM32L1xx) && !defined(STM32MP1xx)
#define TIM6_IRQn TIM6_DAC_IRQn
#define TIM6_IRQHandler TIM6_DAC_IRQHandler
#endif
#endif
#endif
#if defined(TIM7_BASE) && !defined(TIM7_IRQn)
#if defined(STM32G0xx)
#define TIM7_IRQn TIM7_LPTIM2_IRQn
#define TIM7_IRQHandler TIM7_LPTIM2_IRQHandler
#elif defined(STM32G4xx)
#define TIM7_IRQn TIM7_DAC_IRQn
#define TIM7_IRQHandler TIM7_DAC_IRQHandler
#endif
#endif

#if defined(TIM8_BASE) && !defined(TIM8_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)\
 || defined(STM32H7xx)
#define TIM8_IRQn TIM8_UP_TIM13_IRQn
#define TIM8_IRQHandler TIM8_UP_TIM13_IRQHandler
#elif  defined(STM32F3xx) || defined(STM32G4xx) || defined(STM32L4xx) || defined(STM32MP1xx)
#define TIM8_IRQn TIM8_UP_IRQn
#define TIM8_IRQHandler TIM8_UP_IRQHandler
#endif
#endif
#if defined(TIM9_BASE) && !defined(TIM9_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
#define TIM9_IRQn TIM1_BRK_TIM9_IRQn
#define TIM9_IRQHandler TIM1_BRK_TIM9_IRQHandler
#endif
#endif
#if defined(TIM10_BASE) && !defined(TIM10_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
#define TIM10_IRQn TIM1_UP_TIM10_IRQn
//TIM10_IRQHandler is mapped on TIM1_IRQHandler  when TIM10_IRQn is not defined
#endif
#endif
#if defined(TIM11_BASE) && !defined(TIM11_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)
#define TIM11_IRQn TIM1_TRG_COM_TIM11_IRQn
#define TIM11_IRQHandler TIM1_TRG_COM_TIM11_IRQHandler
#endif
#endif
#if defined(TIM12_BASE) && !defined(TIM12_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)\
 || defined(STM32H7xx)
#define TIM12_IRQn TIM8_BRK_TIM12_IRQn
#define TIM12_IRQHandler TIM8_BRK_TIM12_IRQHandler
#endif
#endif
#if defined(TIM13_BASE) && !defined(TIM13_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)\
 || defined(STM32H7xx)
#define TIM13_IRQn TIM8_UP_TIM13_IRQn
#endif
#endif
#if defined(TIM14_BASE) && !defined(TIM14_IRQn)
#if defined(STM32F1xx) || defined(STM32F2xx) ||defined(STM32F4xx) || defined(STM32F7xx)\
 || defined(STM32H7xx)
#define TIM14_IRQn TIM8_TRG_COM_TIM14_IRQn
#define TIM14_IRQHandler TIM8_TRG_COM_TIM14_IRQHandler
#endif
#endif
#if defined(TIM15_BASE) && !defined(TIM15_IRQn)
#if defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32G4xx) || defined(STM32L4xx)
#define TIM15_IRQn TIM1_BRK_TIM15_IRQn
#define TIM15_IRQHandler TIM1_BRK_TIM15_IRQHandler
#endif
#endif
#if defined(TIM16_BASE) && !defined(TIM16_IRQn)
#if defined(STM32F1xx) || defined(STM32F3xx)  || defined(STM32G4xx) || defined(STM32L4xx) || \
    defined(STM32WBxx)
#define TIM16_IRQn TIM1_UP_TIM16_IRQn
//TIM16_IRQHandler is mapped on TIM1_IRQHandler when TIM16_IRQn is not defined
#endif
#endif
#if defined(TIM17_BASE) && !defined(TIM17_IRQn)
#if defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32G4xx) || defined(STM32L4xx) || \
    defined(STM32WBxx)
#define TIM17_IRQn TIM1_TRG_COM_TIM17_IRQn
#define TIM17_IRQHandler TIM1_TRG_COM_TIM17_IRQHandler
#endif
#endif
#if defined(TIM18_BASE) && !defined(TIM18_IRQn)
#if defined(STM32F3xx)
#define TIM18_IRQn TIM18_DAC2_IRQn
#define TIM18_IRQHandler TIM18_DAC2_IRQHandler
#endif
#endif
#if defined(TIM20_BASE) && !defined(TIM20_IRQn)
#if defined(STM32F3xx) || defined(STM32G4xx)
#define TIM20_IRQn TIM20_UP_IRQn
#define TIM20_IRQHandler TIM20_UP_IRQHandler
#endif
#endif

typedef enum {
#if defined(TIM1_BASE)
  TIMER1_INDEX,
#endif
#if defined(TIM2_BASE)
  TIMER2_INDEX,
#endif
#if defined(TIM3_BASE)
  TIMER3_INDEX,
#endif
#if defined(TIM4_BASE)
  TIMER4_INDEX,
#endif
#if defined(TIM5_BASE)
  TIMER5_INDEX,
#endif
#if defined(TIM6_BASE)
  TIMER6_INDEX,
#endif
#if defined(TIM7_BASE)
  TIMER7_INDEX,
#endif
#if defined(TIM8_BASE)
  TIMER8_INDEX,
#endif
#if defined(TIM9_BASE)
  TIMER9_INDEX,
#endif
#if defined(TIM10_BASE)
  TIMER10_INDEX,
#endif
#if defined(TIM11_BASE)
  TIMER11_INDEX,
#endif
#if defined(TIM12_BASE)
  TIMER12_INDEX,
#endif
#if defined(TIM13_BASE)
  TIMER13_INDEX,
#endif
#if defined(TIM14_BASE)
  TIMER14_INDEX,
#endif
#if defined(TIM15_BASE)
  TIMER15_INDEX,
#endif
#if defined(TIM16_BASE)
  TIMER16_INDEX,
#endif
#if defined(TIM17_BASE)
  TIMER17_INDEX,
#endif
#if defined(TIM18_BASE)
  TIMER18_INDEX,
#endif
#if defined(TIM19_BASE)
  TIMER19_INDEX,
#endif
#if defined(TIM20_BASE)
  TIMER20_INDEX,
#endif
#if defined(TIM21_BASE)
  TIMER21_INDEX,
#endif
#if defined(TIM22_BASE)
  TIMER22_INDEX,
#endif
  TIMER_NUM,
  UNKNOWN_TIMER = 0XFFFF
} timer_index_t;


// This structure is used to be able to get HardwareTimer instance (C++ class)
// from handler (C structure) specially for interrupt management
typedef struct  {
  // Those 2 first fields must remain in this order at the beginning of the structure
  void    *__this;
  TIM_HandleTypeDef handle;
  uint32_t preemptPriority;
  uint32_t subPriority;
} timerObj_t;

/* Exported functions ------------------------------------------------------- */
timerObj_t *get_timer_obj(TIM_HandleTypeDef *htim);

void enableTimerClock(TIM_HandleTypeDef *htim);
void disableTimerClock(TIM_HandleTypeDef *htim);

uint32_t getTimerIrq(TIM_TypeDef *tim);
uint8_t getTimerClkSrc(TIM_TypeDef *tim);

IRQn_Type getTimerUpIrq(TIM_TypeDef *tim);
IRQn_Type getTimerCCIrq(TIM_TypeDef *tim);

#endif /* HAL_TIM_MODULE_ENABLED && !HAL_TIM_MODULE_ONLY */

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
