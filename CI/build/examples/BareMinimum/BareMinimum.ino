/*
 * This sketch is for CI build purpose.
 * It allows to test build of built-in libraries
 * and can not be executed.
 */

#include <EEPROM.h>
#ifndef STM32MP1xx
#include <IWatchdog.h>
#endif
#ifdef TIMER_SERVO
#include <Servo.h>
#endif
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#ifndef USER_BTN
#define USER_BTN      2
#endif

#ifndef LED_BUILTIN
#define LED_BUILTIN   13
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

#ifdef TIMER_SERVO
Servo servo;
#endif
SoftwareSerial swSerial(10, 11);

void setup() {
  // Serial HW & SW
#if (!defined(USBD_USE_CDC) && !defined(DISABLE_GENERIC_SERIALUSB)) &&\
    (!defined(VIRTIOCON) && !defined(DISABLE_GENERIC_SERIALVIRTIO))
  Serial.setRx(PIN_SERIAL_RX);
  Serial.setTx(digitalPinToPinName(PIN_SERIAL_TX));
#endif
  Serial.begin(9600);  // start serial for output
  while (!Serial) {};

  swSerial.begin(4800);
  swSerial.write("x");
  if (!swSerial.isListening()) {
    swSerial.listen();
    if (swSerial.available()) {
      swSerial.read();
    }
  }
  swSerial.end();

  // EEPROM
  byte value = EEPROM.read(0x01);
  EEPROM.write(EEPROM.length()-1, value);

#ifndef STM32MP1xx
  // IWDG
  if (!IWatchdog.isReset(true)) {
    IWatchdog.begin(10000000);
    IWatchdog.isEnabled();
  }
  IWatchdog.reload();
#endif

#ifdef TIMER_SERVO
  // Servo
  servo.attach(3, 900, 2100);
  servo.write(1500);
  servo.detach();
#endif

  // SPI
  SPISettings settings(SPI_SPEED_CLOCK_DEFAULT, MSBFIRST, SPI_MODE_0);
  SPI.setMISO(PIN_SPI_MISO);
  SPI.setMOSI(PIN_SPI_MOSI);
  SPI.setSCLK(PIN_SPI_SCK);
  SPI.setSSEL(digitalPinToPinName(PIN_SPI_SS));
  SPI.begin(PIN_SPI_SS);
  SPI.beginTransaction(1, settings);
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