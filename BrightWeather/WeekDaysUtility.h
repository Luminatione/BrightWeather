#pragma once

#include <string>

#include "WeekDaysNames.h"

class WeekDaysUtility
{
public:
	WeekDaysUtility() = default;
	static std::vector<std::string> GetNext7DaysWeekNames();
};