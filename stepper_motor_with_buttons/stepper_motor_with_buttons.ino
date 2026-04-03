#include<Stepper.h>

int rButton = 8;
int gButton = 9;
int bButton = 10;
int yButton = 11;

int rVal;
int gVal;
int bVal;
int yVal;

int rValOld;
int gValOld;
int bValOld;
int yValOld;

int f5 = 28;
int f90 = 510;
int r5 = -28;
int r90 = -510;

int STEPS = 2038;
int rpm = 15;

Stepper stepper(STEPS, 2, 3, 4, 5);

void setup() {
  // put your setup code here, to run once:
  stepper.setSpeed(rpm);

  pinMode(rButton, INPUT_PULLUP);
  pinMode(gButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  pinMode(yButton, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper.setSpeed(rpm);

  rVal = digitalRead(rButton);
  if(rVal == 0 && rValOld == 1) {
    stepper.step(f5);
    delay(100);
  }
  rValOld=rVal;

  gVal = digitalRead(gButton);
  if(gVal == 0 && gValOld == 1) {
    stepper.step(f90);
    delay(100);
  }
  gValOld=gVal;

  bVal = digitalRead(bButton);
  if(bVal == 0 && bValOld == 1) {
    stepper.step(r5);
    delay(100);
  }
  bValOld=bVal;

  yVal = digitalRead(yButton);
  if(yVal == 0 && yValOld == 1) {
    stepper.step(r90);
    delay(100);
  }
  yValOld=yVal;
}
