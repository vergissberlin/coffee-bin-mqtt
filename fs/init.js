load('api_config.js');
load('api_gpio.js');
load('api_mqtt.js');
load('api_timer.js');
load("api_esp8266.js");


// ...or set io.adafruit mqtt settings and set feed name here:
let feedName = 'coffeebin.sensor';

// Some millisecond settings. adjust to your needs
let millisToTurnOff = 60000000;
//***********************************************

// Deep sleep
/*
Timer.set(millisToTurnOff , false , function() {
  print("deep sleep");
  ESP8266.deepSleep(0);
}, null);
*/

// Configure LED
let led = 2;
GPIO.set_mode(led, GPIO.MODE_OUTPUT);

// GPIO 0 is typically a 'Flash' buttonmos
let button = 0;  
let pin = 14;  

// Functions
function blink() {
  GPIO.write(led,0);
  print('on');
  Timer.set(1000, false, function() {
    print('off');
    GPIO.write(led,1);
  }, null);
}

function send(feed, msg, qos) {
	let topic = Cfg.get('mqtt.user') + '/feeds/' + feed;
	let ok = MQTT.pub(topic, JSON.stringify(msg||1), qos||1);
	if(ok) print('sent mqtt for ' + feed)
	else print('failed mqtt for' + feed);
	MQTT.setEventHandler(function(){}, null);
}

// GPIO listener
GPIO.set_button_handler(button, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function(x) {
  print('Button press, pin:', x);
  send(feedName);
}, true);
GPIO.set_button_handler(pin, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function(x) {
  print('Sensor active, pin', x);
  send(feedName);
}, true);

// MQTT subsriber
MQTT.sub(Cfg.get('mqtt.user') + '/feeds/' + feedName, function(conn, topic, msg) {
     print('Topic:', topic, 'message:', msg);
     blink();
 }, null);

// MQTT on booting
MQTT.setEventHandler(function(conn, ev, edata) {
	if (ev === MQTT.EV_CONNACK) {
    send('coffeebin.status');
	}
}, null);

// Info
print('Flash button is configured on GPIO pin ', pin);
print('Press the flash button now!');
