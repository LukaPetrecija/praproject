# Arduino BME680 Sensor Readings and MQTT Publishing

This project reads sensor data from a BME680 sensor and publishes it using MQTT. The project is built for the purposes of the PRA course.

## Overview

This project involves using an ESP8266 microcontroller to read temperature, pressure, humidity, gas resistance, and altitude from a BME680 sensor and publish these readings to an MQTT broker.

## Hardware Requirements

- ESP8266 microcontroller (e.g., NodeMCU)
- BME680 sensor
- Breadboard and jumper wires

## Software Requirements

- Arduino IDE
- Libraries:
  - [ESP8266WiFi](https://github.com/esp8266/Arduino)
  - [PubSubClient](https://github.com/knolleary/pubsubclient)
  - [Adafruit BME680](https://github.com/adafruit/Adafruit_BME680)

## Circuit Diagram

Connect the BME680 sensor to the ESP8266 as follows:

| BME680 | ESP8266 |
|--------|---------|
| VIN    | 3.3V    |
| GND    | GND     |
| SCL    | D1 (GPIO 5) |
| SDA    | D2 (GPIO 4) |

## Installation

1. **Clone the Repository:**
   ```sh
   git clone https://github.com/LukaPetrecija/praproject.git
   cd praproject
2. ## Install Libraries:
    Open the Arduino IDE and go to Sketch > Include Library > Manage Libraries..., then search for and install the following libraries:

    - ESP8266WiFi
    - PubSubClient
    - Adafruit BME680

3. ## Open the Project:
    Open the main.ino file in the Arduino IDE.

4. ## Configure WiFi and MQTT:
    Update the following lines in main.ino with your WiFi credentials and MQTT broker details:
    ```sh
    const char* ssid = "YourSSID";
    const char* password = "YourPassword";
    const char* mqtt_server = "your.mqtt.server";
    const String mqtt_user = "yourMQTTUser";
    const String mqtt_password = "yourMQTTPassword";
5. ## Upload the Code:
    Connect your ESP8266 to your computer via USB. Select the appropriate board and port in the Arduino IDE, then click the upload button.

## Usage
Once the code is uploaded and the ESP8266 is connected to WiFi, it will start publishing sensor readings to the MQTT broker every 2 seconds. You can view these readings by subscribing to the outTopic topic on your MQTT broker.

## Acknowledgements
Based on libraries and examples from Adafruit and PubSubClient.

