#include <ctime>

#include "WeekDaysUtility.h"

std::vector<std::string> WeekDaysUtility::GetNext7DaysWeekNames()
{
	std::time_t now = time(NULL);
	struct std::tm* nowOut = new std::tm();
	if (localtime_s(nowOut, &now) != errno)
	{
		throw std::exception("localtime_s call failure");
	}
	return WeekDaysNames::GetDaysFromTo(nowOut->tm_wday, nowOut->tm_wday+6);
}
