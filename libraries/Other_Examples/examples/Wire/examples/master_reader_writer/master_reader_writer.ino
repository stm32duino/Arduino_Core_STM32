/* Wire Master Reader Writer
by Wi6Labs

Demonstrates use of the Wire library.
Reads/writes data from/to an I2C/TWI slave device.
Refer to the "Wire Slave Sender Receiver" example for use with this.

Created 27 June 2017
Updated 14 August 2017
  - this example is now common to all STM32 boards

This example code is in the public domain.
*/

#include <Wire.h>

#define I2C_ADDR  2

byte x = 0;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  Wire.requestFrom(I2C_ADDR, 6);  // request 6 bytes from slave device

  while(Wire.available())         // slave may send less than requested
  {
    char c = Wire.read();         // receive a byte as character
    Serial.print(c);              // print the character
  }

  delay(10);

  Wire.beginTransmission(I2C_ADDR); // transmit to device
  Wire.write("x is ");              // sends five bytes
  Wire.write(x);                    // sends one byte
  Wire.endTransmission();           // stop transmitting
  x++;

  delay(500);
}
