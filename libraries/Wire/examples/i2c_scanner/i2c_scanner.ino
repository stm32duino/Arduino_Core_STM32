// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//



/* Example pinmap for Bluepill I2Cs (by Testato)

 I2C-1 standard pins: PB7(sda) PB6(scl)
 Use it by "Wire" without pin declaration
  Wire.begin();

 I2C-1 alternative pins: PB9(sda) PB8(scl)
 Remap the first I2C before call begin()
  Wire.setSDA(PB9);
  Wire.setSCL(PB8);
  Wire.begin();

 I2C-2: PB11(sda) PB10(scl)
 Remap the second I2C before call begin()
  Wire.setSDA(PB11);
  Wire.setSCL(PB10);
  Wire.begin();

 If you want to use the two I2Cs simultaneously, create a new instance for the second I2C
  TwoWire Wire2(PB11,PB10);
  Wire2.begin();
 
*/


#include <Wire.h>


void setup() {

  Serial.begin(9600);
  Wire.begin();
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.

    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("done");

  delay(5000);           // wait 5 seconds for next scan
}
