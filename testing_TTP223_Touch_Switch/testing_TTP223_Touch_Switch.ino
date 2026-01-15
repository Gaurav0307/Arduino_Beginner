#define TOUCH_PIN 2     // TTP223 OUT pin
#define LED_PIN   8     // LED pin

bool ledState = false;
bool lastTouchState = LOW;

void setup() {
  pinMode(TOUCH_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  bool touchState = digitalRead(TOUCH_PIN);

  // Detect touch (rising edge)
  if (touchState == HIGH && lastTouchState == LOW) {
    ledState = !ledState;            // Toggle LED state
    digitalWrite(LED_PIN, ledState);
    delay(200);                      // Debounce delay
  }

  lastTouchState = touchState;
}
