#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

char ssid[] = "Airtel_Gaurav_5G";
char pass[] = "4Mice@Home";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org"; 
int port = 1883;

const char lightSetTopic[] = "gaurav03071992_home/light/set";       // Flutter → Arduino
const char lightStatusTopic[] = "gaurav03071992_home/light/status"; // Arduino → Flutter

const int relayPin = 2;
bool lightState = false;

void onMessageReceived(int messageSize) {
  String message = mqttClient.readString();

  Serial.print("Received: ");
  Serial.println(message);

  if (message == "ON") {
    lightState = true;
    digitalWrite(relayPin, LOW);
  }
  else if (message == "OFF") {
    lightState = false;
    digitalWrite(relayPin, HIGH);
  }

  // Publish current state back
  mqttClient.beginMessage(lightStatusTopic);
  mqttClient.print(lightState ? "ON" : "OFF");
  mqttClient.endMessage();
}

void setup() {
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  // Connect WiFi
  Serial.print("Connecting WiFi");
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected!");

  // Connect MQTT
  mqttClient.onMessage(onMessageReceived);

  Serial.print("Connecting to MQTT");
  while (!mqttClient.connect(broker, port)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected!");

  mqttClient.subscribe(lightSetTopic);
}

void loop() {
  mqttClient.poll();
}