#include "es_log.h"
#include "es_delay.h"
#include "project_configuration.h"

#if defined(USING_LOG)

es_log::es_log()
{
}

es_log::~es_log()
{
}

void es_log::init(void)
{
    USB_SERIAL.begin(115200);
    while ((!USB_SERIAL) && (millis() < 5000))
        ;

    DELAY_MANAGER.delay_ms(100);
}

void es_log::println(void)
{
    USB_SERIAL.println();
}

void es_log::print(String s)
{
    USB_SERIAL.print(s);
}

void es_log::println(String s)
{
    USB_SERIAL.println(s);
}

void es_log::print(const char *s)
{
    USB_SERIAL.print(s);
}

void es_log::println(const char *s)
{
    USB_SERIAL.println(s);
}

void es_log::print(char c)
{
    USB_SERIAL.print(c);
}

void es_log::println(char c)
{
    USB_SERIAL.println(c);
}

void es_log::print(int i)
{
    USB_SERIAL.print(i);
}

void es_log::print_hex(int i)
{
    USB_SERIAL.print(i, HEX);
}

void es_log::println(unsigned int i)
{
    USB_SERIAL.println(i);
}

void es_log::print(unsigned int i)
{
    USB_SERIAL.print(i);
}

void es_log::println(int i)
{
    USB_SERIAL.println(i);
}

void es_log::print(float f)
{
    USB_SERIAL.print(f);
}

void es_log::println(float f)
{
    USB_SERIAL.println(f);
}

void es_log::print(double d)
{
    USB_SERIAL.print(d);
}

void es_log::println(double d)
{
    USB_SERIAL.println(d);
}

#else

es_log::es_log()
{
}

es_log::~es_log()
{
}

void es_log::init(void)
{
}

void es_log::println(void)
{
}

void es_log::print(String s)
{
}

void es_log::println(String s)
{
}

void es_log::print(const char *s)
{
}

void es_log::println(const char *s)
{
}

void es_log::print(char c)
{
}

void es_log::println(char c)
{
}

void es_log::print(int i)
{
}

void es_log::print_hex(int i)
{
}

void es_log::println(unsigned int i)
{
}

void es_log::print(unsigned int i)
{
}

void es_log::println(int i)
{
}

void es_log::print(float f)
{
}

void es_log::println(float f)
{
}

void es_log::print(double d)
{
}

void es_log::println(double d)
{
}

#endif /* USING_LOG */

es_log LOG;