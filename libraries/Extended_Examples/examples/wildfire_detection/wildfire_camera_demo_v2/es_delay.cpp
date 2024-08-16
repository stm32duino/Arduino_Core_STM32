#include "es_delay.h"
#include "project_configuration.h"

#include <STM32LowPower.h>
#include <STM32RTC.h>

static STM32RTC &rtc = STM32RTC::getInstance();
static uint32_t atime = 600;

es_delay::es_delay(void)
{
}

es_delay::~es_delay(void)
{
}

void es_delay::init(void)
{
    // Low-power library initialization
    rtc.begin();
    LowPower.begin();
    LowPower.enableWakeupFrom(&rtc, es_delay::alarm_match_irq, &atime);
}

void es_delay::delay_ms(uint32_t delay_time_ms)
{
#ifndef USING_SLEEP_MODE
    delay(delay_time_ms);
#else

    if (delay_time_ms >= 2000)
    {
        uint32_t second = delay_time_ms / 1000;
        uint32_t millisecond = delay_time_ms % 1000;

        rtc.setAlarmEpoch(rtc.getEpoch() + second);
        LowPower.deepSleep();

        delay(millisecond);
    }
    else
    {
        delay(delay_time_ms);
    }
#endif
}

void es_delay::delay_s(uint32_t delay_time_s)
{
    this->delay_ms(delay_time_s * 1000);
}

es_delay DELAY_MANAGER;