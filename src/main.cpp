//all the #include here:
#include <Arduino.h>
#include "../lib/pythonparser.h"
#include "../lib/debug.h"
#include "../lib/dataobjekt.h"
#include "../lib/relai.h"
//all the #define here:
#define PinEcSensor
#define PinPhSensor 2
#define PinTempSensor
#define PinLuefterA 11


#define Relai1 47   //PUMPE1
#define Relai2 49   //PUMPE2
#define Relai3 51   //PUMPE3
#define Relai4 53   //PUMPE4

#define Relai5 46   //NAME IT!
#define Relai6 48   //NAME IT!
#define Relai7 50   //NAME IT!
#define Relai8 52   //NAME IT!

// #define PinX 0
// #define PinX 0
Dataobjekt allmadata(PinEcSensor,PinPhSensor,PinTempSensor, PinLuefterA);

void setup() {
    Serial.begin(9600);

    //PIN 11&12
    TCCR1B = (TCCR1B & 0b11111000) | 0x01; //sets the frequence to 31372.55 http://playground.arduino.cc/Main/TimerPWMCheatsheet
    // put your setup code here, to run once:
    // pinMode();
    pinMode(13,OUTPUT);
    pinMode(PinLuefterA,OUTPUT);

<<<<<<< HEAD
    pinMode(Relai1,OUTPUT);
    pinMode(Relai2,OUTPUT);
    pinMode(Relai3,OUTPUT);
    pinMode(Relai4,OUTPUT);

    pinMode(Relai5,OUTPUT);
    pinMode(Relai6,OUTPUT);
    pinMode(Relai7,OUTPUT);
    pinMode(Relai8,OUTPUT);
=======

>>>>>>> fe74d073d784cf0544835c5ba28f7b71acc7edd4
}

void loop() {
  //will produce a chart, where we can see the strukture ...
  //get all the data...


  //checkForDataCorrectness(allmadata); //just a failsave for debugging. Shoud see if there are values we can work with.




    }
      //ph_adjust
    }

    }
    else{
      //ec_adjust
    }
//Data
    //all the checks should log their actions!
  //  sendDataToPi(); //Display the Data to the User aka. send it to the pi and the pi should display it to the user.

  //  updates_check(); // checks for updates? not sure with this one @Abhishek maybe you can code this section.
}
