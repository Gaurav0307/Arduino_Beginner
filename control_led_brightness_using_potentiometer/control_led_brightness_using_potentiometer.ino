int ANALOG_PIN_A2 = A2;
int ANALOG_PIN_10 = 10; //~10
int potVal;
int brightness;
int BAUD = 9600;

void setup() {
  // put your setup code here, to run once:
  pinMode(ANALOG_PIN_A2, INPUT);
  pinMode(ANALOG_PIN_10, OUTPUT);
  Serial.begin(BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = getPodVal(ANALOG_PIN_A2);

  brightness = getBrightness(potVal);

  analogWrite(ANALOG_PIN_10, brightness);
  
  delay(500);
}

int getPodVal(int potPin) {
  int potVal = analogRead(potPin);

  float volts = (5.0/1023) * potVal;

  Serial.print("Potentiometer Value: " + String(potVal));
  Serial.print(", Volts: " + String(volts));

  return potVal;
}

int getBrightness(int potVal) {
  // int brightness = (255.0/1023) * potVal;
  int brightness = pow(2, potVal/127.875) - 1;

  Serial.println(", Brightness: " + String(brightness));

  return brightness;
}

