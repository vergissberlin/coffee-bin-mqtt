load('api_config.js');
load('api_grove.js');
load('api_gpio.js');
load('api_sys.js');
load('api_timer.js');
load('api_mqtt.js');

// Functions
function send(feed, msg, qos) {
	let topic = Cfg.get('mqtt.user') + '/feeds/' + feed;
	let ok = MQTT.pub(topic, JSON.stringify(msg||1), qos||2);
	MQTT.setEventHandler(function(){}, null);
}

// let PIN = ffi('int get_led_gpio_pin()')();
// GPIO.set_mode(PIN, GPIO.MODE_OUTPUT);
/*
Grove.Button.attach(5, function() {
    print('Sensor: ', Grove.LightSensor.get(0));
    GPIO.toggle(PIN);
});
*/
// GPIO listener
GPIO.set_button_handler(0, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function(x) {
    Timer.set(200 , true , function() {
        let sensorValue = Grove.LightSensor.get(0);
        print('Sensor: ', sensorValue);
        if(sensorValue < 200) {
            send('piball.goal_gray', sensorValue);
        }
      }, null);  
  }, true);
  
 
