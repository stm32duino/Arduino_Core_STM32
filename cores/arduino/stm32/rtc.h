/**
  ******************************************************************************
  * @file    rtc.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    12-December-2017
  * @brief   Header for RTC driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
#ifndef __RTC_H
#define __RTC_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stm32_def.h"
#include "backup.h"
#include "clock.h"

#if defined(HAL_RTC_MODULE_ENABLED) && !defined(HAL_RTC_MODULE_ONLY)

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef enum {
  HOUR_FORMAT_12,
  HOUR_FORMAT_24
} hourFormat_t;

typedef enum {
  HOUR_AM,
  HOUR_PM
} hourAM_PM_t;

/* See AN4579 Table 5 for possible values */
typedef enum {
  OFF_MSK = 0,
  SS_MSK  = 1, /* MSK0 */
  MM_MSK  = 2, /* MSK1 */
  HH_MSK  = 4, /* MSK2 */
  D_MSK   = 8, /* MSK3 */
  /* NOTE: STM32 RTC can't assign a month or a year to an alarm. Those enum
  are kept for compatibility but are ignored inside enableAlarm(). */
  M_MSK   = 16,
  Y_MSK   = 32
} alarmMask_t;

typedef void(*voidCallbackPtr)(void *);

/* Exported constants --------------------------------------------------------*/
/* Interrupt priority */
#ifndef RTC_IRQ_PRIO
#define RTC_IRQ_PRIO       2
#endif
#ifndef RTC_IRQ_SUBPRIO
#define RTC_IRQ_SUBPRIO    0
#endif


#define HSE_RTC_MAX 1000000U

#if !defined(STM32F1xx)
#if !defined(RTC_PRER_PREDIV_S) || !defined(RTC_PRER_PREDIV_S)
#error "Unknown Family - unknown synchronous prescaler"
#endif
#define PREDIVA_MAX (RTC_PRER_PREDIV_A >> RTC_PRER_PREDIV_A_Pos)
#define PREDIVS_MAX (RTC_PRER_PREDIV_S >> RTC_PRER_PREDIV_S_Pos)
#endif /* !STM32F1xx */

/* Ultra Low Power High (ULPH) density */
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) ||\
    defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) ||\
    defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) ||\
    defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) ||\
    defined (STM32L162xD) || defined(STM32L151xE) || defined(STM32L151xDX) ||\
    defined (STM32L152xE) || defined (STM32L152xDX) || defined (STM32L162xE) ||\
    defined (STM32L162xDX)
#define STM32L1_ULPH
#endif

#if defined(STM32F0xx) || defined(STM32L0xx)
#define RTC_Alarm_IRQn RTC_IRQn
#define RTC_Alarm_IRQHandler RTC_IRQHandler
#endif
#if defined(STM32G0xx)
#define RTC_Alarm_IRQn RTC_TAMP_IRQn
#define RTC_Alarm_IRQHandler RTC_TAMP_IRQHandler
#endif

#if defined(STM32F1xx) && !defined(IS_RTC_WEEKDAY)
/* Compensate missing HAL definition */
#define IS_RTC_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_WEEKDAY_MONDAY)    || \
                                 ((WEEKDAY) == RTC_WEEKDAY_TUESDAY)   || \
                                 ((WEEKDAY) == RTC_WEEKDAY_WEDNESDAY) || \
                                 ((WEEKDAY) == RTC_WEEKDAY_THURSDAY)  || \
                                 ((WEEKDAY) == RTC_WEEKDAY_FRIDAY)    || \
                                 ((WEEKDAY) == RTC_WEEKDAY_SATURDAY)  || \
                                 ((WEEKDAY) == RTC_WEEKDAY_SUNDAY))

/* F1 doesn't manage 12h format */
#define IS_RTC_HOUR12(HOUR)      IS_RTC_HOUR24(HOUR)
#endif /* !STM32F1xx && !IS_RTC_WEEKDAY */

/* __HAL_RCC_GET_RTC_SOURCE is not defined for F2*/
/*
#ifndef __HAL_RCC_GET_RTC_SOURCE
static uint32_t RTC_getSource(void) {
  RCC_PeriphCLKInitTypeDef  *PeriphClkInit;
  HAL_RCCEx_GetPeriphCLKConfig(PeriphClkInit);
  return PeriphClkInit->RTCClockSelection;
}
#define __HAL_RCC_GET_RTC_SOURCE()  RTC_getSource()
#endif
*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RTC_SetClockSource(sourceClock_t source);

void RTC_getPrediv(int8_t *asynch, int16_t *synch);
void RTC_setPrediv(int8_t asynch, int16_t synch);

void RTC_init(hourFormat_t format, sourceClock_t source, bool reset);
void RTC_DeInit(void);
bool RTC_IsTimeSet(void);

void RTC_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, hourAM_PM_t period);
void RTC_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint32_t *subSeconds, hourAM_PM_t *period);

void RTC_SetDate(uint8_t year, uint8_t month, uint8_t day, uint8_t wday);
void RTC_GetDate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *wday);

void RTC_StartAlarm(uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, hourAM_PM_t period, uint8_t mask);
void RTC_StopAlarm(void);
void RTC_GetAlarm(uint8_t *day, uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint32_t *subSeconds, hourAM_PM_t *period, uint8_t *mask);
void attachAlarmCallback(voidCallbackPtr func, void *data);
void detachAlarmCallback(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_RTC_MODULE_ENABLED  && !HAL_RTC_MODULE_ONLY */

#endif /* __RTC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
