/**
 * mqtt_client.cpp - MQTT клиент
 */

#include <PubSubClient.h>
#include "mqtt_client.h"
#include "config.h"

extern PubSubClient mqttClient;
extern bool mqttConfigured;

void configureMQTT() {
  Serial.println("[MQTT] Configuring...");
  
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);
  
  if (mqttClient.connect(DEVICE_ID, MQTT_USER, MQTT_PASSWORD)) {
    mqttConfigured = true;
    Serial.println("[MQTT] Connected");
    
    // Отправка статуса
    mqttClient.publish(MQTT_TOPIC_STATUS, "online");
  } else {
    mqttConfigured = false;
    Serial.print("[MQTT] Connection failed, rc=");
    Serial.println(mqttClient.state());
  }
}

void reconnectMQTT() {
  Serial.println("[MQTT] Reconnecting...");
  
  if (mqttClient.connect(DEVICE_ID, MQTT_USER, MQTT_PASSWORD)) {
    mqttConfigured = true;
    Serial.println("[MQTT] Reconnected");
    mqttClient.publish(MQTT_TOPIC_STATUS, "online");
  } else {
    mqttConfigured = false;
    Serial.print("[MQTT] Reconnect failed, rc=");
    Serial.println(mqttClient.state());
  }
}

void publishMQTT(float temp, float hum, float press, int pm25) {
  if (!mqttConfigured) return;
  
  char msg[50];
  
  // Температура
  snprintf(msg, 50, "%.1f", temp);
  mqttClient.publish(MQTT_TOPIC_TEMP, msg);
  
  // Влажность
  snprintf(msg, 50, "%.1f", hum);
  mqttClient.publish(MQTT_TOPIC_HUM, msg);
  
  // Давление
  snprintf(msg, 50, "%.1f", press);
  mqttClient.publish(MQTT_TOPIC_PRESS, msg);
  
  // PM2.5
  if (pm25 >= 0) {
    snprintf(msg, 50, "%d", pm25);
    mqttClient.publish(MQTT_TOPIC_PM25, msg);
  }
  
  Serial.println("[MQTT] Data published");
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("[MQTT] Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}