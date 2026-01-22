#include <Wire.h>
#include <U8g2lib.h>
#include "DHT.h"
#include <MQ135.h>
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
int relayPins[DEVICE_COUNT] = {3, 4, 5, 6};
// States
bool deviceState[DEVICE_COUNT] = {false, false, false, false};

// Topics
String setTopics[DEVICE_COUNT];
String statusTopics[DEVICE_COUNT];

void relaySetup() {
  for (int i = 0; i < DEVICE_COUNT; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);

    setTopics[i] = "gaurav03071992_home/device/" + String(i + 1) + "/set";
    statusTopics[i] = "gaurav03071992_home/device/" + String(i + 1) + "/status";
  }
}

void connectWifi() {
    // Connect WiFi
  Serial.print("Connecting WiFi");
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected!");
}

void connectMQTT() {
  // Connect MQTT
  mqttClient.onMessage(onMessageReceived);

  Serial.print("Connecting to MQTT");
  while (!mqttClient.connect(broker, port)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected!");

  int indicatorPin = 8;
  pinMode(indicatorPin, OUTPUT);
  digitalWrite(indicatorPin, HIGH);
}

void subscribe() {
  // subscribe to all devices
  for (int i = 0; i < DEVICE_COUNT; i++) {
    mqttClient.subscribe(setTopics[i]);
  }
}

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

/* ================= OLED =================
   1.3" OLED (128x64)
   PAGE BUFFER MODE (LOW SRAM)
*/
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(
  U8G2_R0,
  U8X8_PIN_NONE
);

// U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(
//   U8G2_R0,
//   U8X8_PIN_NONE
// );

/* ================= MQ135 ================= */
#define MQ135_PIN A0
MQ135 gasSensor(MQ135_PIN);

/* ================= DHT22 ================= */
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/* ================= GLOBALS ================= */
float tempC, tempF, humidity;
float correctedPPM;
char* airStatus;

void sensorSetup() {
  dht.begin();
  u8g2.begin();

  /* Splash screen */
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.drawStr(28, 30, "Weather Data");
  } while (u8g2.nextPage());

  delay(2000);
}

void weather() {
  delay(2000);   // DHT22 safe delay

  /* ===== Read DHT ===== */
  humidity = dht.readHumidity();
  tempC = dht.readTemperature();
  tempF = dht.readTemperature(true);

  if (isnan(humidity) || isnan(tempC)) {
    Serial.println(F("DHT read failed"));

    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_6x12_tf);
      u8g2.drawStr(25, 32, "Sensor Error!");
    } while (u8g2.nextPage());

    return;
  }

  /* ===== Serial Output ===== */
  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.print(" °C  ");
  Serial.print(tempF);
  Serial.print(" °F  ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  /* ===== MQ135 ===== */
  float rzero = gasSensor.getRZero();
  float correctedRZero = gasSensor.getCorrectedRZero(tempC, humidity); // 25°C, 50%
  float ppm = gasSensor.getPPM();
  correctedPPM = gasSensor.getCorrectedPPM(tempC, humidity);     // Apply temperature & humidity correction

  /* ===== AQI Status ===== */
  if (correctedPPM <= 50) airStatus = "Excellent";
  else if (correctedPPM <= 100) airStatus = "Good";
  else if (correctedPPM <= 200) airStatus = "Moderate";
  else if (correctedPPM <= 300) airStatus = "Poor";
  else if (correctedPPM <= 500) airStatus = "Unhealthy";
  else airStatus = "Hazard";

  /* ===== Serial Output ===== */
  Serial.print("RZero: ");
  Serial.print(rzero);
  Serial.print(" | Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print(" | PPM: ");
  Serial.print(ppm);
  Serial.print(" | Corrected PPM: ");
  Serial.println(correctedPPM);

  /* ===== OLED DISPLAY ===== */
  u8g2.firstPage();
  do {
    /* Header */
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.drawStr(28, 10, "Weather Data");

    /* Temperature °C */
    u8g2.setFont(u8g2_font_7x13B_tf);
    u8g2.setCursor(2, 28);
    u8g2.print(tempC, 1);
    u8g2.print("\xB0");   // degree symbol
    u8g2.print("C");

    /* Temperature °F */
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.setCursor(2, 42);
    u8g2.print(tempF, 1);
    u8g2.print("\xB0");   // degree symbol
    u8g2.print("F");

    /* Humidity */
    u8g2.setFont(u8g2_font_10x20_tf);
    u8g2.setCursor(78, 32);
    u8g2.print((int)humidity);
    u8g2.print("%");

    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.drawStr(78, 46, "Humidity");

    /* AQI */
    u8g2.setCursor(2, 60);
    u8g2.print(F("AQI "));
    u8g2.print((int)correctedPPM);
    u8g2.print(" ");
    u8g2.print(airStatus);

  } while (u8g2.nextPage());
}

void publishSensorStatus() {
  mqttClient.beginMessage("gaurav03071992_home/sensor/tempC");
  mqttClient.print(tempC);
  mqttClient.endMessage();

  mqttClient.beginMessage("gaurav03071992_home/sensor/tempF");
  mqttClient.print(tempF);
  mqttClient.endMessage();

  mqttClient.beginMessage("gaurav03071992_home/sensor/humidity");
  mqttClient.print((int)humidity);
  mqttClient.endMessage();

  mqttClient.beginMessage("gaurav03071992_home/sensor/aqi");
  mqttClient.print((int)correctedPPM);
  mqttClient.endMessage();

  mqttClient.beginMessage("gaurav03071992_home/sensor/airStatus");
  mqttClient.print(airStatus);
  mqttClient.endMessage();
}

/* ================= SETUP ================= */
void setup() {
  Serial.begin(115200);
  relaySetup();
  connectWifi();
  connectMQTT();
  subscribe();
  sensorSetup();
}

/* ================= LOOP ================= */
void loop() {
  mqttClient.poll();
  weather();
  publishSensorStatus();
}
