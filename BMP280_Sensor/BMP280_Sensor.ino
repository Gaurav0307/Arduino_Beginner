/*
#include <Adafruit_BMP280.h>
#include <SPI.h>

#define BMP_SCK  13 // SCL
#define BMP_MISO 12 // SDO
#define BMP_MOSI 11 // SDA
#define BMP_CS   10 // CSB

Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);

void setup() {
  Serial.begin(9600);
  delay(1000);

  if (!bmp.begin()) {
    Serial.println("BMP280 not detected using SPI!");
    while (1);
  }

  Serial.println("BMP280 SPI Mode Initialized!");
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude(1013.25));
  Serial.println(" m");

  Serial.println("--------------------------");
  delay(1000);
}
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C

// SDA = A4
// SCL = A5

void setup() {
  Serial.begin(9600);

  if (!bmp.begin(0x76)) {  // Most BMP280 use 0x76
    Serial.println("BMP280 not found!");
    while (1);
  }

  // Optional settings (more accuracy or low-power)
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,   // Temp oversampling
                  Adafruit_BMP280::SAMPLING_X16,  // Pressure oversampling
                  Adafruit_BMP280::FILTER_X16,    // Filter
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude(1013.25)); // Change 1013.25 to your local pressure for accuracy
  Serial.println(" m");

  Serial.println("-----------------------------");
  delay(1000);
}

