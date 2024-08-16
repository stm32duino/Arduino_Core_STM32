#ifndef __ES_DELAY_H__
#define __ES_DELAY_H__

#include <Arduino.h>

class es_delay
{
private:
public:
    es_delay(void);
    ~es_delay(void);

    void init(void);
    void delay_ms(uint32_t delay_time_ms);
    void delay_s(uint32_t delay_time_s);

    static void alarm_match_irq(void *data)
    {
        // Do nothing here
    }
};

extern es_delay DELAY_MANAGER;

#endif /* __ES_DELAY_H__ */
