#include <WiFi.h> // For ESP32
#include <ArduinoMqttClient.h>

char ssid[] = "Airtel_Gaurav_5G";
char pass[] = "4Mice@Home";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org"; 
int port = 1883;

const char lightSetTopic[] = "gaurav03071992_home/light/set";       // Flutter → Arduino
const char lightStatusTopic[] = "gaurav03071992_home/light/status"; // Arduino → Flutter

const int relayPin = 10;
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
  delay(1000);   // Important for ESP32-C3

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  // Connect WiFi
  WiFi.disconnect(true);   // Stop connection and clear previous config
  delay(200);

  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, pass);

  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected!");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Connect MQTT
  mqttClient.onMessage(onMessageReceived);

  Serial.print("Connecting to MQTT");
  while (!mqttClient.connect(broker, port)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected!");

  mqttClient.subscribe(lightSetTopic);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  mqttClient.poll();
}
