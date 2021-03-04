#pragma once
#define __STDC_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__
#include <ctime>
#include <string>
#include <exception>

#include "WeekDaysNames.h"

class WeekDaysUtility
{
public:
	static std::vector<std::string> GetNext7DaysWeekNames()
	{
		std::time_t now = time(NULL);
		struct std::tm* nowOut = new std::tm();
		if(localtime_s(nowOut, &now) != errno)
		{
			throw std::exception("localtime_s call failure");
		}
		return WeekDaysNames::GetDaysFromTo(nowOut->tm_wday, nowOut->tm_wday + 6);
	}
	
};