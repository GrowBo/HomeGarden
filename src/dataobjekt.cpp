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

float Dataobjekt::checkph(){
  return ph_check(PinPhSensor);
}

float Dataobjekt::checkec(){
  return ec_check(PinEcSensor);
}

void Dataobjekt::checktemp(){
  this->temp = temp_check(PinTempSensor);
}
