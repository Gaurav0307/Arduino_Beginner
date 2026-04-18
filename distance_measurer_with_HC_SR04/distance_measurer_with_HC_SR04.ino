#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

int echoPin = 3;
int trigPin = 4;

int pingTime;
double distance;
int ft;
double in;

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

    ft = distance / 12;

    in = distance - (ft * 12.0);

    Serial.print("Distance : ");

    Serial.print(String(ft) + " ft ");

    Serial.println(String(in) + " in");

    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setTextSize(1);
    oled.setCursor(40, 0);
    oled.print("Distance");
    oled.drawLine(0, 8, 128, 8, WHITE);
    oled.setTextSize(2);
    oled.setCursor(10, 15);
    oled.print(String(ft) + " ft");
    oled.setTextSize(1);
    oled.setCursor(90, 14);
    oled.print(in);
    oled.setCursor(90, 22);
    oled.print("inch");
    oled.display();

    delay(200); // Debounce delay
  }

  lastTouchState = touchState;
}

