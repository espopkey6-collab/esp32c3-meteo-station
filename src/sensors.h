
#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

bool initSensors();
float readTemperature();
float readHumidity();
float readPressure();
int readPM25();

#endif // SENSORS_H