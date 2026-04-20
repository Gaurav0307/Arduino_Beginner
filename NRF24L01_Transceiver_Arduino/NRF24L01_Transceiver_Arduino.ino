/*
🔌Wiring (Important)
 NRF24L01 → Arduino (same for both boards)

| NRF24L01 Pin | Arduino Pin      |
| ------------ | ---------------- |
| VCC          | 3.3V (not 5v)    |
| GND          | GND              |
| CE           | D9               |
| CSN          | D10              |
| SCK          | D13              |
| MOSI         | D11              |
| MISO         | D12              |

*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "GP003";

const String type = "Transmitter";
// const String type = "Receiver";

#define LED_PIN 2

void setup() {
  Serial.begin(9600);
  radio.begin();
  if(type.equals("Transmitter")) {
    radio.openWritingPipe(address);
    radio.setChannel(108);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_HIGH);
    radio.stopListening();
  } else if(type == "Receiver") {
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

  if(type.equals("Transmitter")) {
    const char text[] = "Hello World";
    radio.write(&text, sizeof(text));
    Serial.println("Sent: " + String(text));
    delay(1000);
  } else if(type == "Receiver") {
    if (radio.available()) {
      char text[32] = "";
      radio.read(&text, sizeof(text));
      Serial.println("Received: " + String(text));

      digitalWrite(LED_PIN, LOW);
      delay(500);
    }
  }
}
