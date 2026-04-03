#include "I3C.h"

#define I3C_BUS I3C1Bus
static I3CDiscoveredDevice devices[8];

void printHex2(uint8_t v) {
  if (v < 0x10) Serial.print('0');
  Serial.print(v, HEX);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(1000);

  Serial.println("=== Controller Write / Target Receive ===");

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

  Serial.print("Target DA=0x");
  printHex2(da);
  Serial.println();

  delay(1000);

  uint8_t tx[16] = {
    0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C,
    0x0D, 0x0E, 0x0F, 0x10
  };

  int wr = I3C_BUS.write(da, tx, sizeof(tx), 1000);
  Serial.print("write rc = ");
  Serial.println(wr);
}

void loop() {
  delay(1000);
}
