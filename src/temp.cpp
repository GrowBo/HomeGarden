#include "../lib/temp.h"
// First we include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

float temp_messure(int pin){
  // start serial port
  // Start up the library

  OneWire oneWire(ONE_WIRE_BUS);
  sensors.begin();
  DallasTemperature sensors(&oneWire);

 Serial.print(" Requesting temperatures...");
 sensors.requestTemperatures(); // Send the command to get temperature readings
 Serial.println("DONE");
/********************************************************************/
 Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"?
 return sensors.getTempCByIndex(0);
}
