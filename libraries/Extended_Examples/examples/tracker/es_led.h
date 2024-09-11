#ifndef __ES_LED_H__
#define __ES_LED_H__

#include <Arduino.h>
#include "project_configuration.h"

class es_led_t
{
private:
    int _led_current_state;
    bool _is_disbled;

public:
    es_led_t(void);
    ~es_led_t(void);

    void init(void);

    void on(void);
    void off(void);

    void disable(void);
    void enable(void);

    void blink(unsigned int num_of_blink, unsigned int on_period_ms, unsigned int off_period_ms);
    void long_blink(unsigned int num_of_blink);
    void short_blink(unsigned int num_of_blink);

};

extern es_led_t LED;

#endif /* __ES_LED_H__ */
