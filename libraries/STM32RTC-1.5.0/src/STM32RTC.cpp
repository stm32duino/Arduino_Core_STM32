/**
  ******************************************************************************
  * @file    STM32RTC.cpp
  * @author  Frederic Pillon
  * @brief   Provides a RTC interface for Arduino
  *
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
#include "STM32RTC.h"

#define EPOCH_TIME_OFF      946684800  // This is 1st January 2000, 00:00:00 in epoch time
#define EPOCH_TIME_YEAR_OFF 100        // years since 1900

// Initialize static variable
bool STM32RTC::_timeSet = false;

/**
  * @brief initializes the RTC
  * @param format: hour format: HOUR_12 or HOUR_24(default)
  * @retval None
  */
void STM32RTC::begin(Hour_Format format)
{
  begin(false, format);
}

/**
  * @brief initializes the RTC
  * @param resetTime: if true reconfigures the RTC
  * @param format: hour format: HOUR_12 or HOUR_24(default)
  * @retval None
  */
void STM32RTC::begin(bool resetTime, Hour_Format format)
{
  bool reinit;

  _format = format;
  reinit = RTC_init((format == HOUR_12) ? HOUR_FORMAT_12 : HOUR_FORMAT_24,
                    (_mode == MODE_MIX) ? ::MODE_BINARY_MIX : ((_mode == MODE_BIN) ? ::MODE_BINARY_ONLY : ::MODE_BINARY_NONE),
                    (_clockSource == LSE_CLOCK) ? ::LSE_CLOCK :
                    (_clockSource == HSE_CLOCK) ? ::HSE_CLOCK : ::LSI_CLOCK
                    , resetTime);
  _timeSet = !reinit;

  syncTime();
  syncDate();
  syncAlarmTime();
  if (!IS_RTC_DATE(_alarmDay)) {
    // Use current time to init alarm members,
    // specially in case _alarmDay is 0 (reset value) which is an invalid value
    _alarmDay  = _day;
    _alarmHours = _hours;
    _alarmMinutes = _minutes;
    _alarmSeconds = _seconds;
    _alarmSubSeconds = _subSeconds;
    _alarmPeriod = _hoursPeriod;
  }
#ifdef RTC_ALARM_B
  syncAlarmTime(ALARM_B);
  if (!IS_RTC_DATE(_alarmBDay)) {
    // Use current time to init alarm members,
    // specially in case _alarmDay is 0 (reset value) which is an invalid value
    _alarmBDay  = _day;
    _alarmBHours = _hours;
    _alarmBMinutes = _minutes;
    _alarmBSeconds = _seconds;
    _alarmBSubSeconds = _subSeconds;
    _alarmBPeriod = _hoursPeriod;
  }
#endif
}

/**
  * @brief Deinitialize and stop the RTC
  * @param None
  * @retval None
  */
void STM32RTC::end(void)
{
  RTC_DeInit(true);
  _timeSet = false;
}

/**
  * @brief get the RTC clock source.
  * @retval clock source: LSI_CLOCK, LSE_CLOCK or HSE_CLOCK
  */
STM32RTC::Source_Clock STM32RTC::getClockSource(void)
{
  return _clockSource;
}

/**
  * @brief set the RTC clock source and user (a)synchronous prescalers values.
  * @note  By default LSI clock is selected. This method must be called before begin().
  * @param source: clock source: LSI_CLOCK, LSE_CLOCK or HSE_CLOCK
  * @param  predivA: Asynchronous prescaler value.
  * @note   Reset value: RTC_AUTO_1_SECOND for STM32F1xx series, else (PREDIVA_MAX + 1)
  * @param  predivS: Synchronous prescaler value.
  * @note   Reset value: (PREDIVS_MAX + 1), not used for STM32F1xx series.
  * @retval None
  */
void STM32RTC::setClockSource(Source_Clock source, uint32_t predivA, uint32_t predivS)
{
  if (IS_CLOCK_SOURCE(source)) {
    _clockSource = source;
    RTC_SetClockSource((_clockSource == LSE_CLOCK) ? ::LSE_CLOCK :
                       (_clockSource == HSE_CLOCK) ? ::HSE_CLOCK : ::LSI_CLOCK);
  }
  RTC_setPrediv(predivA, predivS);
}

/**
  * @brief get the Binary Mode.
  * @retval mode: MODE_BCD, MODE_BIN or MODE_MIX
  */
STM32RTC::Binary_Mode STM32RTC::getBinaryMode(void)
{
  return _mode;
}

/**
  * @brief set the Binary Mode. By default MODE_BCD is selected. This
  *        method must be called before begin().
  * @param mode: the RTC mode: MODE_BCD, MODE_BIN or MODE_MIX
  * @retval None
  */
void STM32RTC::setBinaryMode(Binary_Mode mode)
{
#if defined(RTC_BINARY_NONE)
  _mode = mode;
#else
#warning "only BCD mode is supported"
  UNUSED(mode);
  _mode = MODE_BCD;
#endif /* RTC_BINARY_NONE */
}

/**
  * @brief  get user (a)synchronous prescaler values if set else computed
  *         ones for the current clock source.
  * @param  predivA: pointer to the current Asynchronous prescaler value
  * @param  predivS: pointer to the current Synchronous prescaler value,
  *         not used for STM32F1xx series.
  * @retval None
  */
void STM32RTC::getPrediv(uint32_t *predivA, uint32_t *predivS)
{
  if ((predivA != nullptr)
#if !defined(STM32F1xx)
      && (predivS != nullptr)
#endif /* STM32F1xx */
     ) {
    RTC_getPrediv(predivA, predivS);
  }
}

/**
  * @brief  set user (a)synchronous prescalers values.
  * @note   This method must be called before begin().
  * @param  predivA: Asynchronous prescaler value.
  * @note   Reset value: RTC_AUTO_1_SECOND for STM32F1xx series, else (PREDIVA_MAX + 1)
  * @param  predivS: Synchronous prescaler value.
  * @note   Reset value: (PREDIVS_MAX + 1), not used for STM32F1xx series.
  * @retval None
  */
void STM32RTC::setPrediv(uint32_t predivA, uint32_t predivS)
{
  setClockSource(_clockSource, predivA, predivS);
}

/**
  * @brief enable the RTC alarm.
  * @param match: Alarm_Match configuration
  * @param name: optional (default: ALARM_A)
  *        ALARM_A or ALARM_B if exists
  * @retval None
  */
void STM32RTC::enableAlarm(Alarm_Match match, Alarm name)
{
#ifdef RTC_ALARM_B
  if (name == ALARM_B) {
    _alarmBMatch = match;
  } else
#else
  UNUSED(name);
#endif
  {
    _alarmMatch = match;
  }
  switch (match) {
    case MATCH_OFF:
#ifdef RTC_ALARM_B
      if (name == ALARM_B) {
        RTC_StopAlarm(::ALARM_B);
      } else
#endif
      {
        RTC_StopAlarm(::ALARM_A);
      }
      break;
    case MATCH_SUBSEC:
      /* force _alarmday to 0 to go to the right alarm config in MIX mode */
#ifdef RTC_ALARM_B
      if (name == ALARM_B) {
        RTC_StartAlarm(::ALARM_B, 0, 0, 0, 0,
                       _alarmBSubSeconds, (_alarmBPeriod == AM) ? HOUR_AM : HOUR_PM,
                       static_cast<uint8_t>(31UL));
      } else
#endif
      {
        RTC_StartAlarm(::ALARM_A, 0, 0, 0, 0,
                       _alarmSubSeconds, (_alarmPeriod == AM) ? HOUR_AM : HOUR_PM,
                       static_cast<uint8_t>(31UL));
      }
      break;
    case MATCH_YYMMDDHHMMSS://kept for compatibility
    case MATCH_MMDDHHMMSS:  //kept for compatibility
    case MATCH_DHHMMSS:
    case MATCH_HHMMSS:
    case MATCH_MMSS:
    case MATCH_SS:
#ifdef RTC_ALARM_B
      if (name == ALARM_B) {
        RTC_StartAlarm(::ALARM_B, _alarmBDay, _alarmBHours, _alarmBMinutes, _alarmBSeconds,
                       _alarmBSubSeconds, (_alarmBPeriod == AM) ? HOUR_AM : HOUR_PM,
                       static_cast<uint8_t>(_alarmBMatch));
      } else
#endif
      {
        RTC_StartAlarm(::ALARM_A, _alarmDay, _alarmHours, _alarmMinutes, _alarmSeconds,
                       _alarmSubSeconds, (_alarmPeriod == AM) ? HOUR_AM : HOUR_PM,
                       static_cast<uint8_t>(_alarmMatch));
      }
      break;
    default:
      break;
  }
}

/**
  * @brief disable the RTC alarm.
  * @param name: optional (default: ALARM_A)
  *        ALARM_A or ALARM_B if exists
  * @retval None
  */
void STM32RTC::disableAlarm(Alarm name)
{
  RTC_StopAlarm(static_cast<alarm_t>(name));
}


/**
  * @brief attach a callback to the RTC alarm interrupt.
  * @param callback: pointer to the callback
  * @param name: optional (default: ALARM_A)
  *        ALARM_A or ALARM_B if exists
  * @retval None
  */
void STM32RTC::attachInterrupt(voidFuncPtr callback, Alarm name)
{
  attachInterrupt(callback, nullptr, name);
}

/**
  * @brief attach a callback to the RTC alarm interrupt.
  * @param callback: pointer to the callback
  * @param data: pointer to callback argument if any (default: nullptr)
  * @param name: optional (default: ALARM_A)
  *        ALARM_A or ALARM_B if exists
  * @retval None
  */
void STM32RTC::attachInterrupt(voidFuncPtr callback, void *data, Alarm name)
{
  attachAlarmCallback(callback, data, static_cast<alarm_t>(name));
}

/**
  * @brief detach the RTC alarm callback.
  * @param name: optional (default: ALARM_A)
  *        ALARM_A or ALARM_B if exists
  * @retval None
  */
void STM32RTC::detachInterrupt(Alarm name)
{
  detachAlarmCallback(static_cast<alarm_t>(name));
}

#ifdef ONESECOND_IRQn
/**
  * @brief attach a callback to the RTC Seconds interrupt.
  * @param callback: pointer to the callback
  * @retval None
  */
void STM32RTC::attachSecondsInterrupt(voidFuncPtr callback)
{
  attachSecondsIrqCallback(callback);
}

/**
  * @brief detach the RTC Seconds callback.
  * @retval None
  */
void STM32RTC::detachSecondsInterrupt(void)
{
  detachSecondsIrqCallback();
}

#endif /* ONESECOND_IRQn */

#ifdef STM32WLxx
/**
  * @brief attach a callback to the RTC SubSeconds underflow interrupt.
  * @note  only for STM32WLxx
  * @param callback: pointer to the callback
  * @retval None
  */
void STM32RTC::attachSubSecondsUnderflowInterrupt(voidFuncPtr callback)
{
  attachSubSecondsUnderflowIrqCallback(callback);
}

/**
  * @brief detach the RTC SubSeconds underflow callback.
  * @retval None
  */
void STM32RTC::detachSubSecondsUnderflowInterrupt(void)
{
  detachSubSecondsUnderflowIrqCallback();
}

#endif /* STM32WLxx */


// Kept for compatibility. Use STM32LowPower library.
void STM32RTC::standbyMode(void)
{

}

/*
 * Get Functions
 */

/**
  * @brief  get RTC subseconds.
  * @retval return the current milliseconds from the RTC.
  */
uint32_t STM32RTC::getSubSeconds(void)
{
  syncTime();
  return _subSeconds;
}

/**
  * @brief  get RTC seconds.
  * @retval return the current seconds from the RTC.
  */
uint8_t STM32RTC::getSeconds(void)
{
  syncTime();
  return _seconds;
}

/**
  * @brief  get RTC minutes.
  * @retval return the current minutes from the RTC.
  */
uint8_t STM32RTC::getMinutes(void)
{
  syncTime();
  return _minutes;
}

/**
  * @brief  get RTC hours.
  * @param  format: optional (default: nullptr)
  *         pointer to the current hour period set in the RTC: AM or PM
  * @retval return the current hours from the RTC.
  */
uint8_t STM32RTC::getHours(AM_PM *period)
{
  syncTime();
  if (period != nullptr) {
    *period = _hoursPeriod;
  }
  return _hours;
}

/**
  * @brief  get RTC time.
  * @param  hours: pointer to the current hours
  * @param  minutes: pointer to the current minutes
  * @param  seconds: pointer to the current seconds
  * @param  subSeconds: pointer to the current subSeconds (in milliseconds)
  * @param  period: optional (default: nullptr)
  *         pointer to the current hour period set in the RTC: AM or PM
  * @retval none
  */
void STM32RTC::getTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint32_t *subSeconds, AM_PM *period)
{
  syncTime();
  if (hours != nullptr) {
    *hours = _hours;
  }
  if (minutes != nullptr) {
    *minutes = _minutes;
  }
  if (seconds != nullptr) {
    *seconds = _seconds;
  }
  if (subSeconds != nullptr) {
    *subSeconds = _subSeconds;
  }
  if (period != nullptr) {
    *period = _hoursPeriod;
  }
}

/**
  * @brief  get RTC week day.
  * @retval return the current week day from the RTC.
  */
uint8_t STM32RTC::getWeekDay(void)
{
  syncDate();
  return _wday;
}

/**
  * @brief  get RTC day.
  * @retval return the current day from the RTC.
  */
uint8_t STM32RTC::getDay(void)
{
  syncDate();
  return _day;
}

/**
  * @brief  get RTC month.
  * @retval return the current month from the RTC.
  */
uint8_t STM32RTC::getMonth(void)
{
  syncDate();
  return _month;
}

/**
  * @brief  get RTC year.
  * @retval return the current year from the RTC.
  */
uint8_t STM32RTC::getYear(void)
{
  syncDate();
  return _year;
}

/**
  * @brief  get RTC time.
  * @param  weekDay: pointer to the current weekDay
  * @param  day: pointer to the current day
  * @param  month: pointer to the current month
  * @param  year: pointer to the current year
  * @retval none
  */
void STM32RTC::getDate(uint8_t *weekDay, uint8_t *day, uint8_t *month, uint8_t *year)
{
  syncDate();
  if (weekDay != nullptr) {
    *weekDay = _wday;
  }
  if (day != nullptr) {
    *day = _day;
  }
  if (month != nullptr) {
    *month = _month;
  }
  if (year != nullptr) {
    *year = _year;
  }
}

/**
  * @brief  get RTC alarm subsecond.
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval return the current alarm subsecond.
  */
uint32_t STM32RTC::getAlarmSubSeconds(Alarm name)
{
  uint32_t alarmSubSeconds = 0;
  syncAlarmTime(name);
#ifdef RTC_ALARM_B
  if (name == ALARM_B) {
    alarmSubSeconds =  _alarmBSubSeconds;
  } else
#endif
  {
    alarmSubSeconds =  _alarmSubSeconds;
  }
  return alarmSubSeconds;
}

/**
  * @brief  get RTC alarm second.
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval return the current alarm second.
  */
uint8_t STM32RTC::getAlarmSeconds(Alarm name)
{
  uint8_t alarmSeconds = 0;
  syncAlarmTime(name);
#ifdef RTC_ALARM_B
  if (name == ALARM_B) {
    alarmSeconds =  _alarmBSeconds;
  } else
#endif
  {
    alarmSeconds =  _alarmSeconds;
  }
  return alarmSeconds;
}

/**
  * @brief  get RTC alarm minute.
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval return the current alarm minute.
  */
uint8_t STM32RTC::getAlarmMinutes(Alarm name)
{
  uint8_t alarmMinutes = 0;
  syncAlarmTime(name);
#ifdef RTC_ALARM_B
  if (name == ALARM_B) {
    alarmMinutes =  _alarmBMinutes;
  } else
#endif
  {
    alarmMinutes =  _alarmMinutes;
  }
  return alarmMinutes;
}

/**
  * @brief  get RTC alarm hour.
  * @param name: optional (default: ALARM_A)
  *        ALARM_A or ALARM_B if exists
  * @retval return the current alarm hour.
  */
uint8_t STM32RTC::getAlarmHours(Alarm name)
{
  return getAlarmHours(nullptr, name);
}

/**
  * @brief  get RTC alarm hour.
  * @param  format: optional (default: nullptr)
  *         pointer to the current hour format set in the RTC: AM or PM
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval return the current alarm hour.
  */
uint8_t STM32RTC::getAlarmHours(AM_PM *period, Alarm name)
{
  uint8_t alarmHours = 0;
  syncAlarmTime(name);
#ifdef RTC_ALARM_B
  if (name == ALARM_B) {
    if (period != nullptr) {
      *period = _alarmBPeriod;
    }
    alarmHours =  _alarmBHours;
  } else
#endif
  {
    if (period != nullptr) {
      *period = _alarmPeriod;
    }
    alarmHours =  _alarmHours;
  }
  return alarmHours;
}

/**
  * @brief  get RTC alarm day.
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval return the current alarm day.
  */
uint8_t STM32RTC::getAlarmDay(Alarm name)
{
  uint8_t alarmDay = 0;
  syncAlarmTime(name);
#ifdef RTC_ALARM_B
  if (name == ALARM_B) {
    alarmDay =  _alarmBDay;
  } else
#endif
  {
    alarmDay =  _alarmDay;
  }
  return alarmDay;
}

/**
  * @brief  get RTC alarm month.
  * @NOTE   This function is kept for compatibility but the STM32 RTC
  *         can't assign a month to an alarm. See board datasheet.
  * @retval always returns 0
  */
uint8_t STM32RTC::getAlarmMonth(void)
{
  return 0;
}

/**
  * @brief  get RTC alarm year.
  * @NOTE   This function is kept for compatibility but the STM32 RTC
  *         can't assign a year to an alarm. See board datasheet.
  * @retval always returns 0
  */
uint8_t STM32RTC::getAlarmYear(void)
{
  return 0;
}

/*
 * Set Functions
 */

/**
  * @brief  set RTC subseconds.
  * @param  subseconds: 0-999 milliseconds
  * @retval none
  */
void STM32RTC::setSubSeconds(uint32_t subSeconds)
{
  syncTime();
  if (subSeconds < 1000) {
    _subSeconds = subSeconds;
  }
  RTC_SetTime(_hours, _minutes, _seconds, _subSeconds, (_hoursPeriod == AM) ? HOUR_AM : HOUR_PM);
  _timeSet = true;
}

/**
  * @brief  set RTC seconds.
  * @param  seconds: 0-59
  * @retval none
  */
void STM32RTC::setSeconds(uint8_t seconds)
{
  syncTime();
  if (seconds < 60) {
    _seconds = seconds;
  }
  RTC_SetTime(_hours, _minutes, _seconds, _subSeconds, (_hoursPeriod == AM) ? HOUR_AM : HOUR_PM);
  _timeSet = true;
}

/**
  * @brief  set RTC minutes.
  * @param  minutes: 0-59
  * @retval none
  */
void STM32RTC::setMinutes(uint8_t minutes)
{
  syncTime();
  if (minutes < 60) {
    _minutes = minutes;
  }
  RTC_SetTime(_hours, _minutes, _seconds, _subSeconds, (_hoursPeriod == AM) ? HOUR_AM : HOUR_PM);
  _timeSet = true;
}

/**
  * @brief  set RTC hours.
  * @param  hours: 0-23
  * @param  period: hour format AM or PM (optional)
  * @retval none
  */
void STM32RTC::setHours(uint8_t hours, AM_PM period)
{
  syncTime();
  if (hours < 24) {
    _hours = hours;
  }
  if (_format == HOUR_12) {
    _hoursPeriod = period;
  }
  RTC_SetTime(_hours, _minutes, _seconds, _subSeconds, (_hoursPeriod == AM) ? HOUR_AM : HOUR_PM);
  _timeSet = true;
}

/**
  * @brief  set RTC time.
  * @param  hours: 0-23
  * @param  minutes: 0-59
  * @param  seconds: 0-59
  * @param  subSeconds: 0-999 (optional)
  * @param  period: hour format AM or PM (optional)
  * @retval none
  */
void STM32RTC::setTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, AM_PM period)
{
  syncTime();
  if (subSeconds < 1000) {
    _subSeconds = subSeconds;
  }
  if (seconds < 60) {
    _seconds = seconds;
  }
  if (minutes < 60) {
    _minutes = minutes;
  }
  if (hours < 24) {
    _hours = hours;
  }
  if (_format == HOUR_12) {
    _hoursPeriod = period;
  }
  RTC_SetTime(_hours, _minutes, _seconds, _subSeconds, (_hoursPeriod == AM) ? HOUR_AM : HOUR_PM);
  _timeSet = true;
}

/**
  * @brief  set RTC week day.
  * @param  week day: 1-7 (Monday first)
  * @retval none
  */
void STM32RTC::setWeekDay(uint8_t weekDay)
{
  syncDate();
  if ((weekDay >= 1) && (weekDay <= 7)) {
    _wday = weekDay;
  }
  RTC_SetDate(_year, _month, _day, _wday);
  _timeSet = true;
}

/**
  * @brief  set RTC day.
  * @param  day: 1-31
  * @retval none
  */
void STM32RTC::setDay(uint8_t day)
{
  syncDate();
  if ((day >= 1) && (day <= 31)) {
    _day = day;
  }
  RTC_SetDate(_year, _month, _day, _wday);
  _timeSet = true;
}

/**
  * @brief  set RTC month.
  * @param  month: 1-12
  * @retval none
  */
void STM32RTC::setMonth(uint8_t month)
{
  syncDate();
  if ((month >= 1) && (month <= 12)) {
    _month = month;
  }
  RTC_SetDate(_year, _month, _day, _wday);
  _timeSet = true;
}

/**
  * @brief  set RTC year.
  * @param  year: 0-99
  * @retval none
  */
void STM32RTC::setYear(uint8_t year)
{
  syncDate();
  if (year < 100) {
    _year = year;
  }
  RTC_SetDate(_year, _month, _day, _wday);
  _timeSet = true;
}

/**
  * @brief  set RTC calendar.
  * @param  day: 1-31
  * @param  month: 1-12
  * @param  year: 0-99
  * @retval none
  */
void STM32RTC::setDate(uint8_t day, uint8_t month, uint8_t year)
{
  syncDate();
  if ((day >= 1) && (day <= 31)) {
    _day = day;
  }
  if ((month >= 1) && (month <= 12)) {
    _month = month;
  }
  if (year < 100) {
    _year = year;
  }
  RTC_SetDate(_year, _month, _day, _wday);
  _timeSet = true;
}

/**
  * @brief  set RTC calendar.
  * @param  weekDay: 1-7 (Monday first)
  * @param  day: 1-31
  * @param  month: 1-12
  * @param  year: 0-99
  * @retval none
  */
void STM32RTC::setDate(uint8_t weekDay, uint8_t day, uint8_t month, uint8_t year)
{
  syncDate();
  if ((weekDay >= 1) && (weekDay <= 7)) {
    _wday = weekDay;
  }
  if ((day >= 1) && (day <= 31)) {
    _day = day;
  }
  if ((month >= 1) && (month <= 12)) {
    _month = month;
  }
  if (year < 100) {
    _year = year;
  }
  RTC_SetDate(_year, _month, _day, _wday);
  _timeSet = true;
}

/**
  * @brief  set RTC alarm subseconds.
  * @param  subseconds: 0-999 (in ms) or 32bit nb of milliseconds in BIN mode
  * @param name: optional (default: ALARM_A)
  *        ALARM_A or ALARM_B if exists
  * @retval none
  */
void STM32RTC::setAlarmSubSeconds(uint32_t subSeconds, Alarm name)
{
#ifndef RTC_ALARM_B
  UNUSED(name);
#endif
  if ((_mode == MODE_BIN) || (subSeconds < 1000)) {
#ifdef RTC_ALARM_B
    if (name == ALARM_B) {
      _alarmBSubSeconds = subSeconds;
    } else
#endif
    {
      _alarmSubSeconds = subSeconds;
    }
  }
}

/**
  * @brief  set RTC alarm second.
  * @param  seconds: 0-59
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval none
  */
void STM32RTC::setAlarmSeconds(uint8_t seconds, Alarm name)
{
  if (seconds < 60) {
#ifdef RTC_ALARM_B
    if (name == ALARM_B) {
      _alarmBSeconds = seconds;
    } else
#else
    UNUSED(name);
#endif
    {
      _alarmSeconds = seconds;
    }
  }
}

/**
  * @brief  set RTC alarm minute.
  * @param  minutes: 0-59
  * @param name: optional (default: ALARM_A)
  *        ALARM_A or ALARM_B if exists
  * @retval none
  */
void STM32RTC::setAlarmMinutes(uint8_t minutes, Alarm name)
{
  if (minutes < 60) {
#ifdef RTC_ALARM_B
    if (name == ALARM_B) {
      _alarmBMinutes = minutes;
    } else
#else
    UNUSED(name);
#endif
    {
      _alarmMinutes = minutes;
    }
  }
}

/**
  * @brief  set RTC alarm hour.
  * @param  hour: 0-23 or 0-12
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval none
  */
void STM32RTC::setAlarmHours(uint8_t hours, Alarm name)
{
  setAlarmHours(hours, AM, name);
}

/**
  * @brief  set RTC alarm hour.
  * @param  hour: 0-23 or 0-12
  * @param  period: hour format AM or PM (optional)
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval none
  */
void STM32RTC::setAlarmHours(uint8_t hours, AM_PM period, Alarm name)
{
  if (hours < 24) {
#ifdef RTC_ALARM_B
    if (name == ALARM_B) {
      _alarmBHours = hours;
      if (_format == HOUR_12) {
        _alarmBPeriod = period;
      }
    } else
#else
    UNUSED(name);
#endif
    {
      _alarmHours = hours;
      if (_format == HOUR_12) {
        _alarmPeriod = period;
      }
    }
  }
}


/**
  * @brief  set RTC alarm time.
  * @param  subSeconds: 0-999 ms or 32bit nb of milliseconds in BIN mode
  * @param  name: ALARM_A or ALARM_B if exists
  * @retval none
  */
void STM32RTC::setAlarmTime(uint32_t subSeconds, Alarm name)
{
  setAlarmTime(0, 0, 0, subSeconds, AM, name);
}

/**
  * @brief  set RTC alarm time.
  * @param  hours: 0-23
  * @param  minutes: 0-59
  * @param  seconds: 0-59
  * @param  name: ALARM_A or ALARM_B if exists
  * @retval none
  */
void STM32RTC::setAlarmTime(uint8_t hours, uint8_t minutes, uint8_t seconds, Alarm name)
{
  setAlarmTime(hours, minutes, seconds, 0, AM, name);
}

/**
  * @brief  set RTC alarm time.
  * @param  hours: 0-23
  * @param  minutes: 0-59
  * @param  seconds: 0-59
  * @param  subSeconds: 0-999 ms or 32bit nb of milliseconds in BIN mode
  * @param  name: ALARM_A or ALARM_B if exists
  * @retval none
  */
void STM32RTC::setAlarmTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, Alarm name)
{
  setAlarmTime(hours, minutes, seconds, subSeconds, AM, name);
}

/**
  * @brief  set RTC alarm time.
  * @param  hours: 0-23 (not used in BIN mode)
  * @param  minutes: 0-59 (not used in BIN mode)
  * @param  seconds: 0-59 (not used in BIN mode)
  * @param  subSeconds: 0-999 ms (optional) or 32bit nb of milliseconds in BIN mode
  * @param  period: hour format AM or PM (optional)
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval none
  */
void STM32RTC::setAlarmTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t subSeconds, AM_PM period, Alarm name)
{
  setAlarmHours(hours, period, name);
  setAlarmMinutes(minutes, name);
  setAlarmSeconds(seconds, name);
  setAlarmSubSeconds(subSeconds, name);
}

/**
  * @brief  set RTC alarm day.
  * @param  day: 1-31
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval none
  */
void STM32RTC::setAlarmDay(uint8_t day, Alarm name)
{
  if ((day >= 1) && (day <= 31)) {
#ifdef RTC_ALARM_B
    if (name == ALARM_B) {
      _alarmBDay = day;
    }
#else
    UNUSED(name);
#endif
    {
      _alarmDay = day;
    }
  }
}

/**
  * @brief  set RTC alarm month.
  * @NOTE   This function is kept for compatibility but the STM32 RTC
  *         can't assign a month to an alarm. See board datasheet.
  * @param  month is ignored.
  */
void STM32RTC::setAlarmMonth(uint8_t month)
{
  UNUSED(month);
}

/**
  * @brief  set RTC alarm year.
  * @NOTE   This function is kept for compatibility but the STM32 RTC
  *         can't assign a year to an alarm. See board datasheet.
  * @param  year is ignored.
  */
void STM32RTC::setAlarmYear(uint8_t year)
{
  UNUSED(year);
}

/**
  * @brief  set RTC alarm date.
  * @NOTE   Parameters month and year are ignored because the STM32 RTC can't
  *         assign a month or year to an alarm. See board datasheet.
  * @param  day: 1-31
  * @param  month is ignored
  * @param  year is ignored
  * @param name: optional (default: ALARM_A)
  *        ALARM_A or ALARM_B if exists
  */
void STM32RTC::setAlarmDate(uint8_t day, uint8_t month, uint8_t year, Alarm name)
{
  UNUSED(month);
  UNUSED(year);

  setAlarmDay(day, name);
}

/**
  * @brief  get epoch time
  * @param  subSeconds: optional pointer to where to store subseconds of the epoch in ms
  * @retval epoch time in seconds
  */
time_t STM32RTC::getEpoch(uint32_t *subSeconds)
{
  struct tm tm;

  syncDate();
  syncTime();

  tm.tm_isdst = -1;
  /*
   * mktime ignores the values supplied by the caller in the
   * tm_wday and tm_yday fields
   */
  tm.tm_yday = 0;
  tm.tm_wday = 0;
  tm.tm_year = _year + EPOCH_TIME_YEAR_OFF;
  tm.tm_mon = _month - 1;
  tm.tm_mday = _day;
  tm.tm_hour = _hours;
  tm.tm_min = _minutes;
  tm.tm_sec = _seconds;
  if (subSeconds != nullptr) {
    *subSeconds = _subSeconds;
  }

  return mktime(&tm);
}

/**
  * @brief  get epoch time since 1st January 2000, 00:00:00
  * @retval epoch time in seconds
  */
time_t STM32RTC::getY2kEpoch(void)
{
  return (getEpoch() - EPOCH_TIME_OFF);
}

/**
  * @brief  get alarm epoch time
  * @param  name: ALARM_A or ALARM_B if exists
  * @retval epoch time in seconds
  */
time_t STM32RTC::getAlarmEpoch(Alarm name)
{
  return getAlarmEpoch(nullptr, name);
}

/**
  * @brief  get alarm epoch time
  * @param  subSeconds: optional pointer to where to store subseconds of the epoch in ms
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  * @retval epoch time in seconds
  */
time_t STM32RTC::getAlarmEpoch(uint32_t *subSeconds, Alarm name)
{
  struct tm tm;

  tm.tm_isdst = -1;
  /*
   * mktime ignores the values supplied by the caller in the
   * tm_wday and tm_yday fields
   */
  tm.tm_yday = 0;
  tm.tm_wday = 0;
  tm.tm_year = _year + EPOCH_TIME_YEAR_OFF;
  tm.tm_mon = _month - 1;
  syncAlarmTime(name);
#ifdef RTC_ALARM_B
  if (name == ALARM_B) {
    tm.tm_mday = _alarmBDay;
    tm.tm_hour = _alarmBHours;
    tm.tm_min = _alarmBMinutes;
    tm.tm_sec = _alarmBSeconds;
    if (subSeconds != nullptr) {
      *subSeconds = _alarmBSubSeconds;
    }
  } else
#endif
  {
    tm.tm_mday = _alarmDay;
    tm.tm_hour = _alarmHours;
    tm.tm_min = _alarmMinutes;
    tm.tm_sec = _alarmSeconds;
    if (subSeconds != nullptr) {
      *subSeconds = _alarmSubSeconds;
    }
  }
  return mktime(&tm);
}

/**
  * @brief  set RTC alarm from epoch time
  * @param  epoch time in seconds
  * @param  Alarm_Match match enum
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  */
void STM32RTC::setAlarmEpoch(time_t ts, Alarm_Match match, Alarm name)
{
  setAlarmEpoch(ts, match, 0, name);
}

/**
  * @brief  set RTC alarm from epoch time
  * @param  epoch time in seconds
  * @param  Alarm_Match match enum
  * @param  subSeconds optional subSeconds in ms (default: 0)
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  */
void STM32RTC::setAlarmEpoch(time_t ts, Alarm_Match match, uint32_t subSeconds, Alarm name)
{
  if (ts < EPOCH_TIME_OFF) {
    ts = EPOCH_TIME_OFF;
  }

  time_t t = ts;
  struct tm *tmp = gmtime(&t);

  /* in BIN only mode, the time_t is not relevant, but only the subSeconds in ms */
  if (_mode != MODE_BIN) {
    setAlarmDay(tmp->tm_mday, name);
    setAlarmHours(tmp->tm_hour, name);
    setAlarmMinutes(tmp->tm_min, name);
    setAlarmSeconds(tmp->tm_sec, name);
  }
  setAlarmSubSeconds(subSeconds, name);
  enableAlarm(match, name);
}

/**
  * @brief  set RTC time from epoch time
  * @param  epoch time in seconds
  * @param  subSeconds subSeconds in ms
  */
void STM32RTC::setEpoch(time_t ts, uint32_t subSeconds)
{
  if (ts < EPOCH_TIME_OFF) {
    ts = EPOCH_TIME_OFF;
  }

  time_t t = ts;
  struct tm *tmp = gmtime(&t);

  _year = tmp->tm_year - EPOCH_TIME_YEAR_OFF;
  _month = tmp->tm_mon + 1;
  _day = tmp->tm_mday;
  if (tmp->tm_wday == 0) {
    _wday = RTC_WEEKDAY_SUNDAY;
  } else {
    _wday = tmp->tm_wday;
  }
  _hours = tmp->tm_hour;
  _minutes = tmp->tm_min;
  _seconds = tmp->tm_sec;
  _subSeconds = subSeconds;

  RTC_SetDate(_year, _month, _day, _wday);
  RTC_SetTime(_hours, _minutes, _seconds, _subSeconds, (_hoursPeriod == AM) ? HOUR_AM : HOUR_PM);
  _timeSet = true;
}

/**
  * @brief  set RTC time from epoch time since 1st January 2000, 00:00:00
  * @param  epoch time in seconds
  */
void STM32RTC::setY2kEpoch(time_t ts)
{
  setEpoch(ts + EPOCH_TIME_OFF);
}

/**
  * @brief  configure RTC source clock for low power
  * @param  none
  */
void STM32RTC::configForLowPower(Source_Clock source)
{
#if defined(HAL_PWR_MODULE_ENABLED)
#ifdef __HAL_RCC_RTCAPB_CLKAM_ENABLE
  __HAL_RCC_RTCAPB_CLKAM_ENABLE();
#endif

  setClockSource(source);
  begin();

  if (!isTimeSet()) {
    // Set arbitrary time for Lowpower; if not already set
    setTime(12, 0, 0, 0, AM);
  }
#endif
}

/**
  * @brief Check whether RTC alarm is set
  * @param name: optional (default: ALARM_A)
  *        ALARM_A or ALARM_B if exists
  * @retval True if Alarm is set
  */
bool STM32RTC::isAlarmEnabled(Alarm name)
{
  return RTC_IsAlarmSet(static_cast<alarm_t>(name));
}

/**
  * @brief  synchronise the time from the current RTC one
  * @param  none
  */
void STM32RTC::syncTime(void)
{
  hourAM_PM_t p = HOUR_AM;

  RTC_GetTime(&_hours, &_minutes, &_seconds, &_subSeconds, &p);
  _hoursPeriod = (p == HOUR_AM) ? AM : PM;
}

/**
  * @brief  synchronise the time from the current RTC one
  * @param  none
  */
void STM32RTC::syncDate(void)
{
  RTC_GetDate(&_year, &_month, &_day, &_wday);
#if defined(STM32F1xx)
  RTC_StoreDate();
#endif /* STM32F1xx */
}

/**
  * @brief  synchronise the specified alarm time from the current RTC one
  * @param  name: optional (default: ALARM_A)
  *         ALARM_A or ALARM_B if exists
  */
void STM32RTC::syncAlarmTime(Alarm name)
{
  hourAM_PM_t p = HOUR_AM;
  uint8_t match;
#ifdef RTC_ALARM_B
  if (name == ALARM_B) {
    RTC_GetAlarm(::ALARM_B, &_alarmBDay, &_alarmBHours, &_alarmBMinutes, &_alarmBSeconds,
                 &_alarmBSubSeconds, &p, &match);
    _alarmBPeriod = (p == HOUR_AM) ? AM : PM;
  } else
#else
  UNUSED(name);
#endif
  {
    RTC_GetAlarm(::ALARM_A, &_alarmDay, &_alarmHours, &_alarmMinutes, &_alarmSeconds,
                 &_alarmSubSeconds, &p, &match);
    _alarmPeriod = (p == HOUR_AM) ? AM : PM;
  }
  switch (static_cast<Alarm_Match>(match)) {
    case MATCH_OFF:
    case MATCH_YYMMDDHHMMSS://kept for compatibility
    case MATCH_MMDDHHMMSS:  //kept for compatibility
    case MATCH_DHHMMSS:
    case MATCH_HHMMSS:
    case MATCH_MMSS:
    case MATCH_SS:
#ifdef RTC_ALARM_B
      if (name == ALARM_B) {
        _alarmBMatch = static_cast<Alarm_Match>(match);
      } else
#endif
      {
        _alarmMatch = static_cast<Alarm_Match>(match);
      }
      break;
    default:
#ifdef RTC_ALARM_B
      if (name == ALARM_B) {
        _alarmBMatch = MATCH_OFF;
      } else
#endif
      {
        _alarmMatch = MATCH_OFF;
      }
      break;
  }
}
