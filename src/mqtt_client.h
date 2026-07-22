#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <Arduino.h>

void configureMQTT();
void reconnectMQTT();
void publishMQTT(float temp, float hum, float press, int pm25);
void mqttCallback(char* topic, byte* payload, unsigned int length);

#endif // MQTT_CLIENT_H