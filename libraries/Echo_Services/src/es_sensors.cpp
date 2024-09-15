#include "es_sensors.h"
#include "es_sensors_address.h"
#include "es_log.h"
#include "es_delay.h"
#include "project_configuration.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h> // https://github.com/adafruit/Adafruit_BME680
#include <LIS3DHTR.h>
#include <Kionix_KX023.h> // https://github.com/nguyenmanhthao996tn/Kionix_KX023

es_sensors SENSORS;

static Adafruit_BME680 bme;
static LIS3DHTR<TwoWire> lis;
static KX023 kx(Wire, SENSORS_KX023_ADDRESS);

es_sensors::es_sensors(void)
{
    lis3dhtr_available = false;
    bme680_available = false;
    bme688_available = false;
}

es_sensors::~es_sensors(void)
{
}

void es_sensors::power_on(void)
{
    digitalWrite(SENSORS_PWR_ENABLE_PIN, HIGH);

    DELAY_MANAGER.delay_ms(100);

    // TODO: Only do init if the previous power state is OFF
    if (lis3dhtr_available)
    {
        lis.begin(Wire, SENSORS_LIS3DHTR_ADDRESS);
        delay(100);
        lis.setFullScaleRange(LIS3DHTR_RANGE_16G);
        lis.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
        lis.setHighSolution(true); // High solution enable
    }

    if (kx023_available)
    {
        KX023_Status_t status = kx.begin();
        if (status == KX023_STATUS_OK)
        {
            kx.configAsynchronousReadBackAccelerationData(KX023_ACCLERATION_RANGE_8G, KX023_ODR_25HZ);
            kx.setOperatingMode();
        }
    }

    if (bme688_available || bme680_available)
    {
        if (bme.begin())
        {
            bme.setTemperatureOversampling(BME680_OS_8X);
            bme.setHumidityOversampling(BME680_OS_2X);
            bme.setPressureOversampling(BME680_OS_4X);
        }
    }
}

void es_sensors::power_off(void)
{
    digitalWrite(SENSORS_PWR_ENABLE_PIN, LOW);
}

void es_sensors::init(void)
{
    pinMode(SENSORS_PWR_ENABLE_PIN, OUTPUT);
    power_on();

    DELAY_MANAGER.delay_ms(100);

    Wire.setSDA(SENSORS_I2C_SDA_PIN);
    Wire.setSCL(SENSORS_I2C_SCL_PIN);
    Wire.begin();

    DELAY_MANAGER.delay_ms(100);

    for (int i = 1; i <= 3; i++) // 3 try
    {
        LOG.print("[INFO] es_sensors::init() | Pinging accelerometers try #");
        LOG.print(i);
        LOG.print(": ");

        if (ping_lis3dhtr())
        {
            LOG.println("LIS3DHTR OK");
            lis3dhtr_available = true;
            break;
        }
        else if (ping_kx023())
        {
            LOG.println("KX023 OK");
            kx023_available = true;
            break;
        }
        else
        {
            LOG.println("FAIL");
        }

        DELAY_MANAGER.delay_ms(100);
    }

    for (int i = 1; i <= 3; i++) // 3 try
    {
        LOG.print("[INFO] es_sensors::init() | Pinging BME68x try #");
        LOG.print(i);
        LOG.print(": ");

        if (ping_bme68x())
        {
            LOG.println("OK");
            if (is_bme688())
            {
                bme688_available = true;
            }
            else
            {
                bme680_available = true;
            }

            break;
        }
        else
        {
            LOG.println("FAIL");
        }

        DELAY_MANAGER.delay_ms(100);
    }

    power_off();
}

void es_sensors::deinit(void)
{
    power_off();
}

bool es_sensors::ping_lis3dhtr(void)
{
    Wire.beginTransmission(SENSORS_LIS3DHTR_ADDRESS);
    uint8_t error = Wire.endTransmission();
    return (error == 0);
}

bool es_sensors::ping_kx023(void)
{
    Wire.beginTransmission(SENSORS_KX023_ADDRESS);
    uint8_t error = Wire.endTransmission();
    return (error == 0);
}

bool es_sensors::ping_bme68x(void)
{
    Wire.beginTransmission(SENSORS_BME68X_ADDRESS);
    uint8_t error = Wire.endTransmission();
    return (error == 0);
}

bool es_sensors::is_bme688(void)
{
    Wire.beginTransmission(SENSORS_BME68X_ADDRESS);

    Wire.write(0xF0); /* Variant_id reg address */
    Wire.endTransmission();
    Wire.requestFrom(SENSORS_BME68X_ADDRESS, 1);
    uint8_t value = Wire.read();

    Wire.endTransmission();

    return (value == 0x01);
}

float es_sensors::read_temperature(void)
{
    if (bme688_available || bme680_available)
    {
        return bme.readTemperature();
    }
    else
    {
        return 0;
    }
}

float es_sensors::read_humidity(void)
{
    if (bme688_available || bme680_available)
    {
        return bme.readHumidity();
    }
    else
    {
        return 0;
    }
}

float es_sensors::read_pressure(void)
{
    if (bme688_available || bme680_available)
    {
        return bme.readPressure();
    }
    else
    {
        return 0;
    }
}

void es_sensors::get_accel(float *x, float *y, float *z)
{
    if ((x == NULL) ||
        (y == NULL) ||
        (z == NULL))
    {
        return;
    }

    if (lis3dhtr_available)
    {
        lis.getAcceleration(x, y, z);
    }
    else if (kx023_available)
    {
        kx.readAsynchronousReadBackAccelerationData(x, y, z);
    }
    else
    {
        return;
    }
}

float es_sensors::get_accel_x(void)
{
    if (lis3dhtr_available)
    {
        return lis.getAccelerationX();
    }
    else if (kx023_available)
    {
        float x, y, z;
        kx.readAsynchronousReadBackAccelerationData(&x, &y, &z);
        return x;
    }
    else
    {
        return 0;
    }
}

float es_sensors::get_accel_y(void)
{
    if (lis3dhtr_available)
    {
        return lis.getAccelerationY();
    }
    else if (kx023_available)
    {
        float x, y, z;
        kx.readAsynchronousReadBackAccelerationData(&x, &y, &z);
        return y;
    }
    else
    {
        return 0;
    }
}

float es_sensors::get_accel_z(void)
{
    if (lis3dhtr_available)
    {
        return lis.getAccelerationZ();
    }
    else if (kx023_available)
    {
        float x, y, z;
        kx.readAsynchronousReadBackAccelerationData(&x, &y, &z);
        return z;
    }
    else
    {
        return 0;
    }
}
