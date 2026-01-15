/*
 * This sketch is for CI build purpose.
 * It allows to test build of built-in libraries
 * and can not be executed.
 */

#include <SoftwareSerial.h>

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

  // Test SoftwareSerial
  swSerial.begin(4800);
  swSerial.println("X");
  delay(20);
  while (swSerial.available()) {
    int c = swSerial.read();
    Serial.print("swSerial read: ");
    Serial.println((char)c);
  }
  swSerial.end();

}

void loop() {
}


