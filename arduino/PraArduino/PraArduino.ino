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

const char* ssid = "Patrik";
const char* password = "qwertqwerty";
const char* mqtt_server = "praalgebra.cloud.shiftr.io";
const String mqtt_user = "praalgebra";
const String mqtt_password = "h1sXSluD0OUMAZpv";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (200)
char msg[MSG_BUFFER_SIZE];
int value = 0;

#define SEALEVELPRESSURE_HPA (1013.25)

float temperature = 20.0;
float pressure = 1013.25;
float humidity = 50.0;
float gas_resistance = 100.0;
float altitude = 100.0;

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

  // if (!bme.begin()) {
  //   Serial.println("Could not find a valid BME680 sensor, check wiring!");
  //   while (1)
  //     ;
  // }

  // // Set up oversampling and filter initialization
  // bme.setTemperatureOversampling(BME680_OS_8X);
  // bme.setHumidityOversampling(BME680_OS_2X);
  // bme.setPressureOversampling(BME680_OS_4X);
  // bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  // bme.setGasHeater(320, 150);  // 320*C for 150 ms
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

    // if (!bme.performReading()) {
    //   Serial.println("Failed to perform reading :(");
    //   return;
    // }

    temperature += random(-10, 10) * 0.1;
    pressure += random(-100, 100) * 0.01;
    humidity += random(-50, 50) * 0.1;
    gas_resistance += random(-100, 100) * 0.1;
    altitude += random(-5, 5) * 0.1;

    snprintf(msg, MSG_BUFFER_SIZE,
             "Temperature = %.1f *C\nPressure = %.2f hPa\nHumidity = %.1f %%\nGas = %.1f KOhms\nApprox. Altitude = %.1f m",
             temperature,
             pressure,
             humidity,
             gas_resistance,
             altitude);

    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}
