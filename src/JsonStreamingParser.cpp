#include "../lib/Time/Time.h"
#include "../lib/Time/TimeLib.h"
#include "../lib/StandardCplusplus/vector"
#include "../lib/ArduinoJson/ArduinoJson.h"
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
						\"LED\":[{\"StartDateTime\": \"2018.02.10 05:45\",\"EndDateTime\": \"2018.02.10 05:45 18:45\"}],\
						\"Nutritions\":[{\"StartDate\": \"2018.01.10\",\"EndDate\": \"2018.02.15\",\"ECHighValue\": 7.0,\"ECLowValue\": 6.0}],\
						\"PH\":[{\"StartDate\": \"2018.03.10\",\"EndDate\": \"2018.02.15\",\"PHHighValue\": 6.0,\"PHLowValue\": 2.0}],\
						\"AirflowVent_1\":[{\"Speed\": 255}],\
						\"AirflowVent_2\":[{\"StartDateTime\": \"2018.02.10 05:45\",\"EndDateTime\": \"2018.02.10 18:45\",\"Speed\":255}]\
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
	Serial.print("NutritionsArraySize:");
	Serial.println(NutritionsArraySize);

 	for (int i = 0; i < NutritionsArraySize; i++) // Uses SizeType instead of size_t
	{
			NutritionDefs ND;
			ND.N_StartDate = root["Nutritions"][i]["StartDate"].as<String>();
			ND.N_EndDate = root["Nutritions"][i]["EndDate"].as<String>();
			ND.EC_HighValue = root["Nutritions"][i]["ECHighValue"];
			ND.EC_LowValue = root["Nutritions"][i]["ECLowValue"];
			Data.N_Defs.push_back(ND);
	}

	int PHArraySize = root["PH"].size();

	Serial.print("PHArraySize:");
	Serial.println(PHArraySize);

	for (int i = 0; i < PHArraySize; i++) // Uses SizeType instead of size_t
	{
			PHDefs PDef;
			PDef.PhStartDate = root["PH"][i]  ["StartDate"].as<String>();
			PDef.PhEndDate = root["PH"][i]["EndDate"].as<String>();
			PDef.Ph_HighValue = root["PH"][i]["PHHighValue"];
			PDef.Ph_LowValue = root["PH"][i]["PHLowValue"];
			Data.P_Defs.push_back(PDef);
	}

	int Vent1_Speed = root["AirflowVent_1"][0]["Speed"];
	Serial.print("Vent1_Speed:");
	Serial.println(Vent1_Speed);
	Data.vent1_speed = Vent1_Speed;

  int Vent2_ArraySize = root["AirflowVent_2"].size();
	Serial.print("Vent2_ArraySize:");
	Serial.println(Vent2_ArraySize);
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
				if(IsdateIncluded(StartDate, EndDate, true))
				{
						PhHighValue = it->Ph_HighValue;
						Serial.print("PH HIGH VALUE IS: ");
						Serial.println(PhHighValue);
				}
				else
				{
						PhHighValue = -1;
						Serial.print("PH HIGH IS NOT SET");
				}
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
			if(IsdateIncluded(StartDate, EndDate, true))
			{
					PhLowValue = it->Ph_LowValue;
					Serial.print(PhLowValue);
					Serial.print("PH LOW VALUE IS: ");
					Serial.println(PhLowValue);
			}
			else
				PhLowValue = -1;
	}
	return PhLowValue;
}

float ParsedData::PhOrg_FromExtern(ParsedData P)
{
	/*
		This is not required for now
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
	*/
}

float ParsedData::EcOrg_FromExtern(ParsedData P)
{
	/*
		float EC_Value = 0;
		std::vector<NutritionDefs>::iterator it;

		for( it = P.N_Defs.begin( ); it != P.N_Defs.end( ); ++it)
		{
				String StartDate, EndDate;
				StartDate = it->N_StartDate;
				EndDate = it->N_EndDate;
				//if()
				EC_Value = it->EC_Value;
				Serial.print(EC_Value);
		}
	return EC_Value;
	*/
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
			if(IsdateIncluded(StartDate, EndDate, true))
			{
					EC_HighValue = it->EC_HighValue;
					Serial.print(EC_HighValue);
					Serial.print("EC HIGH VALUE IS: ");
					Serial.println(EC_HighValue);
			}
			else
			{
				EC_HighValue = -1;
				Serial.print("EC HIGH VALUE IS NOT SET");
			}
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
			if(IsdateIncluded(StartDate, EndDate, true))
			{
					EC_LowValue = it->EC_LowValue;
					Serial.print(EC_LowValue);
					Serial.print("EC LOW VALUE IS: ");
					Serial.println(EC_LowValue);
			}
			else
			{
				EC_LowValue = -1;
				Serial.print("EC LOW VALUE IS NOT SET");
			}
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
			if(IsdateIncluded(StartDate, EndDate, false))
			{
					State = true;
					Serial.print(State);
					Serial.print("LED STATE IS ON.");
			}
			else
					Serial.print("LED STATE IS OFF");
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
			if(IsdateIncluded(StartDate, EndDate, false))
			{
				Serial.print(Speed);
			}
			else
				Speed = 0;
	}
	return Speed;
}

bool ParsedData::IsdateIncluded(String StartDateString, String EndDateString, bool CompareDateOnly)
{
		const char *StartDate = StartDateString.c_str();
		const char *EndDate = EndDateString.c_str();
		tmElements_t s_tmSet;
		tmElements_t e_tmSet;
		int s_year = 0, s_month = 0, s_day = 0, s_hour = 0, s_min = 0;
		int e_year = 0, e_month = 0, e_day = 0, e_hour = 0, e_min = 0;
		if(!CompareDateOnly)
		{
			sscanf(StartDate, "%4d.%2d.%2d %2d:%2d", &s_year, &s_month, &s_day, &s_hour, &s_min);
			sscanf(EndDate, "%4d.%2d.%2d %2d:%2d", &e_year, &e_month, &e_day, &e_hour, &e_min);
			s_tmSet.Year = s_year - 1970;
			s_tmSet.Month = s_month;
			s_tmSet.Day = s_day;
		}
		else
		{
			sscanf(StartDate, "%4d.%2d.%2d", &s_year, &s_month, &s_day);
			sscanf(EndDate, "%4d.%2d.%2d", &e_year, &e_month, &e_day);
			e_tmSet.Year = e_year - 1970;
			e_tmSet.Month = e_month;
			e_tmSet.Day = e_day;
			e_tmSet.Hour = e_hour;
			e_tmSet.Minute = e_min;
		}
	  time_t StartDateTime = makeTime(s_tmSet);
		time_t EndDateTime = makeTime(e_tmSet);
    time_t nw = now();
		if(nw <= EndDateTime && nw >= StartDateTime)
		{
			return 1;
		}
		else
			return 0;
}
