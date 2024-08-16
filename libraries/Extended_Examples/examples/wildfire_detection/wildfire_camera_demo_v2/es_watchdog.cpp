#include "es_watchdog.h"
#include "es_log.h"

#include <IWatchdog.h>
#include <STM32RTC.h>

#ifdef USING_WATCHDOG

static STM32RTC &rtc = STM32RTC::getInstance();

es_watchdog::es_watchdog(void)
{
}

es_watchdog::~es_watchdog(void)
{
}

bool es_watchdog::isResetByWatchdog(void)
{
    bool reset_by_watchdog_flag = IWatchdog.isReset(true); // Clear the flag after read

    LOG.print("[DEBUG] es_watchdog::isResetByWatchdog() | The last reset is caused by ");
    if (reset_by_watchdog_flag)
    {
        LOG.println("WATCHDOG");
    }
    else
    {
        LOG.println("EXTERNAL");
    }

    return reset_by_watchdog_flag;
}

bool es_watchdog::init(void)
{
    // LOG.print("[DEBUG] es_watchdog::init() | Init Watchdog with the timeout of ");
    // LOG.print((int) WATCHDOG_TIMEOUT_S);
    // LOG.println(" seconds");

    IWatchdog.begin(1000000 * WATCHDOG_TIMEOUT_S);
    return IWatchdog.isEnabled();
}

void es_watchdog::reload(void)
{
    // LOG.print("[DEBUG] es_watchdog::init() | A watchdog reload is called at ");
    // LOG.println((unsigned int)rtc.getEpoch());
    
    IWatchdog.reload();
}

#else /* USING_WATCHDOG is commented out / disable */

es_watchdog::es_watchdog(void)
{
}

es_watchdog::~es_watchdog(void)
{
}

bool es_watchdog::isResetByWatchdog(void)
{
    return false;
}

bool es_watchdog::init(void)
{
    return false;
}

void es_watchdog::reload(void)
{
}

#endif

es_watchdog WATCHDOG;