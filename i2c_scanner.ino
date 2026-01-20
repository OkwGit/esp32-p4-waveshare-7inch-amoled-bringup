#include <Wire.h>

void setup() {
  Serial.begin(115200);
  delay(1500);

  Serial.println("\n========================================");
  Serial.println("I2C Scanner");
  Serial.println("========================================\n");

  Wire.begin();

  Serial.println("Scanning I2C bus...");
  Serial.println("Address range: 0x01 - 0x7E\n");

  int foundCount = 0;
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found I2C device at 0x");
      if (addr < 16) Serial.print("0");
      Serial.print(addr, HEX);
      Serial.print(" (");
      Serial.print(addr);
      Serial.println(")");
      foundCount++;
    }
  }

  Serial.println("\n========================================");
  if (foundCount == 0) {
    Serial.println("No I2C devices found!");
    Serial.println("\nCheck:");
    Serial.println("1. SDA/SCL pins are correct");
    Serial.println("2. I2C devices are connected");
    Serial.println("3. Pull-up resistors are present");
  } else {
    Serial.print("Total devices found: ");
    Serial.println(foundCount);
    Serial.println("\nExpected backlight chip: 0x45");
  }
  Serial.println("========================================\n");
}

void loop() {}

