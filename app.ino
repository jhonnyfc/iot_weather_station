#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <math.h>

#include "./config/cloudVars.h"
#include "./config/thingProperties.h"
#include "./constants/global.h"
#include "./utils/tick.h"

#define DHT11_PIN 19
#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);

const int seaLevelPreassure = 1007.2;
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);  // sda= GPIO_21 /scl= GPIO_22
  delay(2000);

  dht.begin();

  if (!bmp.begin(0x76)) {
    Serial.println(F("#### Could not find a valid BMP280 sensor, check wiring! ####"));
  }

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(0);  // Nivel de logs 0 - 4
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  humidity = roundFloat(dht.readHumidity());
  altitude = roundFloat(bmp.readAltitude(seaLevelPreassure));
  pressure = roundFloat(bmp.readPressure() / 100);
  temperature = roundFloat(bmp.readTemperature());

  if (isTick()) {
    Serial.print("- Tick: ");
    Serial.println(getDiff());

    printWeatherStats();

    saveTick();
  }
}

void printWeatherStats() {
  Serial.print("DHT11 -> Temperature: ");
  Serial.print(dht.readTemperature());
  Serial.print(" C");

  Serial.print("- Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print(F("BMP280 -> Temperature: "));
  Serial.print(temperature);
  Serial.print(" C");

  Serial.print(F(" - Pressure: "));
  Serial.print(pressure);
  Serial.print(" hPa");

  Serial.print(F(" - Approx altitude: "));
  Serial.print(altitude);  // The "1019.66" is the pressure(hPa) at sea level in day in your region
  Serial.println(" m");
}

float roundFloat(float value) {
  return roundf(value * 10) / 10;
}