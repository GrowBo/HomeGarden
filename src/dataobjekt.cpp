#include "../lib/dataobjekt.h"
#include "../lib/ph.h"
#include "../lib/ec.h"
#include "../lib/temp.h"
#include <Arduino.h>

Dataobjekt::Dataobjekt(int PinEcSensor, int PinPhSensor, int PinTempSensor){
  this->PinEcSensor = PinEcSensor;
  this->PinPhSensor = PinPhSensor;
  this->PinTempSensor = PinTempSensor;
}

Dataobjekt::~Dataobjekt(){
  Serial.print("Dataobjekt wurde geloescht");
}

void Dataobjekt::updateph(){
  this->ph = ph_messure(PinPhSensor);
}

void Dataobjekt::updateec(){
  this->ec = ec_messure(PinEcSensor);
}

void Dataobjekt::updatetemp(){
  this->temp = temp_messure(PinTempSensor);
}

float Dataobjekt::getec(){
  return ec;
}

float Dataobjekt::getph(){
  return ph;
}

float Dataobjekt::gettemp(){
  return temp;
}
