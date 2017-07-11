/* Wire Slave Receiver
by Wi6Labs

Demonstrates use of the Wire library, particullary with STM32F1xx boards where
we can't use slave Tx & Rx mode in same time.
Receives/sends data as an I2C/TWI slave device.
Refer to the "Wire Master Reader Writer" example for use with this.

Created 27 June 2017

This example code is in the public domain.
*/

#include <Wire.h>

#define SLAVE_MODE_RX 0
#define SLAVE_MODE_TX 1

#define I2C_ADDR  2

int w_r_mode = SLAVE_MODE_TX;
bool switch_mode = false;

void setup()
{
  Wire.begin(I2C_ADDR);         // join i2c bus with address #4
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop()
{
  if(switch_mode == true) {
    switch_mode = false;
    Wire.end();
    Wire.begin(I2C_ADDR);
    if(w_r_mode == SLAVE_MODE_TX) {
      Wire.onRequest(requestEvent); // register event
    } else {
      Wire.onReceive(receiveEvent); // register event
    }
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer

  switch_mode = true;
  w_r_mode = SLAVE_MODE_TX;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write("hello "); // respond with message of 6 bytes
                       // as expected by master

  switch_mode = true;
  w_r_mode = SLAVE_MODE_RX;
}
