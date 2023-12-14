/**
* @brief This example demonstrates how to read data from BME280.
*
* @author mtnguyen
* @version 1.0.0
*/

#include <Wire.h>
#include <Adafruit_Sensor.h> // https://github.com/adafruit/Adafruit_BME280_Library
#include <Adafruit_BME280.h> // https://github.com/adafruit/Adafruit_Sensor

Adafruit_BME280 bme;
#define SEALEVELPRESSURE_HPA (1013.25)

void setup()
{
  pinMode(SENSORS_ENABLE_PIN, OUTPUT);
  digitalWrite(SENSORS_ENABLE_PIN, HIGH);

  Wire.setSDA(SENSORS_I2C_SDA_PIN);
  Wire.setSCL(SENSORS_I2C_SCL_PIN);
  Wire.begin();

  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("\nEchoStar I2C Scanner");

  delay(200);

  unsigned status = bme.begin(SENSORS_BME280_ADDRESS, &Wire);
  if (!status)
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1)
      delay(10);
  }

  Serial.println("BME280 Initialization DONE");
}

void loop()
{
  printValues();
  delay(1000);
}

void printValues()
{
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}
