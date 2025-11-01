int redPin = 2;
int greenPin = 3;
int bluePin = 4;

int baudRate = 9600;
int sDelay = 400;
int lDelay = 800;
int i;
String msg = "Enter blink repeat times : ";
int blinkTimes;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(baudRate);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(msg);
  while(Serial.available() == 0);
  blinkTimes = Serial.parseInt();

  i=0;
  while(i < blinkTimes) {
    // Red
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    delay(sDelay);

    // Green
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    delay(sDelay);

    // Blue
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    delay(sDelay);

    // Off
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);

    delay(lDelay);

    i++;
  }
}
