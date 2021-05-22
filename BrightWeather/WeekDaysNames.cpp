#include "WeekDaysNames.h"

std::string WeekDaysNames::weekDays[7]{ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

std::vector<std::string> WeekDaysNames::GetDaysFromTo(int start, int end)
{
	if (start < 0 || end < 0 || start > end)
	{
		throw InvalidArgumentException();
	}
	auto result = std::vector<std::string>(end - start + 1);
	for (int i = 0, j = start; j <= end; i++, j++)
	{
		result[i] = weekDays[j % 7];
	}
	return result;
}
