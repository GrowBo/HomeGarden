
#include <vector>
#include "ArduinoJson.h"
#include <Arduino.h>

struct LEDTimings
{
	String LED_StartDateTime;
	String LED_EndDateTime;
};

struct NutritionDefs
{
	String N_StartDate;
	String N_EndDate;
	float EC_Value;
	float N_Accuracy;
};

struct PHDefs
{
	String PhStartDate;
	String PhEndDate;
	float Ph_Value;
	float ph_Accuracy;
};


struct AirVent_2
{
	String Vent_StartDateTime;
	String Vent_EndDateTime;
	int VentSpeed;
};

class ParsedData
{
	//Use the individual variables for testing only, to be removed
	public: String LED_StartDateTime;
	public: String LED_EndDateTime;

	public: String N_StartDate;
	public: String N_EndDate;

	public: float N_ECValue;
	public: float N_Accuracy;

	public: String PH_StartDate;
	public: String PH_EndDate;

	public: float PH_Value;
	public: float PH_Accuracy;

	public: String Vent1_Speed;

	public: String Vent2_StartDateTime;
	public: String Vent2_EndDateTime;

	public: String Vent2_Speed;

	public:	std::vector<LEDTimings> LedTimes;
	public: std::vector<NutritionDefs> N_Defs;
	public: std::vector<PHDefs> P_Defs;
	public:	int AirVent_1;
	public: std::vector<AirVent_2> AirVent_2;


	public:	int getVentSpeed(String Speed)
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
		};
};


ParsedData PopulateData( char JsonInput[])
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
						\"AirflowVent_1\":[{\"Speed\": \"Medium\"}],\
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
			AirVent_2 Vent2;
			Vent2.Vent_StartDateTime = root["AirflowVent_2"][i]["StartDateTime"].as<String>();
			Vent2.Vent_EndDateTime = root["AirflowVent_2"][i]["EndDateTime"].as<String>();
			int VentSpeed = Data.getVentSpeed(root["AirflowVent_2"][i]["Speed"].as<String>());
			Vent2.VentSpeed = VentSpeed;
			Data.AirVent_2.push_back(Vent2);
	}

	//Use the individual references for testing only, to be removed
	Data.LED_StartDateTime = root["LED"]["StartDateTime"].as<String>();
	Data.LED_EndDateTime = root["LED"]["EndDateTime"].as<String>();

	Data.N_StartDate = root["Nutritions"]["StartDate"].as<String>();
	Data.N_EndDate = root["Nutritions"]["EndDate"].as<String>();

	Data.N_ECValue = root["Nutritions"]["ECValue"];
	Data.N_Accuracy = root["Nutritions"]["Accuracy"];

	Data.PH_StartDate = root["PH"]["StartDate"].as<String>();
	Data.PH_EndDate = root["PH"]["EndDate"].as<String>();

	Data.PH_Value = root["PH"]["PHValue"];
	Data.PH_Accuracy = root["PH"]["Accuracy"];

	Data.Vent1_Speed = root["AirflowVent_1"]["Speed"].as<String>();

	Data.Vent2_StartDateTime = root["AirflowVent_2"]["StartDateTime"].as<String>();
	Data.Vent2_EndDateTime = root["AirflowVent_2"]["EndDateTime"].as<String>();

	Data.Vent2_Speed = root["AirflowVent_2"]["Speed"].as<String>();
	return Data;
}
