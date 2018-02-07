#include <time.h>
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <vector>
#include "ArduinoJson.h"
#include <Arduino.h>
#include "../lib/JsonStreamingParser.h"

ParsedData ParsedData::PopulateDataRoot()
{
	ParsedData Data;
	DynamicJsonBuffer jsonBuffer;
	//PARSER JSON HERE
	Serial.println("Starting ...");
	String input =
			"{\
						\"LED\":[{\"StartDateTime\": \"12.12.2017 05:45:00\",\"EndDateTime\": \"12.12.2018T18:45:00\"}],\
						\"Nutritions\":[{\"StartDate\": \"12:12:2017\",\"EndDate\": \"12:12:2018\",\"ECValue\": 7.89,\"Accuracy\": 0.5}],\
						\"PH\":[{\"StartDate\": \"12:12:2017\",\"EndDate\": \"12:12:2018\",\"PHValue\": 7.89,\"Accuracy\": 0.5}],\
						\"AirflowVent_1\":[{\"Speed\": 255}],\
						\"AirflowVent_2\":[{\"StartDateTime\": \"12.12.2017T05:45\",\"EndDateTime\": \"12.12.2018T18:45\",\"Speed\":255}]\
					}";
	JsonObject& root = jsonBuffer.parseObject(input);
	int LEDArraySize = root["LED"].size();

	Serial.println("LEDArraySize:");
	Serial.print(LEDArraySize);

	for (int i = 0; i < LEDArraySize; i++) // Uses SizeType instead of size_t
	{
			LEDTimings LT;
			LT.LED_StartDateTime = root["LED"][i]["StartDateTime"].as<String>();
			LT.LED_EndDateTime = root["LED"][i]["EndDateTime"].as<String>();
			Data.LedTimes.push_back(LT);
	}

	int NutritionsArraySize = root["Nutritions"].size();
	Serial.println("NutritionsArraySize:");
	Serial.print(NutritionsArraySize);

 	for (int i = 0; i < NutritionsArraySize; i++) // Uses SizeType instead of size_t
	{
			NutritionDefs ND;
			ND.N_StartDate = root["Nutritions"][i]["StartDate"].as<String>();
			ND.N_EndDate = root["Nutritions"][i]["EndDate"].as<String>();
			ND.EC_Value = root["Nutritions"][i]["ECValue"];
			ND.N_Accuracy = root["Nutritions"][i]["Accuracy"];
			Data.N_Defs.push_back(ND);
	}

	int PHArraySize = root["PH"].size();

	Serial.println("PHArraySize:");
	Serial.print(PHArraySize);

	for (int i = 0; i < PHArraySize; i++) // Uses SizeType instead of size_t
	{
			PHDefs PDef;
			PDef.PhStartDate = root["PH"][i]  ["StartDate"].as<String>();
			PDef.PhEndDate = root["PH"][i]["EndDate"].as<String>();
			PDef.Ph_Value = root["PH"][i]["PHValue"];
			PDef.ph_Accuracy = root["PH"][i]["Accuracy"];
			Data.P_Defs.push_back(PDef);
	}

	int Vent1_Speed = root["AirflowVent_1"][0]["Speed"];
	Serial.println("Vent1_Speed:");
	Serial.print(Vent1_Speed);
	Data.vent1_speed = Vent1_Speed;

  int Vent2_ArraySize = root["AirflowVent_2"].size();
	Serial.println("Vent2_ArraySize:");
	Serial.print(Vent2_ArraySize);
	for (int i = 0; i < Vent2_ArraySize; i++) // Uses SizeType instead of size_t
	{
			AVent_2 Vent2;
			Vent2.Vent_StartDateTime = root["AirflowVent_2"][i]["StartDateTime"].as<String>();
			Vent2.Vent_EndDateTime = root["AirflowVent_2"][i]["EndDateTime"].as<String>();
			int VentSpeed = root["AirflowVent_2"][i]["Speed"];
			Vent2.VentSpeed = VentSpeed;
			Data.AirVent_2.push_back(Vent2);
	}
	return Data;
}


float ParsedData::PhHigh_FromExtern(ParsedData P)
{
		float PhHighValue = 0;
	 	std::vector<PHDefs>::iterator it;

		for( it = P.P_Defs.begin( ); it != P.P_Defs.end( ); ++it)
		{
				String StartDate, EndDate;
				StartDate = it->PhStartDate;
				EndDate = it->PhEndDate;
				//if()
				PhHighValue = it->Ph_Value + it->ph_Accuracy;
				Serial.print("PH HIGH VALUE IS:::::::::::::");
				Serial.println(PhHighValue);
		}
		return PhHighValue;
}

float ParsedData::PhLow_FromExtern(ParsedData P)
{
	float PhLowValue = 0;
	std::vector<PHDefs>::iterator it;

	for( it = P.P_Defs.begin( ); it != P.P_Defs.end( ); ++it)
	{
			String StartDate, EndDate;
			StartDate = it->PhStartDate;
			EndDate = it->PhEndDate;
			//if()
			PhLowValue = it->Ph_Value - it->ph_Accuracy;
			Serial.print(PhLowValue);
	}
	return PhLowValue;
}

float ParsedData::PhOrg_FromExtern(ParsedData P)
{
		float PhValue = 0;
		std::vector<PHDefs>::iterator it;

		for( it = P.P_Defs.begin( ); it != P.P_Defs.end( ); ++it)
		{
				String StartDate, EndDate;
				StartDate = it->PhStartDate;
				EndDate = it->PhEndDate;
				//if()
				PhValue = it->Ph_Value;
				Serial.print(PhValue);
		}
		return PhValue;
}
float ParsedData::EcOrg_FromExtern(ParsedData P)
{
	float EC_Value = 0;
	std::vector<NutritionDefs>::iterator it;

	for( it = P.N_Defs.begin( ); it != P.N_Defs.end( ); ++it)
	{
			String StartDate, EndDate;
			StartDate = it->N_StartDate;
			EndDate = it->N_EndDate;
			//if()
			EC_Value = it->EC_Value + it->N_Accuracy;
			Serial.print(EC_Value);
	}
	return EC_Value;
}
float ParsedData::EcHigh_FromExtern(ParsedData P)
{
	float EC_HighValue = 0;
	std::vector<NutritionDefs>::iterator it;

	for( it = P.N_Defs.begin( ); it != P.N_Defs.end( ); ++it)
	{
			String StartDate, EndDate;
			StartDate = it->N_StartDate;
			EndDate = it->N_EndDate;
			//if()
			EC_HighValue = it->EC_Value + it->N_Accuracy;
			Serial.print(EC_HighValue);
	}
	return EC_HighValue;
}
float ParsedData::EcLow_FromExtern(ParsedData P)
{
	float EC_LowValue = 0;
	std::vector<NutritionDefs>::iterator it;

	for( it = P.N_Defs.begin( ); it != P.N_Defs.end( ); ++it)
	{
			String StartDate, EndDate;
			StartDate = it->N_StartDate;
			EndDate = it->N_EndDate;
			//if()
			EC_LowValue = it->EC_Value + it->N_Accuracy;
			Serial.print(EC_LowValue);
	}
	return EC_LowValue;
}
bool ParsedData::LEDState_FromExtern(ParsedData P)
{
	bool State = false;
	std::vector<LEDTimings>::iterator it;

	for( it = P.LedTimes.begin( ); it != P.LedTimes.end( ); ++it)
	{
			String StartDate, EndDate;
			StartDate = it->LED_StartDateTime;
			EndDate = it->LED_EndDateTime;
			//if()
			State = true;
			Serial.print(State);
	}
	return State;
}

int  ParsedData::Vent1_ValueFromExtern(ParsedData P)
{
   return P.vent1_speed;
}

int  ParsedData::Vent2_valueFromExtern(ParsedData P)
{
	int Speed = 0;
	std::vector<AVent_2>::iterator it;

	for( it = P.AirVent_2.begin( ); it != P.AirVent_2.end( ); ++it)
	{
			String StartDate, EndDate;
			StartDate = it->Vent_StartDateTime;
			EndDate = it->Vent_EndDateTime;
			Speed = it->VentSpeed;
			//if()
			Serial.print(Speed);
	}
	return Speed;
}

bool ParsedData::GetConvertedTime(String DateTimeString)
{
		const char T[] = "2017.11.23 22:05";
		const char *tempStr = DateTimeString.c_str();
		int year = 0, month = 0, day = 0, hour = 0, min = 0;
		sscanf(tempStr, "%4d.%2d.%2d %2d:%2d", &year, &month, &day, &hour, &min);

		tmElements_t tmSet;
		tmSet.Year = year - 1970;
		tmSet.Month = month;
		tmSet.Day = day;
		tmSet.Hour = hour;
		tmSet.Minute = min;
	  time_t Converted_time = makeTime(tmSet);
		Serial.print("time set to: ");
		Serial.print(Converted_time);

    time_t nw = now();
		if(nw == Converted_time)
		{
			return 1;
		}
		else
			return 0;
}
