#include <Stepper.h>

int STEPS = 2038;
int rpm = 15;

/*
Stepper Motor Driver Connection with Arduino
  IN1 = 2
  IN2 = 4
  IN3 = 3
  IN4 = 5
*/
Stepper stepper(STEPS, 2, 3, 4, 5);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  stepper.setSpeed(rpm);
  stepper.step(STEPS);
  delay(1000);
  stepper.setSpeed(rpm);
  stepper.step(-STEPS);
  delay(1000);
}
