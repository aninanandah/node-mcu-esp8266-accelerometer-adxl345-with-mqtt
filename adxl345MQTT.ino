#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
// ADXL345 I2C address = 0x53(83)
#define Addr 0x53

const char* dataX = "timjembatan1/1/X/";
const char* dataY = "timjembatan1/1/Y/";
const char* dataZ = "timjembatan1/1/Z/";
const char* ssid = "Timjembatan";                       //ssid your wifi
const char* password = "wisuda2017";                    //your wifi password
//const char* mqtt_server = "broker.mqttdashboard.com"; //mqtt broker choose one
const char* mqtt_server = "test.mosquitto.org";
//const char* mqtt_server = "iot.eclipse.org";
WiFiClient espClient;
PubSubClient client(espClient);

int interval = 100;
long lastMsg = 0;
//char msg[50];
int value = 0;
//int threhold = 50; // you might need to adjust this value to define light on/off status

float xAccl, yAccl, zAccl;

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);                  //mqtt broker port
  client.setCallback(callback);
}
void loop()
{
   if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();

  if (now - lastMsg > interval) {
     lastMsg = now;
   bacaSensor();
  }
}

