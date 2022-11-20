#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#include "../constants/arduino_secrets.h"

void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);

  ArduinoCloud.addProperty(altitude, READ, 5 * SECONDS, NULL);
  ArduinoCloud.addProperty(humidity, READ, 5 * SECONDS, NULL);
  ArduinoCloud.addProperty(pressure, READ, 5 * SECONDS, NULL);
  ArduinoCloud.addProperty(temperature, READ, 5 * SECONDS, NULL);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
