#include "../lib/LED.h"
#include <Arduino.h>

void SetLEDState(int pin,bool state){
  pinMode(pin,OUTPUT);
  if (state == 1) {
  digitalWrite(pin,HIGH);
  }
  else if (state == 0) {
    digitalWrite(pin,LOW);
  }
};
