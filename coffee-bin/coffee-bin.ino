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
#include <ButtonDebounce.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Load configuration
#include "config.h"

// Include librarie
//#include "mqtt.h"
#include "ota.h"

// Buttons
ButtonDebounce button(0, 5000);

void setupWifi() {
  /*
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    digitalWrite(led2, HIGH);
    delay(20);  
    digitalWrite(led1, LOW); 
    ESP.restart();
  }
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setupPins() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  button.setCallback(buttonChanged);
}

void buttonChanged(int state){
  Serial.println("Changed: " + String(state));
}

void setup() {
  Serial.begin(9600);
  Serial.println("Booting");
  setupWifi();
  setupOta();
  setupPins();
  //setupMqtt();
}

void loop() {
  ArduinoOTA.handle();
  button.update();

  // MQTT
  /*
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &bin) {
      Serial.print(F("Got: "));
      Serial.println((char *)bin.lastread);
    }
  }

  // Now we can publish stuff!
  Serial.print(F("\nSending maintenance val "));
  Serial.print("...");
  if (! maintenance.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  */

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
