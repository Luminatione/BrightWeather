#pragma once

#include <string>

class Utility
{
public:
	/// <summary>
	/// rewrite std::string to std::wstring
	/// </summary>
	static std::wstring AsciiStringToWstring(const std::string& a);

	static std::string AddColonAndSpaceAtEnd(const std::string& a);
};
