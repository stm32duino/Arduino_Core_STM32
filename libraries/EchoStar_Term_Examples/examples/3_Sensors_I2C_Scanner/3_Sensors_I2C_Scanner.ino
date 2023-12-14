/**
 * @brief This example will scan for the address of I2C sensors on the board.
 *
 * @author mtnguyen
 * @version 1.0.0
 */

#include <Wire.h>

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
}

void loop() {
  do_i2c_scan();
  delay(5000);
}

void do_i2c_scan(void) {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}
