#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 2

DHT dht(DHTPIN, DHTTYPE);

int baud = 9600;
int delayT = 3; // Seconds

float tempC;
float tempF;
int humid;
float heatIndexC;
float heatIndexF;
String message;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(baud);
  dht.begin();

  delayT*=1000;
}

void loop() {
  // put your main code here, to run repeatedly:
  tempC = dht.readTemperature();
  tempF = dht.readTemperature(true);
  humid = dht.readHumidity();

  if (isnan(tempC) || isnan(tempF) || isnan(humid)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(5000);
    return;
  }

  heatIndexC = dht.computeHeatIndex(tempC, humid, false);
  heatIndexF = dht.computeHeatIndex(tempF, humid, true);

  message = "Temperature: " + String(tempC) + "°C and " + String(tempF) + "°F | Humidity: " + String(humid) + "% \n";

  message += "Heat Index / Feels Like: " + String(heatIndexC) + "°C and " + String(heatIndexF) + "°F";

  Serial.println(message);

  delay(delayT);
}
