
#include <Wire.h>
#include <Adafruit_BME280.h>
#include "sensors.h"
#include "config.h"

extern Adafruit_BME280 bme;

bool initSensors() {
  Serial.println("[Sensors] Initializing...");
  
  // Инициализация I2C
  Wire.begin();
  
  // Инициализация BME280
  if (!bme.begin(BME280_ADDRESS)) {
    Serial.println("[Sensors] BME280 not found!");
    return false;
  }
  
  Serial.println("[Sensors] BME280 OK");
  return true;
}

float readTemperature() {
  float temp = bme.readTemperature();
  if (isnan(temp)) {
    return -99.9;
  }
  return temp;
}

float readHumidity() {
  float hum = bme.readHumidity();
  if (isnan(hum)) {
    return -99.9;
  }
  return hum;
}

float readPressure() {
  float press = bme.readPressure() / 100.0F;
  if (isnan(press)) {
    return -99.9;
  }
  return press;
}

int readPM25() {
  // Реализация для PMS5003
  // Возвращает -1 если датчик не найден
  return -1; // Временная заглушка
}