#pragma once

#include <string>

class Utility
{
public:
	/// <summary>
	/// rewrite std::string to std::wstring
	/// </summary>
	static std::wstring AsciiStringToWstring(const std::string& a)
	{
		return std::wstring(a.begin(), a.end());
	}
	static std::string AddColonAndSpaceAtEnd(const std::string& a)
	{
		std::string temp = std::string(a + ": ");
		return temp;
	}
};
