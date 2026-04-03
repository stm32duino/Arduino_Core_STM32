#include "I3C.h"

#define I3C_BUS I3C1Bus

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(1000);

  Serial.println("=== Target IBI Example ===");

  I3CTargetConfig cfg{};
  cfg.identifier = 0x62;
  cfg.mipiIdentifier = 0x1;
  cfg.ibiRequest = true;
  cfg.ibiPayload = false;

  if (!I3C_BUS.beginTarget(I3C_SDA, I3C_SCL, cfg)) {
    Serial.println("beginTarget failed");
    while (1) {}
  }

  while (!I3C_BUS.hasAddress()) {
    delay(10);
  }

  Serial.print("DA = 0x");
  Serial.println(I3C_BUS.address(), HEX);

  delay(2000);

  int rc = I3C_BUS.sendIbi(nullptr, 0, 1000);
  Serial.print("sendIbi rc = ");
  Serial.println(rc);
}

void loop() {
  delay(1000);
}
