/*
  Coffee bin

  MQTT bin project for coffee-bin https://coffee-bin-mqtt.readthedocs.io/

  The circuit:
  * Input: Swtich for maintenance mode on pin XX to ground
  * Input: Coffee bin bin attached to pin XX  from +3V
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

#include <ArduinoOTA.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ButtonDebounce.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Load configuration
#include "config.h"

// Include libraries
#include "wifi.h"
#include "mqtt.h"
#include "ota.h"
#include "pins.h"

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println(F(" ✰✰✰  Coffee-Bin booting ✰✰✰ "));
  
  setupWifi();
  setupOta();
  setupPins();
  setupMqtt();
}


void loop() {
  loopMqtt();
  loopOta();
  loopPin();

  // Heartbeat LED
  digitalWrite(led1, LOW);
  delay(80);
  digitalWrite(led2, LOW);
  delay(20);
  digitalWrite(led1, HIGH);
  delay(80);
  digitalWrite(led2, HIGH);
  delay(1200);
}
