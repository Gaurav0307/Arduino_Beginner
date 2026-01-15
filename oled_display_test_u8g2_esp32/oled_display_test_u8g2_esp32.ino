#include <Wire.h>
#include <U8g2lib.h>

// For SH1106 1.3" OLED (most common)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// If your display is SSD1306 instead, use this:
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  Wire.begin(9, 10);  // SDA, SCL for ESP32-C3
  delay(1000);
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tf);
  u8g2.drawStr(10, 15, "ESP32-C3 OLED");
  u8g2.drawStr(10, 30, "1.3 Inch Display");
  u8g2.drawStr(10, 45, "Working OK!");

  // Draw test box
  static int x = 0;
  u8g2.drawFrame(x, 54, 20, 8);
  x += 2;
  if (x > 108) x = 0;

  u8g2.sendBuffer();
  delay(100);
}
