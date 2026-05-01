#include <Arduino.h>
#include "USBCDC.h"

USBCDC USBSerial;

void setup()
{
  USBSerial.begin(115200);
  USB_Begin();
  while (!USB_Running())
  {
    // wait until usb connected
    delay(5);
  }
  while (!USBSerial)
  {
    //(optional) wait until Serial port is connected
    delay(5);
  }
}

void loop()
{
  if (USBSerial.available())
  {
    USBSerial.print((char)USBSerial.read());
  }
}