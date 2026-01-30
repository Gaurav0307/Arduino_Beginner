int BUZZER_PIN = 2;
int DELAY = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(BUZZER_PIN, HIGH);
  delay(DELAY);

  digitalWrite(BUZZER_PIN, LOW);
  delay(DELAY);
}
