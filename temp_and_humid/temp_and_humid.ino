#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create display object (I2C address 0x3C is common)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT11 setup
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Check address (0x3C or 0x3D)
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 10);
  display.println("DHT11 Sensor Ready");
  display.display();
  delay(2000);
}

void loop() {
  // Wait 5 seconds between readings
  delay(5000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    display.clearDisplay();
    display.setCursor(10, 25);
    display.setTextSize(1);
    display.println("Sensor Error!");
    display.display();
    return;
  }

  // Print to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %  |  ");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Display on OLED
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("DHT11 SENSOR");

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print("Temp. ");
  display.setTextSize(2);
  display.print(temperature);
  display.print((char)247); // Degree symbol
  display.println("C");

  display.setTextSize(1);
  display.setCursor(0, 45);
  display.print("Humi. ");
  display.setTextSize(2);
  display.print(humidity);
  display.println("%");

  display.display();
}

// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include "DHT.h"

// // OLED display configuration
// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// #define OLED_RESET -1
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// // DHT11 sensor configuration
// #define DHTPIN 2
// #define DHTTYPE DHT11
// DHT dht(DHTPIN, DHTTYPE);

// void setup() {
//   Serial.begin(9600);
//   dht.begin();

//   // Initialize OLED
//   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//     Serial.println(F("SSD1306 allocation failed"));
//     for (;;);
//   }

//   display.clearDisplay();
//   display.setTextColor(SSD1306_WHITE);
//   display.setTextSize(1);
//   display.setCursor(20, 25);
//   display.println("Weather Station");
//   display.display();
//   delay(2000);
// }

// void loop() {
//   delay(2000); // DHT11 reads slowly

//   float humidity = dht.readHumidity();
//   float tempC = dht.readTemperature();
//   float tempF = dht.readTemperature(true);

//   if (isnan(humidity) || isnan(tempC)) {
//     Serial.println(F("Failed to read from DHT sensor!"));
//     display.clearDisplay();
//     display.setCursor(15, 25);
//     display.setTextSize(1);
//     display.println("Sensor Error!");
//     display.display();
//     return;
//   }

//   // Print to Serial
//   Serial.print("Temp: ");
//   Serial.print(tempC);
//   Serial.print(" °C  ");
//   Serial.print(tempF);
//   Serial.print(" °F  ");
//   Serial.print("Humidity: ");
//   Serial.print(humidity);
//   Serial.println(" %");

//   // Display on OLED
//   display.clearDisplay();

//   // Header
//   display.setTextSize(1);
//   display.setCursor(20, 0);
//   display.println("Weather Monitor");

//   // Temperature in Celsius
//   display.setTextSize(1);
//   display.setCursor(0, 20);
//   display.print(tempC, 1);
//   display.print((char)247); // Degree symbol
//   display.print("C");

//   // Temperature in Fahrenheit
//   display.setTextSize(1);
//   display.setCursor(0, 40);
//   display.print(tempF, 1);
//   display.print((char)247);
//   display.println("F");

//   // Humidity
//   display.setTextSize(2);
//   display.setCursor(80, 20);
//   display.print(humidity, 0);
//   display.println("%");

//   // Optional labels
//   display.setTextSize(1);
//   display.setCursor(80, 48);
//   display.println("Humidity");

//   display.display();
// }

