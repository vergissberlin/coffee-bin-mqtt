/*
  Coffee bin

  MQTT bin project for coffee-bin https://coffee-bin-mqtt.readthedocs.io/

  Created 11 September 2018
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/coffee-bin-mqtt
*/

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// ************ Global State (you don't need to change this!) ******************

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);

// ****************************** Feeds *****************************************
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish bin = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME MQTT_FEED_BIN);
Adafruit_MQTT_Publish mqttMaintenancePublish = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME MQTT_FEED_MAINTENANCE);
Adafruit_MQTT_Subscribe maintenance = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME MQTT_FEED_MAINTENANCE);

// *************************** Sketch Code **************************************

void MQTT_connect();

void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.println("Connecting to MQTT\t\"" + String(MQTT_SERVER) + "\"");
  Serial.print(F("Status\t\t\t"));
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.print(F("Retrying MQTT connection in 5 seconds … "));
       mqtt.disconnect();
       delay(5000); // wait 5 seconds
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println(F("MQTT Connected!"));
}

int mqttInvert(int value) {
  if(value == 1) return 0;
  if(value == 0) return 1;
}

void mqttPinBin(int state) {
  state=mqttInvert(state);

  // MQTT message
  if (! bin.publish(state)) {
    blinkError(pinLedBottom, "MQTT bin failed.",true);
  } else {
    Serial.println("\tBin:\t\t" + String(state));
  }  
  if(state == 1) {
    statusBin = true;
  } else {
    statusBin = false;
  }
}

void mqttPinMaintenance(int state) {
  state=mqttInvert(state);
  if (! mqttMaintenancePublish.publish(state)) {
    blinkError(pinLedBottom,"MQTT bin failed.", true);
  } else {
    Serial.println("\tMaintenance:\t" + String(state));
  }
  if(state == 1) {
    statusMaintenance = true;
  } else {
    statusMaintenance = false;
  }
}

void setupMqtt() {
  Serial.println(F("\n▶ MQTT"));
}

void loopMqtt() {
  MQTT_connect();
}
