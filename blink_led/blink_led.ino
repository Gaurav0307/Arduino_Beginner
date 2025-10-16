// C++ code
//

int OUTPUT_PIN = 3; // ~3
void setup()
{
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(OUTPUT_PIN, HIGH); // Turn to 5V/on
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(OUTPUT_PIN, LOW); // Turn to 0V/off
  delay(1000); // Wait for 1000 millisecond(s)
}