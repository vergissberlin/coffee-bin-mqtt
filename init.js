// Load Mongoose OS API
load('api_gpio.js');

// Configure LED
let led = 15;// ffi('int get_led_gpio_pin()')();  // Get built-in LED GPIO pin
GPIO.set_mode(led, GPIO.MODE_OUTPUT);

let pin = 0;   // GPIO 0 is typically a 'Flash' button
GPIO.set_button_handler(pin, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function(x) {
  let value = GPIO.toggle(led);
  print('Button press, pin:', x, 'LED pin:', led, ' Value: ', value);
}, true);

GPIO.set_button_handler(14, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function(x) {
  let value = GPIO.toggle(led);
  print('Button press, pin:', x, 'LED pin:', led, ' Value: ', value);
}, true);

print('Flash button is configured on GPIO pin ', pin);
print('Press the flash button now!');
