#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

// Display Configuration
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 62
#define DISPLAY_RESET -1
#define I2C_ADDRESS 0x3C

Adafruit_SSD1306 oled(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, DISPLAY_RESET);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  oled.begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS);
}

void loop() {
  // put your main code here, to run repeatedly:
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(2);
  oled.setCursor(5, 2);
  oled.println("Hi");
  oled.setTextSize(1);
  oled.setCursor(5, 18);
  oled.print("How are you?");
  oled.drawLine(5, 26, 76, 26, WHITE);
  oled.drawRect(0, 0, 128, 28, WHITE);
  oled.display();
  delay(1000);
  oled.drawRect(0, 0, 128, 28, BLACK);
  oled.display();
  delay(1000);
  // oled.invertDisplay(1);
}
