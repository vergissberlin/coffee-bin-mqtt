/*
  Coffee bin

  MQTT bin project for coffee-bin https://coffee-bin-mqtt.readthedocs.io/

  Created 11 September 2018
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/coffee-bin-mqtt
*/

#include <ButtonDebounce.h>

// Buttons & sensors
ButtonDebounce buttonFlash(pinFlash, 5000);
ButtonDebounce buttonBin(pinBin, 5000);
ButtonDebounce buttonMaintenance(pinMaintenance, 5000);

// LEDs
TimedBlink ledTop(pinLedTop);
TimedBlink ledBottom(pinLedBottom);
TimedBlink ledExtern(pinLedExtern);

void setupPins() {
  pinMode(pinLedTop,      OUTPUT);
  pinMode(pinLedBottom,   OUTPUT);
  pinMode(pinLedExtern,   OUTPUT);
  pinMode(pinLedExtern,   OUTPUT);
  pinMode(pinBin,         INPUT_PULLUP);
  pinMode(pinMaintenance, INPUT_PULLUP);

  const int pinFlash       = 0;
  const int pinBin         = 4;
  const int pinMaintenance = 5;

  digitalWrite(pinLedTop,     HIGH);
  digitalWrite(pinLedBottom,  HIGH);
  digitalWrite(pinLedExtern,  LOW);

  buttonBin.setCallback(mqttPinBin);
  buttonFlash.setCallback(mqttPinMaintenance);
  buttonMaintenance.setCallback(mqttPinMaintenance);

  // Heartbeat LED
  ledBottom.blink(3000, 200);
  ledTop.blink(3100, 100);
}

void loopPin() {
  buttonBin.update();
  buttonFlash.update();
  buttonMaintenance.update();

  if(statusBin == true) {
    digitalWrite(pinLedExtern, !digitalRead(pinLedExtern));
    delay(1000);
  } else {
    digitalWrite(pinLedExtern, LOW);
  }
  
  ledTop.blink();
  ledBottom.blink();
  ledExtern.blink();
}
