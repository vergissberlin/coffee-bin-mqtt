load('api_config.js');
load('api_gpio.js');
load('api_mqtt.js');
load('api_timer.js');
load("api_esp8266.js");

// ... or set io.adafruit mqtt settings and set feed name here:
let feedSensor = 'coffeebin.sensor';
let feedLed = 'coffeebin.led';

// HELLEL WORLS

// Some millisecond settings. adjust to your needs
let millisToTurnOff = 60000;

// Configure LED
let led = 2;
GPIO.set_mode(led, GPIO.MODE_OUTPUT);

// GPIO 0 is typically a 'Flash' buttonmos
let button = 0;
let pin = 14;

//***********************************************

// Functions
function send(feed, msg, qos) {
  let topic = Cfg.get('mqtt.user') + '/feeds/' + feed;
  let ok = MQTT.pub(topic, JSON.stringify(msg || 1), qos || 1);
  if (ok) print('sent mqtt for ' + feed)
  else print('failed mqtt for' + feed);
  MQTT.setEventHandler(function () { }, null);
}

// Deep sleep
/*
Timer.set(millisToTurnOff , false , function() {
  print("deep sleep");
  ESP8266.deepSleep(0);
}, null);
*/


// GPIO listener
GPIO.set_button_handler(button, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function (x) {
  print('Button press, pin:', x);
  send(feedSensor);
}, true);
GPIO.set_button_handler(pin, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function (x) {
  print('Sensor active, pin', x);
  send(feedSensor);
}, true);

// MQTT subsriber
MQTT.sub(Cfg.get('mqtt.user') + '/feeds/' + feedSensor, function (conn, topic, msg) {
  print('Topic:', topic, 'message:', msg);
}, null);
MQTT.sub(Cfg.get('mqtt.user') + '/feeds/' + feedLed, function (conn, topic, msg) {
  print('Topic:', topic, 'message:', msg);
  if (JSON.parse(msg) === 0) {
    GPIO.write(led, 1);
  } else {
    GPIO.write(led, 0);
  }
}, null);


// MQTT on booting
MQTT.setEventHandler(function (conn, ev, edata) {
  if (ev === MQTT.EV_CONNACK) send('coffeebin.status')
  if (ev === MQTT.EV_CLOSE) send('coffeebin.status', 0);
}, null);

// Info
print('Flash button is configured on GPIO pin ', pin);
print('Press the flash button now!');
