#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int xPos=3;
int yPos=2;
int deltaX=1;
int deltaY=1;

byte frame[8][12];

int delayTime=100;

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<=11; i++) {
    for(int j=0; j<=7; j++) {
      frame[j][i]=0;

      if(i==xPos && j==yPos) {
        frame[j][i]=1;
      }
    }
  }

  matrix.renderBitmap(frame, 8, 12);

  if(xPos==0 || xPos==11) {
    deltaX = -deltaX;
  }

  if(yPos==0 || yPos==7) {
    deltaY = -deltaY;
  }

  xPos = xPos + deltaX;
  yPos = yPos + deltaY;
  
  delay(delayTime);
}
