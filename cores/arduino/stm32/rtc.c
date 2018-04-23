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

#ifdef HAL_RTC_MODULE_ENABLED

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
static int8_t AsynchPrediv = -1; // 1 to 127
static int16_t SynchPrediv = -1; // 0 to 32767

static hourFormat_t initFormat = HOUR_FORMAT_12;

/* Private function prototypes -----------------------------------------------*/
static void RTC_setClock(sourceClock_t source);
static void RTC_getPrediv(uint32_t *asynch, uint32_t *synch);

/* Exported functions --------------------------------------------------------*/

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
static void RTC_setClock(sourceClock_t source)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  if(source == LSE_CLOCK) {
    // Enable the clock if not already set by user.
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET) {
#ifdef __HAL_RCC_LSEDRIVE_CONFIG
      __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
#endif
      RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSE;
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
      RCC_OscInitStruct.LSEState = RCC_LSE_ON;
      if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
      }
    }

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
      Error_Handler();
    }
    clkSrc = LSE_CLOCK;
  } else if(source == HSE_CLOCK) {
    // Enable the clock if not already set by user.
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET) {
      RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_HSE;
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
      RCC_OscInitStruct.HSEState = RCC_HSE_ON;
      if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
      }
    }
    /* HSE division factor for RTC clock must be set to ensure that
     * the clock supplied to the RTC is less than or equal to 1 MHz
     */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
#if defined(STM32F1xx)
    /* HSE max is 16 MHZ divided by 128 --> 125 KHz */
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV128;
    HSEDiv = 128;
#elif defined(STM32F0xx) || defined(STM32F3xx) || defined(STM32L4xx)
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV32;
    HSEDiv = 32;
#elif defined(STM32L0xx) || defined(STM32L1xx)
    if((HSE_VALUE/2) <= HSE_RTC_MAX) {
      PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV2;
      HSEDiv = 2;
    } else if((HSE_VALUE/4) <= HSE_RTC_MAX) {
      PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV4;
      HSEDiv = 4;
    } else if((HSE_VALUE/8) <= HSE_RTC_MAX) {
      PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV8;
      HSEDiv = 8;
    } else if((HSE_VALUE/16) <= HSE_RTC_MAX) {
      PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV16;
      HSEDiv = 16;
    }
#elif defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
/* Not defined for STM32Fxx */
#ifndef RCC_RTCCLKSOURCE_HSE_DIVX
#define RCC_RTCCLKSOURCE_HSE_DIVX 0x00000300U
#endif
    for(HSEDiv = 2; HSEDiv<32; HSEDiv++) {
      if((HSE_VALUE/HSEDiv) <= HSE_RTC_MAX) {
        PeriphClkInit.RTCClockSelection = (HSEDiv<<16) | RCC_RTCCLKSOURCE_HSE_DIVX;
        break;
      }
    }
#else
#error "Unknown Family - could not define RTCClockSelection"
#endif
    if((HSE_VALUE/HSEDiv) > HSE_RTC_MAX) {
      Error_Handler();
    }

    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
      Error_Handler();
    }
    clkSrc = HSE_CLOCK;
  } else if(source == LSI_CLOCK) {
    // Enable the clock if not already set by user.
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == RESET) {
      RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI;
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
      RCC_OscInitStruct.LSIState = RCC_LSI_ON;
      if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
      }
    }

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
      Error_Handler();
    }
    clkSrc = LSI_CLOCK;
  } else {
    Error_Handler();
  }

  __HAL_RCC_RTC_ENABLE();
}

/**
  * @brief RTC_setPrediv
  *        Allow to user to set manually the prescaler values.
  * @param Asynch: asynchronous prescaler value in range 1 - 127
  * @param Synch: synchronous prescaler value in range 0 - 32767
  * @retval None
  */
void RTC_setPrediv(int8_t Asynch, int16_t Synch)
{
  if((Asynch >= 1) && (Synch >= 0)) {
    AsynchPrediv = Asynch;
    SynchPrediv = Synch;
  }
}

/**
  * @brief RTC_getPrediv
  *        RTC prescalers are set to obtain the RTC clock to 1Hz. See AN4759.
  * @param asynch: pointer where return asynchronous prescaler value.
  * @param synch: pointer where return synchronous prescaler value.
  * @retval None
  */
static void RTC_getPrediv(uint32_t *asynch, uint32_t *synch)
{
  uint32_t predivA;
  uint32_t predivS;
  uint32_t clk = 0;

  if((asynch == NULL) || (synch == NULL)) {
    return;
  }

  // Get user predividers if manually configured
  if((AsynchPrediv > 0) && (SynchPrediv > 0)) {
    *asynch = AsynchPrediv;
    *synch = SynchPrediv;
    return;
  }

  // Get clock frequency
  if(clkSrc == LSE_CLOCK) {
    clk = LSE_VALUE;
  }
  else if(clkSrc == LSI_CLOCK) {
    clk = LSI_VALUE;
  }
  else if(clkSrc == HSE_CLOCK) {
    clk = HSE_VALUE/HSEDiv;
  } else {
    Error_Handler();
  }

  // Get prescalers
  if(clk > 0) {
    for(predivA = 128; predivA > 1; predivA--) {
      predivS = clk / predivA;
      if((predivS <= 32768) && ((predivS * predivA) == clk)) {
        *asynch = predivA - 1;
        *synch = predivS - 1;
        break;
      }
    }
  }
}

/**
  * @brief RTC Initialization
  *        This function configures the RTC time and calendar. By default, the
  *        RTC is set to the 1st January 2017 0:0:0:00
  * @param format: enable the RTC in 12 or 24 hours mode
  * @retval None
  */
void RTC_init(hourFormat_t format, sourceClock_t source)
{
  initFormat = format;

  // Set RTC clock
  RTC_setClock(source);

  RtcHandle.Instance = RTC;

#if defined(STM32F1xx)
  RtcHandle.Init.AsynchPrediv = RTC_AUTO_1_SECOND; //Leave HAL calculate the prescaler
  RtcHandle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  UNUSED(format);
#else
  if(format == HOUR_FORMAT_12) {
    RtcHandle.Init.HourFormat = RTC_HOURFORMAT_12;
  } else {
    RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  }
  RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RTC_getPrediv(&(RtcHandle.Init.AsynchPrediv), &(RtcHandle.Init.SynchPrediv));
#if defined(STM32L0xx) || defined(STM32L4xx)
  RtcHandle.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
#endif // defined(STM32L0xx) || defined(STM32L4xx)
  RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RtcHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
#endif // defined(STM32F1xx)

  HAL_RTC_Init( &RtcHandle );

  /*Sunday 1st January 2017*/
  RTC_SetDate(17, 1, 1, 7);

  /*at 0:0:0*/
  RTC_SetTime(0,0,0,0,AM);

#if !defined(STM32F1xx) && !defined(STM32F2xx)
  /*Enable Direct Read of the calendar registers (not through Shadow) */
  HAL_RTCEx_EnableBypassShadow(&RtcHandle);
#endif // !defined(STM32F1xx) && !defined(STM32F2xx)

  HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
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
  * @brief Set RTC time
  * @param hours: 0-12 or 0-23. Depends on the format used.
  * @param minutes: 0-59
  * @param seconds: 0-59
  * @param subSeconds: 0-999
  * @param period: select AM or PM period in case RTC is set in 12 hours mode. Else ingored.
  * @retval None
  */
void RTC_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, hourAM_PM_t period)
{
  RTC_TimeTypeDef RTC_TimeStruct;

  // Ignore time AM PM configuration if in 24 hours format
  if(initFormat == HOUR_FORMAT_24) {
    period = AM;
  }

  if((((initFormat == HOUR_FORMAT_24) && IS_RTC_HOUR24(hours)) || IS_RTC_HOUR12(hours))
      && IS_RTC_MINUTES(minutes) && IS_RTC_SECONDS(seconds)) {
    RTC_TimeStruct.Hours = hours;
    RTC_TimeStruct.Minutes = minutes;
    RTC_TimeStruct.Seconds = seconds;
#if !defined(STM32F1xx)
    if(period == PM) {
      RTC_TimeStruct.TimeFormat = RTC_HOURFORMAT12_PM;
    } else {
      RTC_TimeStruct.TimeFormat = RTC_HOURFORMAT12_AM;
    }
#if !defined(STM32F2xx) && !defined(STM32L1xx) || defined(STM32L1_ULPH)
    RTC_TimeStruct.SubSeconds = subSeconds;
    RTC_TimeStruct.SecondFraction = 0;
#else
    UNUSED(subSeconds);
#endif //!defined(STM32F2xx) && !defined(STM32L1xx) || defined(STM32L1_ULPH)
    RTC_TimeStruct.DayLightSaving = RTC_STOREOPERATION_RESET;
    RTC_TimeStruct.StoreOperation = RTC_DAYLIGHTSAVING_NONE;
#else
    UNUSED(subSeconds);
    UNUSED(period);
#endif // !defined(STM32F1xx)

    HAL_RTC_SetTime(&RtcHandle , &RTC_TimeStruct, RTC_FORMAT_BIN);
  }
}

/**
  * @brief Get RTC time
  * @param hours: 0-12 or 0-23. Depends on the format used.
  * @param minutes: 0-59
  * @param seconds: 0-59
  * @param subSeconds: 0-999
  * @param period: returns AM or PM period in case RTC is set in 12 hours mode.
  * @retval None
  */
void RTC_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint32_t *subSeconds, hourAM_PM_t *period)
{
  RTC_TimeTypeDef RTC_TimeStruct;

  if((hours != NULL) && (minutes != NULL) && (seconds != NULL) && (subSeconds != NULL) && (period != NULL)) {
    HAL_RTC_GetTime(&RtcHandle , &RTC_TimeStruct, RTC_FORMAT_BIN);
    *hours = RTC_TimeStruct.Hours;
    *minutes = RTC_TimeStruct.Minutes;
    *seconds = RTC_TimeStruct.Seconds;
#if !defined(STM32F1xx)
    if(RTC_TimeStruct.TimeFormat == RTC_HOURFORMAT12_PM) {
      *period = PM;
    } else {
      *period = AM;
    }
#if !defined(STM32F2xx) && !defined(STM32L1xx) || defined(STM32L1_ULPH)
    *subSeconds = RTC_TimeStruct.SubSeconds;
#endif
#endif // !defined(STM32F1xx)
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

  if(IS_RTC_YEAR(year) && IS_RTC_MONTH(month) && IS_RTC_DATE(day) && IS_RTC_WEEKDAY(wday)) {
    RTC_DateStruct.Year = year;
    RTC_DateStruct.Month = month;
    RTC_DateStruct.Date = day;
    RTC_DateStruct.WeekDay = wday;
    HAL_RTC_SetDate(&RtcHandle , &RTC_DateStruct, RTC_FORMAT_BIN);
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

  if((year != NULL) && (month != NULL) && (day != NULL) && (wday != NULL)) {
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
  * @param period: AM or PM if in 12 hours mode else ignored.
  * @param mask: configure alarm behavior using alarmMask_t combination.
  *              See AN4579 Table 5 for possible values.
  * @retval None
  */
void RTC_StartAlarm(uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, hourAM_PM_t period, uint8_t mask)
{
  RTC_AlarmTypeDef RTC_AlarmStructure;

  // Ignore time AM PM configuration if in 24 hours format
  if(initFormat == HOUR_FORMAT_24) {
    period = AM;
  }

  if((((initFormat == HOUR_FORMAT_24) && IS_RTC_HOUR24(hours)) || IS_RTC_HOUR12(hours))
    && IS_RTC_DATE(day) && IS_RTC_MINUTES(minutes) && IS_RTC_SECONDS(seconds)) {
    /* Set RTC_AlarmStructure with calculated values*/
    RTC_AlarmStructure.Alarm = RTC_ALARM_A; //Use alarm A by default because it is common to all STM32 HAL.
    RTC_AlarmStructure.AlarmTime.Seconds = seconds;
    RTC_AlarmStructure.AlarmTime.Minutes = minutes;
    RTC_AlarmStructure.AlarmTime.Hours = hours;
#if !defined(STM32F1xx)
#if !defined(STM32F2xx) && !defined(STM32L1xx) || defined(STM32L1_ULPH)
    RTC_AlarmStructure.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_10;
    RTC_AlarmStructure.AlarmTime.SubSeconds = subSeconds;
#else
    UNUSED(subSeconds);
#endif
    if(period == PM) {
      RTC_AlarmStructure.AlarmTime.TimeFormat = RTC_HOURFORMAT12_PM;
    } else {
      RTC_AlarmStructure.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
    }
    RTC_AlarmStructure.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    RTC_AlarmStructure.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
    RTC_AlarmStructure.AlarmDateWeekDay = day;
    RTC_AlarmStructure.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    /* configure AlarmMask (M_MSK and Y_MSK ignored) */
	if(mask == OFF_MSK) {
      RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_ALL;
	} else {
      RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_NONE;
      if( !(mask & SS_MSK)) {
        RTC_AlarmStructure.AlarmMask |= RTC_ALARMMASK_SECONDS;
      }
      if( !(mask & MM_MSK)) {
        RTC_AlarmStructure.AlarmMask |= RTC_ALARMMASK_MINUTES;
      }
      if( !(mask & HH_MSK)) {
        RTC_AlarmStructure.AlarmMask |= RTC_ALARMMASK_HOURS;
      }
      if( !(mask & D_MSK)) {
        RTC_AlarmStructure.AlarmMask |= RTC_ALARMMASK_DATEWEEKDAY;
      }
    }
#else
    UNUSED(subSeconds);
    UNUSED(period);
    UNUSED(day);
    UNUSED(mask);
#endif // !defined(STM32F1xx)

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
  * @param day: 1-31 (day of the month)
  * @param hours: 0-12 or 0-23 depends on the hours mode.
  * @param minutes: 0-59
  * @param seconds: 0-59
  * @param subSeconds: 0-999
  * @param period: AM or PM
  * @retval None
  */
void RTC_GetAlarm(uint8_t *day, uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint32_t *subSeconds, hourAM_PM_t *period, uint8_t *mask)
{
  RTC_AlarmTypeDef RTC_AlarmStructure;

  if((day != NULL) && (hours != NULL) && (minutes != NULL) && (seconds != NULL) && (subSeconds != NULL) && (period != NULL) && (mask != NULL)) {
    HAL_RTC_GetAlarm(&RtcHandle, &RTC_AlarmStructure, RTC_ALARM_A, RTC_FORMAT_BIN);

    *seconds = RTC_AlarmStructure.AlarmTime.Seconds;
    *minutes = RTC_AlarmStructure.AlarmTime.Minutes;
    *hours = RTC_AlarmStructure.AlarmTime.Hours;

#if !defined(STM32F1xx)
    *day = RTC_AlarmStructure.AlarmDateWeekDay;
    if(RTC_AlarmStructure.AlarmTime.TimeFormat == RTC_HOURFORMAT12_PM) {
      *period = PM;
    } else {
      *period = AM;
    }
#if !defined(STM32F2xx) && !defined(STM32L1xx) || defined(STM32L1_ULPH)
    *subSeconds = RTC_AlarmStructure.AlarmTime.SubSeconds;
#endif
    *mask = OFF_MSK;
    if(!(RTC_AlarmStructure.AlarmMask & RTC_ALARMMASK_SECONDS)) {
      *mask |= SS_MSK;
    }
    if(!(RTC_AlarmStructure.AlarmMask & RTC_ALARMMASK_MINUTES)) {
      *mask |= MM_MSK;
    }
    if(!(RTC_AlarmStructure.AlarmMask & RTC_ALARMMASK_HOURS)) {
      *mask |= HH_MSK;
    }
    if(!(RTC_AlarmStructure.AlarmMask & RTC_ALARMMASK_DATEWEEKDAY)) {
      *mask |= D_MSK;
    }
#endif // !defined(STM32F1xx)
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

  if(RTCUserCallback != NULL)
    RTCUserCallback(callbackUserData);
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

#endif // HAL_RTC_MODULE_ENABLED

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
