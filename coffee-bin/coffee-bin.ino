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
#include <TimedBlink.h>
#include <WiFiUdp.h>


// Load configuration
#include "config.h"

// Variables
boolean statusBin = false;
boolean statusMaintenance = false;

// Include libraries
#include "blink.h"
#include "mqtt.h"
#include "pins.h"
#include "wifi.h"
#include "ota.h"


void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println(F("\n      ✰✰✰  Coffee-Bin booting ✰✰✰      "));
  Serial.println("\n\
            __  __            _     _       \n\
           / _|/ _|          | |   (_)      \n\
  ___ ___ | |_| |_ ___  ___  | |__  _ _ __  \n\
 / __/ _ \\|  _|  _/ _ \\/ _ \\ | '_ \\| | '_ \\ \n\
| (_| (_) | | | ||  __/  __/ | |_) | | | | |\n\
 \\___\\___/|_| |_| \\___|\\___| |_.__/|_|_| |_|\n\    
  ");
  
  setupPins();
  setupWifi();
  setupOta();
  setupMqtt();
}

void loop() {
  loopMqtt();
  loopOta();
  loopPin();
}
