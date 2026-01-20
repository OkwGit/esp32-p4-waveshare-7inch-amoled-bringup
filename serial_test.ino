void setup() {
  Serial.begin(115200);
  delay(1500);
  Serial.println("BOOT OK");
}

void loop() {
  Serial.println("tick");
  delay(1000);
}

