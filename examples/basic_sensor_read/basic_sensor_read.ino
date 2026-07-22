#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Создаем объект датчика
Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32-C3 BME280 Test");
  
  // Инициализация BME280
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
  Serial.println("BME280 initialized!");
}

void loop() {
  // Чтение данных
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;
  
  // Вывод в Serial
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
  
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");
  
  Serial.println("---");
  
  delay(2000);
}