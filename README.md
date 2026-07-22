# 🌦️ Метеостанция на ESP32-C3

![ESP32-C3](https://img.shields.io/badge/ESP32--C3-ESP-IDF-blue?logo=espressif)
![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32--C3-orange)
![License](https://img.shields.io/badge/License-MIT-green)

Компактная Wi-Fi метеостанция на базе **ESP32-C3** (RISC-V). Измеряет температуру, влажность и атмосферное давление, отправляет данные в MQTT и отображает на встроенном OLED-экране (опционально).

---

## 🚀 Возможности
- 🌡️ Датчик **BME280** (температура, влажность, давление) или **DHT11/22**
- 📡 Передача данных по **MQTT** (поддержка Adafruit IO, Home Assistant, ThingsBoard)
- 🖥️ Встроенный веб-сервер для просмотра данных в реальном времени
- 📟 Поддержка **OLED SSD1306** (I²C) для отображения показаний
- 💤 Режим глубокого сна (Deep Sleep) для экономии батареи
- ⚙️ Настройка Wi-Fi через **WiFiManager** (без перепрошивки)

---

## 📦 Содержимое репозитория
```plaintext
📁 Метеостанция-ESP32C3/
├── 📁 firmware/
│   ├── 📁 v1.0.0/                  # Стабильная версия
│   │   ├── meteo_esp32c3_v1.0.0.bin
│   │   └── meteo_esp32c3_v1.0.0.elf
│   ├── 📁 v1.1.0-beta/             # Бета-версия с поддержкой BME680
│   │   └── meteo_esp32c3_v1.1.0-beta.bin
│   └── 📄 README_FIRMWARE.md       # Описание версий и changelog
├── 📁 libraries/                   # Необходимые библиотеки (если нет в PlatformIO)
│   ├── BME280/
│   ├── SSD1306/
│   └── WiFiManager/
├── 📁 schematics/                  # Схемы подключения
│   ├── connection_diagram.png
│   └── pinout_esp32c3.png
├── 📁 docs/                        # Документация (Datasheets, инструкции)
│   ├── BME280_datasheet.pdf
│   └── setup_guide.pdf
├── 📄 platformio.ini               # Конфиг PlatformIO (для сборки из исходников)
├── 📄 LICENSE
└── 📄 README.md                    # Этот файл
