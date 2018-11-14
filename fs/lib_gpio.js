load('api_gpio.js');
load('api_sys.js');

// Configure LED
let led =  16;
let ledRed = 2;
GPIO.set_mode(led, GPIO.MODE_OUTPUT);
GPIO.set_mode(ledRed, GPIO.MODE_OUTPUT);

// Buttons
let buttonFlash = 0;
let buttonBin = 5;
GPIO.set_mode(buttonBin, GPIO.MODE_INPUT);
GPIO.write(led, 0);

// Status
let status = 0;

// Flash button
GPIO.set_button_handler(buttonFlash, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function (x) {
    print('Button press, pin:', x);
    if (status === 0) {
        status = 1;
        GPIO.write(led, 1);
        send('coffeebin.maintenance', 0);
      } else {
        status = 0;
        GPIO.write(led, 0);
        send('coffeebin.maintenance', 1);
      }
  }, true);

// Bin
GPIO.set_button_handler(buttonBin, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 20, function (x) {
    print('Button press, pin:', x);
    if (GPIO.read(ledRed) === 0) {
        GPIO.write(ledRed, 1);
        send('coffeebin.bin', 1);
    } else {
        GPIO.write(ledRed, 0);
        send('coffeebin.bin', 0);
    }
}, true);
