int ANALOG_PIN_3 = 3; //~3
int USER_INPUT;
int BRIGHTNESS;
int BAUD = 9600;


void setup() {
  // put your setup code here, to run once:
  pinMode(ANALOG_PIN_3, OUTPUT);
  Serial.begin(BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Enter brightness (0-10):");
  while(Serial.available()==0);
  USER_INPUT = Serial.parseInt();

  if(USER_INPUT >=1 && USER_INPUT <=10) {
    BRIGHTNESS = pow(2, (8.0/10.0)*USER_INPUT) -1;

    Serial.println("User Input: " + String(USER_INPUT) + ", LED Brightness: " + String(BRIGHTNESS));

    analogWrite(ANALOG_PIN_3, BRIGHTNESS);
  } else {
    Serial.println("Invalid Input!!!");
  }
}
