#include <Arduino.h>
#include "Mouse.h"
#include "Joystick.h"

#define LED PC13
#define HIGHPIN A7
#define ADCPIN A6
#define LOWPIN A5

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_JOYSTICK, 0, 0,
                   true, false, false, false, false, false,
                   false, false, false, false, false);

int analogvalue = 0;

void setup()
{
  Joystick.setXAxisRange(0, 255);
  Joystick.begin();
  Mouse.begin();
  USB_Begin();
  pinMode(HIGHPIN, OUTPUT);
  pinMode(ADCPIN, INPUT);
  pinMode(LOWPIN, OUTPUT);
  digitalWrite(HIGHPIN, HIGH);
  digitalWrite(LOWPIN, LOW);
  pinMode(LED, OUTPUT);
}

bool high = false;
int loops = 0;

void loop()
{
  auto last = analogvalue;
  auto val = analogRead(ADCPIN);
  analogvalue <<= 1;
  analogvalue += val;
  analogvalue /= 3;
  if (analogvalue >> 2 != last >> 2)
  {
    Joystick.setXAxis(analogvalue >> 2);
  }
  delay(1);
  loops++;
  if (loops >= 500)
  {
    // every 500ms
    loops = 0;
    high = !high;
    digitalWrite(LED, high ? HIGH : LOW);
    if (high)
    {
      Mouse.move(10, 0);
    }
    else
    {
      Mouse.move(-10, 0);
    }
  }
}
