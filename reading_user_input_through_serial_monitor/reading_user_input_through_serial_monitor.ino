String name;
int age;
float height;

int BAUD = 9600;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:

  /// Name
  Serial.println("Enter your name : ");
  while(Serial.available() == 0);
  name = Serial.readString();

  /// Age
  Serial.println("Enter your age (Years) : ");
  while(Serial.available() == 0);
  age = Serial.parseInt();

  /// Height
  Serial.println("Enter your height (Feet) : ");
  while(Serial.available() == 0);
  height = Serial.parseFloat();

  Serial.println("Your name is " + name + ". You are " + String(age) + " years old. You are " + String(height) + " feet tall.");

  delay(5000);
}
