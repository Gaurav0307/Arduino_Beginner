int DIGITAL_pin_2 = 2;
int DIGITAL_pin_3 = 3;
int DIGITAL_pin_4 = 4;

int BAUD = 9600;

String color;

void setup() {
  // put your setup code here, to run once:
  pinMode(DIGITAL_pin_2, OUTPUT);
  pinMode(DIGITAL_pin_3, OUTPUT);
  pinMode(DIGITAL_pin_4, OUTPUT);

  Serial.begin(BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Enter color:");
  while(Serial.available() == 0);
  color = Serial.readString();

  color.toLowerCase();

  if(color == "red") {
    digitalWrite(DIGITAL_pin_2, HIGH);
    digitalWrite(DIGITAL_pin_3, LOW);
    digitalWrite(DIGITAL_pin_4, LOW);
  } else if(color == "yellow") {
    digitalWrite(DIGITAL_pin_2, LOW);
    digitalWrite(DIGITAL_pin_3, HIGH);
    digitalWrite(DIGITAL_pin_4, LOW);
  } else if(color == "green") {
    digitalWrite(DIGITAL_pin_2, LOW);
    digitalWrite(DIGITAL_pin_3, LOW);
    digitalWrite(DIGITAL_pin_4, HIGH);
  }
}
