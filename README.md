# 🌦️ Метеостанция на ESP32-C3

[![ESP32-C3](https://img.shields.io/badge/ESP32--C3-ESP--IDF-blue?logo=espressif)](https://www.espressif.com/en/products/socs/esp32-c3)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32--C3-orange)](https://platformio.org/)
[![Arduino](https://img.shields.io/badge/Arduino-ESP32--C3-green)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub release](https://img.shields.io/badge/Release-v1.0.0-brightgreen)](https://github.com/your-username/meteo-esp32c3/releases)

**Компактная Wi-Fi метеостанция на базе ESP32-C3 для мониторинга температуры, влажности, атмосферного давления и качества воздуха с отображением на OLED-экране и передачей данных в MQTT.**

---

## 📋 Оглавление

- [📖 Описание](#-описание)
- [✨ Возможности](#-возможности)
- [🛠️ Требуемые компоненты](#️-требуемые-компоненты)
- [🔌 Схема подключения](#-схема-подключения)
- [⚙️ Настройка и прошивка](#️-настройка-и-прошивка)
- [🚀 Использование](#-использование)
- [📁 Структура файлов прошивок](#-структура-файлов-прошивок)
- [📊 Примеры данных](#-примеры-данных)
- [🐛 Известные проблемы](#-известные-проблемы)
- [🛣️ Планы по развитию](#️-планы-по-развитию)
- [📄 Лицензия](#-лицензия)
- [📬 Контакты](#-контакты)

---

## 📖 Описание

ESP32-C3 MeteoStation Pro — это полнофункциональная метеостанция для умного дома и DIY-проектов. Устройство построено на базе **ESP32-C3** (RISC-V архитектура) и использует датчики **BME280** (температура, влажность, давление) и **PMS5003** (качество воздуха, опционально).

Данные отображаются на **OLED-дисплее SSD1306** (I²C) и передаются через Wi-Fi на **MQTT-брокер**, что позволяет легко интегрировать станцию в **Home Assistant**, **OpenHAB** или **Adafruit IO**. Проект поддерживает режим энергосбережения и может работать до 3 недель от батареи 18650.

Прошивка написана в **Arduino IDE** с использованием библиотек U8g2, Adafruit BME280 и PubSubClient. Настройка Wi-Fi и MQTT выполняется через последовательный порт или веб-интерфейс.

---

## ✨ Возможности

| Функция | Описание |
|---------|----------|
| 🌡️ **Метеоданные** | Температура (±1°C), влажность (±3%), атмосферное давление (±1 гПа) |
| 🏭 **Качество воздуха** | PM1.0, PM2.5, PM10 (при использовании PMS5003) |
| 🖥️ **OLED-дисплей** | Отображение текущих показаний в реальном времени |
| 📶 **Wi-Fi & MQTT** | Передача данных на любой MQTT-брокер (поддержка TLS) |
| 🌐 **Веб-интерфейс** | Страница с данными и графиками (доступна по IP) |
| 💾 **EEPROM** | Сохранение настроек (Wi-Fi, MQTT, имя устройства) |
| 💤 **Deep Sleep** | Экономия энергии (потребление < 20 мкА в режиме сна) |
| 🚨 **Индикация** | Светодиод для отображения статуса (Wi-Fi, ошибки) |
| 🔄 **OTA-обновления** | Обновление прошивки по Wi-Fi (в разработке) |

---

## 🛠️ Требуемые компоненты

### Основные компоненты

| Компонент | Модель | Количество | Примечание |
|-----------|--------|------------|------------|
| Микроконтроллер | ESP32-C3 DevKitM-1 (или Seeed XIAO ESP32C3) | 1 | Поддержка Arduino/ESP-IDF |
| Датчик температуры/влажности/давления | BME280 (I²C) | 1 | Адрес: 0x77 (или 0x76) |
| OLED-дисплей | SSD1306 (I²C, 128x64) | 1 | Адрес: 0x3C |
| Датчик качества воздуха | PMS5003 (UART) | 1 | Опционально |
| Кнопка | Тактовая кнопка (GPIO0) | 1 | Для сброса настроек |
| Светодиод | LED (GPIO10) | 1 | Индикация статуса |
| Резистор | 220 Ом | 1 | Для светодиода |
| Источник питания | Micro-USB или Li-Ion 18650 | 1 | 3.3V-5V |

### Дополнительные компоненты (опционально)

- Корпус для устройства
- Аккумулятор 18650 с защитой
- Модуль зарядки TP4056

---

## 🔌 Схема подключения

### Подключение по шине I²C (BME280 + OLED)

| ESP32-C3 Pin | BME280 | OLED SSD1306 | Примечание |
|--------------|--------|--------------|------------|
| GPIO8 (SDA) | SDA | SDA | Подтяжка 4.7кОм к 3.3V |
| GPIO9 (SCL) | SCL | SCL | Подтяжка 4.7кОм к 3.3V |
| 3.3V | VCC | VCC | Питание 3.3V |
| GND | GND | GND | Общий минус |

### Подключение датчика качества воздуха PMS5003 (UART)

| ESP32-C3 Pin | PMS5003 | Примечание |
|--------------|---------|------------|
| GPIO6 (RX) | TX | Прием данных от датчика |
| GPIO7 (TX) | RX | Передача данных (не используется) |
| 5V | VCC | Питание 5V (потребляет ~100 мА) |
| GND | GND | Общий минус |

### Дополнительные пины

| ESP32-C3 Pin | Компонент | Примечание |
|--------------|-----------|------------|
| GPIO0 | Кнопка (GND) | Сброс настроек Wi-Fi |
| GPIO10 | LED -> 220 Ом -> 3.3V | Индикация статуса |

### Схема подключения (визуальная)

![Схема подключения](schematics/connection_diagram.png)

---

## ⚙️ Настройка и прошивка

### 1. Подготовка среды разработки

#### Вариант A: Arduino IDE (рекомендуется для новичков)

1. Установите Arduino IDE (версия 2.0+)
2. Добавьте поддержку ESP32:
   - Откройте **Файл -> Настройки** -> **Дополнительные ссылки для менеджера плат**:
   - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   - Откройте **Инструменты -> Плата -> Менеджер плат** -> найдите **esp32** -> установите (версия 2.0.14+)
3. Установите библиотеки через **Скетч -> Подключить библиотеку -> Управлять библиотеками...**:
   - U8g2 (для OLED-дисплея)
   - Adafruit BME280 Library
   - Adafruit Unified Sensor
   - PubSubClient (для MQTT)
   - ArduinoJson (для парсинга данных)

#### Вариант B: PlatformIO (для опытных)

1. Установите Visual Studio Code
2. Установите расширение PlatformIO IDE
3. Склонируйте репозиторий:
   git clone https://github.com/your-username/meteo-esp32c3.git
   cd meteo-esp32c3
4. Откройте папку в VSCode (PlatformIO автоматически подгрузит зависимости из platformio.ini)

### 2. Настройка параметров Wi-Fi и MQTT

Перед прошивкой отредактируйте файл config.h (или введите данные через монитор порта после загрузки):

// config.h
#define WIFI_SSID         "your_wifi_ssid"
#define WIFI_PASSWORD     "your_wifi_password"
#define MQTT_SERVER       "192.168.1.100"
#define MQTT_PORT         1883
#define MQTT_USER         "mqtt_user"
#define MQTT_PASSWORD     "mqtt_password"
#define MQTT_TOPIC_TEMP   "home/meteo/temperature"
#define MQTT_TOPIC_HUM    "home/meteo/humidity"
#define MQTT_TOPIC_PRESS  "home/meteo/pressure"
#define DEVICE_NAME       "MeteoStation-001"

### 3. Прошивка устройства

#### Через Arduino IDE:

1. Выберите плату: **Инструменты -> Плата -> ESP32 Arduino -> ESP32C3 Dev Module**
2. Настройте параметры:
   - CPU Frequency: 160 MHz
   - Flash Size: 4MB (32Mb)
   - Partition Scheme: Default 4MB
   - Upload Speed: 921600
3. Подключите ESP32-C3 через USB-кабель
4. Выберите порт: **Инструменты -> Порт -> COMx (ESP32-C3)**
5. Нажмите **Загрузить** (Стрелка вправо)
6. При ошибке загрузки: удерживайте кнопку BOOT на плате во время нажатия кнопки "Загрузить"

#### Через esptool.py (готовые прошивки):

Установка esptool:
pip install esptool

Стирание флеш-памяти:
esptool.py --chip esp32c3 --port /dev/ttyUSB0 erase_flash

Загрузка прошивки:
esptool.py --chip esp32c3 --port /dev/ttyUSB0 write_flash 0x0 firmware/meteo_esp32c3_v1.0.0.bin

### 4. Проверка работы

1. Откройте монитор порта: **Инструменты -> Монитор порта** (скорость 115200 бод)
2. Нажмите кнопку **Reset** на плате
3. Вы увидите логи загрузки и приглашение для ввода команд

---

## 🚀 Использование

### Первый запуск

1. После прошивки откройте монитор порта (115200 бод)
2. Нажмите **Reset** и дождитесь приглашения:

*** ESP32-C3 MeteoStation v1.0.0 ***
Device name: MeteoStation-001
Wi-Fi: Not connected
Enter command (help for list):

3. Введите команды для настройки:
   - wifi set <SSID> <PASSWORD> — настройка Wi-Fi
   - mqtt set <SERVER> <PORT> <USER> <PASS> — настройка MQTT
   - name set <NAME> — задать имя устройства
   - save — сохранить настройки в EEPROM
   - reboot — перезагрузить устройство

### Команды управления

| Команда | Описание | Пример |
|---------|----------|--------|
| help | Вывод списка команд | help |
| info | Показать текущие показания | info |
| status | Показать статус устройства | status |
| wifi set <SSID> <PASS> | Настройка Wi-Fi | wifi set MyWiFi pass123 |
| mqtt set <SERVER> <PORT> <USER> <PASS> | Настройка MQTT | mqtt set 192.168.1.100 1883 user pass |
| name set <NAME> | Задать имя устройства | name set Meteo-Kitchen |
| reset | Сброс всех настроек | reset |
| sleep <SECONDS> | Перейти в Deep Sleep | sleep 60 |
| save | Сохранить настройки | save |
| reboot | Перезагрузить устройство | reboot |

### Работа в автономном режиме

- **OLED-дисплей**: автоматически отображает данные в цикле (температура -> влажность -> давление -> имя устройства -> IP-адрес)
- **Веб-интерфейс**: доступен по IP-адресу устройства (например, http://192.168.1.101/)
- **MQTT**: данные публикуются каждые 60 секунд в указанные топики

### Сброс настроек Wi-Fi

Если вы забыли пароль или хотите сменить сеть:
1. Во время загрузки удерживайте кнопку, подключенную к GPIO0 (земля)
2. Дождитесь, пока светодиод начнет мигать 3 раза
3. Отпустите кнопку — устройство войдет в режим AP (точка доступа)
4. Подключитесь к Wi-Fi сети MeteoStation-XXXX и откройте 192.168.4.1 для настройки

---

## 📁 Структура файлов прошивок

meteo-esp32c3/
├── firmware/                     # Скомпилированные прошивки
│   ├── v1.0.0/                   # Стабильная версия
│   │   ├── meteo_esp32c3_v1.0.0.bin
│   │   ├── meteo_esp32c3_v1.0.0.elf
│   │   └── meteo_esp32c3_v1.0.0.map
│   ├── v1.1.0-beta/              # Бета-версия с поддержкой PMS5003
│   │   ├── meteo_esp32c3_v1.1.0-beta.bin
│   │   └── CHANGELOG.md
│   └── README_FIRMWARE.md        # Описание версий и изменений
├── libraries/                    # Внешние библиотеки (для PlatformIO)
│   ├── U8g2/
│   ├── Adafruit_BME280_Library/
│   └── PubSubClient/
├── schematics/                   # Схемы и чертежи
│   ├── connection_diagram.png
│   ├── pcb_layout.png
│   └── pinout_esp32c3.png
├── docs/                         # Документация
│   ├── BME280_datasheet.pdf
│   ├── SSD1306_datasheet.pdf
│   └── PMS5003_datasheet.pdf
├── examples/                     # Примеры кода
│   ├── basic_sensor_read/
│   └── mqtt_publish/
├── src/                          # Исходный код прошивки
│   ├── main.ino
│   ├── config.h
│   ├── wifi_manager.cpp
│   ├── mqtt_client.cpp
│   └── sensors.cpp
├── platformio.ini                # Конфигурация PlatformIO
├── LICENSE                       # Лицензия MIT
└── README.md                     # Этот файл

---

## 📊 Примеры данных

### MQTT-сообщение (JSON)

{
  "device": "MeteoStation-001",
  "timestamp": "2026-07-22T14:30:00Z",
  "temperature": 24.5,
  "humidity": 55.2,
  "pressure": 1012.3,
  "pm2.5": 12.4,
  "pm10": 18.7,
  "battery": 3.8
}

### Веб-интерфейс (HTML)

<!DOCTYPE html>
<html>
<head><title>ESP32-C3 MeteoStation</title></head>
<body>
  <h1>MeteoStation-001</h1>
  <p>Temperature: 24.5 °C</p>
  <p>Humidity: 55.2 %</p>
  <p>Pressure: 1012.3 hPa</p>
  <p>PM2.5: 12.4 µg/m³</p>
  <p>Last update: 2026-07-22 14:30:00</p>
</body>
</html>

### Лог в мониторе порта

[INFO] Device: MeteoStation-001
[INFO] Wi-Fi connected, IP: 192.168.1.101
[INFO] MQTT connected to 192.168.1.100:1883
[INFO] Temp: 24.5°C, Humidity: 55.2%, Pressure: 1012.3 hPa
[INFO] PM2.5: 12.4 µg/m³, PM10: 18.7 µg/m³
[INFO] Publishing to MQTT... done.
[INFO] Entering Deep Sleep for 60 seconds...

---

## 🐛 Известные проблемы

| Проблема | Решение |
|----------|---------|
| ESP32-C3 не прошивается | Удерживайте кнопку BOOT во время загрузки |
| Не подключается к Wi-Fi | Проверьте правильность SSID/пароля, отключите MAC-фильтр в роутере |
| BME280 не читается | Проверьте I²C-адрес (0x77 или 0x76), подтяните линии резисторами 4.7кОм |
| OLED не отображает данные | Проверьте адрес (обычно 0x3C), переключите напряжение питания на 3.3V |
| MQTT не подключается | Проверьте IP-адрес, порт, логин/пароль, разрешите подключение с этого IP |
| Высокое энергопотребление | Отключите в коде ненужные модули, используйте режим Deep Sleep |
| PMS5003 не работает | Проверьте питание 5V, используйте уровни 3.3V (ESP32-C3 совместим) |

---

## 🛣️ Планы по развитию

- [ ] OTA-обновления: загрузка прошивок через Wi-Fi без USB-кабеля
- [ ] Поддержка BME680: добавление датчика качества воздуха (VOC, газа)
- [ ] Графики на веб-интерфейсе: визуализация данных за последние 24 часа
- [ ] Поддержка SD-карты: логирование данных на microSD
- [ ] Датчик дождя: определение осадков
- [ ] Анемометр: измерение скорости ветра
- [ ] Telegram-бот: отправка уведомлений при изменениях погоды
- [ ] Мобильное приложение: управление через Bluetooth (ESP32-C3 поддерживает BLE)

---

## 📄 Лицензия

Этот проект распространяется под лицензией MIT. Вы можете свободно использовать, модифицировать и распространять код с указанием авторства.

MIT License

Copyright (c) 2026 Alex

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

## 📬 Контакты

- **Автор**: [Alex]
- **Email**: espopkey6@gmail.com

---

## 🙏 Благодарности

- Espressif за отличный ESP32-C3
- Сообщество Arduino за библиотеки
- Всем, кто тестировал и предлагал улучшения

---

⭐ Поддержать проект https://choco.tips/qr/88643103

---
