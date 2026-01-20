/*
 * This sketch is for CI build purpose.
 * It allows to test build of built-in libraries
 * and can not be executed.
 */

#include <SPI.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#ifndef USER_BTN
#define USER_BTN 2
#endif

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

#ifndef PIN_SERIAL_RX
#define PIN_SERIAL_RX 0
#endif

#ifndef PIN_SERIAL_TX
#define PIN_SERIAL_TX 1
#endif

#ifndef Serial
HardwareSerial Serial(PIN_SERIAL_RX, PIN_SERIAL_TX);
#endif

SoftwareSerial swSerial(10, 11);

void setup() {
  // Serial HW & SW
#if (!defined(USBD_USE_CDC) && !defined(DISABLE_GENERIC_SERIALUSB)) && (!defined(VIRTIOCON) && !defined(DISABLE_GENERIC_SERIALVIRTIO))
  Serial.setRx(PIN_SERIAL_RX);
  Serial.setTx(digitalPinToPinName(PIN_SERIAL_TX));
#endif
  Serial.begin(9600);  // start serial for output
  while (!Serial) {};

  swSerial.begin(4800);
  swSerial.println("X");
  delay(20);
  while (swSerial.available()) {
    int c = swSerial.read();
    Serial.print("swSerial read: ");
    Serial.println((char)c);
  }
  swSerial.end();

  // SPI
  SPISettings settings(SPI_SPEED_CLOCK_DEFAULT, MSBFIRST, SPI_MODE0);
  SPI.setMISO(PIN_SPI_MISO);
  SPI.setMOSI(PIN_SPI_MOSI);
  SPI.setSCLK(PIN_SPI_SCK);
  SPI.setSSEL(digitalPinToPinName(PIN_SPI_SS));
  SPI.begin();
  SPI.beginTransaction(settings);
  SPI.endTransaction();
  SPI.transfer(1);
  SPI.end();
  // Wire
  Wire.setSCL(PIN_WIRE_SCL);
  Wire.setSDA(digitalPinToPinName(PIN_WIRE_SDA));
  Wire.setClock(400000);
  Wire.begin(4);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Wire.beginTransmission(4);
  Wire.endTransmission();
  Wire.requestFrom(2, 1);
  Wire.end();

}

void loop() {
}

// Wire
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int) {
  while (1 < Wire.available()) {
    Wire.read();
  }
}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("x");
}


