/*
  Watchdog + Button

  This example code is in the public domain.

  The code demonstrates the use of a watchdog timer. The watchdog timer is
  initialized with timeout of 10 seconds. Every time the button is pressed,
  the watchdog timer is reset. If left unattended the system would reset
  itself about every 10 seconds.

  You would have to keep pressing the button frequently (< 10 seoncds apart)
  to prevent the system from reseting itself.

  You would recongnize the reset condition when the LED blinks rapidly a
  few times.

  This is not a practical example, in real code you would reset the watchdog
  timer in the main loop without requiring user input.
  
  The code is modified version of the code from:
  http://www.arduino.cc/en/Tutorial/Button
*/

#include <Watchdog.h>

const int buttonPin = USER_BTN;
const int ledPin = LED_BUILTIN;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Blink the LED to indicate reset.
  for(uint8_t idx = 0; idx < 5; idx++) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  // Init the watchdog timer with 10 seconds timeout
  watchdog_init(10000);
}

void loop() {
  // read the state of the pushbutton value:
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    // Reset the watchdog only when the button is pressed.
    watchdog_reset();
  }
}
