#pragma once

#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <cmath>

#include "ApiKeys.h"
#include "BrightWeatherExceptions.h"
#include "json.hpp"

class WeatherInfoGetter
{
	std::string IPinfoURL = "https://ipinfo.io?token=" + apiKeyIPInfo;
	std::string OpenWeatherMapURL = "https://api.openweathermap.org/data/2.5/onecall?";


public:
	WeatherInfoGetter();

	struct WeatherData
	{
		std::string temperature;
		std::string pressure;
	};
	struct Location
	{
		std::string lat = 0;
		std::string lon = 0;
	};
private:
	std::string GetOpenWeatherMapFilledURL(Location& location);

	std::string GetWebsiteContent(const std::string& URL, void onError() = nullptr);

	static int Writer(void* data, size_t size, size_t nmemb, void* buffer);

	static void OnError();

	Location GetUserLocation();
public:
	std::vector<WeatherData> GetWeatherData();
};