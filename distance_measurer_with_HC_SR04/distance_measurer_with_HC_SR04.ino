#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

int echoPin = 3;
int trigPin = 4;

int pingTime;
double distance;

int BAUD = 9600;

int TOUCH_PIN = 2;     // TTP223 OUT pin

bool lastTouchState = LOW;

// Display Configuration
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 62
#define DISPLAY_RESET -1
#define I2C_ADDRESS 0x3C

Adafruit_SSD1306 oled(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, DISPLAY_RESET);

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(TOUCH_PIN, INPUT);
  oled.begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS);
  Serial.begin(BAUD);
}

void loop() {
  bool touchState = digitalRead(TOUCH_PIN);

  // Detect touch (rising edge)
  if (touchState == HIGH && lastTouchState == LOW) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(trigPin, LOW);

    pingTime = pulseIn(echoPin, HIGH);

    Serial.print("Ping Time : ");

    Serial.println(pingTime);

    distance = 0.0134492 * pingTime / 2;

    Serial.print("Distance : ");

    Serial.println(distance);

    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setTextSize(1);
    oled.setCursor(10, 2);
    oled.print("Distance");
    oled.setTextSize(2);
    oled.setCursor(10, 12);
    oled.print(distance);
    oled.setTextSize(1);
    oled.setCursor(90, 18);
    oled.print(" inch");
    oled.display();

    delay(200); // Debounce delay
  }

  lastTouchState = touchState;
}

