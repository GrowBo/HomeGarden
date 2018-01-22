//all the #include here:
#include <Arduino.h>
#include "../lib/pythonparser.h"
#include "../lib/debug.h"
#include "../lib/dataobjekt.h"

//all the #define here:
#define PinEcSensor 4
#define PinPhSensor 5
#define PinTempSensor 6
#define PinLuefterA 11
// #define PinX 0
// #define PinX 0
// #define PinX 0

//TIMERMAIPULATION



//Var GLOBAL
Dataobjekt allmadata(PinEcSensor,PinPhSensor,PinTempSensor, PinLuefterA);

void setup() {
    Serial.begin(9600);

    //PIN 11&12
    TCCR1B = (TCCR1B & 0b11111000) | 0x01; //sets the frequence to 31372.55 http://playground.arduino.cc/Main/TimerPWMCheatsheet
    // put your setup code here, to run once:
    // pinMode();
    pinMode(13,OUTPUT);
    pinMode(PinLuefterA,OUTPUT);

}

void loop() {
  //will produce a chart, where we can see the strukture ...
  //get all the data...

  //json parser should fill all the allmadata.phhigh and allmadata.phlow etc.


    allmadata.updateph();
    allmadata.updateec();
    allmadata.updatetemp();
    allmadata.updateluefterA(); //only when changes occur

    checkForDataCorrectness(allmadata); //just a failsave for debugging. Shoud see if there are values we can work with.

//IF CHANGES FOR VENT 1
/*
allmadata.setluefterApower(input); //input needs to be 0-255 function checks it tho.
allmadata.updateluefterA();
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
