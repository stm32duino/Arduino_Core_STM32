/**
******************************************************************************
* @file    STM32LowPower.cpp
* @author  Frederic Pillon
* @brief   Provides a STM32 Low Power interface with Arduino
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

#include "STM32LowPower.h"

STM32LowPower LowPower;


STM32LowPower::STM32LowPower()
{
  _configured = false;
  _serial = NULL;
  _rtc_wakeup = false;
}

/**
  * @brief  Initializes the low power mode
  * @param  None
  * @retval None
  */
void STM32LowPower::begin(void)
{
  LowPower_init();
  _configured = true;
}

/**
  * @brief  Enable the idle low power mode (STM32 sleep). Exit this mode on
  *         interrupt or in n milliseconds.
  * @param  ms: optional delay before leave the idle mode (default: 0).
  * @retval None
  */
void STM32LowPower::idle(uint32_t ms)
{
  if ((ms != 0) || _rtc_wakeup) {
    programRtcWakeUp(ms, IDLE_MODE);
  }
  LowPower_sleep(PWR_MAINREGULATOR_ON);
}

/**
  * @brief  Enable the sleep low power mode (STM32 sleep). Exit this mode on
  *         interrupt or in n milliseconds.
  * @param  ms: optional delay before leave the sleep mode (default: 0).
  * @retval None
  */
void STM32LowPower::sleep(uint32_t ms)
{
  if ((ms != 0) || _rtc_wakeup) {
    programRtcWakeUp(ms, SLEEP_MODE);
  }
#if defined(PWR_LOWPOWERREGULATOR_ON)
  LowPower_sleep(PWR_LOWPOWERREGULATOR_ON);
#else
  LowPower_sleep(PWR_MAINREGULATOR_ON);
#endif

}

/**
  * @brief  Enable the deepsleep low power mode (STM32 stop). Exit this mode on
  *         interrupt or in n milliseconds.
  * @param  ms: optional delay before leave the deepSleep mode (default: 0).
  * @retval None
  */
void STM32LowPower::deepSleep(uint32_t ms)
{
  if ((ms != 0) || _rtc_wakeup) {
    programRtcWakeUp(ms, DEEP_SLEEP_MODE);
  }
  LowPower_stop(_serial);
}

/**
  * @brief  Enable the shutdown low power mode (STM32 shutdown or standby mode).
  *          Exit this mode on interrupt or in n milliseconds.
  * @param  ms: optional delay before leave the shutdown mode (default: 0).
  * @retval None
  */
void STM32LowPower::shutdown(uint32_t ms)
{
  if ((ms != 0) || _rtc_wakeup) {
    programRtcWakeUp(ms, SHUTDOWN_MODE);
  }
  /* Get the rtc object to know if it is configured */
  STM32RTC &rtc = STM32RTC::getInstance();
  LowPower_shutdown(rtc.isConfigured());
}

/**
  * @brief  Enable GPIO pin in interrupt mode. If the pin is a wakeup pin, it is
  *         configured as wakeup source.
  * @param  pin:  pin number
  * @param  callback: pointer to callback function.
  * @param  mode: pin interrupt mode (HIGH, LOW, RISING, FALLING or CHANGE)
  * @param  LowPowerMode: Low power mode which will be used
  *         (IDLE_MODE, SLEEP_MODE, DEEP_SLEEP_MODE, SHUTDOWN_MODE)
  *         In case of SHUTDOWN_MODE only, Wakeup pin capability is activated
  * @retval None
  */
void STM32LowPower::attachInterruptWakeup(uint32_t pin, voidFuncPtrVoid callback, uint32_t mode, LP_Mode LowPowerMode)
{
  attachInterrupt(pin, callback, mode);

  if (LowPowerMode == SHUTDOWN_MODE) {
    // If Gpio is a Wake up pin activate it for shutdown (standby or shutdown stm32)
    LowPower_EnableWakeUpPin(pin, mode);
  }
}

/**
  * @brief  Enable a serial interface as a wakeup source.
  * @param  serial: pointer to a HardwareSerial
  * @param  callback: pointer to callback function called when leave the low power
  *                   mode.
  * @retval None
  */
void STM32LowPower::enableWakeupFrom(HardwareSerial *serial, voidFuncPtrVoid callback)
{
  if (serial != NULL) {
    _serial = &(serial->_serial);
    // Reconfigure serial for low power mode (using HSI as clock source)
    serial->configForLowPower();
    LowPower_EnableWakeUpUart(_serial, callback);
  }
}

/**
  * @brief  Attach a callback to a RTC alarm.
  * @param  rtc: pointer to a STM32RTC. Can be NULL as RTC is a Singleton.
  * @param  callback: pointer to callback function called when leave the low power
  *                   mode.
  * @param  data: optional pointer to callback data parameters (default NULL).
  * @retval None
  */
void STM32LowPower::enableWakeupFrom(STM32RTC *rtc, voidFuncPtr callback, void *data)
{
  if (rtc == NULL) {
    rtc = &(STM32RTC::getInstance());
  }
  _rtc_wakeup = true;
  rtc->attachInterrupt(callback, data);
}

/**
  * @brief  Configure the RTC alarm
  * @param  ms: time of the alarm in milliseconds.
  * @param  lp_mode: low power mode targeted.
  * @retval None
  */
void STM32LowPower::programRtcWakeUp(uint32_t ms, LP_Mode lp_mode)
{
  STM32RTC &rtc = STM32RTC::getInstance();
  STM32RTC::Source_Clock clkSrc = rtc.getClockSource();

  switch (lp_mode) {
    case IDLE_MODE:
    case SLEEP_MODE:
      break;
    // LSI or LSE must be selected as clock source to wakeup the device.
    case DEEP_SLEEP_MODE:
      clkSrc = (clkSrc == STM32RTC::HSE_CLOCK) ? STM32RTC::LSI_CLOCK : clkSrc;
      break;
    default:
    case SHUTDOWN_MODE:
#if defined(PWR_CR1_LPMS)
      // For shutdown mode LSE have to be used
      clkSrc = STM32RTC::LSE_CLOCK;
#else
      // LSE or LSI
      clkSrc = (clkSrc == STM32RTC::HSE_CLOCK) ? STM32RTC::LSI_CLOCK : clkSrc;
#endif
      break;
  }
  rtc.configForLowPower(clkSrc);

  setAlarmTime(ms, rtc);
}

static bool isLeapYear(uint8_t year2k)
{
  int year = year2k + 2000;

  // if year not divisible by 4 - not a leap year
  // else if year divisible by 4 and not by 100 - a leap year
  // else if year divisible by 400 - a leap year
  return (year % 4 != 0) ? false : (year % 100 != 0) ? true : year % 400 == 0;
}

void STM32LowPower::setAlarmTime(uint32_t ms, STM32RTC &rtc)
{
  if (ms != 0) {
    uint16_t subSecondsToAdd = ms % 1000;

    ms = ms / 1000;
    uint8_t daysToAdd = ms / 86400;
    uint8_t hoursToAdd = (ms - daysToAdd * 86400) / 3600;
    uint8_t minutesToAdd = (ms - daysToAdd * 86400 - hoursToAdd * 3600) / 60;
    uint8_t secondsToAdd = (ms - daysToAdd * 86400 - hoursToAdd * 3600 - minutesToAdd * 60);

    uint8_t hrCurrent, minCurrent, secCurrent;
    uint32_t subSecondsCurrent;
    STM32RTC::AM_PM period;
    rtc.getTime(&hrCurrent, &minCurrent, &secCurrent, &subSecondsCurrent, &period);

    uint8_t weekDay, currentDay, currentMonth, currentYear;
    rtc.getDate(&weekDay, &currentDay, &currentMonth, &currentYear);

    uint32_t ss = subSecondsCurrent + subSecondsToAdd;
    if (ss >= 1000) {
      ss -= 1000;
      secondsToAdd++;
    }

    if (secondsToAdd >= 60) {
      secondsToAdd = 0;
      minutesToAdd++;
    }
    uint8_t s = secCurrent + secondsToAdd;
    if (s >= 60) {
      s -= 60;
      minutesToAdd++;
    }

    if (minutesToAdd >= 60) {
      minutesToAdd -= 60;
      hoursToAdd++;
    }
    uint8_t m = minCurrent + minutesToAdd;
    if (m >= 60) {
      m -= 60;
      hoursToAdd++;
    }

    if (hoursToAdd >= 24) {
      hoursToAdd -= 24;
      daysToAdd++;
    }
    uint8_t h = hrCurrent + hoursToAdd;
    if (rtc._format == STM32RTC::Hour_Format::HOUR_12) {
      if (h >= 24) {
        h -= 24;
        daysToAdd++;
      } else if (h >= 12) {
        if (period == STM32RTC::AM_PM::AM) {
          period = STM32RTC::AM_PM::PM;
        } else {
          period = STM32RTC::AM_PM::AM;
          daysToAdd++;
        }

        if (h > 12) {
          h -= 12;
        }
      }
    } else if (h >= 24) {
      h -= 24;
      daysToAdd++;
    }

    // numbers of days in each month (february is calculated based on leap year)
    static uint8_t daysInMonths[] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    uint8_t endDay;
    if (currentMonth == 2) {
      endDay = isLeapYear(currentYear) ? 29 : 28;
    } else {
      endDay = daysInMonths[currentMonth - 1];
    }

    uint8_t d = currentDay + daysToAdd;
    if (d > endDay) {
      d -= endDay;
    }

    // month-year overflow isn't handled because its not supported by RTC's alarm

    rtc.setAlarmTime(h, m, s, ss, period);
    rtc.setAlarmDay(d);
    rtc.enableAlarm(STM32RTC::Alarm_Match::MATCH_DHHMMSS);
  }
}
