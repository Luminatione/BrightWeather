#pragma once
#include <exception>

class ClassNotInitializedException : public std::exception
{
	char const* what() const override
	{
		return "Class wasn't correctly initialized";
	}
};
class InvalidArgumentException : public std::exception
{
	char const* what() const override
	{
		return "Invalid argument was passed to function";
	}
};