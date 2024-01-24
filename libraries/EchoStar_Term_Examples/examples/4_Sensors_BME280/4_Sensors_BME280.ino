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
  pinMode(SENSORS_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(SENSORS_PWR_ENABLE_PIN, HIGH);

  Wire.setSDA(SENSORS_I2C_SDA_PIN);
  Wire.setSCL(SENSORS_I2C_SCL_PIN);
  Wire.begin();

  USB_SERIAL.begin(115200);
  while (!USB_SERIAL)
    ;
  USB_SERIAL.println("\nEchoStar I2C Scanner");

  delay(200);

  unsigned status = bme.begin(SENSORS_BME280_ADDRESS, &Wire);
  if (!status)
  {
    USB_SERIAL.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    USB_SERIAL.print("SensorID was: 0x");
    USB_SERIAL.println(bme.sensorID(), 16);
    USB_SERIAL.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    USB_SERIAL.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    USB_SERIAL.print("        ID of 0x60 represents a BME 280.\n");
    USB_SERIAL.print("        ID of 0x61 represents a BME 680.\n");
    while (1)
      delay(10);
  }

  USB_SERIAL.println("BME280 Initialization DONE");
}

void loop()
{
  printValues();
  delay(1000);
}

void printValues()
{
  USB_SERIAL.print("Temperature = ");
  USB_SERIAL.print(bme.readTemperature());
  USB_SERIAL.println(" °C");

  USB_SERIAL.print("Pressure = ");

  USB_SERIAL.print(bme.readPressure() / 100.0F);
  USB_SERIAL.println(" hPa");

  USB_SERIAL.print("Approx. Altitude = ");
  USB_SERIAL.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  USB_SERIAL.println(" m");

  USB_SERIAL.print("Humidity = ");
  USB_SERIAL.print(bme.readHumidity());
  USB_SERIAL.println(" %");

  USB_SERIAL.println();
}
