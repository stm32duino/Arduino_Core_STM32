/* Wire Slave Receiver
by Wi6Labs

Demonstrates use of the Wire library.
Receives/sends data as an I2C/TWI slave device.
Refer to the "Wire Master Reader Writer" example for use with this.

Created 27 June 2017
Updated 14 August 2017
  - this example is now common to all STM32 boards

This example code is in the public domain.
*/

#include <Wire.h>

#define I2C_ADDR  2

void setup()
{
  Wire.begin(I2C_ADDR);         // join i2c bus with address #4
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop()
{
  //empty loop
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read();     // receive byte as a character
    Serial.print(c);          // print the character
  }
  int x = Wire.read();        // receive byte as an integer
  Serial.println(x);          // print the integer
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write("hello\n");  // respond with message of 6 bytes
                          // as expected by master
}
