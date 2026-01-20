#include <Wire.h>

uint8_t addrs[] = {0x18, 0x40, 0x5D};
uint8_t regs_to_try[] = {0x00, 0x01, 0x02, 0x10, 0x20, 0xAB, 0xFF};

void try_write(uint8_t addr, uint8_t reg, uint8_t val) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);
  uint8_t err = Wire.endTransmission();
  
  Serial.print("  [");
  if (err == 0) {
    Serial.print("OK ");
  } else {
    Serial.print("FAIL");
  }
  Serial.print("] ");
  Serial.print("Address: 0x");
  if (addr < 16) Serial.print("0");
  Serial.print(addr, HEX);
  Serial.print(" | Register: 0x");
  if (reg < 16) Serial.print("0");
  Serial.print(reg, HEX);
  Serial.print(" | Brightness: ");
  Serial.print(val);
  Serial.print("/255");
  if (err == 0) {
    Serial.println(" ✓");
  } else {
    Serial.print(" (error code: ");
    Serial.print(err);
    Serial.println(")");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  
  Serial.println("\n");
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║   BACKLIGHT PROBE TEST                 ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println("");
  Serial.println("What we're doing:");
  Serial.println("  • Testing 3 I2C devices we found");
  Serial.println("  • Trying different brightness values");
  Serial.println("  • Looking for the backlight controller");
  Serial.println("");
  Serial.println("⚠️  IMPORTANT: Watch your screen!");
  Serial.println("   If it gets brighter/dimmer, we found it!");
  Serial.println("");
  Serial.println("Testing addresses: 0x18, 0x40, 0x5D");
  Serial.println("(Note: 0x5D might be touch controller)");
  Serial.println("");
  Serial.println("Starting in 2 seconds...");
  Serial.println("");
  delay(2000);
  
  Wire.begin();
  delay(100);

  uint8_t vals[] = {0, 64, 128, 255};
  int total_tests = sizeof(addrs)/sizeof(addrs[0]) * sizeof(regs_to_try)/sizeof(regs_to_try[0]) * sizeof(vals)/sizeof(vals[0]);
  int current_test = 0;

  for (uint8_t a = 0; a < sizeof(addrs)/sizeof(addrs[0]); a++) {
    Serial.println("");
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    Serial.print("Testing Device at Address: 0x");
    if (addrs[a] < 16) Serial.print("0");
    Serial.print(addrs[a], HEX);
    Serial.print(" (");
    Serial.print(addrs[a]);
    Serial.println(")");
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    Serial.println("");
    
    for (uint8_t r = 0; r < sizeof(regs_to_try)/sizeof(regs_to_try[0]); r++) {
      Serial.print("  Register 0x");
      if (regs_to_try[r] < 16) Serial.print("0");
      Serial.print(regs_to_try[r], HEX);
      Serial.println(" - Trying brightness levels:");
      
      for (uint8_t v = 0; v < sizeof(vals)/sizeof(vals[0]); v++) {
        current_test++;
        Serial.print("    [");
        Serial.print(current_test);
        Serial.print("/");
        Serial.print(total_tests);
        Serial.print("] ");
        try_write(addrs[a], regs_to_try[r], vals[v]);
        delay(150);
      }
      Serial.println("");
    }
    
    Serial.println("");
    Serial.println("  >>> Finished testing this device <<<");
    Serial.println("  >>> Check screen - did brightness change? <<<");
    Serial.println("");
    delay(1000);
  }

  Serial.println("");
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║   TEST COMPLETE!                       ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println("");
  Serial.println("What to report:");
  Serial.println("  ✓ Did the screen brightness change?");
  Serial.println("  ✓ Which address made it change?");
  Serial.println("  ✓ Which register number?");
  Serial.println("  ✓ At what brightness value?");
  Serial.println("");
  Serial.println("Look for lines marked [OK] - those are successful writes.");
  Serial.println("");
}

void loop() {}

