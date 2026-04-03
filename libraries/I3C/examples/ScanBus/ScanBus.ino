#include "I3C.h"

static I3CDiscoveredDevice devices[8];

void printHex2(uint8_t v) {
  if (v < 0x10) Serial.print('0');
  Serial.print(v, HEX);
}

void printHex64(uint64_t v) {
  uint32_t hi = (uint32_t)(v >> 32);
  uint32_t lo = (uint32_t)(v & 0xFFFFFFFFULL);
  Serial.print(hi, HEX);
  Serial.print(lo, HEX);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(1000);

  Serial.println("=== I3C ScanBus ===");

  if (!I3C1Bus.begin(I3C_SDA, I3C_SCL, 1000000U)) {
    Serial.println("begin() failed");
    while (1) {}
  }

  size_t found = 0;

  int rc = I3C1Bus.discover(devices, 8, &found);

  Serial.print("discover rc = ");
  Serial.println(rc);

  Serial.print("found = ");
  Serial.println(found);

  for (size_t i = 0; i < found; ++i) {
    Serial.print("#");
    Serial.print(i);
    Serial.print(" DA=0x");
    printHex2(devices[i].dynAddr);

    Serial.print(" SA=0x");
    printHex2(devices[i].staticAddr);

    Serial.print(" BCR=0x");
    printHex2(devices[i].bcr);

    Serial.print(" DCR=0x");
    printHex2(devices[i].dcr);

    Serial.print(" PID=0x");
    printHex64(devices[i].pid);

    Serial.print(" RAW=0x");
    printHex64(devices[i].entdaaPayloadRaw);

    Serial.print(" fromDaa=");
    Serial.print(devices[i].fromDaa ? "yes" : "no");

    Serial.print(" setdasa=");
    Serial.print(devices[i].assignedBySetdasa ? "yes" : "no");

    Serial.print(" matchedKnown=");
    Serial.println(devices[i].matchedKnown ? "yes" : "no");
  }
}

void loop() {
  delay(1000);
}
