#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

// Wi-Fi настройки
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

// MQTT настройки
const char* mqtt_server = "192.168.1.100";
const int mqtt_port = 1883;
const char* mqtt_topic = "home/meteo/data";

// Объекты
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  
  // Инициализация BME280
  if (!bme.begin(0x76)) {
    Serial.println("BME280 not found!");
    while (1);
  }
  
  // Подключение к Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" OK");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  
  // Настройка MQTT
  client.setServer(mqtt_server, mqtt_port);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32C3_Meteo")) {
      Serial.println(" OK");
    } else {
      Serial.print(" FAILED, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 sec...");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Чтение данных
  float temp = bme.readTemperature();
  float hum = bme.readHumidity();
  float press = bme.readPressure() / 100.0F;
  
  // Формирование сообщения
  char msg[200];
  snprintf(msg, 200, "{\"temp\":%.1f,\"hum\":%.1f,\"press\":%.1f}", 
           temp, hum, press);
  
  // Отправка
  client.publish(mqtt_topic, msg);
  Serial.print("Published: ");
  Serial.println(msg);
  
  delay(60000); // 1 минута
}