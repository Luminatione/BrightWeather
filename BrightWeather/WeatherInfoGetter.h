#pragma once

#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <cmath>

#include "ApiKeys.h"
#include "BrightWeatherExceptions.h"
#include "json.hpp"

class WeatherInfoGetter//TODO: implement
{
	//std::string apiKeyOpenWeatherMap = "d3aa3b8991cba14d22f3cfd35ce2d0f8";
	//std::string apiKeyIPinfo = "0ef995f3b1731e";
	std::string IPinfoURL = "https://ipinfo.io?token=" + apiKeyIPInfo;
	std::string OpenWeatherMapURL = "https://api.openweathermap.org/data/2.5/onecall?";


public:
	WeatherInfoGetter()
	{
		curl_global_init(CURL_GLOBAL_ALL);
	}
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
	std::string GetOpenWeatherMapFilledURL(Location& location)
	{
		return OpenWeatherMapURL + "lat=" + location.lat + "&lon=" + location.lon + "&exclude=alerts,hourly,minutely,current&appid=" + apiKeyOpenWeatherMap;
	}
	std::string GetWebsiteContent(const std::string& URL, void onError() = nullptr)
	{
		std::string output;
		CURL* connection = curl_easy_init();
		if (connection)
		{
			curl_easy_setopt(connection, CURLOPT_URL, URL.c_str());
			curl_easy_setopt(connection, CURLOPT_HEADER, 0);
			curl_easy_setopt(connection, CURLOPT_WRITEFUNCTION, Writer);
			curl_easy_setopt(connection, CURLOPT_WRITEDATA, &output);
			curl_easy_setopt(connection, CURLOPT_TIMEOUT, 5);
			CURLcode result = curl_easy_perform(connection);
			
			if(result != CURLE_OK && onError != nullptr)
			{
				onError();
			}
		}
		else if(onError != nullptr)
		{		
			onError();
		}
		curl_easy_cleanup(connection);
		return output;
	}
	static int Writer(void* data, size_t size, size_t nmemb, void* buffer)
	{
		((std::string*)buffer)->append((char*)data, size * nmemb);
		return size * nmemb;
	}
	static void OnError()
	{
		throw ConnectionFailureException();
	}
	Location GetUserLocation()
	{
		std::string result = GetWebsiteContent(IPinfoURL, OnError);
		nlohmann::json resultParsed = nlohmann::json::parse(result);
		std::string loc = resultParsed["loc"];
		return { std::string(loc, 0, 7), std::string(loc, 8, 7) };
	}
public:
	std::vector<WeatherData> GetWeatherData()
	{
		Location userLocation = GetUserLocation();
		std::string openWeatherMapFilledURL = GetOpenWeatherMapFilledURL(userLocation);
		std::string openWeatherContent = GetWebsiteContent(openWeatherMapFilledURL);
		nlohmann::json resultParsed = nlohmann::json::parse(openWeatherContent);

		std::vector<WeatherData> result(resultParsed["daily"].size());
		int i = 0;
		for (auto& element : resultParsed["daily"])
		{
			result[i] = { std::to_string((float)element["temp"]["day"] - 273), std::to_string((float)element["pressure"]) };
			result[i].temperature = std::to_string((int)round(std::stod(result[i].temperature)));
			result[i].pressure = std::to_string((int)round(std::stod(result[i].pressure)));
			i++;
		}

		return result;
	}
};