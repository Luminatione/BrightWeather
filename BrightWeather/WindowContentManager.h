#pragma once

#include <string>
#include <Windows.h>
#include <vector>

#include "BrightWeatherExceptions.h"
#include "WeekDaysUtility.h"
#include "Utility.h"

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

	struct Caption
	{
		HWND handle;
		int x, y;
		int height, width;
		Caption() = default;
		Caption(HWND parent, std::string& caption, int x, int y, int width, int height, int fontSize = 18) : x(x), y(y), height(height), width(width)
		{
			handle = CreateWindow(L"STATIC", Utility::AsciiStringToWstring(caption).c_str(), WS_CHILD | WS_VISIBLE, x, y, width, height, parent, nullptr, nullptr, nullptr);
			HFONT font = CreateFontA(fontSize, 0, 0, 0, 0, 0, 0, 0, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
			SendMessageA(handle, WM_SETFONT, (WPARAM)font, TRUE);
		}
		void ChangeText(std::string& newText)
		{
			SetWindowTextW(handle, Utility::AsciiStringToWstring(newText).c_str());
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

	WindowContentManager(HWND mainWindowHandle) :mainWindow(mainWindowHandle)
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
		currentWeekDayCaption = Caption(mainWindow, caption, 60, 60, 120, 30, 25);
		caption = "temperature: -";
		temperatureCaption = Caption(mainWindow, caption, 70, 100, 130, 20);
		caption = "pressure: -";
		pressureCaption = Caption(mainWindow, caption, 70, 125, 130, 20);
		refreshButton = CreateWindow(L"BUTTON", L"Refresh",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10,
			220, 70, 25, mainWindow, NULL,
			(HINSTANCE)GetWindowLongPtr(mainWindow, GWLP_HINSTANCE), NULL);
	}

	LRESULT CALLBACK ProcessEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message != WM_COMMAND)
		{
			throw InvalidArgumentException();
		}
		if(wParam == REFRESH_BUTTON)
		{
			//TODO: implement
		}
		if (wParam >= BUTTON_PARAM_START && wParam < BUTTON_PARAM_START + daySelectionSize)
		{
			std::string	temp = Utility::AddColonAndSpaceAtEnd(weekDays[wParam - BUTTON_PARAM_START]);
			currentWeekDayCaption.ChangeText(temp);
			//TODO: show weather for specific day
		}
		else
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
};