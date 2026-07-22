#ifndef CONFIG_H
#define CONFIG_H

// ============================
// Wi-Fi настройки
// ============================
#define WIFI_SSID         "your_wifi_ssid"
#define WIFI_PASSWORD     "your_wifi_password"
#define WIFI_TIMEOUT      30  // Секунд

// ============================
// MQTT настройки
// ============================
#define MQTT_SERVER       "192.168.1.100"
#define MQTT_PORT         1883
#define MQTT_USER         "mqtt_user"
#define MQTT_PASSWORD     "mqtt_password"

#define MQTT_TOPIC_TEMP   "home/meteo/temperature"
#define MQTT_TOPIC_HUM    "home/meteo/humidity"
#define MQTT_TOPIC_PRESS  "home/meteo/pressure"
#define MQTT_TOPIC_PM25   "home/meteo/pm25"
#define MQTT_TOPIC_PM10   "home/meteo/pm10"
#define MQTT_TOPIC_STATUS "home/meteo/status"

// ============================
// Настройки датчиков
// ============================
#define BME280_ADDRESS    0x76  // или 0x77
#define PMS5003_RX_PIN    GPIO_NUM_6
#define PMS5003_TX_PIN    GPIO_NUM_7

// ============================
// Настройки OLED
// ============================
#define OLED_ADDRESS      0x3C
#define OLED_WIDTH        128
#define OLED_HEIGHT       64

// ============================
// Настройки устройства
// ============================
#define DEVICE_NAME       "MeteoStation-001"
#define DEVICE_ID         "ESP32C3_001"
#define FIRMWARE_VERSION  "1.1.0-beta"

// ============================
// Настройки энергосбережения
// ============================
#define DEEP_SLEEP_ENABLE true
#define DEEP_SLEEP_DELAY  60000  // 60 секунд
#define WAKEUP_PIN        GPIO_NUM_0

#endif // CONFIG_H