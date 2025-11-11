// PIR + buzzer - sound as long as motion is detected

const int PIR_PIN = 2;       // PIR output pin
const int BUZZER_PIN = 9;    // Buzzer pin (use tone for passive buzzer)
const int LED_PIN = 13;      // Optional LED

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("PIR Sensor warming up...");
  delay(30000);  // 30 seconds warm-up time (optional)
  Serial.println("Ready!");
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    tone(BUZZER_PIN, 2500);   // Turn buzzer ON with a 2.5kHz tone
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Motion detected!");
  } else {
    noTone(BUZZER_PIN);       // Turn buzzer OFF
    digitalWrite(LED_PIN, LOW);
    Serial.println("No motion.");
  }

  delay(1000);
}
