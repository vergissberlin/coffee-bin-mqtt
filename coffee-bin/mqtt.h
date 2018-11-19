/*
  Coffee bin

  MQTT bin project for coffee-bin https://coffee-bin-mqtt.readthedocs.io/

  Created 11 September 2018
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/coffee-bin-mqtt
*/

uint32_t x=0;

/*
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// *********** Global State (you don't need to change this!) ******************
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
// Adafruit_MQTT_Client mqtt(&client, mqttServer, mqttPort, mqttUser, mqttKey);

// ***************************** Feeds ***************************************

//Adafruit_MQTT_Publish bin = Adafruit_MQTT_Publish(&mqtt, mqttUser mqttFeedBin);
//Adafruit_MQTT_Subscribe maintenance = Adafruit_MQTT_Subscribe(&mqtt, mqttUser mqttFeedMaintenance);
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, mqttServer, mqttPort, mqttUser, mqttKey);
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, mqttUser "/feeds/photocell");
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, mqttUser "/feeds/onoff");





// *************************** Sketch Code ************************************

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

uint32_t x=0;

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print(F("Connecting to MQTT... "));

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println(F("Retrying MQTT connection in 5 seconds..."));
       mqtt.disconnect();
       delay(5000);
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println(F("MQTT Connected!"));
}
*/

/*

*/

// ************************* Adafruit.io Setup *********************************

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "vergissberlin"
#define AIO_KEY         "ad755b7b9d994e4abe62bc0ace181023"

// ************ Global State (you don't need to change this!) ******************

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// ****************************** Feeds *****************************************

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");

// *************************** Sketch Code **************************************

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();


// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

void setupMqtt() {
  Serial.println(F("\n▶ MQTT"));
  mqtt.subscribe(&onoffbutton);
}

void loopMqtt() {
   MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
    }
  }

  // Now we can publish stuff!
  Serial.print(F("\nSending photocell val "));
  Serial.print(x);
  Serial.print("...");
  if (! photocell.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}
