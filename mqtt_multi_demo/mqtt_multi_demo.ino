#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

char ssid[] = "Airtel_Gaurav_5G";
char pass[] = "4Mice@Home";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org"; 
int port = 1883;

// Number of devices
#define DEVICE_COUNT 4

// Relay pins
int relayPins[DEVICE_COUNT] = {2, 3, 4, 5};
// States
bool deviceState[DEVICE_COUNT] = {false, false, false, false};

// Topics
String setTopics[DEVICE_COUNT];
String statusTopics[DEVICE_COUNT];

void publishStatus(int id) {
  mqttClient.beginMessage(statusTopics[id]);
  mqttClient.print(deviceState[id] ? "ON" : "OFF");
  mqttClient.endMessage();
}

void onMessageReceived(int messageSize) {
  String topic = mqttClient.messageTopic();
  String message = mqttClient.readString();

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Msg: ");
  Serial.println(message);

  for (int i = 0; i < DEVICE_COUNT; i++) {
    if (topic == setTopics[i]) {
      if (message == "ON") {
        deviceState[i] = true;
        digitalWrite(relayPins[i], LOW);
      } else {
        deviceState[i] = false;
        digitalWrite(relayPins[i], HIGH);
      }
      publishStatus(i);
    }
  }
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < DEVICE_COUNT; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);

    setTopics[i] = "gaurav03071992_home/device/" + String(i + 1) + "/set";
    statusTopics[i] = "gaurav03071992_home/device/" + String(i + 1) + "/status";
  }

  // Connect WiFi
  Serial.print("Connecting WiFi...");
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected!");

  // Connect MQTT
  mqttClient.onMessage(onMessageReceived);

  Serial.print("Connecting to MQTT...");
  while (!mqttClient.connect(broker, port)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected!");

  // subscribe to all devices
  for (int i = 0; i < DEVICE_COUNT; i++) {
    mqttClient.subscribe(setTopics[i]);
  }
}

void loop() {
  mqttClient.poll();
}
