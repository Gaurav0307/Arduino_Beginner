
#include <Wire.h>
#include <TM1637Display.h>

// Define TM1637 pins
#define CLK 2
#define DIO 3

// Create display object
TM1637Display display(CLK, DIO);

int ANALOG_PIN_5 = 5; // ~5
int DIGITAL_PIN_6 = 6; // ~6

void setup() {
  pinMode(ANALOG_PIN_5, OUTPUT);
  pinMode(DIGITAL_PIN_6, OUTPUT);

  digitalWrite(DIGITAL_PIN_6, HIGH);

  Serial.begin(9600);
  
  display.setBrightness(7); // Brightness: 0 (dim) to 7 (bright)
}

void loop() {
  if(Serial.available()) {
    int seconds = Serial.parseInt();
    
    while(seconds >= 0) {
      // Show the counter value (0–9999)
      display.showNumberDec(seconds, false);  // 'true' shows leading zeros
      
      tone(ANALOG_PIN_5, 2500, 100);
      
      if(seconds == 0) {
        tone(ANALOG_PIN_5, 2500, 3000);

        digitalWrite(DIGITAL_PIN_6, LOW);
        delay(3000);
        digitalWrite(DIGITAL_PIN_6, HIGH);
      }
      
      delay(1000); // Delay for visible counting speed
      
      seconds--;
    }
  }
}