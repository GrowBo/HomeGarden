#include "../lib/dataobjekt.h"
#include "../lib/ph.h"
#include "../lib/ec.h"
#include "../lib/temp.h"
#include <Arduino.h>

Dataobjekt::Dataobjekt(int PinEcSensor, int PinPhSensor, int PinTempSensor, int PinLuefterA){
  this->PinEcSensor = PinEcSensor;
  this->PinPhSensor = PinPhSensor;
  this->PinTempSensor = PinTempSensor;
  this->PinLuefterA = PinLuefterA;
  luefterApower = 150;
}

Dataobjekt::~Dataobjekt(){
  Serial.print("Dataobjekt wurde geloescht");
}

void Dataobjekt::updateph(){
  this->ph = ph_messure(PinPhSensor);
}

void Dataobjekt::updateec(){
  //this->ec = ec_messure(PinEcSensor);
}

void Dataobjekt::updatetemp(){
  this->temp = temp_messure(PinTempSensor);
}

void Dataobjekt::updateluefterA(){
  analogWrite(PinLuefterA, luefterApower);
};

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

int Dataobjekt::getluefterApower(){
  return luefterApower;
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

void Dataobjekt::setluefterApower(int luefterApower){
  if (luefterApower >= 0 && luefterApower <= 255){
    this->luefterApower = luefterApower;
  }
  else {
    //Error report "PWM Value not 0 - 255"
  }
}
