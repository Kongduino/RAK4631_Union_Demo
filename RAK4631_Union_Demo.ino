#include <ArduinoJson.h>
#include <Adafruit_TinyUSB.h>

union S {
  float n[3];
  uint8_t c[12];
};

char buff[128];
S s;
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
  s.n[0] = doc["temp"];
  s.n[1] = doc["hm"];
  s.n[2] = doc["hpa"];
  sprintf(buff, "temp = %.2f\n", s.n[0]);
  Serial.print(buff);
  S v = {0.0, 0.0, 0.0};
  memcpy(v.c, s.c, 12);
  sprintf(buff, "check temp = %.2f\n", v.n[0]);
  Serial.print(buff);

  sprintf(buff, "humidity = %.2f\n", s.n[1]);
  Serial.print(buff);
  sprintf(buff, "check humidity = %.2f\n", v.n[1]);
  Serial.print(buff);

  sprintf(buff, "pressure = %.2f HPa\n", s.n[2]);
  Serial.print(buff);
  sprintf(buff, "check pressure = %.2f HPa\n", v.n[2]);
  Serial.print(buff);

  memset(buff, 0, 128);
  Serial.println("s:");
  for (uint8_t i = 0; i < 12; i++) sprintf(buff + (i * 3), "%02x ", s.c[i]);
  Serial.println(buff);

  memset(buff, 0, 128);
  Serial.println("v:");
  for (uint8_t i = 0; i < 12; i++) sprintf(buff + (i * 3), "%02x ", v.c[i]);
  Serial.println(buff);
}

void loop() {
}
