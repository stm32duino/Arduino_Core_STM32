/**
  ******************************************************************************
  * @file    rtc.h
  * @author  Frederic Pillon
  * @brief   Header for RTC driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 STMicroelectronics</center></h2>
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
  MODE_BINARY_NONE, /* BCD only */
  MODE_BINARY_ONLY,
  MODE_BINARY_MIX
} binaryMode_t;

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
  Y_MSK   = 32,
  SUBSEC_MSK = 48,
  ALL_MSK = 0xFF
} alarmMask_t;

typedef enum {
  ALARM_A = RTC_ALARM_A,
#ifdef RTC_ALARM_B
  ALARM_B = RTC_ALARM_B
#endif
} alarm_t;

typedef void(*voidCallbackPtr)(void *);

/* Exported constants --------------------------------------------------------*/

#if defined(STM32F1xx)
/* select 32 bits in backup memory to store date.
   2 consecutive 16bit reg. are reserved: RTC_BKP_DATE & RTC_BKP_DATE + 1 */
#if !defined(RTC_BKP_DATE)
/* can be changed for your convenience (here : LL_RTC_BKP_DR6 & LL_RTC_BKP_DR7) */
#define RTC_BKP_DATE LL_RTC_BKP_DR6
#endif
#endif /* STM32F1xx */

/* Interrupt priority */
#ifndef RTC_IRQ_PRIO
#define RTC_IRQ_PRIO       2
#endif
#ifndef RTC_IRQ_SUBPRIO
#define RTC_IRQ_SUBPRIO    0
#endif
#ifndef RTC_IRQ_SSRU_PRIO
#define RTC_IRQ_SSRU_PRIO     0
#endif
#ifndef RTC_IRQ_SSRU_SUBPRIO
#define RTC_IRQ_SSRU_SUBPRIO  0
#endif
#define HSE_RTC_MAX 1000000U

#if !defined(STM32F1xx)
#if !defined(RTC_PRER_PREDIV_S) || !defined(RTC_PRER_PREDIV_S)
#error "Unknown Family - unknown synchronous prescaler"
#endif
#define PREDIVA_MAX (RTC_PRER_PREDIV_A >> RTC_PRER_PREDIV_A_Pos)
#define PREDIVS_MAX (RTC_PRER_PREDIV_S >> RTC_PRER_PREDIV_S_Pos)
#else
/* for stm32F1 the MAX value is combining PREDIV low & high registers */
#define PREDIVA_MAX 0xFFFFFU
#define PREDIVS_MAX 0xFFFFFFFFU /* Unused for STM32F1xx series */
#endif /* !STM32F1xx */

#if defined(STM32C0xx) || defined(STM32F0xx) || defined(STM32H5xx) || \
    defined(STM32L0xx) || defined(STM32L5xx) || defined(STM32U5xx) || \
    defined(STM32WBAxx)
#define RTC_Alarm_IRQn RTC_IRQn
#define RTC_Alarm_IRQHandler RTC_IRQHandler
#endif
#if defined(STM32G0xx)
#define RTC_Alarm_IRQn RTC_TAMP_IRQn
#define RTC_Alarm_IRQHandler RTC_TAMP_IRQHandler
#endif

/* mapping the IRQn for the one-second interrupt depending on the soc */
#if defined(STM32F1xx) || (defined(STM32F0xx) && defined(RTC_CR_WUTE)) || \
    defined(STM32H5xx) || defined(STM32L0xx) || defined(STM32L5xx) || \
    defined(STM32U5xx) || defined(STM32WBAxx)
// specific WakeUp interrupt
#define ONESECOND_IRQn RTC_IRQn
#elif defined(STM32MP1xx)
// global RTC interrupt
#define ONESECOND_IRQn RTC_WKUP_ALARM_IRQn
#elif defined(STM32G0xx)
// global RTC/TAMP interrupt
#define ONESECOND_IRQn RTC_TAMP_IRQn
#elif defined(CORE_CM0PLUS) && \
      (defined(STM32WL54xx) || defined(STM32WL55xx) || defined(STM32WL5Mxx))
// global RTC/LSS interrupt
#define ONESECOND_IRQn RTC_LSECSS_IRQn
#elif defined(RTC_CR_WUTE)
// specific WakeUp interrupt (including M4 cpu of the STM32WLE5xx)
#define ONESECOND_IRQn RTC_WKUP_IRQn
#else
// no One-Second IRQ available for the series
#endif /* STM32F1xx || etc */

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

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
RTC_HandleTypeDef *RTC_GetHandle(void);
void RTC_SetClockSource(sourceClock_t source);
void RTC_getPrediv(uint32_t *asynch, uint32_t *synch);
void RTC_setPrediv(uint32_t asynch, uint32_t synch);

bool RTC_init(hourFormat_t format, binaryMode_t mode, sourceClock_t source, bool reset);
void RTC_DeInit(bool reset_cb);
bool RTC_IsConfigured(void);

void RTC_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, hourAM_PM_t period);
void RTC_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint32_t *subSeconds, hourAM_PM_t *period);

void RTC_SetDate(uint8_t year, uint8_t month, uint8_t day, uint8_t wday);
void RTC_GetDate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *wday);

void RTC_StartAlarm(alarm_t name, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, hourAM_PM_t period, uint8_t mask);
void RTC_StartAlarm64(alarm_t name, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds, uint64_t subSeconds, hourAM_PM_t period, uint8_t mask);
void RTC_StopAlarm(alarm_t name);
bool RTC_IsAlarmSet(alarm_t name);
void RTC_GetAlarm(alarm_t name, uint8_t *day, uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint32_t *subSeconds, hourAM_PM_t *period, uint8_t *mask);
void attachAlarmCallback(voidCallbackPtr func, void *data, alarm_t name);
void detachAlarmCallback(alarm_t name);
#ifdef ONESECOND_IRQn
void attachSecondsIrqCallback(voidCallbackPtr func);
void detachSecondsIrqCallback(void);
#endif /* ONESECOND_IRQn */
#ifdef STM32WLxx
void attachSubSecondsUnderflowIrqCallback(voidCallbackPtr func);
void detachSubSecondsUnderflowIrqCallback(void);
#endif /* STM32WLxx */
#if defined(STM32F1xx)
void RTC_StoreDate(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* HAL_RTC_MODULE_ENABLED  && !HAL_RTC_MODULE_ONLY */

#endif /* __RTC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
