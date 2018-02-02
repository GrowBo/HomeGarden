//all the #include here:
#include <vector>
#include "ArduinoJson.h"
#include <Arduino.h>
#include "../lib/pythonparser.h"
#include "../lib/debug.h"
#include "../lib/dataobjekt.h"
#include "../lib/relai.h"
#include "../lib/JsonStreamingParser.h"


//all the #define here:
#define PinEcSensor 4
#define PinPhSensor 5
#define PinTempSensor 6
#define PinLuefterA 11

#define Relai1 51   //NAME IT!
#define Relai2 XX   //NAME IT!
#define Relai3 XX   //NAME IT!
#define Relai4 XX   //NAME IT!

#define Relai5 XX   //NAME IT!
#define Relai6 XX   //NAME IT!
#define Relai7 XX   //NAME IT!
#define Relai8 XX   //NAME IT!

// #define PinX 0
// #define PinX 0
Dataobjekt allmadata(PinEcSensor,PinPhSensor,PinTempSensor, PinLuefterA);
ParsedData ParsedJsonData;
void setup() {
    Serial.begin(9600);

    //PIN 11&12
    TCCR1B = (TCCR1B & 0b11111000) | 0x01; //sets the frequence to 31372.55 http://playground.arduino.cc/Main/TimerPWMCheatsheet
    // put your setup code here, to run once:
    // pinMode();
    pinMode(13,OUTPUT);
    pinMode(PinLuefterA,OUTPUT);
    ParsedJsonData = ParsedJsonData.PopulateDataRoot();

    float PhHighValue = ParsedJsonData.PhHigh_FromExtern(ParsedJsonData);
    allmadata.setphhigh(PhHighValue);

    float PhLowValue = ParsedJsonData.PhLow_FromExtern(ParsedJsonData);
    allmadata.setphlow(PhLowValue);

    float phValue = ParsedJsonData.PhOrg_FromExtern(ParsedJsonData);
    allmadata.setph(phValue);

    float EcHighValue = ParsedJsonData.EcHigh_FromExtern(ParsedJsonData);
    allmadata.setechigh(EcHighValue);

    float EcLowValue = ParsedJsonData.EcLow_FromExtern(ParsedJsonData);
    allmadata.seteclow(EcLowValue);

    float EcValue = ParsedJsonData.EcOrg_FromExtern(ParsedJsonData);
    allmadata.setec(EcValue);

    int Vent2Speed = ParsedJsonData.Vent2_valueFromExtern(ParsedJsonData);
    allmadata.setluefterApower(Vent2Speed);

    //allmadata.jsetphlow(ParsedJsonData.P_Defs);
    //Read the json string
}

void loop() {
  //will produce a chart, where we can see the strukture ...
  //get all the data...

  //json parser should fill all the allmadata.phhigh and allmadata.phlow etc.


    allmadata.updateph();
    Serial.print("pH wurde geupdated.\t pH ist ");
    Serial.println(allmadata.getph());

    allmadata.updateec();
    Serial.print("EC wurde geupdated.\t EC ist ");
    Serial.println(allmadata.getec());

    allmadata.updatetemp();
    Serial.print("Temp wurde geupdated.\t Temp ist ");
    Serial.println(allmadata.gettemp());

    allmadata.updateluefterA(); //only when changes occur
    Serial.print("LuefterA wurde geupdated.\t LuefterA ist ");
    Serial.println(allmadata.getluefterApower());

    checkForDataCorrectness(allmadata); //just a failsave for debugging. Shoud see if there are values we can work with.

//IF CHANGES FOR VENT 1
/*
allmadata.setluefterApower(input); //input needs to be 0-255 function checks it tho.
allmadata.updateluefterA();
*/

//IF PUMP OR AN OTHER RELAY NEEDS TO SWITCH ON
/*
pumpitvolume(pin,ml) //pin as defined top so Relai1 - Relai8; ml in ml :P;
pumpit(pin,time) //pin as defined top so Relai1 - Relai8; Time in ms;
onoff(pin,on or off) // pin as defined top to Relai1- Relai8; on or off as 1 or 0;
*/

//PH
    if (allmadata.getph() > allmadata.getphlow() && allmadata.getph() < allmadata.getphhigh()) {
      //send all okay ph
    }
    else{
      //ph_adjust
    }

//EC
    if (allmadata.getec() > allmadata.geteclow() && allmadata.getec() < allmadata.getechigh()){
      //send all okay ec
    }
    else{
      //ec_adjust
    }
//Data
    //all the checks should log their actions!
  //  sendDataToPi(); //Display the Data to the User aka. send it to the pi and the pi should display it to the user.

  //  updates_check(); // checks for updates? not sure with this one @Abhishek maybe you can code this section.
}
