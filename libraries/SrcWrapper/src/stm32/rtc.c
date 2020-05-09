/**
  ******************************************************************************
  * @file    rtc.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    12-December-2017
  * @brief   Provides a RTC driver
  *
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

#include "rtc.h"

#if defined(HAL_RTC_MODULE_ENABLED) && !defined(HAL_RTC_MODULE_ONLY)
#if defined(STM32MP1xx)
  /**
  * Currently there is no RTC driver for STM32MP1xx. If RTC is used in the future
  * the function call HAL_RCCEx_PeriphCLKConfig() shall be done under
  * if(IS_ENGINEERING_BOOT_MODE()), since clock source selection is done by
  * First Stage Boot Loader on Cortex-A.
  */
  #error "RTC shall not be handled by Arduino in STM32MP1xx."
#endif /* STM32MP1xx */

#ifdef __cplusplus
extern "C" {
#endif

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static RTC_HandleTypeDef RtcHandle = {0};
static voidCallbackPtr RTCUserCallback = NULL;
static void *callbackUserData = NULL;

static sourceClock_t clkSrc = LSI_CLOCK;
static uint8_t HSEDiv = 0;
#if !defined(STM32F1xx)
/* Custom user values */
static int8_t userPredivAsync = -1;
static int16_t userPredivSync = -1;
#endif /* !STM32F1xx */

static hourFormat_t initFormat = HOUR_FORMAT_12;

/* Private function prototypes -----------------------------------------------*/
static void RTC_initClock(sourceClock_t source);
#if !defined(STM32F1xx)
static void RTC_computePrediv(int8_t *asynch, int16_t *synch);
#endif /* !STM32F1xx */

/* Exported functions --------------------------------------------------------*/

/**
  * @brief Set RTC clock source
  * @param source: RTC clock source: LSE, LSI or HSE
  * @retval None
  */
void RTC_SetClockSource(sourceClock_t source)
{
  switch (source) {
    case LSI_CLOCK:
    case LSE_CLOCK:
    case HSE_CLOCK:
      clkSrc = source;
      break;
    default:
      clkSrc = LSI_CLOCK;
      break;
  }
}

/**
  * @brief RTC clock initialization
  *        This function configures the hardware resources used.
  * @param source: RTC clock source: LSE, LSI or HSE
  * @note  Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select
  *        the RTC clock source; in this case the Backup domain will be reset in
  *        order to modify the RTC Clock source, as consequence RTC registers (including
  *        the backup registers) and RCC_CSR register are set to their reset values.
  * @retval None
  */
static void RTC_initClock(sourceClock_t source)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  if (source == LSE_CLOCK) {
    /* Enable the clock if not already set by user */
    enableClock(LSE_CLOCK);

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
      Error_Handler();
    }
    clkSrc = LSE_CLOCK;
  } else if (source == HSE_CLOCK) {
    /* Enable the clock if not already set by user */
    enableClock(HSE_CLOCK);

    /* HSE division factor for RTC clock must be set to ensure that
     * the clock supplied to the RTC is less than or equal to 1 MHz
     */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
#if defined(STM32F1xx)
    /* HSE max is 16 MHZ divided by 128 --> 125 KHz */
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV128;
    HSEDiv = 128;
#elif defined(STM32F0xx) || defined(STM32F3xx) || defined(STM32G0xx) ||\
      defined(STM32G4xx) || defined(STM32L4xx) || defined(STM32WBxx)
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV32;
    HSEDiv = 32;
#elif defined(STM32L0xx) || defined(STM32L1xx)
    if ((HSE_VALUE / 2) <= HSE_RTC_MAX) {
      PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV2;
      HSEDiv = 2;
    } else if ((HSE_VALUE / 4) <= HSE_RTC_MAX) {
      PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV4;
      HSEDiv = 4;
    } else if ((HSE_VALUE / 8) <= HSE_RTC_MAX) {
      PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV8;
      HSEDiv = 8;
    } else if ((HSE_VALUE / 16) <= HSE_RTC_MAX) {
      PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV16;
      HSEDiv = 16;
    }
#elif defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx) || defined(STM32H7xx)
    /* Not defined for STM32F2xx */
#ifndef RCC_RTCCLKSOURCE_HSE_DIVX
#define RCC_RTCCLKSOURCE_HSE_DIVX 0x00000300U
#endif /* RCC_RTCCLKSOURCE_HSE_DIVX */
#if defined(STM32H7xx)
#define HSEDIV_MAX 64
#define HSESHIFT 12
#else
#define HSEDIV_MAX 32
#define HSESHIFT 16
#endif
    for (HSEDiv = 2; HSEDiv < HSEDIV_MAX; HSEDiv++) {
      if ((HSE_VALUE / HSEDiv) <= HSE_RTC_MAX) {
        PeriphClkInit.RTCClockSelection = (HSEDiv << HSESHIFT) | RCC_RTCCLKSOURCE_HSE_DIVX;
        break;
      }
    }
#else
#error "Unknown Family - could not define RTCClockSelection"
#endif /* STM32F1xx */
    if ((HSE_VALUE / HSEDiv) > HSE_RTC_MAX) {
      Error_Handler();
    }

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
      Error_Handler();
    }
    clkSrc = HSE_CLOCK;
  } else if (source == LSI_CLOCK) {
    /* Enable the clock if not already set by user */
    enableClock(LSI_CLOCK);

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
      Error_Handler();
    }
    clkSrc = LSI_CLOCK;
  } else {
    Error_Handler();
  }
#ifdef __HAL_RCC_RTCAPB_CLK_ENABLE
  __HAL_RCC_RTCAPB_CLK_ENABLE();
#endif
  __HAL_RCC_RTC_ENABLE();
}

/**
  * @brief set user (a)synchronous prescaler values.
  * @note  use -1 to reset value and use computed ones
  * @param asynch: asynchronous prescaler value in range 0 - PREDIVA_MAX
  * @param synch: synchronous prescaler value in range 0 - PREDIVS_MAX
  * @retval None
  */
void RTC_setPrediv(int8_t asynch, int16_t synch)
{
#if !defined(STM32F1xx)
  if ((asynch >= -1) && (synch >= -1)) {
    userPredivAsync = asynch;
    userPredivSync = synch;
  }
#else
  UNUSED(asynch);
  UNUSED(synch);
#endif /* !STM32F1xx */
}

/**
  * @brief get user (a)synchronous prescaler values if set else computed ones
  *        for the current clock source.
  * @param asynch: pointer where return asynchronous prescaler value.
  * @param synch: pointer where return synchronous prescaler value.
  * @retval None
  */
void RTC_getPrediv(int8_t *asynch, int16_t *synch)
{
#if !defined(STM32F1xx)
  if ((userPredivAsync == -1) || (userPredivSync == -1)) {
    RTC_computePrediv(asynch, synch);
  } else {
    if ((asynch != NULL) && (synch != NULL)) {
      *asynch = userPredivAsync;
      *synch = userPredivSync;
    }
  }
#else
  UNUSED(asynch);
  UNUSED(synch);
#endif /* !STM32F1xx */
}

#if !defined(STM32F1xx)
/**
  * @brief Compute (a)synchronous prescaler
  *        RTC prescalers are compute to obtain the RTC clock to 1Hz. See AN4759.
  * @param asynch: pointer where return asynchronous prescaler value.
  * @param synch: pointer where return synchronous prescaler value.
  * @retval None
  */
static void RTC_computePrediv(int8_t *asynch, int16_t *synch)
{
  uint32_t predivS = PREDIVS_MAX + 1;
  uint32_t clk = 0;

  /* Get user predividers if manually configured */
  if ((asynch == NULL) || (synch == NULL)) {
    return;
  }

  /* Get clock frequency */
  if (clkSrc == LSE_CLOCK) {
    clk = LSE_VALUE;
  } else if (clkSrc == LSI_CLOCK) {
    clk = LSI_VALUE;
  } else if (clkSrc == HSE_CLOCK) {
    clk = HSE_VALUE / HSEDiv;
  } else {
    Error_Handler();
  }

  /* Find (a)synchronous prescalers to obtain the 1Hz calendar clock */
  for (*asynch = PREDIVA_MAX; *asynch >= 0; (*asynch)--) {
    predivS = (clk / (*asynch + 1)) - 1;

    if (((predivS + 1) * (*asynch + 1)) == clk) {
      break;
    }
  }

  /*
   * Can't find a 1Hz, so give priority to RTC power consumption
   * by choosing the higher possible value for predivA
   */
  if ((predivS > PREDIVS_MAX) || (*asynch < 0)) {
    *asynch = PREDIVA_MAX;
    predivS = (clk / (*asynch + 1)) - 1;
  }

  if (predivS > PREDIVS_MAX) {
    Error_Handler();
  }
  *synch = (int16_t)predivS;
}
#endif /* !STM32F1xx */

/**
  * @brief RTC Initialization
  *        This function configures the RTC time and calendar. By default, the
  *        RTC is set to the 1st January 2017 0:0:0:00
  * @param format: enable the RTC in 12 or 24 hours mode
  * @retval None
  */
void RTC_init(hourFormat_t format, sourceClock_t source, bool reset)
{
  initFormat = format;

  if (reset) {
    resetBackupDomain();
  }

  /* Init RTC clock */
  RTC_initClock(source);

  RtcHandle.Instance = RTC;

#if defined(STM32F1xx)
  /* Let HAL calculate the prescaler */
  RtcHandle.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  RtcHandle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  UNUSED(format);
#else
  if (format == HOUR_FORMAT_12) {
    RtcHandle.Init.HourFormat = RTC_HOURFORMAT_12;
  } else {
    RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  }
  RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RTC_getPrediv((int8_t *) & (RtcHandle.Init.AsynchPrediv), (int16_t *) & (RtcHandle.Init.SynchPrediv));
#if defined(STM32G0xx) || defined(STM32H7xx) || defined(STM32L0xx) || defined(STM32L4xx)
  RtcHandle.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
#endif /* STM32H7xx || STM32L0xx || STM32L4xx */
  RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RtcHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
#endif /* STM32F1xx */

  HAL_RTC_Init(&RtcHandle);

#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32L1xx) || defined(STM32L1_ULPH)
  /* Enable Direct Read of the calendar registers (not through Shadow) */
  HAL_RTCEx_EnableBypassShadow(&RtcHandle);
#endif /* !STM32F1xx && !STM32F2xx */

  HAL_NVIC_SetPriority(RTC_Alarm_IRQn, RTC_IRQ_PRIO, RTC_IRQ_SUBPRIO);
  HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
  /* Ensure backup domain is enabled */
  enableBackupDomain();
}

/**
  * @brief RTC deinitialization. Stop the RTC.
  * @retval None
  */
void RTC_DeInit(void)
{
  HAL_RTC_DeInit(&RtcHandle);
  RTCUserCallback = NULL;
  callbackUserData = NULL;
}

/**
  * @brief Check wether time is already set
  * @retval True if set else false
  */
bool RTC_IsTimeSet(void)
{
  return (getBackupRegister(RTC_BKP_INDEX) == RTC_BKP_VALUE) ? true : false;
}

/**
  * @brief Set RTC time
  * @param hours: 0-12 or 0-23. Depends on the format used.
  * @param minutes: 0-59
  * @param seconds: 0-59
  * @param subSeconds: 0-999
  * @param period: select HOUR_AM or HOUR_PM period in case RTC is set in 12 hours mode. Else ingored.
  * @retval None
  */
void RTC_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, hourAM_PM_t period)
{
  RTC_TimeTypeDef RTC_TimeStruct;

  /* Ignore time AM PM configuration if in 24 hours format */
  if (initFormat == HOUR_FORMAT_24) {
    period = HOUR_AM;
  }

  if ((((initFormat == HOUR_FORMAT_24) && IS_RTC_HOUR24(hours)) || IS_RTC_HOUR12(hours))
      && IS_RTC_MINUTES(minutes) && IS_RTC_SECONDS(seconds)) {
    RTC_TimeStruct.Hours = hours;
    RTC_TimeStruct.Minutes = minutes;
    RTC_TimeStruct.Seconds = seconds;
#if !defined(STM32F1xx)
    if (period == HOUR_PM) {
      RTC_TimeStruct.TimeFormat = RTC_HOURFORMAT12_PM;
    } else {
      RTC_TimeStruct.TimeFormat = RTC_HOURFORMAT12_AM;
    }
#if !defined(STM32F2xx) && !defined(STM32L1xx) || defined(STM32L1_ULPH)
    RTC_TimeStruct.SubSeconds = subSeconds;
    RTC_TimeStruct.SecondFraction = 0;
#else
    UNUSED(subSeconds);
#endif /* !STM32F2xx && !STM32L1xx || STM32L1_ULPH */
    RTC_TimeStruct.DayLightSaving = RTC_STOREOPERATION_RESET;
    RTC_TimeStruct.StoreOperation = RTC_DAYLIGHTSAVING_NONE;
#else
    UNUSED(subSeconds);
    UNUSED(period);
#endif /* !STM32F1xx */

    HAL_RTC_SetTime(&RtcHandle, &RTC_TimeStruct, RTC_FORMAT_BIN);
    setBackupRegister(RTC_BKP_INDEX, RTC_BKP_VALUE);
  }
}

/**
  * @brief Get RTC time
  * @param hours: 0-12 or 0-23. Depends on the format used.
  * @param minutes: 0-59
  * @param seconds: 0-59
  * @param subSeconds: 0-999 (optional could be NULL)
  * @param period: HOUR_AM or HOUR_PM period in case RTC is set in 12 hours mode (optional could be NULL).
  * @retval None
  */
void RTC_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint32_t *subSeconds, hourAM_PM_t *period)
{
  RTC_TimeTypeDef RTC_TimeStruct;

  if ((hours != NULL) && (minutes != NULL) && (seconds != NULL)) {
    HAL_RTC_GetTime(&RtcHandle, &RTC_TimeStruct, RTC_FORMAT_BIN);
    *hours = RTC_TimeStruct.Hours;
    *minutes = RTC_TimeStruct.Minutes;
    *seconds = RTC_TimeStruct.Seconds;
#if !defined(STM32F1xx)
    if (period != NULL) {
      if (RTC_TimeStruct.TimeFormat == RTC_HOURFORMAT12_PM) {
        *period = HOUR_PM;
      } else {
        *period = HOUR_AM;
      }
    }
#if (!defined(STM32F2xx) && !defined(STM32L1xx)) || defined(STM32L1_ULPH)
    if (subSeconds != NULL) {
      *subSeconds = RTC_TimeStruct.SubSeconds;
    }
#else
    UNUSED(subSeconds);
#endif
#else
    UNUSED(period);
    UNUSED(subSeconds);
#endif /* !STM32F1xx */
  }
}

/**
  * @brief Set RTC calendar
  * @param year: 0-99
  * @param month: 1-12
  * @param day: 1-31
  * @param wday: 1-7
  * @retval None
  */
void RTC_SetDate(uint8_t year, uint8_t month, uint8_t day, uint8_t wday)
{
  RTC_DateTypeDef RTC_DateStruct;

  if (IS_RTC_YEAR(year) && IS_RTC_MONTH(month) && IS_RTC_DATE(day) && IS_RTC_WEEKDAY(wday)) {
    RTC_DateStruct.Year = year;
    RTC_DateStruct.Month = month;
    RTC_DateStruct.Date = day;
    RTC_DateStruct.WeekDay = wday;
    HAL_RTC_SetDate(&RtcHandle, &RTC_DateStruct, RTC_FORMAT_BIN);
    setBackupRegister(RTC_BKP_INDEX, RTC_BKP_VALUE);
  }
}

/**
  * @brief Get RTC calendar
  * @param year: 0-99
  * @param month: 1-12
  * @param day: 1-31
  * @param wday: 1-7
  * @retval None
  */
void RTC_GetDate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *wday)
{
  RTC_DateTypeDef RTC_DateStruct;

  if ((year != NULL) && (month != NULL) && (day != NULL) && (wday != NULL)) {
    HAL_RTC_GetDate(&RtcHandle, &RTC_DateStruct, RTC_FORMAT_BIN);
    *year = RTC_DateStruct.Year;
    *month = RTC_DateStruct.Month;
    *day = RTC_DateStruct.Date;
    *wday = RTC_DateStruct.WeekDay;
  }
}

/**
  * @brief Set RTC alarm and activate it with IT mode
  * @param day: 1-31 (day of the month)
  * @param hours: 0-12 or 0-23 depends on the hours mode.
  * @param minutes: 0-59
  * @param seconds: 0-59
  * @param subSeconds: 0-999
  * @param period: HOUR_AM or HOUR_PM if in 12 hours mode else ignored.
  * @param mask: configure alarm behavior using alarmMask_t combination.
  *              See AN4579 Table 5 for possible values.
  * @retval None
  */
void RTC_StartAlarm(uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, hourAM_PM_t period, uint8_t mask)
{
  RTC_AlarmTypeDef RTC_AlarmStructure;

  /* Ignore time AM PM configuration if in 24 hours format */
  if (initFormat == HOUR_FORMAT_24) {
    period = HOUR_AM;
  }

  if ((((initFormat == HOUR_FORMAT_24) && IS_RTC_HOUR24(hours)) || IS_RTC_HOUR12(hours))
      && IS_RTC_DATE(day) && IS_RTC_MINUTES(minutes) && IS_RTC_SECONDS(seconds)) {
    /* Set RTC_AlarmStructure with calculated values*/
    /* Use alarm A by default because it is common to all STM32 HAL */
    RTC_AlarmStructure.Alarm = RTC_ALARM_A;
    RTC_AlarmStructure.AlarmTime.Seconds = seconds;
    RTC_AlarmStructure.AlarmTime.Minutes = minutes;
    RTC_AlarmStructure.AlarmTime.Hours = hours;
#if !defined(STM32F1xx)
#if !defined(STM32F2xx) && !defined(STM32L1xx) || defined(STM32L1_ULPH)
    RTC_AlarmStructure.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_10;
    RTC_AlarmStructure.AlarmTime.SubSeconds = subSeconds;
#else
    UNUSED(subSeconds);
#endif /* !STM32F2xx && !STM32L1xx || STM32L1_ULPH */
    if (period == HOUR_PM) {
      RTC_AlarmStructure.AlarmTime.TimeFormat = RTC_HOURFORMAT12_PM;
    } else {
      RTC_AlarmStructure.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
    }
    RTC_AlarmStructure.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    RTC_AlarmStructure.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
    RTC_AlarmStructure.AlarmDateWeekDay = day;
    RTC_AlarmStructure.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    /* configure AlarmMask (M_MSK and Y_MSK ignored) */
    if (mask == OFF_MSK) {
      RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_ALL;
    } else {
      RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_NONE;
      if (!(mask & SS_MSK)) {
        RTC_AlarmStructure.AlarmMask |= RTC_ALARMMASK_SECONDS;
      }
      if (!(mask & MM_MSK)) {
        RTC_AlarmStructure.AlarmMask |= RTC_ALARMMASK_MINUTES;
      }
      if (!(mask & HH_MSK)) {
        RTC_AlarmStructure.AlarmMask |= RTC_ALARMMASK_HOURS;
      }
      if (!(mask & D_MSK)) {
        RTC_AlarmStructure.AlarmMask |= RTC_ALARMMASK_DATEWEEKDAY;
      }
    }
#else
    UNUSED(subSeconds);
    UNUSED(period);
    UNUSED(day);
    UNUSED(mask);
#endif /* !STM32F1xx */

    /* Set RTC_Alarm */
    HAL_RTC_SetAlarm_IT(&RtcHandle, &RTC_AlarmStructure, RTC_FORMAT_BIN);
  }
}

/**
  * @brief Disable RTC alarm
  * @param None
  * @retval None
  */
void RTC_StopAlarm(void)
{
  /* Clear RTC Alarm Flag */
  __HAL_RTC_ALARM_CLEAR_FLAG(&RtcHandle, RTC_FLAG_ALRAF);

  /* Disable the Alarm A interrupt */
  HAL_RTC_DeactivateAlarm(&RtcHandle, RTC_ALARM_A);
}

/**
  * @brief Get RTC alarm
  * @param day: 1-31 day of the month (optional could be NULL)
  * @param hours: 0-12 or 0-23 depends on the hours mode
  * @param minutes: 0-59
  * @param seconds: 0-59
  * @param subSeconds: 0-999 (optional could be NULL)
  * @param period: HOUR_AM or HOUR_PM (optional could be NULL)
  * @param mask: alarm behavior using alarmMask_t combination (optional could be NULL)
  *              See AN4579 Table 5 for possible values
  * @retval None
  */
void RTC_GetAlarm(uint8_t *day, uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint32_t *subSeconds, hourAM_PM_t *period, uint8_t *mask)
{
  RTC_AlarmTypeDef RTC_AlarmStructure;

  if ((hours != NULL) && (minutes != NULL) && (seconds != NULL)) {
    HAL_RTC_GetAlarm(&RtcHandle, &RTC_AlarmStructure, RTC_ALARM_A, RTC_FORMAT_BIN);

    *seconds = RTC_AlarmStructure.AlarmTime.Seconds;
    *minutes = RTC_AlarmStructure.AlarmTime.Minutes;
    *hours = RTC_AlarmStructure.AlarmTime.Hours;

#if !defined(STM32F1xx)
    if (day != NULL) {
      *day = RTC_AlarmStructure.AlarmDateWeekDay;
    }
    if (period != NULL) {
      if (RTC_AlarmStructure.AlarmTime.TimeFormat == RTC_HOURFORMAT12_PM) {
        *period = HOUR_PM;
      } else {
        *period = HOUR_AM;
      }
    }
#if !defined(STM32F2xx) && !defined(STM32L1xx) || defined(STM32L1_ULPH)
    if (subSeconds != NULL) {
      *subSeconds = RTC_AlarmStructure.AlarmTime.SubSeconds;
    }
#else
    UNUSED(subSeconds);
#endif /* !STM32F2xx && !STM32L1xx || STM32L1_ULPH */
    if (mask != NULL) {
      *mask = OFF_MSK;
      if (!(RTC_AlarmStructure.AlarmMask & RTC_ALARMMASK_SECONDS)) {
        *mask |= SS_MSK;
      }
      if (!(RTC_AlarmStructure.AlarmMask & RTC_ALARMMASK_MINUTES)) {
        *mask |= MM_MSK;
      }
      if (!(RTC_AlarmStructure.AlarmMask & RTC_ALARMMASK_HOURS)) {
        *mask |= HH_MSK;
      }
      if (!(RTC_AlarmStructure.AlarmMask & RTC_ALARMMASK_DATEWEEKDAY)) {
        *mask |= D_MSK;
      }
    }
#else
    UNUSED(day);
    UNUSED(period);
    UNUSED(subSeconds);
    UNUSED(mask);
#endif /* !STM32F1xx */
  }
}

/**
  * @brief Attach alarm callback.
  * @param func: pointer to the callback
  * @retval None
  */
void attachAlarmCallback(voidCallbackPtr func, void *data)
{
  RTCUserCallback = func;
  callbackUserData = data;
}

/**
  * @brief Detach alarm callback.
  * @param None
  * @retval None
  */
void detachAlarmCallback(void)
{
  RTCUserCallback = NULL;
  callbackUserData = NULL;
}

/**
  * @brief  Alarm A callback.
  * @param  hrtc RTC handle
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  UNUSED(hrtc);

  if (RTCUserCallback != NULL) {
    RTCUserCallback(callbackUserData);
  }
}

/**
  * @brief  RTC Alarm IRQHandler
  * @param  None
  * @retval None
  */
void RTC_Alarm_IRQHandler(void)
{
  HAL_RTC_AlarmIRQHandler(&RtcHandle);
}

#ifdef __cplusplus
}
#endif

#endif /* HAL_RTC_MODULE_ENABLED  && !HAL_RTC_MODULE_ONLY */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
