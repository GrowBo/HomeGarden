//all the #include here:
#include <vector>
#include "ArduinoJson.h"
#include <Arduino.h>
#include "../lib/pythonparser.h"
#include "../lib/debug.h"
#include "../lib/dataobjekt.h"
#include "../lib/relai.h"
#include "../lib/JsonStreamingParser.h"
#include <TimeLib.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <DS3231.h>
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

//TIMERMAIPULATION


DS3231 clock;
RTCDateTime dt;
//Var GLOBAL
Dataobjekt allmadata(PinEcSensor,PinPhSensor,PinTempSensor, PinLuefterA);
ParsedData ParsedJsonData;


void setup() {
    Serial.begin(9600);
    Wire.begin();

    /* This is alternative to the current time function.
    clock.begin();
    clock.setDateTime(2014, 4, 13, 19, 21, 00);
    dt = clock.getDateTime();

    Serial.print("Long number format:          ");
    Serial.println(clock.dateFormat("d-m-Y H:i:s", dt));
  */

    //PIN 11&12
    TCCR1B = (TCCR1B & 0b11111000) | 0x01; //sets the frequence to 31372.55 http://playground.arduino.cc/Main/TimerPWMCheatsheet
    // put your setup code here, to run once:
    // pinMode();
    pinMode(13,OUTPUT);
    pinMode(PinLuefterA,OUTPUT);

    //TIMER SETTINGS AND INTEGRITY CHECK
    tmElements_t tm;
    if (RTC.read(tm))
    {
      // setTime(hr,min,sec,day,month,yr);
      setTime(00,15,12,06,02,2018);
      time_t Current_time = now();
      Serial.print("SETTING TIME:");
      Serial.println(Current_time);
      Serial.println(".........Current time set on RTC..............");
    }
    else
    {
        if (RTC.chipPresent())
        {
            Serial.println("The DS3231 is stopped.");
        }
      else
      {
          Serial.println("DS3231 read error!");
          Serial.println();
      }
    }


    //Read the json string
    ParsedJsonData = ParsedJsonData.PopulateDataRoot();
}

void loop() {
  //will produce a chart, where we can see the strukture ...
  //get all the data...

    allmadata.updateph();
    allmadata.updateec();
    allmadata.updatetemp();
    allmadata.updateluefterA(); //only when changes occur

  //checkForDataCorrectness(allmadata); //just a failsave for debugging. Shoud see if there are values we can work with.

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
  Serial.print("CHECKING THE DATE LIMITS");
  //CHECK IF THE CURRENT DATE TIME IS WITHIN THE RANGE
    float PhHighValue = ParsedJsonData.PhHigh_FromExtern(ParsedJsonData);
    allmadata.setphhigh(PhHighValue);

    float PhLowValue = ParsedJsonData.PhLow_FromExtern(ParsedJsonData);
    allmadata.setphlow(PhLowValue);

    //float phValue = ParsedJsonData.PhOrg_FromExtern(ParsedJsonData);
    //allmadata.setph(phValue);

    float EcHighValue = ParsedJsonData.EcHigh_FromExtern(ParsedJsonData);
    allmadata.setechigh(EcHighValue);

    float EcLowValue = ParsedJsonData.EcLow_FromExtern(ParsedJsonData);
    allmadata.seteclow(EcLowValue);

    //float EcValue = ParsedJsonData.EcOrg_FromExtern(ParsedJsonData);
    //allmadata.setec(EcValue);

    int Vent2Speed = ParsedJsonData.Vent2_valueFromExtern(ParsedJsonData);
    allmadata.setluefterApower(Vent2Speed);

    //PH
    if (allmadata.getph() > allmadata.getphlow() && allmadata.getph() < allmadata.getphhigh())
    {
      Serial.print("PH is fine. No need for adjustments.");
    }
    else
    {
      //ph_adjust
    }

    //EC
    if (allmadata.getec() > allmadata.geteclow() && allmadata.getec() < allmadata.getechigh())
    {
      Serial.print("EC is fine. No need for adjustments.");
    }
    else{
      //ec_adjust
    }
//Data
    //all the checks should log their actions!
  //  sendDataToPi(); //Display the Data to the User aka. send it to the pi and the pi should display it to the user.

  //  updates_check(); // checks for updates? not sure with this one @Abhishek maybe you can code this section.
}
