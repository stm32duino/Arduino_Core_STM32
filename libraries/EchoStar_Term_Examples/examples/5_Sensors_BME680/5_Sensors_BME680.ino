/**
 * @brief This example demonstrates how to read data from BME680.
 *
 * @author mtnguyen
 * @version 1.1.0
 */

#ifndef SENSORS_BME680_ADDRESS
#error This board version do not has BME680, please check again your parameters!
#endif

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h" // https://github.com/adafruit/Adafruit_BME680

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme;

void setup(void)
{
  pinMode(SENSORS_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(SENSORS_PWR_ENABLE_PIN, HIGH);

  Wire.setSDA(SENSORS_I2C_SDA_PIN);
  Wire.setSCL(SENSORS_I2C_SCL_PIN);
  Wire.begin();

  USB_SERIAL.begin(115200);
  while (!USB_SERIAL)
    ;
  USB_SERIAL.println("\nEchoStar BME680 Test");

  if (!bme.begin(SENSORS_BME680_ADDRESS))
  {
    USB_SERIAL.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1)
      ;
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop(void)
{
  // Tell BME680 to begin measurement.
  unsigned long endTime = bme.beginReading();
  if (endTime == 0)
  {
    USB_SERIAL.println(F("Failed to begin reading :("));
    return;
  }
  USB_SERIAL.print(F("Reading started at "));
  USB_SERIAL.print(millis());
  USB_SERIAL.print(F(" and will finish at "));
  USB_SERIAL.println(endTime);

  USB_SERIAL.println(F("You can do other work during BME680 measurement."));
  delay(50);

  if (!bme.endReading())
  {
    USB_SERIAL.println(F("Failed to complete reading :("));
    return;
  }
  USB_SERIAL.print(F("Reading completed at "));
  USB_SERIAL.println(millis());

  USB_SERIAL.print(F("Temperature = "));
  USB_SERIAL.print(bme.temperature);
  USB_SERIAL.println(F(" *C"));

  USB_SERIAL.print(F("Pressure = "));
  USB_SERIAL.print(bme.pressure / 100.0);
  USB_SERIAL.println(F(" hPa"));

  USB_SERIAL.print(F("Humidity = "));
  USB_SERIAL.print(bme.humidity);
  USB_SERIAL.println(F(" %"));

  USB_SERIAL.print(F("Gas = "));
  USB_SERIAL.print(bme.gas_resistance / 1000.0);
  USB_SERIAL.println(F(" KOhms"));

  USB_SERIAL.print(F("Approx. Altitude = "));
  USB_SERIAL.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  USB_SERIAL.println(F(" m"));

  USB_SERIAL.println();
  delay(2000);
}
