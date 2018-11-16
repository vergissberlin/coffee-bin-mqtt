/*
  Coffee bin

  MQTT sensor project for coffee-bin https://coffee-bin-mqtt.readthedocs.io/

  The circuit:
  * Input: Swtich for maintenance mode on pin XX to ground
  * Input: Coffee bin sensor attached to pin XX  from +3V
  * 10K resistor attached to pin 2 from ground 
  * Output: External LED to visualize the fill status on pin XX
  * Output: Internal LED to visualize the maintance status on pin XX
  * Output: Internal LED to visualize the wifi status on pin XX
  * list the components attached to each input
  * list the components attached to each output 

  Created 11 September 2018
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/coffee-bin-mqtt

*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Load configuration
#include "config.h"

void setupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
}

void setupOta() {
  ArduinoOTA.setPort(otaPort);
  ArduinoOTA.setHostname(otaHostName);
  ArduinoOTA.setPassword(otaPassword);

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

void setupPins() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void setup() {
  Serial.begin(9200);
  Serial.println("Booting");

  setupWifi();
  setupOta();
  setupPins();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  ArduinoOTA.handle();

  // Heartbeat LED
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  delay(20);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  delay(1200);
}
