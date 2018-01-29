#include "../lib/relai.h"
#include <Arduino.h>

void onoff(int pin,bool oro){
  pinMode(pin,OUTPUT);
  if (oro == 1) {
  digitalWrite(pin,LOW);
  }
  else if (oro == 0) {
    digitalWrite(pin,HIGH);
  }
};

void pumpit(int pin, int timems) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(timems);
  digitalWrite(pin,HIGH);
}

void pumpitvolume(int pin, int volumeml) {

  int timeml=(0.9090909091*volumeml); //TODO take care of timeml right rounded

  pinMode(pin, OUTPUT);
  digitalWrite(pin,LOW);
  delay(timeml);
  digitalWrite(pin,HIGH);
}
