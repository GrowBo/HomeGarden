#include "../lib/temp.h"
// First we include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float temp_messure(int pin){
  // start serial port
  // Start up the library
  sensors.begin();

 Serial.print(" Requesting temperatures...");
 sensors.requestTemperatures(); // Send the command to get temperature readings
 Serial.println("DONE");
/********************************************************************/
 Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"?
 return sensors.getTempCByIndex(0);
}
