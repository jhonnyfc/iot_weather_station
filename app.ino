#include "DHT.h"

#define DHT11_PIN 4
#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  Serial.print("Temperature: ");
  Serial.print(dht.readTemperature());
  Serial.print(" C");

  Serial.print("- Humidity: ");
  Serial.print(dht.readHumidity());
  Serial.println(" %");
  delay(5000);
}
