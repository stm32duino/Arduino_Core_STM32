/**
 * @brief This example will scan for the address of I2C sensors on the board.
 *
 * @author mtnguyen
 * @version 1.0.0
 */

#include <Wire.h>

void setup() {
  pinMode(SENSORS_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(SENSORS_PWR_ENABLE_PIN, HIGH);

  Wire.setSDA(SENSORS_I2C_SDA_PIN);
  Wire.setSCL(SENSORS_I2C_SCL_PIN);
  Wire.begin();

  USB_SERIAL.begin(115200);
  while (!USB_SERIAL);
  USB_SERIAL.println("\nEchoStar I2C Scanner");

  delay(200);
}

void loop() {
  do_i2c_scan();
  delay(5000);
}

void do_i2c_scan(void) {
  byte error, address;
  int nDevices;

  USB_SERIAL.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      USB_SERIAL.print("I2C device found at address 0x");
      if (address < 16)
        USB_SERIAL.print("0");
      USB_SERIAL.print(address, HEX);
      USB_SERIAL.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      USB_SERIAL.print("Unknown error at address 0x");
      if (address < 16)
        USB_SERIAL.print("0");
      USB_SERIAL.println(address, HEX);
    }
  }
  if (nDevices == 0)
    USB_SERIAL.println("No I2C devices found\n");
  else
    USB_SERIAL.println("done\n");
}
