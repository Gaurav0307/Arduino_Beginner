#include<Servo.h>

int servoPin = 3; //~3

int servoAngle = 0;
int baud = 9600;

Servo servo;

void setup()
{ 
  servo.attach(servoPin);
  
  Serial.begin(baud);

  servo.write(servoAngle);
}

void loop()
{
  Serial.println("Enter angle (0-180) : ");

  while(Serial.available() == 0);

  servoAngle = Serial.parseInt();

  if(servoAngle >= 0 && servoAngle <= 180) {
    servo.write(servoAngle);
  } else {
    Serial.println("Invalid Angle!");
  }
}