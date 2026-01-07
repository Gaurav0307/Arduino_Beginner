#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include <MQ135.h>

// OLED display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MQ135_PIN A0
MQ135 gasSensor = MQ135(MQ135_PIN);

// DHT11 sensor configuration
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(20, 25);
  display.println("Weather Station");
  display.display();
  delay(2000);
}

void loop() {
  delay(2000); // DHT11 reads slowly

  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  if (isnan(humidity) || isnan(tempC)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    display.clearDisplay();
    display.setCursor(25, 25);
    display.setTextSize(1);
    display.println("Sensor Error!");
    display.display();
    return;
  }

  // Print to Serial
  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.print(" °C  ");
  Serial.print(tempF);
  Serial.print(" °F  ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Air Quality Sensor MQ135
  float rzero = gasSensor.getRZero();
  float correctedRZero = gasSensor.getCorrectedRZero(tempC, humidity); // 25°C, 50%
  float ppm = gasSensor.getPPM();
  float correctedPPM = gasSensor.getCorrectedPPM(tempC, humidity);     // Apply temperature & humidity correction

  // Print to Serial
  Serial.print("RZero: ");
  Serial.print(rzero);
  Serial.print(" | Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print(" | PPM: ");
  Serial.print(ppm);
  Serial.print(" | Corrected PPM: ");
  Serial.println(correctedPPM);

  // Determine Air Quality
  String airStatus;
  if (correctedPPM <= 50) airStatus = "Excellent";
  else if (correctedPPM <= 100) airStatus = "Good";
  else if (correctedPPM <= 200) airStatus = "Moderate";
  else if (correctedPPM <= 300) airStatus = "Poor";
  else if (correctedPPM <= 500) airStatus = "Unhealthy";
  else airStatus = "Hazardous";

  // Display on OLED
  display.clearDisplay();

  // Header
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.println("Weather Station");

  // Temperature in Celsius
  display.setTextSize(1);
  display.setCursor(2, 20);
  display.print(tempC, 1);
  display.print((char)247); // Degree symbol
  display.print("C");

  // Temperature in Fahrenheit
  display.setTextSize(1);
  display.setCursor(2, 35);
  display.print(tempF, 1);
  display.print((char)247);
  display.println("F");

  // Air Quality
  display.setTextSize(1);
  display.setCursor(2, 50);
  display.print("AQI ");
  display.print(correctedPPM, 0);
  display.println(" - " + airStatus);

  // Humidity
  display.setTextSize(2);
  display.setCursor(75, 20);
  display.print(humidity, 0);
  display.println("%");

  // Optional labels
  display.setTextSize(1);
  display.setCursor(75, 38);
  display.println("Humidity");

  display.display();
}



