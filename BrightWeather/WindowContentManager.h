#pragma once

#include <string>
#include <Windows.h>
#include <vector>

#include "BrightWeatherExceptions.h"
#include "WeekDaysUtility.h"
#include "Utility.h"
#include "WeatherInfoGetter.h"

#define BUTTON_PARAM_START 1000
#define REFRESH_BUTTON 999

class WindowContentManager
{
	int currentSelectedDay = 0;

	const int daySelectionSize = 7;
	const int weekDayControlsWidth = 90;
	const int weekDayControlsHeight = 35;
	const int weekDayControlsXOffset = 10;
	const int weekDayControlsMarginTop = 10;
	const int weekDayControlsMarginLeft = 10;

	std::vector<std::string> weekDays;

	HWND mainWindow;
	std::vector<HWND> daySelectionControls = std::vector<HWND>(daySelectionSize);
	std::vector<WeatherInfoGetter::WeatherData> weatherData;

	WeatherInfoGetter weatherInfoGetter;

	struct Caption
	{
		HWND handle;
		int x, y;
		int height, width;
		std::string defaultStr;
		
		Caption() = default;
		
		Caption(HWND parent, std::string& caption, int x, int y, int width, int height, std::string defaultStr = "", int fontSize = 18) : x(x), y(y), height(height), width(width), defaultStr(defaultStr)
		{
			handle = CreateWindow(L"STATIC", Utility::AsciiStringToWstring(caption).c_str(), WS_CHILD | WS_VISIBLE, x, y, width, height, parent, nullptr, nullptr, nullptr);
			HFONT font = CreateFontA(fontSize, 0, 0, 0, 0, 0, 0, 0, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
			SendMessageA(handle, WM_SETFONT, (WPARAM)font, TRUE);
		}
		
		void ChangeText(std::string& newText, bool onlyUpdate = false)
		{
			std::string temp = (onlyUpdate ? defaultStr : "") + newText;
			SetWindowTextW(handle, Utility::AsciiStringToWstring(temp).c_str());
		}
	};

	HWND refreshButton;

	Caption currentWeekDayCaption;
	Caption temperatureCaption;
	Caption pressureCaption;

public:
	WindowContentManager& operator=(const WindowContentManager& a)
	{
		this->daySelectionControls = a.daySelectionControls;
		this->mainWindow = a.mainWindow;
		return *this;
	}

	WindowContentManager(HWND mainWindowHandle) : mainWindow(mainWindowHandle)
	{
	}

	WindowContentManager() = default;

	void CreateDaySelectionControls()
	{
		if (!mainWindow)
		{
			throw ClassNotInitializedException();
		}
		weekDays = WeekDaysUtility::GetNext7DaysWeekNames();
		for (int i = 0; i < daySelectionSize; i++)
		{
			daySelectionControls[i] = CreateWindow(L"BUTTON", Utility::AsciiStringToWstring(weekDays[i]).c_str(),
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, weekDayControlsMarginLeft + (weekDayControlsXOffset + weekDayControlsWidth) * i,
				weekDayControlsMarginTop, weekDayControlsWidth, weekDayControlsHeight, mainWindow, (HMENU)(BUTTON_PARAM_START + i),
				(HINSTANCE)GetWindowLongPtr(mainWindow, GWLP_HINSTANCE), NULL);
		}
	}

	void CreateInformationDisplayControls()
	{
		std::string caption = Utility::AddColonAndSpaceAtEnd(weekDays[0]);
		currentWeekDayCaption = Caption(mainWindow, caption, 60, 60, 120, 30, caption,25);
		caption = "temperature: ";
		temperatureCaption = Caption(mainWindow, caption, 70, 100, 230, 20, caption);
		caption = "pressure: ";
		pressureCaption = Caption(mainWindow, caption, 70, 125, 230, 20, caption);
		refreshButton = CreateWindow(L"BUTTON", L"Refresh",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10,
			220, 70, 25, mainWindow, (HMENU)REFRESH_BUTTON,
			(HINSTANCE)GetWindowLongPtr(mainWindow, GWLP_HINSTANCE), NULL);
	}
	void LoadWeatherData()
	{
		weatherData = weatherInfoGetter.GetWeatherData();
		DisplayCurrentStoredData();
	}
	void DisplayCurrentStoredData()
	{
		std::string temperature = weatherData[currentSelectedDay].temperature + "C";
		std::string pressure = weatherData[currentSelectedDay].pressure + "hPa";
		temperatureCaption.ChangeText(temperature, true);
		pressureCaption.ChangeText(pressure, true);
	}
	LRESULT CALLBACK ProcessEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message != WM_COMMAND)
		{
			throw InvalidArgumentException();
		}
		if (wParam == REFRESH_BUTTON)
		{
			LoadWeatherData();
		}
		else if (wParam >= BUTTON_PARAM_START && wParam < BUTTON_PARAM_START + daySelectionSize)
		{
			std::string	temp = Utility::AddColonAndSpaceAtEnd(weekDays[wParam - BUTTON_PARAM_START]);
			currentWeekDayCaption.ChangeText(temp);
			currentSelectedDay = wParam - BUTTON_PARAM_START;
			DisplayCurrentStoredData();
		}
		else
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
};