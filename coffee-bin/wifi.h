/*
  Coffee bin

  MQTT bin project for coffee-bin https://coffee-bin-mqtt.readthedocs.io/

  Created 11 September 2018
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/coffee-bin-mqtt
*/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
// WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

void setupWifi() {
  Serial.println(F("\n▶ WiFi"));
  Serial.print(F("Connecting to \""));
  Serial.print(wifiSsid);
  Serial.print(F("\"\t"));
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSsid, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(led2, HIGH);
    delay(20);  
    digitalWrite(led1, LOW); 
    Serial.print(F("."));
  }
  Serial.println();

  Serial.println(F("Status\t\t\tWiFi connected!"));
  Serial.print(F("IP address\t\t")); 
  Serial.println(WiFi.localIP());
}
