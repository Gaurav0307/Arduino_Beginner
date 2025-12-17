int redPin=2;
int greenPin=3;
int bluePin=4;
int ldrPin=A0;
int ldrVal=0;
int baud=9600;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(ldrPin, INPUT);

  Serial.begin(baud);
}

void loop() {
  // put your main code here, to run repeatedly:
  ldrVal = analogRead(ldrPin);

  Serial.println(ldrVal);

  if(ldrVal > 750) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  } else if(ldrVal >= 300 && ldrVal <= 750) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }  else if(ldrVal < 300) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }

  delay(300);
}
