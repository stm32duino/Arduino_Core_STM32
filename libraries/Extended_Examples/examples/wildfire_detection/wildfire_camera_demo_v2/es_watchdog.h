#ifndef __ES_WATCHDOG_H__
#define __ES_WATCHDOG_H__

#include <Arduino.h>
#include "project_configuration.h"

class es_watchdog
{
private:
public:
    es_watchdog(void);
    ~es_watchdog(void);

    bool isResetByWatchdog(void);

    bool init(void);
    void reload(void);
};

extern es_watchdog WATCHDOG;

#endif /* __ES_WATCHDOG_H__ */
