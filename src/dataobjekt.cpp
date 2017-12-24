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

//GET

float Dataobjekt::getec(){
  return ec;
}

float Dataobjekt::getph(){
  return ph;
}

float Dataobjekt::gettemp(){
  return temp;
}

float Dataobjekt::getphlow(){
  return phlow;
}

float Dataobjekt::getphhigh(){
  return phhigh;
}

float Dataobjekt::geteclow(){
  return eclow;
}

float Dataobjekt::getechigh(){
  return echigh;
}

//SET

void Dataobjekt::setec(float ec){
    this->ec = ec;
}

void Dataobjekt::setph(float ph){
  this->ph = ph;
}

void Dataobjekt::settemp(float temp){
  this->temp = temp;
}

void Dataobjekt::setphlow(float phlow){
  this->phlow = phlow;
}

void Dataobjekt::setphhigh(float phhigh){
  this->phhigh = phhigh;
}

void Dataobjekt::seteclow(float eclow){
  this->eclow = eclow;
}

void Dataobjekt::setechigh(float echigh){
  this->echigh = echigh;
}
