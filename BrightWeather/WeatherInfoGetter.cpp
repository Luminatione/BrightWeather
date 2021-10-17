#pragma once

#include "WeatherInfoGetter.h"

WeatherInfoGetter::WeatherInfoGetter()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

std::string WeatherInfoGetter::GetOpenWeatherMapFilledURL(Location& location)
{
	return OpenWeatherMapURL + "lat=" + location.lat + "&lon=" + location.lon +
		"&exclude=alerts,hourly,minutely,current&appid=" + apiKeyOpenWeatherMap;
}

std::string WeatherInfoGetter::GetWebsiteContent(const std::string& URL, void onError())
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

		if (result != CURLE_OK && onError != nullptr)
		{
			onError();
		}
	}
	else if (onError != nullptr)
	{
		onError();
	}
	curl_easy_cleanup(connection);
	return output;
}

int WeatherInfoGetter::Writer(void* data, size_t size, size_t nmemb, void* buffer)
{
	((std::string*)buffer)->append((char*)data, size * nmemb);
	return size * nmemb;
}

void WeatherInfoGetter::OnError()
{
	throw ConnectionFailureException();
}

WeatherInfoGetter::Location WeatherInfoGetter::GetUserLocation()
{
	std::string result = GetWebsiteContent(IPinfoURL, OnError);
	nlohmann::json resultParsed = nlohmann::json::parse(result);
	std::string loc = resultParsed["loc"];

	return {std::string(loc, 0, 7), std::string(loc, 8, 7)};
}

std::vector<WeatherInfoGetter::WeatherData> WeatherInfoGetter::GetWeatherData()
{
	Location userLocation = GetUserLocation();
	std::string openWeatherMapFilledURL = GetOpenWeatherMapFilledURL(userLocation);
	std::string openWeatherContent = GetWebsiteContent(openWeatherMapFilledURL);
	nlohmann::json resultParsed = nlohmann::json::parse(openWeatherContent);

	std::vector<WeatherData> result(resultParsed["daily"].size());
	int i = 0;
	for (auto& element : resultParsed["daily"])
	{
		result[i] = {std::to_string((float)element["temp"]["day"] - 273), std::to_string((float)element["pressure"])};
		result[i].temperature = std::to_string((int)round(std::stod(result[i].temperature)));
		result[i].pressure = std::to_string((int)round(std::stod(result[i].pressure)));
		i++;
	}

	return result;
}
