const char* wifiSsid              = "xxx";
const char* wifiPassword          = "xxx";
const char* wifiHostname          = "coffee-bin";

const int   pinLedTop             = BUILTIN_LED;
const int   pinLedBottom          = 2;
const int   pinLedExtern          = D5;
const int   pinFlash              = 0;
const int   pinBin                = 4;
const int   pinMaintenance        = 5;

const char* otaHostName           = "coffee-bin";
const char* otaPassword           = "passwrd";
const int   otaPort               = 8266;

#define     MQTT_SERVER           "io.adafruit.com"
#define     MQTT_SERVERPORT       1883 // use 8883 for SSL
#define     MQTT_USERNAME         "xxx"
#define     MQTT_KEY              "xxx"
#define     MQTT_FEED_BIN         "/feeds/coffee-bin.bin"
#define     MQTT_FEED_MAINTENANCE "/feeds/coffee-bin.maintenance"
