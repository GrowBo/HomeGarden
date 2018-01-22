#include "../lib/relai.h"
#include <Arduino.h>

void onoff(int pin,bool oro){
  pinMode(pin,OUTPUT);
  if (oro == 1) {
  digitalWrite(pin,HIGH);
  }
  else if (oro == 0) {
    digitalWrite(pin,LOW);
  }
};

void pumpit(int pin, int timems) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(timems);
  digitalWrite(pin,LOW);
}

void pumpitvolume(int pin, int volumeml) {

  int timeml=timepervolume*volumeml; //TODO timepervolume needs to be set; AND take care of timeml right rounded

  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(timeml);
  digitalWrite(pin,LOW);
}
