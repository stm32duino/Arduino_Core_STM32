#include "I3C.h"

#define I3C_BUS I3C1Bus

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(1000);

  Serial.println("=== Target Event Notification ===");

  I3CTargetConfig cfg{};
  cfg.identifier = 0x62;
  cfg.mipiIdentifier = 0x1;

  if (!I3C_BUS.beginTarget(I3C_SDA, I3C_SCL, cfg)) {
    Serial.println("beginTarget failed");
    while (1) {}
  }

  while (!I3C_BUS.hasAddress()) {
    delay(10);
  }

  Serial.print("DA = 0x");
  Serial.println(I3C_BUS.address(), HEX);

  int rc = I3C_BUS.enableTargetEvents(nullptr, HAL_I3C_IT_INTUPDIE);
  Serial.print("enableTargetEvents rc = ");
  Serial.println(rc);
}

void loop() {
  uint32_t eventId = 0;
  if (I3C_BUS.readTargetEvent(eventId)) {
    Serial.print("Target event = 0x");
    Serial.println(eventId, HEX);

    if ((eventId & EVENT_ID_ENEC_DISEC) != 0U) {
      I3C_CCCInfoTypeDef info{};
      if (HAL_I3C_GetCCCInfo(I3C_BUS.halHandle(), EVENT_ID_ENEC_DISEC, &info) == HAL_OK) {
        Serial.print("  HotJoinAllowed = ");
        Serial.println(info.HotJoinAllowed ? "YES" : "NO");

        Serial.print("  InBandAllowed  = ");
        Serial.println(info.InBandAllowed ? "YES" : "NO");

        Serial.print("  CtrlRoleAllowed = ");
        Serial.println(info.CtrlRoleAllowed ? "YES" : "NO");
      }
    }
  }

  static uint32_t last = 0;
  if ((millis() - last) > 1000) {
    last = millis();
    Serial.println("target alive");
  }
}
