int ldrPin=A0;
int ldrVal;
int BAUD=115200;

void setup() {
  // put your setup code here, to run once:
  pinMode(ldrPin, OUTPUT);
  Serial.begin(BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:
  ldrVal=analogRead(ldrPin);
  Serial.println(String(ldrVal) + "," + String(0) + ","+ String(1023));
  delay(200);
}
