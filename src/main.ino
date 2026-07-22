#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <Adafruit_BME280.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <EEPROM.h>

// Подключение заголовочных файлов
#include "config.h"
#include "wifi_manager.h"
#include "mqtt_client.h"
#include "sensors.h"

// Константы
#define EEPROM_SIZE 512
#define SLEEP_DELAY 60000  // 60 секунд

// Глобальные объекты
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);
Adafruit_BME280 bme;
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Переменные
unsigned long lastReadTime = 0;
bool wifiConfigured = false;
bool mqttConfigured = false;

void setup() {
  // Инициализация Serial
  Serial.begin(115200);
  Serial.println("========================================");
  Serial.println("  ESP32-C3 MeteoStation Pro v1.1.0-beta");
  Serial.println("========================================");
  
  // Инициализация EEPROM
  EEPROM.begin(EEPROM_SIZE);
  
  // Инициализация OLED
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 20, "ESP32-C3");
  u8g2.drawStr(0, 40, "MeteoStation");
  u8g2.drawStr(0, 60, "v1.1.0-beta");
  u8g2.sendBuffer();
  delay(2000);
  
  // Инициализация датчиков
  if (initSensors()) {
    Serial.println("[OK] Sensors initialized");
  } else {
    Serial.println("[ERROR] Sensors not found");
    displayError("SENSORS ERROR");
  }
  
  // Настройка Wi-Fi
  configureWiFi();
  
  // Настройка MQTT
  if (wifiConfigured) {
    configureMQTT();
  }
  
  // Показ информации на OLED
  updateDisplay();
  
  Serial.println("[INFO] Setup complete!");
  Serial.println("[INFO] Entering main loop...");
}

void loop() {
  // Обработка MQTT
  if (mqttConfigured && wifiConfigured) {
    mqttClient.loop();
  }
  
  // Чтение данных каждые 5 секунд
  if (millis() - lastReadTime > 5000) {
    lastReadTime = millis();
    
    // Чтение датчиков
    float temp = readTemperature();
    float hum = readHumidity();
    float press = readPressure();
    int pm25 = readPM25();
    
    // Вывод в Serial
    Serial.print("[DATA] Temp: ");
    Serial.print(temp);
    Serial.print(" C, Hum: ");
    Serial.print(hum);
    Serial.print("%, Press: ");
    Serial.print(press);
    Serial.print(" hPa, PM2.5: ");
    Serial.println(pm25);
    
    // Отправка в MQTT
    if (mqttConfigured && wifiConfigured) {
      publishMQTT(temp, hum, press, pm25);
    }
    
    // Обновление OLED
    updateDisplay(temp, hum, press, pm25);
  }
  
  // Проверка Wi-Fi
  if (wifiConfigured && WiFi.status() != WL_CONNECTED) {
    Serial.println("[WARN] Wi-Fi disconnected, reconnecting...");
    reconnectWiFi();
  }
  
  // Проверка MQTT
  if (mqttConfigured && !mqttClient.connected()) {
    Serial.println("[WARN] MQTT disconnected, reconnecting...");
    reconnectMQTT();
  }
  
  delay(100);
}

void displayError(const char* msg) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 20, "ERROR");
  u8g2.drawStr(0, 40, msg);
  u8g2.sendBuffer();
  delay(5000);
}