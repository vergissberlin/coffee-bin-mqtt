load('api_config.js');
load('api_gpio.js');
load('api_mqtt.js');
load('api_timer.js');
load('api_esp8266.js');

// Custom functions
load('mqtt.js');

// ... or set io.adafruit mqtt settings and set feed name here:
let feedSensor = Cfg.get('app.feed.sensor');
let feedLed = Cfg.get('app.feed.led');

// Configure LED
let led =  Cfg.get('app.pin.led');
GPIO.set_mode(led, GPIO.MODE_OUTPUT);

// GPIO 0 is typically a 'Flash' buttonmos
let button =  Cfg.get('app.pin.button');
let pin = Cfg.get('app.pin.pin');

//***********************************************

// Deep sleep
/*
Timer.set(Cfg.get('app.config.sleep') , false , function() {
  print("deep sleep");
  ESP8266.deepSleep(0);
}, null);
*/

// GPIO listener
GPIO.set_button_handler(button, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function (x) {
  print('QQQButton press, pin:', x);
  send(feedSensor);
}, true);
GPIO.set_button_handler(pin, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function (x) {
  print('QQQSensor active, pin', x);
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
