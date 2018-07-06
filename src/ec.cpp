#include <OneWire.h>
#include <DallasTemperature.h>
#include "../lib/ec.h"




//************************* User Defined Variables ********************************************************//


//##################################################################################
//-----------  Do not Replace R1 with a resistor lower than 300 ohms    ------------
//##################################################################################

DallasTemperature* sensorspointer = NULL;// Pass our oneWire reference to Dallas Temperature.

int R1= 1000;
int Ra=25; //Resistance of powering Pins
int ECPin= A0;
int ECGround=A1;
int ECPower =A4;


//*********** Converting to ppm [Learn to use EC it is much better**************//
// Hana      [USA]        PPMconverion:  0.5
// Eutech    [EU]          PPMconversion:  0.64
//Tranchen  [Australia]  PPMconversion:  0.7
// Why didnt anyone standardise this?


float PPMconversion=0.7;


//*************Compensating for temperature ************************************//
//The value below will change depending on what chemical solution we are measuring
//0.019 is generaly considered the standard for plant nutrients [google "Temperature compensation EC" for more info
float TemperatureCoef = 0.019; //this changes depending on what chemical we are measuring




//********************** Cell Constant For Ec Measurements *********************//
//Mine was around 2.9 with plugs being a standard size they should all be around the same
//But If you get bad readings you can use the calibration script and fluid to get a better estimate for K
float K=2.88;




//************ Temp Probe Related *********************************************//
const int TempProbePossitive =8;  //Temp Probe power connected to pin 9
const int TempProbeNegative=9;    //Temp Probe Negative connected to pin 8




//***************************** END Of Recomended User Inputs *****************************************************************//




float Temperature=10;
float EC=0;
float EC25 =0;
int ppm =0;


float raw= 0;
float Vin= 5;
float Vdrop= 0;
float Rc= 0;
float buffer=0;




//*********************************Setup - runs Once and sets pins etc ******************************************************//

//******************************************* End of Setup **********************************************************************//




//************************************* Main Loop - Runs Forever ***************************************************************//
//Moved Heavy Work To subroutines so you can call them from main loop without cluttering the main loop
void ec_lop(OneWire* onewpoint)
{

    pinMode(TempProbeNegative , OUTPUT ); //seting ground pin as output for tmp probe
    digitalWrite(TempProbeNegative , LOW );//Seting it to ground so it can sink current
    pinMode(TempProbePossitive , OUTPUT );//ditto but for positive
    digitalWrite(TempProbePossitive , HIGH );
    pinMode(ECPin,INPUT);
    pinMode(ECPower,OUTPUT);//Setting pin for sourcing current
    pinMode(ECGround,OUTPUT);//setting pin for sinking current
    digitalWrite(ECGround,LOW);//We can leave the ground connected permanantly

    delay(100);// gives sensor time to settle
    sensorspointer->begin();
    delay(100);
    //** Adding Digital Pin Resistance to [25 ohm] to the static Resistor *********//
    // Consule Read-Me for Why, or just accept it as true
    R1=(R1+Ra);// Taking into acount Powering Pin Resitance

    Serial.println("ElCheapo Arduino EC-PPM measurments");
    Serial.println("By: Michael Ratcliffe  Mike@MichaelRatcliffe.com");
    Serial.println("Free software: you can redistribute it and/or modify it under GNU ");
    Serial.println("");
    Serial.println("Make sure Probe and Temp Sensor are in Solution and solution is well mixed");
    Serial.println("");
    Serial.println("Measurments at 5's Second intervals [Dont read Ec morre than once every 5 seconds]:");
        //Calls Code to Go into GetEC() Loop [Below Main Loop] dont call this more that 1/5 hhz [once every five seconds] or you will polarise the water
  // Cals Print routine [below main loop]
//************************************** End Of Main Loop **********************************************************************//
}



//************ This Loop Is called From Main Loop************************//
float ec_messure(OneWire* onewpoint){
if (sensorspointer != NULL){
  sensorspointer = new DallasTemperature(onewpoint);
}
else{exit(1);}
ec_lop(onewpoint);
//*********Reading Temperature Of Solution *******************//
sensorspointer->requestTemperatures();// Send the command to get temperatures
Temperature=sensorspointer->getTempCByIndex(0); //Stores Value in Variable




//************Estimates Resistance of Liquid ****************//
digitalWrite(ECPower,HIGH);
raw= analogRead(ECPin);
raw= analogRead(ECPin);// This is not a mistake, First reading will be low beause if charged a capacitor
digitalWrite(ECPower,LOW);




//***************** Converts to EC **************************//
Vdrop= (Vin*raw)/1024.0;
Rc=(Vdrop*R1)/(Vin-Vdrop);
Rc=Rc-Ra; //acounting for Digital Pin Resitance
EC = 1000/(Rc*K);


//*************Compensating For Temperaure********************//
EC25  =  EC/ (1+ TemperatureCoef*(Temperature-25.0));
ppm=(EC25)*(PPMconversion*1000);

PrintReadings();
return 1;

}
//************************** End OF EC Function ***************************//




//***This Loop Is called From Main Loop- Prints to serial usefull info ***//
void PrintReadings(){
Serial.print("Rc: ");
Serial.print(Rc);
Serial.print(" EC: ");
Serial.print(EC25);
Serial.print(" Simens  ");
Serial.print(ppm);
Serial.print(" ppm  ");
Serial.print(Temperature);
Serial.println(" *C ");


/*
********** Usued for Debugging ************
Serial.print("Vdrop: ");
Serial.println(Vdrop);
Serial.print("Rc: ");
Serial.println(Rc);
Serial.print(EC);
Serial.println("Siemens");
********** end of Debugging Prints *********
*/
};
