#include <Wire.h>
#include <U8g2lib.h>
#include "DHT.h"
#include <MQ135.h>

/* ================= OLED =================
   1.3" OLED (128x64)
   PAGE BUFFER MODE (LOW SRAM)
*/
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0,
  U8X8_PIN_NONE
);

// U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(
//   U8G2_R0,
//   U8X8_PIN_NONE
// );

#define SDA_PIN 9
#define SCL_PIN 10

/* ================= MQ135 ================= */
#define MQ135_PIN 3
MQ135 gasSensor(MQ135_PIN);

/* ================= DHT22 ================= */
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/* ================= GLOBALS ================= */
float tempC, tempF, humidity;
float correctedPPM;
const char* airStatus;

/* ================= SETUP ================= */
void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  delay(1000);
  Serial.begin(9600);
  dht.begin();
  u8g2.begin();

  /* Splash screen */
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.drawStr(20, 35, "Weather Station");
  } while (u8g2.nextPage());

  delay(2000);
}

/* ================= LOOP ================= */
void loop() {
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
  float correctedPPM = gasSensor.getCorrectedPPM(tempC, humidity);     // Apply temperature & humidity correction

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
    u8g2.drawStr(20, 10, "Weather Station");

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
