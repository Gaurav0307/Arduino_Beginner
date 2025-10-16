// C++ code
//

int DIGITAL_PIN_3 = 3; // ~3

int SHORT_DELAY = 100; // 100 millisecond(s)

int LONG_DELAY = 500; // 500 millisecond(s)

int WAIT = 1000; // 1000 millisecond(s)

void setup()
{
  pinMode(DIGITAL_PIN_3, OUTPUT);
}

void loop()
{
  for(int i=0; i<3; i++) {
    delay(SHORT_DELAY);
    digitalWrite(DIGITAL_PIN_3, HIGH);
    delay(SHORT_DELAY);
    digitalWrite(DIGITAL_PIN_3, LOW);
  }
  
  delay(LONG_DELAY);
  
  for(int i=0; i<3; i++) {
    digitalWrite(DIGITAL_PIN_3, HIGH);
    delay(LONG_DELAY);
    digitalWrite(DIGITAL_PIN_3, LOW);
    delay(LONG_DELAY);
  }
  
  for(int i=0; i<3; i++) {
    digitalWrite(DIGITAL_PIN_3, HIGH);
    delay(SHORT_DELAY);
    digitalWrite(DIGITAL_PIN_3, LOW);
    delay(SHORT_DELAY);
  }
  
  delay(WAIT);
}