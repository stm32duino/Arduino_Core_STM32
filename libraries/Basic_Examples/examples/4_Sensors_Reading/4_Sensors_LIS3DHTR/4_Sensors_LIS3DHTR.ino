/**
   @brief This example demonstrates how to read data from LIS3DHTR.

   @author mtnguyen
   @version 1.1.0
*/

#ifndef SENSORS_LIS3DHTR_ADDRESS
#error This board version do not has LIS3DHTR, please check again your parameters!
#endif

#include <LIS3DHTR.h>
#include <Wire.h>

LIS3DHTR<TwoWire> lis;

void setup(void)
{
    pinMode(SENSORS_PWR_ENABLE_PIN, OUTPUT);
    digitalWrite(SENSORS_PWR_ENABLE_PIN, HIGH);

    Serial.begin(115200);
    while (!Serial)
    {
    };

    Wire.setSDA(SENSORS_I2C_SDA_PIN);
    Wire.setSCL(SENSORS_I2C_SCL_PIN);
    Wire.begin();

    lis.begin(Wire, SENSORS_LIS3DHTR_ADDRESS);
    delay(100);
    //  lis.setFullScaleRange(LIS3DHTR_RANGE_2G);
    //  lis.setFullScaleRange(LIS3DHTR_RANGE_4G);
    //  lis.setFullScaleRange(LIS3DHTR_RANGE_8G);
    //  lis.setFullScaleRange(LIS3DHTR_RANGE_16G);
    //  lis.setOutputDataRate(LIS3DHTR_DATARATE_1HZ);
    //  lis.setOutputDataRate(LIS3DHTR_DATARATE_10HZ);
    //  lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
    lis.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
    //  lis.setOutputDataRate(LIS3DHTR_DATARATE_100HZ);
    //  lis.setOutputDataRate(LIS3DHTR_DATARATE_200HZ);
    //  lis.setOutputDataRate(LIS3DHTR_DATARATE_1_6KHZ);
    //  lis.setOutputDataRate(LIS3DHTR_DATARATE_5KHZ);
    lis.setHighSolution(true); // High solution enable
}
void loop(void)
{
    float x, y, z;

    if (!lis)
    {
        while (1)
        {
            Serial.println("LIS3DHTR didn't connect.");
            delay(1000);
        }
    }

    lis.getAcceleration(&x, &y, &z);
    Serial.print("x:");
    Serial.print(x);
    Serial.print("  ");
    Serial.print("y:");
    Serial.print(y);
    Serial.print("  ");
    Serial.print("z:");
    Serial.println(z);

    delay(500);
}