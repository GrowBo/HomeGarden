// #ifndef JSONSTREAMINGPARSER_H
// #define JSONSTREAMINGPARSER_H
// #include <vector>
// #include "ArduinoJson.h"
// #include <Arduino.h>
//
// class ParsedData
// {
// 	public:
// 			struct LEDTimings
// 			{
// 				String LED_StartDateTime;
// 				String LED_EndDateTime;
// 			};
//
// 			struct NutritionDefs
// 			{
// 				String N_StartDate;
// 				String N_EndDate;
// 				float EC_HighValue;
// 				float EC_LowValue;
// 			};
//
// 			struct PHDefs
// 			{
// 				String PhStartDate;
// 				String PhEndDate;
// 				float Ph_HighValue;
// 				float Ph_LowValue;
// 			};
//
// 			struct AVent_2
// 			{
// 				String Vent_StartDateTime;
// 				String Vent_EndDateTime;
// 				int VentSpeed;
// 			};
//
//       std::vector<LEDTimings> LedTimes;
// 	    std::vector<NutritionDefs> N_Defs;
// 	    std::vector<PHDefs> P_Defs;
// 			int vent1_speed;
// 	    std::vector<AVent_2> AirVent_2;
//
// 			public:
//
// 					ParsedData PopulateDataRoot();
//
// 					float PhHigh_FromExtern(ParsedData v);
// 					float PhLow_FromExtern(ParsedData v);
// 			    float PhOrg_FromExtern(ParsedData v);
//
// 			    float EcOrg_FromExtern(ParsedData v);
// 			    float EcHigh_FromExtern(ParsedData v);
// 			    float EcLow_FromExtern(ParsedData v);
//
// 			    bool LEDState_FromExtern(ParsedData v);
// 			    int  Vent1_ValueFromExtern(ParsedData v);
// 			    int  Vent2_valueFromExtern(ParsedData v);
// 					bool IsdateIncluded(String StartDateString, String EndDateString, bool CompareDateOnly);
//
// };
//
// #endif
