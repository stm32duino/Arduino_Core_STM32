#ifndef __ES_EM2050_H__
#define __ES_EM2050_H__

#include <Arduino.h>
#include "project_configuration.h"

struct DLresults
{
  int8_t SNR, RSSI, freq_error;
};

class es_em2050
{
private:
    bool _is_pwr_on;

public:
    es_em2050(void);
    ~es_em2050(void);

    void pwr_on(void);
    void pwr_off(void);

    void init(void);

    void get_device_info_on_log(void);

    void soft_sleep_disable(void);
    void soft_sleep_enable(void);
    void reset_to_bootloader(void);
    void reset_to_run(void);

    bool ping(void);
    bool is_network_joined(void);

    void log_console(uint32_t time_duration_ms);
    int readpwr(void);
    DLresults readDL(void);

    int schedule_uplink(uint8_t *payload, uint8_t payload_len);
};

extern es_em2050 EM2050;

#endif /* __ES_EM2050_H__ */
