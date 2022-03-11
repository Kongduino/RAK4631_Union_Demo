#include <ArduinoJson.h>
#include <Adafruit_TinyUSB.h>
// Necessary to get Serial

union ThreeValues {
  float n[3]; // 3 float values
  uint8_t c[12]; // 3 x 4 bytes = 12 bytes total
  // These are parallel declarations, not consecutive
};

char buff[128]; // Too much probably but let's play it safe
char myJson[] = "{\"temp\":26.5,\"hm\":62.3,\"hpa\":1016.20}";

void setup() {
  delay(2500);
  Serial.begin(115200);
  Serial.flush();
  delay(1000);
  Serial.println("Test!");
  delay(1000);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, myJson);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    while (1);
  }
  Serial.println("=====================================================================\n");
  ThreeValues tv; // An instance of our union.
  ThreeValues ov = {0.0, 0.0, 0.0}; // Another instance, zeroed out
  // Assign the 3 float values to their respective variables
  tv.n[0] = doc["temp"];
  tv.n[1] = doc["hm"];
  tv.n[2] = doc["hpa"];
  // Let's make a copy of the raw bytes from tv to ov
  memcpy(ov.c, tv.c, 12);

  sprintf(buff, "temp = %.2f\n", tv.n[0]);
  Serial.print(buff);
  sprintf(buff, "check temp = %.2f\n", ov.n[0]);
  Serial.print(buff);

  sprintf(buff, "humidity = %.2f\n", tv.n[1]);
  Serial.print(buff);
  sprintf(buff, "check humidity = %.2f\n", ov.n[1]);
  Serial.print(buff);

  sprintf(buff, "pressure = %.2f HPa\n", tv.n[2]);
  Serial.print(buff);
  sprintf(buff, "check pressure = %.2f HPa\n", ov.n[2]);
  Serial.print(buff);

  memset(buff, 0, 128);
  Serial.println("Original:");
  // Quick hexdump
  for (uint8_t i = 0; i < 12; i++) sprintf(buff + (i * 3), "%02x ", tv.c[i]);
  Serial.println(buff);

  memset(buff, 0, 128);
  Serial.println("Copy:");
  for (uint8_t i = 0; i < 12; i++) sprintf(buff + (i * 3), "%02x ", ov.c[i]);
  Serial.println(buff);
}

void loop() {
}
