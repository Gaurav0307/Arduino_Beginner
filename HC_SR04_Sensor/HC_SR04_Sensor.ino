int echoPin = 3;
int trigPin = 4;

int pingTime;
double distance;

int BAUD = 9600;

void setup() {
  // put your setup code here, to run once:
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  Serial.begin(BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:
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

  delay(1000);
}
