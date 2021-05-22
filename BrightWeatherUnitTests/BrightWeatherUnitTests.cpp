#include "pch.h"
#include <iterator>
#include <algorithm>
#include <vector>

#include "CppUnitTest.h"
#include "../BrightWeather/WeekDaysNames.cpp"
#include "../BrightWeather/WeekDaysUtility.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define EXCEPTION_TEST(functor, a, b) {auto lamb = [](){functor(a, b);};Assert::ExpectException<InvalidArgumentException>(lamb);}


bool areEqual(std::vector<std::string> a, std::vector<std::string> b)
{
	return std::equal(std::begin(a), std::end(a), std::begin(b));
}
namespace BrightWeatherUnitTests
{
	TEST_CLASS(BrightWeatherUnitTests)
	{
	public:
		TEST_METHOD(TestWeekDays)
		{
			//some simple tests
			Assert::IsTrue(areEqual({ "Sunday", "Monday", "Tuesday", "Wednesday" }, WeekDaysNames::GetDaysFromTo(0, 3)));
			Assert::IsTrue(areEqual({ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" }, WeekDaysNames::GetDaysFromTo(1, 6)));
			Assert::IsTrue(areEqual({ "Thursday", "Friday", "Saturday", }, WeekDaysNames::GetDaysFromTo(4, 6)));
			Assert::IsTrue(areEqual({ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" }, WeekDaysNames::GetDaysFromTo(0, 6)));
			//harder ones
			Assert::IsTrue(areEqual({ "Sunday", "Monday", "Tuesday" }, WeekDaysNames::GetDaysFromTo(7, 9)));
			Assert::IsTrue(areEqual({ "Thursday", "Friday", "Saturday", "Sunday", "Monday" }, WeekDaysNames::GetDaysFromTo(11, 15)));
			Assert::IsTrue(areEqual({ "Friday", "Saturday", "Sunday","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
			"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday","Monday", "Tuesday", "Wednesday" }, WeekDaysNames::GetDaysFromTo(19, 39)));
			//limit tests
			Assert::IsTrue(areEqual({ "Sunday" }, WeekDaysNames::GetDaysFromTo(0, 0)));
			Assert::IsTrue(areEqual({  "Saturday" }, WeekDaysNames::GetDaysFromTo(6, 6)));
			Assert::IsTrue(areEqual({ "Monday" }, WeekDaysNames::GetDaysFromTo(50, 50)));
			//exceptions tests
			EXCEPTION_TEST(WeekDaysNames::GetDaysFromTo, -1, 12);
			EXCEPTION_TEST(WeekDaysNames::GetDaysFromTo, 4, -16);
			EXCEPTION_TEST(WeekDaysNames::GetDaysFromTo, -2, -5);
			EXCEPTION_TEST(WeekDaysNames::GetDaysFromTo, 5, 4);
			EXCEPTION_TEST(WeekDaysNames::GetDaysFromTo, -4, 0);
			EXCEPTION_TEST(WeekDaysNames::GetDaysFromTo, 6, 0);
			EXCEPTION_TEST(WeekDaysNames::GetDaysFromTo, 0, -7);
		}
		TEST_METHOD(WeekDayUtility)//function is hard to test due to its dependency on current date, useful test would have to have it's own tests, the fastest way to check it is to debug test manually
		{
			std::vector<std::string> a = WeekDaysUtility::GetNext7DaysWeekNames();
		}
	};
}
