//all the #include here:
#include <Arduino.h>
#include "../lib/pythonparser.h"
#include "../lib/debug.h"
#include "../lib/dataobjekt.h"

//all the #define here:
#define PinEcSensor 4
#define PinPhSensor 5
#define PinTempSensor 6
// #define PinX 0
// #define PinX 0
// #define PinX 0

//Var
Dataobjekt allmadata(PinEcSensor,PinPhSensor,PinTempSensor);

void setup() {
    // put your setup code here, to run once:
    // pinMode();


}

void loop() {
  //will produce a chart, where we can see the strukture ...
  //get all the data...
    allmadata.updateph();
    allmadata.updateec();
    allmadata.updatetemp();

    checkForDataCorrectness(); //just a failsave for debugging. Shoud see if there are values we can work with.

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
    sendDataToPi(); //Display the Data to the User aka. send it to the pi and the pi should display it to the user.

    updates_check(); // checks for updates? not sure with this one @Abhishek maybe you can code this section.
}
