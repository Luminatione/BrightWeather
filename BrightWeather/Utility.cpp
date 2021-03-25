#include "Utility.h"

std::wstring Utility::AsciiStringToWstring(const std::string& a)
{
	return std::wstring(a.begin(), a.end());
}

std::string Utility::AddColonAndSpaceAtEnd(const std::string& a)
{
	std::string temp = std::string(a + ": ");
	return temp;
}
