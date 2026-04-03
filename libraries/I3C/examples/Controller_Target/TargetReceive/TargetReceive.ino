#include "I3C.h"

#define I3C_BUS I3C1Bus
static uint8_t rxBuf[16];

void printHex2(uint8_t v) {
  if (v < 0x10) Serial.print('0');
  Serial.print(v, HEX);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(1000);

  Serial.println("=== Target Receive ===");

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

  HAL_I3C_FlushAllFifo(I3C_BUS.halHandle());

  int rc = I3C_BUS.receive(rxBuf, sizeof(rxBuf), 10000);
  Serial.print("receive rc = ");
  Serial.println(rc);

  if (rc == 0) {
    Serial.print("RX: ");
    for (size_t i = 0; i < sizeof(rxBuf); ++i) {
      printHex2(rxBuf[i]);
      Serial.print(' ');
    }
    Serial.println();
  }
}

void loop() {
  delay(1000);
}
