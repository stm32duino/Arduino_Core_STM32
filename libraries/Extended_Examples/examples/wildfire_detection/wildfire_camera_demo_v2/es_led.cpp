#include "es_led.h"
#include "project_configuration.h"

es_led_t::es_led_t(void)
{
    _led_current_state = 0;
    _is_disbled = false;
}

es_led_t::~es_led_t(void)
{
}

void es_led_t::init(void)
{
    pinMode(LED_BUILTIN, OUTPUT);
    off();
}

void es_led_t::on(void)
{
    if (!_is_disbled)
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }
}

void es_led_t::off(void)
{
    digitalWrite(LED_BUILTIN, LOW);
}

void es_led_t::disable(void)
{
    _is_disbled = true;
    off();
}

void es_led_t::enable(void)
{
    _is_disbled = false;
}

void es_led_t::blink(unsigned int num_of_blink, unsigned int on_period_ms, unsigned int off_period_ms)
{
    while (num_of_blink-- > 0)
    {
        on();
        delay(on_period_ms);
        off();
        delay(off_period_ms);
    }
}

void es_led_t::long_blink(unsigned int num_of_blink)
{
    blink(num_of_blink, 1000, 150);
}
void es_led_t::short_blink(unsigned int num_of_blink)
{
    blink(num_of_blink, 150, 50);
}

es_led_t LED;
