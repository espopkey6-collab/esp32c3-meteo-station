
#include <WiFi.h>
#include <WiFiManager.h>
#include "wifi_manager.h"
#include "config.h"

extern bool wifiConfigured;

void configureWiFi() {
  Serial.println("[WiFi] Configuring...");
  
  // Проверка сохраненных настроек
  if (WiFi.getAutoConnect()) {
    Serial.println("[WiFi] Using saved credentials");
    WiFi.begin();
  } else {
    Serial.println("[WiFi] Starting WiFiManager");
    WiFiManager wm;
    
    // Автоматическое подключение
    if (!wm.autoConnect("MeteoStation-AP")) {
      Serial.println("[WiFi] Failed to connect");
      wifiConfigured = false;
      return;
    }
  }
  
  // Проверка подключения
  if (WiFi.status() == WL_CONNECTED) {
    wifiConfigured = true;
    Serial.print("[WiFi] Connected, IP: ");
    Serial.println(WiFi.localIP());
  } else {
    wifiConfigured = false;
    Serial.println("[WiFi] Not connected");
  }
}

void reconnectWiFi() {
  Serial.println("[WiFi] Reconnecting...");
  WiFi.reconnect();
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" OK");
    wifiConfigured = true;
  } else {
    Serial.println(" FAILED");
    wifiConfigured = false;
  }
}

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}