#include "es_em2050.h"
#include "es_log.h"
#include "es_led.h"
#include "project_configuration.h"
#include <STM32RTC.h>

static STM32RTC &rtc = STM32RTC::getInstance();

es_em2050::es_em2050(void)
{
    _is_pwr_on = false;
}

es_em2050::~es_em2050(void)
{
}

void es_em2050::pwr_off(void)
{
    digitalWrite(ECHOSTAR_PWR_ENABLE_PIN, LOW);
    _is_pwr_on = false;
}

void es_em2050::pwr_on(void)
{
    digitalWrite(ECHOSTAR_PWR_ENABLE_PIN, HIGH);
    _is_pwr_on = true;
}

void es_em2050::init(void)
{
    pinMode(ECHOSTAR_PWR_ENABLE_PIN, OUTPUT);
    pwr_on();

    pinMode(ECHOSTAR_BOOT_PIN, OUTPUT);
    pinMode(ECHOSTAR_RTS_PIN, OUTPUT);
    reset_to_run();
    soft_sleep_disable();

    ECHOSTAR_SERIAL.begin(115200);
    delay(1000);

    LOG.print("[INFO] main::em2050_init() | Ping EM2050:");
    while (!ping())
    {
        delay(1000);
        LOG.print(".");
    }
    LOG.println("OK");

    LOG.println("[INFO] main::em2050_init() | Set EM2050 TX Power to 23 dBm");
    while (ECHOSTAR_SERIAL.available())
    {
        ECHOSTAR_SERIAL.read();
    }
    ECHOSTAR_SERIAL.println("AT+TXPMSS=23");
    delay(2000);

    LOG.println("[INFO] main::em2050_init() | Disable LED on EM2050");
    while (ECHOSTAR_SERIAL.available())
    {
        ECHOSTAR_SERIAL.read();
    }
    ECHOSTAR_SERIAL.println("AT+LED=0");
    delay(2000);

#if defined(USING_TERRESTRIAL_NETWORK)
    LOG.println("[INFO] main::em2050_init() | Set EM2050 to use Terrestrial Network");
    ECHOSTAR_SERIAL.println("AT+REGION=EU868");
#else
    LOG.println("[INFO] main::em2050_init() | Set EM2050 to use Satellite Network");
    ECHOSTAR_SERIAL.println("AT+REGION=MSS-S");
#endif /* USING_TERRESTRIAL_NETWORK */
    delay(2000);

    LOG.print("[INFO] main::em2050_init() | Waiting EM2050 to join the network:");
#ifndef DEBUGGING_OPTION_NO_WAITING_FOR_NETWORK_TO_JOIN
    int counter = 0;
    while (!is_network_joined())
    {
        LOG.print(".");
        LED.short_blink(2);

        if (counter++ == 30) // Not joinning after 1 minute
        {
            LOG.println();
            LOG.println("[INFO] main::em2050_init() | Waited for satellite network join Failed");
            LOG.println("[INFO] main::em2050_init() | Switch EM2050 to use Terrestrial Network");
            LOG.print("[INFO] main::em2050_init() | Waiting EM2050 to join the network:");
            ECHOSTAR_SERIAL.println("AT+REGION=EU868");
        }

        delay(1600);
    }
#endif
    LOG.println("OK");
}

void es_em2050::get_device_info_on_log(void)
{
    soft_sleep_disable();
    LOG.println("[DEBUG] es_em2050::get_device_info_on_log() | General information on EM2050: ");

    uint32_t reading_start_timestamp_s = rtc.getEpoch();
    char char_buff[64];

    while (ECHOSTAR_SERIAL.available())
    {
        ECHOSTAR_SERIAL.read();
    }

    while (rtc.getEpoch() - reading_start_timestamp_s <= 5000) // Maximum reading of 5 seconds.
    {
        while (ECHOSTAR_SERIAL.available())
        {
            ECHOSTAR_SERIAL.read();
        }

        ECHOSTAR_SERIAL.println("AT&V");
        String temp = ECHOSTAR_SERIAL.readStringUntil('\n');
        LOG.println(temp);

        memset((void *)char_buff, 0, 64);
        temp.toCharArray(char_buff, 64);
        if ((char_buff[0] == 'O') && (char_buff[1] == 'K'))
        {
            break;
        }
    }
}

void es_em2050::soft_sleep_enable(void)
{
    pinMode(ECHOSTAR_RTS_PIN, OUTPUT);
    digitalWrite(ECHOSTAR_RTS_PIN, HIGH);
    delay(50);
}

void es_em2050::soft_sleep_disable(void)
{
    pinMode(ECHOSTAR_RTS_PIN, INPUT);
    delay(50);
}

bool es_em2050::ping(void)
{
    bool result = false;

    while (ECHOSTAR_SERIAL.available())
    {
        ECHOSTAR_SERIAL.read();
    }

    ECHOSTAR_SERIAL.println("AT");
    String temp = ECHOSTAR_SERIAL.readStringUntil('\n'); // AT
    temp = ECHOSTAR_SERIAL.readStringUntil('\n');        // Empty line
    temp = ECHOSTAR_SERIAL.readStringUntil('\n');        // OK

    char char_buff[16];
    memset((void *)char_buff, 0, 16);
    temp.toCharArray(char_buff, 16);

    return ((char_buff[0] == 'O') && (char_buff[1] == 'K'));
}

bool es_em2050::is_network_joined(void)
{
    bool result = false;

    while (ECHOSTAR_SERIAL.available())
    {
        ECHOSTAR_SERIAL.read();
    }

    ECHOSTAR_SERIAL.println("AT+NJS?");
    String temp = ECHOSTAR_SERIAL.readStringUntil('\n'); // AT+NJS?
    temp = ECHOSTAR_SERIAL.readStringUntil('\n');        // NJS:0 | NJS:1

    if (temp.length() == 6)
    {
        char char_buff[16];
        memset((void *)char_buff, 0, 16);
        temp.toCharArray(char_buff, 16);

        result = (char_buff[0] == 'N') &&
                 (char_buff[1] == 'J') &&
                 (char_buff[2] == 'S') &&
                 (char_buff[3] == ':') &&
                 (char_buff[4] == '1');
    }

    return result;
}

void es_em2050::log_console(uint32_t time_duration_s)
{
    uint32_t log_start_timestamp = rtc.getEpoch();
    while (rtc.getEpoch() - log_start_timestamp <= time_duration_s)
    {
        if (ECHOSTAR_SERIAL.available())
        {
            LOG.print((char)ECHOSTAR_SERIAL.read());
        }
    }
}

void es_em2050::reset_to_bootloader(void)
{
    digitalWrite(ECHOSTAR_nRST_PIN, LOW);
    digitalWrite(ECHOSTAR_BOOT_PIN, LOW);
    delay(200);
    digitalWrite(ECHOSTAR_nRST_PIN, HIGH);
}

void es_em2050::reset_to_run(void)
{
    digitalWrite(ECHOSTAR_nRST_PIN, LOW);
    digitalWrite(ECHOSTAR_BOOT_PIN, HIGH);
    delay(200);
    digitalWrite(ECHOSTAR_nRST_PIN, HIGH);
}

int es_em2050::readpwr(void)
{
    while (ECHOSTAR_SERIAL.available())
    {
        ECHOSTAR_SERIAL.read();
    }

    ECHOSTAR_SERIAL.println("AT+CTP?");

    ECHOSTAR_SERIAL.setTimeout(2000); // Timeout
    String temp = ECHOSTAR_SERIAL.readStringUntil('\n');
    temp = ECHOSTAR_SERIAL.readStringUntil(':');
    temp = ECHOSTAR_SERIAL.readStringUntil('\n');

    return temp.toInt();
}

void array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i * 2 + 0] = nib1 < 0xA ? '0' + nib1 : 'A' + nib1 - 0xA;
        buffer[i * 2 + 1] = nib2 < 0xA ? '0' + nib2 : 'A' + nib2 - 0xA;
    }
    buffer[len * 2] = '\0';
}

// Read Downlink RSSI from EM2050
DLresults es_em2050::readDL(void)
{
    DLresults read;
    while (ECHOSTAR_SERIAL.available())
    {
        ECHOSTAR_SERIAL.read();
    }
    ECHOSTAR_SERIAL.println("AT+PKTST?");

    ECHOSTAR_SERIAL.setTimeout(2000); // Timeout
    String temp = ECHOSTAR_SERIAL.readStringUntil('\n');
    temp = ECHOSTAR_SERIAL.readStringUntil(':');
    temp = ECHOSTAR_SERIAL.readStringUntil(',');
    read.SNR = temp.toInt();
    temp = ECHOSTAR_SERIAL.readStringUntil(',');
    read.RSSI = temp.toInt();
    temp = ECHOSTAR_SERIAL.readStringUntil('\n');
    read.freq_error = temp.toInt();
    return read;
}
int es_em2050::schedule_uplink(uint8_t *payload, uint8_t payload_len)
{
    if (payload == NULL)
    {
        return -1;
    }
    if (payload_len > 51)
    {
        return -2;
    }

    if (!_is_pwr_on)
    {
        pwr_on();
        delay(100);
    }

    uint32_t start_timestamp = rtc.getEpoch();

    bool ping_result = false;
    while (!ping_result)
    {
        ping_result = ping();
        delay(1000);

        if (rtc.getEpoch() - start_timestamp > (EM2050_SENDING_TIMEOUT_S))
        {
            return -3; // Timeout
        }
    }

    char str[128];
    memset((void *)str, 0, 128);
    array_to_string(payload, payload_len, str);

    if (ping_result)
    {

        bool packet_queued = false;
        char char_buff[16];
        while (!packet_queued)
        {
            while (ECHOSTAR_SERIAL.available())
            {
                ECHOSTAR_SERIAL.read();

                if (rtc.getEpoch() - start_timestamp > (EM2050_SENDING_TIMEOUT_S))
                {
                    return -3; // Timeout
                }
            }

            ECHOSTAR_SERIAL.print("AT+SENDB=1,0,1,1,");
            ECHOSTAR_SERIAL.println(str);

            String temp = ECHOSTAR_SERIAL.readStringUntil('\n'); // AT+SENDB=1,0,1,...
            LOG.print("1: ");
            LOG.println(temp);
            temp = ECHOSTAR_SERIAL.readStringUntil('\n'); // Empty line
            LOG.print("1: ");
            LOG.println(temp);
            temp = ECHOSTAR_SERIAL.readStringUntil('\n'); // QUEUED:1 | ERROR...
            LOG.print("1: ");
            LOG.println(temp);

            memset((void *)char_buff, 0, 16);
            temp.toCharArray(char_buff, 16);

            if ((char_buff[0] == 'Q') &&
                (char_buff[1] == 'U') &&
                (char_buff[2] == 'E') &&
                (char_buff[3] == 'U') &&
                (char_buff[4] == 'E') &&
                (char_buff[5] == 'D'))
            {
                break;
            }

            if (rtc.getEpoch() - start_timestamp > (EM2050_SENDING_TIMEOUT_S))
            {
                return -3; // Timeout
            }

            delay(EM2050_SENDING_RETRY_TIME_S * 1000); // Todo: Low power
        }

        LOG.print("[INFO] es_em2050::schedule_uplink() | Data length: ");
        LOG.print(payload_len);
        LOG.print(" | Data: ");
        LOG.println(str);
    }

    return 0; // Done
}

es_em2050 EM2050;
