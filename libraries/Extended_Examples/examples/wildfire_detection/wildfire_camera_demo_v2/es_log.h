#ifndef __ES_LOG_H__
#define __ES_LOG_H__

#include <Arduino.h>
#include "project_configuration.h"

class es_log
{
private:
public:
    es_log();
    ~es_log();

    void init(void);

    void println(void);

    void print(String s);
    void println(String s);

    void print(const char *s);
    void println(const char *s);

    void print(char c);
    void println(char c);

    void print(int i);
    void print_hex(int i);
    void println(int i);

    void print(unsigned int i);
    void println(unsigned int i);

    void print(float f);
    void println(float f);

    void print(double d);
    void println(double d);
};

extern es_log LOG;

#endif /* __ES_LOG_H__ */
