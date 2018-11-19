/*
  Coffee bin

  MQTT bin project for coffee-bin https://coffee-bin-mqtt.readthedocs.io/

  Created 11 September 2018
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/coffee-bin-mqtt
*/

// Buttons
ButtonDebounce button(0, 5000);

void buttonChanged(int state){
  Serial.println("Changed: " + String(state));
}


void setupPins() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  button.setCallback(buttonChanged);
}

void loopPin() {
  button.update();
}
