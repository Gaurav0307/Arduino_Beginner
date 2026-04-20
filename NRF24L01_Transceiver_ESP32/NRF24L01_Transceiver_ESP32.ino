/*
🔌Wiring (Important)
 NRF24L01 → ESP32 (same for both boards)

| NRF24L01 | ESP32-C3 Mini |
| -------- | ------------- |
| VCC      | 3.3V          |
| GND      | GND           |
| CE       | GPIO 7        |
| CSN      | GPIO 10       |
| SCK      | GPIO 4        |
| MOSI     | GPIO 6        |
| MISO     | GPIO 5        |

*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "GP003";

const String type = "Receiver";
// const String type = "Transmitter";

#define LED_PIN 8

void setup() {
  Serial.begin(115200);
  radio.begin();
  if(type == "Transmitter") {
    radio.openWritingPipe(address);
    radio.setChannel(108);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_HIGH);
    radio.stopListening();
  } else if(type.equals("Receiver")) {
    radio.openReadingPipe(0, address);
    radio.setChannel(108);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_HIGH);
    radio.startListening();
  }

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);

  if(type == "Transmitter") {
    const char text[] = "Hello World";
    radio.write(&text, sizeof(text));
    Serial.println("Sent: " + String(text));
    delay(1000);
  } else if(type.equals("Receiver")) {
    if (radio.available()) {
      char text[32] = "";
      radio.read(&text, sizeof(text));
      Serial.println("Received: " + String(text));

      digitalWrite(LED_PIN, LOW);
      delay(500);
    }
  }
}
