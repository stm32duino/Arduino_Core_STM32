#include <USBSerial.h>

void setup() {
  // Default baudrate is set to 9600
  SerialUSB.begin();
}

void loop() {
  SerialUSB.println("Hello world!");
  delay(1000);
}
