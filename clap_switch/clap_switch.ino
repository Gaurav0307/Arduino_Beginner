const int soundPin = 2;
const int devicePin = 8;

bool deviceState = false;

unsigned long lastSoundTime = 0;
unsigned long clap1Time = 0;

const unsigned long soundDebounce = 200;   // ignore repeated pulses within 200ms
const unsigned long clapGap = 500;         // max time allowed between two claps (ms)

bool firstClap = false;

void setup() {
  pinMode(soundPin, INPUT);
  pinMode(devicePin, OUTPUT);
  digitalWrite(devicePin, HIGH);

  Serial.begin(9600);
}

void loop() {
  int soundValue = digitalRead(soundPin);

  // Sound detected
  if (soundValue == HIGH) {

    unsigned long now = millis();

    // Ignore multiple pulses from one clap
    if (now - lastSoundTime > soundDebounce) {

      // FIRST CLAP
      if (!firstClap) {
        firstClap = true;
        clap1Time = now;

        Serial.println("Clap 1 detected");
      }

      // SECOND CLAP within allowed time
      else if (now - clap1Time <= clapGap) {
        Serial.println("Clap 2 detected");

        // Toggle device
        deviceState = !deviceState;
        digitalWrite(devicePin, deviceState ? LOW : HIGH);

        Serial.print("Device turned ");
        Serial.println(deviceState ? "ON" : "OFF");

        firstClap = false;   // reset
      }
    }

    lastSoundTime = now;
  }

  // Reset if second clap not received in time
  if (firstClap && (millis() - clap1Time > clapGap)) {
    firstClap = false;
    Serial.println("Clap timeout, reset.");
  }
}
