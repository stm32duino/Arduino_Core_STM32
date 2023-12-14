/**
* @brief This example demonstrates how to read data from the accelerometer KX023-1025.
*
* @author mtnguyen
* @version 1.0.0
*/

#include <Wire.h>
#include <Kionix_KX023.h> // https://github.com/nguyenmanhthao996tn/Kionix_KX023

KX023 myIMU(Wire, SENSORS_KX023_ADDRESS);
float kx_x, kx_y, kx_z;

void setup() {
  pinMode(SENSORS_ENABLE_PIN, OUTPUT);
  digitalWrite(SENSORS_ENABLE_PIN, HIGH);

  Wire.setSDA(SENSORS_I2C_SDA_PIN);
  Wire.setSCL(SENSORS_I2C_SCL_PIN);
  Wire.begin();

  Serial.begin(115200);
  while (!Serial);
  Serial.println("\nEchoStar I2C Scanner");

  delay(200);

  if (myIMU.begin())
  {
    Serial.println("Could not find KX023-1025? Check wiring");
  }
  else
  {
    Serial.println("KX023-1025: OK");
  }
  myIMU.configContinuousReading(LOWPOWER, RANGE_8G, DATARATE_100HZ);

  delay(2000);
}

void loop() {
  myIMU.readAcceleration(&kx_x, &kx_y, &kx_z);
  Serial.print("KX023-1025: ");
  Serial.print(kx_x);
  Serial.print(", ");
  Serial.print(kx_y);
  Serial.print(", ");
  Serial.print(kx_z);
  Serial.println("");
  
  delay(100);
}
