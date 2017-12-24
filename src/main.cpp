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
    allmadata.checkph();
    allmadata.checkec();
    allmadata.checktemp();

    checkForDataCorrectness(); //just a failsave for debugging. Shoud see if there are values we can work with.

    ph_check(); //Should check if the pH is Balanced if it is just skip. If not run ph_adjust();
    temp_check(); //does nothing for now, but could be addet in the future
    ec_check(); // Should check if the EC is correct. If not run ec_adjust();

    //all the checks should log their actions!
    sendDataToPi(); //Display the Data to the User aka. send it to the pi and the pi should display it to the user.

    updates_check(); // checks for updates? not sure with this one @Abhishek maybe you can code this section.
}
