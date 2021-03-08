#pragma once
#include <exception>

class ClassNotInitializedException : public std::exception
{
public:
	char const* what() const override
	{
		return "Class wasn't correctly initialized";
	}
};
class InvalidArgumentException : public std::exception
{
public:
	char const* what() const override
	{
		return "Invalid argument was passed to function";
	}
};
class ConnectionFailureException : public std::exception
{
public:
	char const* what() const override
	{
		return "Couldn't connect to Internet";
	}
};