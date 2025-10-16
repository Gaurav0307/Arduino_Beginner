// C++ code
//

int ANALOG_PIN_9 = 9;
int ANALOG_PIN_10 = 10;
int ANALOG_PIN_11 = 11;

int RED = 0;
int GREEN = 0;
int BLUE = 0;

void setup()
{
  pinMode(ANALOG_PIN_9, OUTPUT);
  pinMode(ANALOG_PIN_10, OUTPUT);
  pinMode(ANALOG_PIN_11, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // generateColor();
  rainbowColor();
  analogWrite(ANALOG_PIN_9, RED);
  analogWrite(ANALOG_PIN_10, GREEN);
  analogWrite(ANALOG_PIN_11, BLUE);
  Serial.print("R: " + String(RED));
  Serial.print(", G: " + String(GREEN));
  Serial.println(", B: " + String(BLUE));
  delay(1000);
}

void generateColor() {
  RED = random(0, 255);
  GREEN = random(0, 255);
  BLUE = random(0, 255);
}

void rainbowColor() {
  static int colorIndex = 0; // remembers last color between calls

  switch (colorIndex) {
    case 0: RED = 255; GREEN = 0;   BLUE = 0;   break; // Red
    case 1: RED = 255; GREEN = 50; BLUE = 0;   break; // Orange
    case 2: RED = 255; GREEN = 100; BLUE = 0;   break; // Yellow
    case 3: RED = 0;   GREEN = 255; BLUE = 0;   break; // Green
    case 4: RED = 0;   GREEN = 0;   BLUE = 255; break; // Blue
    case 5: RED = 75;   GREEN = 0; BLUE = 130; break; // Purple
    case 6: RED = 255; GREEN = 0;   BLUE = 40; break; // Pink
  }

  colorIndex++; // loop back to start after 7 colors

  if(colorIndex==7) {
    colorIndex =0;
  }
}
