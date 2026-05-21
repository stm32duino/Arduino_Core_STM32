#include <I3C.h>

// Choose the bus instance available on your board.

#define I3C_BUS  I3C1Bus

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  Serial.println("I3C Basic Begin");

  // Option 1: use default board I3C pins
  if (!I3C_BUS.begin(1000000)) {
    Serial.println("Failed to initialize I3C bus");
    while (1) {}
  }

  Serial.println("I3C bus initialized at 1 MHz");
}

void loop() {
  delay(1000);
}
