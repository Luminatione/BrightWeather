#pragma once

#include <string>
#include <Windows.h>
#include <vector>
#include <thread>

#include "WeatherInfoGetter.h"

#define BUTTON_PARAM_START 1000
#define REFRESH_BUTTON 999
#define WEATHER_DATA_LOADED 9980
#define WEATHER_DATA_LOADING_FAILED 9981

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



	struct Caption
	{
		HWND handle;
		int x, y;
		int height, width;
		std::string defaultStr;

		Caption() = default;

		Caption(HWND parent, std::string& caption, int x, int y, int width, int height, std::string defaultStr = "", int fontSize = 18);

		void ChangeText(std::string& newText, bool onlyUpdate = false);
	};

	HWND refreshButton;

	Caption currentWeekDayCaption;
	Caption temperatureCaption;
	Caption pressureCaption;

public:
	WindowContentManager& operator=(const WindowContentManager& a);

	WindowContentManager(HWND mainWindowHandle);

	WindowContentManager();

	void CreateDaySelectionControls();

	void CreateInformationDisplayControls();

	void LoadWeatherData();

	void DisplayCurrentStoredData();

	bool IsValidButtonID(WPARAM wParam);

	LRESULT CALLBACK ProcessEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};