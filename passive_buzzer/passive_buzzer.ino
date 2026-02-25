int BUZZER_PIN = 8;
int freq;
int BAUD = 9600;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Enter tone frequency: ");
  while(Serial.available() == 0);
  freq = Serial.parseInt();

  Serial.println(freq);

  tone(BUZZER_PIN, freq, 1000);

  delay(1000);
}
