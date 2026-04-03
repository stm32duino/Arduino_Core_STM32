#include "I3C.h"

#define I3C_BUS I3C1Bus
static I3CDiscoveredDevice devices[8];
static volatile bool callbackSeen = false;

void myIbiCallback(const I3CControllerIbiInfo &info, void *user) {
  (void)info;
  if (user != nullptr) {
    volatile bool *flag = reinterpret_cast<volatile bool *>(user);
    *flag = true;
  }
}

void printHex2(uint8_t v) {
  if (v < 0x10) Serial.print('0');
  Serial.print(v, HEX);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(1000);

  Serial.println("=== Controller IBI Example ===");

  if (!I3C_BUS.begin(I3C_SDA, I3C_SCL, 1000000U)) {
    Serial.println("begin() failed");
    while (1) {}
  }

  size_t found = 0;
  int rc = I3C_BUS.discover(devices, 8, &found);

  if (rc != 0 || found == 0) {
    Serial.println("No target found");
    while (1) {}
  }

  uint8_t da = devices[0].dynAddr;

  I3C_BUS.onIbi(myIbiCallback, (void *)&callbackSeen);

  rc = I3C_BUS.enableIbi(1, da, false, false, 1000);
  Serial.print("enableIbi rc = ");
  Serial.println(rc);

  rc = I3C_BUS.enableControllerEvents();
  Serial.print("enableControllerEvents rc = ");
  Serial.println(rc);

  Serial.println("Waiting for IBI...");
}

void loop() {
  if (I3C_BUS.hasIbi()) {
    I3CControllerIbiInfo ibi{};
    if (I3C_BUS.peekIbi(ibi)) {
      Serial.print("peekIbi source DA = 0x");
      printHex2(ibi.sourceDa);
      Serial.println();
    }

    if (I3C_BUS.readIbi(ibi)) {
      Serial.print("readIbi source DA = 0x");
      printHex2(ibi.sourceDa);
      Serial.println();
    }

    Serial.print("callbackSeen = ");
    Serial.println(callbackSeen ? "true" : "false");
  }

  delay(100);
}
