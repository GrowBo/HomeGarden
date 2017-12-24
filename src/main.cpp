//all the #include here:
#include <Arduino.h>
#include "../lib/ph.h"
#include "../lib/ec.h"
#include "../lib/temp.h"
#include "../lib/pythonparser.h"
#include "../lib/debug.h"

//all the #define here:
// #define PinX 0
// #define PinX 0
// #define PinX 0
// #define PinX 0

void setup() {
    // put your setup code here, to run once:
    // pinMode();

}

void loop() {
    getTemprature_Data(); //Returnes the temprature. Would say in a float or sth. Celsius.
    getPH_Data(); //returnes average ph value over a time of 30 min or so. float
    getEC_Data(); //returnes current Conductivity (maybe also an average Value). also float?
    //All the data should be in one Object?

    checkForDataCorrectness(); //just a failsave for debugging. Shoud see if there are values we can work with.

    ph_check(); //Should check if the pH is Balanced if it is just skip. If not run ph_adjust();
    temp_check(); //does nothing for now, but could be addet in the future
    ec_check(); // Should check if the EC is correct. If not run ec_adjust();

    //all the checks should log their actions!
    sendDataToPi(); //Display the Data to the User aka. send it to the pi and the pi should display it to the user.

    updates_check(); // checks for updates? not sure with this one @Abhishek maybe you can code this section.
}
