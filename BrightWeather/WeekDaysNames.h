#pragma once

#include <string>
#include <vector>

#include "BrightWeatherExceptions.h"

class WeekDaysNames
{
	static std::string weekDays[7];

public:
	static std::vector<std::string> GetDaysFromTo(int start, int end);
};