#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>

#define DHT11_PIN 19
#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);

const int seaLevelPreassure = 1007.2;
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);  // sda= GPIO_21 /scl= GPIO_22
  dht.begin();

  if (!bmp.begin(0x76)) {
    Serial.println(F("#### Could not find a valid BMP280 sensor, check wiring! ####"));
  }
}

void loop() {
  Serial.print("DHT11 -> Temperature: ");
  Serial.print(dht.readTemperature());
  Serial.print(" C");

  Serial.print("- Humidity: ");
  Serial.print(dht.readHumidity());
  Serial.println(" %");

  Serial.print(F("BMP280 -> Temperature: "));
  Serial.print(bmp.readTemperature());
  Serial.print(" C");

  Serial.print(F(" - Pressure: "));
  Serial.print(bmp.readPressure() / 100);
  Serial.print(" hPa");

  Serial.print(F(" - Approx altitude: "));
  Serial.print(bmp.readAltitude(seaLevelPreassure));  // The "1019.66" is the pressure(hPa) at sea level in day in your region
  Serial.println(" m");
  delay(5000);
}
