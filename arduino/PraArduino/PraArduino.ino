/*
Basic BME680 sensor readings and publishing using mqtt.
Built for the purposes of PRA course.
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

Adafruit_BME680 bme;

const char* ssid = "Algebra-HotSpot";
const char* password = "";
const char* mqtt_server = "praalgebra.cloud.shiftr.io";
const String mqtt_user = "praalgebra";
const String mqtt_password = "h1sXSluD0OUMAZpv";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (200)
char msg[MSG_BUFFER_SIZE];

#define SEALEVELPRESSURE_HPA (1013.25)

// Variables to store the min and max values
float minTemperature = 1000.0;
float maxTemperature = -1000.0;
float minPressure = 10000.0;
float maxPressure = 0.0;
float minHumidity = 100.0;
float maxHumidity = 0.0;
float minGas = 10000.0;
float maxGas = 0.0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_user.c_str(), mqtt_password.c_str())) {  //put your clientId/userName/passWord here
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1)
      ;
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);  // 320*C for 150 ms
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

    if (!bme.performReading()) {
      Serial.println("Failed to perform reading :(");
      return;
    }

    float temperature = bme.temperature;
    float pressure = bme.pressure / 100.0;
    float humidity = bme.humidity;
    float gas = bme.gas_resistance / 1000.0;
    float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

    // Update min and max values
    if (temperature < minTemperature) minTemperature = temperature;
    if (temperature > maxTemperature) maxTemperature = temperature;
    if (pressure < minPressure) minPressure = pressure;
    if (pressure > maxPressure) maxPressure = pressure;
    if (humidity < minHumidity) minHumidity = humidity;
    if (humidity > maxHumidity) maxHumidity = humidity;
    if (gas < minGas) minGas = gas;
    if (gas > maxGas) maxGas = gas;

    snprintf(msg, MSG_BUFFER_SIZE,
             "Temperature = %.2f *C\nPressure = %.2f hPa\nHumidity = %.2f %%\nGas = %.2f KOhms\nApprox. Altitude = %.2f m",
             temperature, pressure, humidity, gas, altitude);

    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);

    // Publish statistics
    snprintf(msg, MSG_BUFFER_SIZE,
             "Min Temperature = %.2f *C\nMax Temperature = %.2f *C\nMin Pressure = %.2f hPa\nMax Pressure = %.2f hPa\nMin Humidity = %.2f %%\nMax Humidity = %.2f %%\nMin Gas = %.2f KOhms\nMax Gas = %.2f KOhms",
             minTemperature, maxTemperature, minPressure, maxPressure, minHumidity, maxHumidity, minGas, maxGas);

    Serial.print("Publish stats: ");
    Serial.println(msg);
    client.publish("statsTopic", msg);
  }
}
