/*
  Coffee bin

  MQTT bin project for coffee-bin https://coffee-bin-mqtt.readthedocs.io/

  Created 11 September 2018
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/coffee-bin-mqtt
*/

// Buttons & sensors
ButtonDebounce buttonFlash(pinFlash, 5000);
ButtonDebounce buttonBin(pinBin, 5000);
ButtonDebounce buttonMaintenance(pinMaintenance, 5000);

void buttonChanged(int state){
  Serial.println("Changed: " + String(state));
}

void setupPins() {
  pinMode(pinLedTop, OUTPUT);
  pinMode(pinLedBottom, OUTPUT);
  buttonBin.setCallback(buttonChanged);
  buttonFlash.setCallback(buttonChanged);
  buttonMaintenance.setCallback(buttonChanged);
}

void loopPin() {
  buttonBin.update();
  buttonFlash.update();
  buttonMaintenance.update();
}
