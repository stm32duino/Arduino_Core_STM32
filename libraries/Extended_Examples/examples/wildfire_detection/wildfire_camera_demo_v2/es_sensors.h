#ifndef __ES_SENSORS_H__
#define __ES_SENSORS_H__

#include <Arduino.h>
#include <Wire.h>
#include "project_configuration.h"

class es_sensors
{
private:
    bool lis3dhtr_available;
    bool bme680_available;
    bool bme688_available;

    bool ping_lis3dhtr(void);
    bool ping_bme68x(void);

    bool is_bme688(void);

public:
    es_sensors(void);
    ~es_sensors(void);

    void power_on(void);
    void power_off(void);

    void init(void);
    void deinit(void);

    float read_temperature(void);
    float read_humidity(void);
    float read_pressure(void);
};

extern es_sensors SENSORS;

#endif /* __ES_SENSORS_H__ */
