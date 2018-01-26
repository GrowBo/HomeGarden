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
						\"LED\":[{\"StartDateTime\": \"12.12.2017T05:45\",\"EndDateTime\": \"12.12.2018T18:45\"}],\
						\"Nutritions\":[{\"StartDate\": \"12:12:2017\",\"EndDate\": \"12:12:2018\",\"ECValue\": 7.89,\"Accuracy\": 0.5}],\
						\"PH\":[{\"StartDate\": \"12:12:2017\",\"EndDate\": \"12:12:2018\",\"PHValue\": 7.89,\"Accuracy\": 0.5}],\
						\"AirflowVent_1\":[{\"Speed\": 255}],
						\"AirflowVent_2\":[{\"StartDateTime\": \"12.12.2017T05:45\",\"EndDateTime\": \"12.12.2018T18:45\",\"Speed\":\"Medium\"}]\
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

	int Vent1_Speed = Data.getVentSpeed(root["AirflowVent_1"][0]["Speed"].as<String>());
	Serial.println("Vent1_Speed:");
	Serial.print(Vent1_Speed);

  int Vent2_ArraySize = root["AirflowVent_2"].size();
	Serial.println("Vent2_ArraySize:");
	Serial.print(Vent2_ArraySize);
	for (int i = 0; i < Vent2_ArraySize; i++) // Uses SizeType instead of size_t
	{
			AVent_2 Vent2;
			Vent2.Vent_StartDateTime = root["AirflowVent_2"][i]["StartDateTime"].as<String>();
			Vent2.Vent_EndDateTime = root["AirflowVent_2"][i]["EndDateTime"].as<String>();
			int VentSpeed = Data.getVentSpeed(root["AirflowVent_2"][i]["Speed"].as<String>());
			Vent2.VentSpeed = VentSpeed;
			Data.AirVent_2.push_back(Vent2);
	}
	return Data;
}


int getVentSpeed(String Speed)
{
		if (Speed = "Off")
		{
			return 0;
		}
		else if (Speed = "Low")
		{
			return 1;
		}
		else if (Speed = "Medium")
		{
			return 2;
		}
		else if (Speed = "High")
		{
			return 3;
		}
}
