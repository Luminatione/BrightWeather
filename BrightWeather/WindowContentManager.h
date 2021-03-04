#pragma once

#include <string>
#include <Windows.h>
#include <vector>

#include "BrightWeatherExceptions.h"
#include "WeekDaysUtility.h"

class WindowContentManager//TODO: implement
{
	const int daySelectionSize = 7;
	HWND mainWindow;
	std::vector<HWND> daySelectionControls = std::vector<HWND>(daySelectionSize);
public:
	explicit WindowContentManager(HWND mainWindowHandle) :mainWindow(mainWindowHandle)
	{
	}
	void CreateDaySelectionControls()
	{
		if (!mainWindow)
		{
			throw ClassNotInitializedException();
		}
		std::vector<std::string> weekDays = WeekDaysUtility::GetNext7DaysWeekNames();
		for (int i = 0; i < daySelectionSize; i++)
		{
			std::wstring temp(weekDays[i].begin(), weekDays[i].end());//this is safe
			daySelectionControls[i] = CreateWindow(L"BUTTON", temp.c_str(),
			                                       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10 + 110 * i,
			                                       10, 100, 50, mainWindow, NULL,
			                                       (HINSTANCE)GetWindowLongPtr(mainWindow, GWLP_HINSTANCE), NULL);
		}
	}
};