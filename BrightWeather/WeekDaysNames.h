#pragma once

#include <string>
#include <vector>
#include "BrightWeatherExceptions.h"
class WeekDaysNames//TODO add tests
{
	static std::string weekDays[7];
	static std::string weekDaysShorts[7];

public:
	static std::vector<std::string> GetDaysFromTo(int start, int end)
	{
		if (start <= 0 || end <= 0 || start > end)
		{
			throw InvalidArgumentException();
		}
		auto result = std::vector<std::string>( end - start + 1);
		for (int i = 0, j = start; j <= end; i++, j++)
		{
			result[i] = weekDays[(j - 1) % 7];
		}
		return result;
	}
};
std::string WeekDaysNames::weekDays[7]{ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
std::string WeekDaysNames::weekDaysShorts[7]{ "Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat.", "Sun." };