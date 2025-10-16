int ANALOG_PIN_A2 = A2;
int ANALOG_PIN_10 = 10; //~10
int PIN_INPUT;
int PIN_OUTPUT;
float VOLTS;
int BAUD = 9600;

void setup() {
  // put your setup code here, to run once:
  pinMode(ANALOG_PIN_A2, INPUT);
  pinMode(ANALOG_PIN_10, OUTPUT);
  Serial.begin(BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:
  PIN_INPUT = analogRead(ANALOG_PIN_A2);
  VOLTS = (5.0/1023) * PIN_INPUT;
  Serial.print("Pin Input: " + String(PIN_INPUT));
  Serial.print(", Volts: " + String(VOLTS));
  // PIN_OUTPUT = (255.0/1023) * PIN_INPUT;
  PIN_OUTPUT = pow(2, PIN_INPUT/127.875) - 1;
  Serial.println(", Pin Output: " + String(PIN_OUTPUT));
  analogWrite(ANALOG_PIN_10, PIN_OUTPUT);
  delay(500);
}
