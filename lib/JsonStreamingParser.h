#ifndef JSONSTREAMINGPARSER_H
#define JSONSTREAMINGPARSER_H
#include <vector>
#include "ArduinoJson.h"
#include <Arduino.h>

class ParsedData
{
	public:
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

			struct AVent_2
			{
				String Vent_StartDateTime;
				String Vent_EndDateTime;
				int VentSpeed;
			};

      std::vector<LEDTimings> LedTimes;
	    std::vector<NutritionDefs> N_Defs;
	    std::vector<PHDefs> P_Defs;
	    int AirVent_1;
	    std::vector<AVent_2> AirVent_2;

			public:
					int getVentSpeed(String Speed);
					ParsedData PopulateDataRoot();
};

#endif
