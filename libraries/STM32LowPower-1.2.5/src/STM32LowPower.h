/**
******************************************************************************
* @file    STM32LowPower.h
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

#ifndef _STM32_LOW_POWER_H_
#define _STM32_LOW_POWER_H_

#include <Arduino.h>

#include "low_power.h"

// Check if PWR HAL enable in variants/board_name/stm32yzxx_hal_conf.h
#ifndef HAL_PWR_MODULE_ENABLED
  #error "PWR configuration is missing. Check flag HAL_PWR_MODULE_ENABLED in variants/board_name/stm32yzxx_hal_conf.h"
#endif

#include "STM32RTC.h"

enum LP_Mode : uint8_t {
  IDLE_MODE,
  SLEEP_MODE,
  DEEP_SLEEP_MODE,
  SHUTDOWN_MODE
};

typedef void (*voidFuncPtrVoid)(void) ;

class STM32LowPower {
  public:
    STM32LowPower();

    void begin(void);

    void idle(uint32_t ms = 0);
    void idle(int ms)
    {
      idle((uint32_t)ms);
    }

    void sleep(uint32_t ms = 0);
    void sleep(int ms)
    {
      sleep((uint32_t)ms);
    }

    void deepSleep(uint32_t ms = 0);
    void deepSleep(int ms)
    {
      deepSleep((uint32_t)ms);
    }

    void shutdown(uint32_t ms = 0);
    void shutdown(int ms)
    {
      shutdown((uint32_t)ms);
    }

    void attachInterruptWakeup(uint32_t pin, voidFuncPtrVoid callback, uint32_t mode, LP_Mode LowPowerMode = SHUTDOWN_MODE);

    void enableWakeupFrom(HardwareSerial *serial, voidFuncPtrVoid callback);
    void enableWakeupFrom(STM32RTC *rtc, voidFuncPtr callback, void *data = NULL);

  private:
    bool _configured;     // Low Power mode initialization status
    serial_t *_serial;    // Serial for wakeup from deep sleep
    bool _rtc_wakeup;     // Is RTC wakeup?
    void programRtcWakeUp(uint32_t ms, LP_Mode lp_mode);
    void setAlarmTime(uint32_t ms, STM32RTC &rtc);

};

extern STM32LowPower LowPower;

#endif // _STM32_LOW_POWER_H_
