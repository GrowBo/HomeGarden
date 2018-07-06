#include "../lib/temp.h"
#include <OneWire.h>
#include <DallasTemperature.h>

extern DallasTemperature* sensorspointer;// Pass our oneWire reference to Dallas Temperature.

// First we include the libraries
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
float temp_messure(OneWire* onewpoint){
  // start serial port
  // Start up the library
  if (sensorspointer != NULL){
    sensorspointer->begin();
    Serial.print(" Requesting temperatures...");
    sensorspointer->requestTemperatures(); // Send the command to get temperature readings
    Serial.println("DONE");
    /********************************************************************/
    Serial.println(sensorspointer->getTempCByIndex(0)); // Why "byIndex"?
    return sensorspointer->getTempCByIndex(0);
  }
  else{exit(1);}
 
}
