// C++ code
//

int ANALOG_PIN_3 = 3; // ~3

int SHORT_DELAY = 5; // 5 millisecond(s)

int WAIT = 1000; // 1000 millisecond(s)

void setup()
{
  pinMode(ANALOG_PIN_3, OUTPUT);
}

void loop()
{
  for(int i=0; i<=255; i++) {
    analogWrite(ANALOG_PIN_3, i);
    delay(SHORT_DELAY);
  }
  
  delay(WAIT);
  
  
  for(int i=255; i>=0; i--) {
    analogWrite(ANALOG_PIN_3, i);
    delay(SHORT_DELAY);
  }
  
  delay(WAIT);
}