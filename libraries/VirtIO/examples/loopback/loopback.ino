int available;
char buffer[1024];

unsigned long start_time = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  available = Serial.available();
  while (available > 0) {
    int size = min(available, Serial.availableForWrite());
    Serial.readBytes(buffer, size);
    Serial.write(buffer, size);
    available -= size;
  }

  // Heartbeat. If Arduino stops the LED won't flash anymore.
  if ((millis() - start_time) > 1000) {
    start_time = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
