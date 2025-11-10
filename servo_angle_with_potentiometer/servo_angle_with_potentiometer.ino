#include<Servo.h>

int servoPin = 3; //~3
int potPin = A1;

int servoAngle = 0;
int potVal = 0;
int baud = 9600;

Servo servo;

void setup()
{
  pinMode(potPin, INPUT);
  
  servo.attach(servoPin);
  
  Serial.begin(baud);
}

void loop()
{
  delay(100);
  
  potVal = analogRead(potPin);
  
  Serial.println("Potentiometer Value = " + String(potVal));
  
  servoAngle = (-180.0/1023.0) * potVal + 180;
  
  Serial.println("Servo Angle = " + String(servoAngle));
  
  servo.write(servoAngle);
  
}