#include "Arduino.h"
#include "../lib/ph.h"

//WHAT TO include for Serial stuff?
Serial.println("Ready");    //Test the serial monitor
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

float ph_messure(int pin) {
    for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
    {
      buf[i]=analogRead(pin);
      delay(10);
    }
    for(int i=0;i<9;i++)        //sort the analog from small to large
    {
      for(int j=i+1;j<10;j++)
      {
        if(buf[i]>buf[j])
        {
          temp=buf[i];
          buf[i]=buf[j];
          buf[j]=temp;
        }
      }
    }
    avgValue=0;
    for(int i=2;i<8;i++)                      //take the average value of 6 center sample
      avgValue+=buf[i];
    float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
    phValue=3.5*phValue;                      //convert the millivolt into pH value
    Serial.print("    pH:");
    Serial.print(phValue,2);                  //Zwei nachkommastellen
    Serial.println(" ");

    return phValue;
}

//Code we could use: Problem: how to continuesly check the ph while controlling the box?
/*
# This sample codes is for testing the pH meter V1.0.
 # Editor : YouYou
 # Date   : 2013.10.12
 # Ver    : 0.1
 # Product: pH meter
 # SKU    : SEN0161
*/
