#include "..\Include\Time\MonthConverter.h"
#include <exception>

Month MonthConverter::IntToMonth(const int month)
{
	if (month < 1 || month > 12)
	{
		throw std::invalid_argument("Trying to covert to enum Month ivalid number");
	}
	return static_cast<Month>(month);
}

int MonthConverter::MonthToInt(const Month month)
{
	return static_cast<int>(month);
}

int MonthConverter::MonthToDays(const Month month, const int year)
{
	int month_int = MonthToInt(month);

	// Consult https://habrahabr.ru/post/261773/ for this formula
	int result = (28 + (month_int + (month_int / 8)) % 2 + 2 % month_int + 2 * (1 / month_int));

	if (month == Month::Feb && year % 4 == 0) {
		result += 1;
	}

	return result;
}

std::string MonthConverter::MonthToString(const Month month)
{
	switch (month)
	{
	case Month::Jan:
		return std::string("January");
	case Month::Feb:
		return std::string("February");
	case Month::Mar:
		return std::string("March");
	case Month::Apr:
		return std::string("April");
	case Month::May:
		return std::string("May");
	case Month::Jun:
		return std::string("June");
	case Month::Jul:
		return std::string("July");
	case Month::Aug:
		return std::string("August");
	case Month::Sep:
		return std::string("September");
	case Month::Oct:
		return std::string("October");
	case Month::Nov:
		return std::string("November");
	case Month::Dec:
		return std::string("December");
	default:
		throw std::invalid_argument("Trying to covert month that doesn't exist.");
	}
	return std::string();
}

Month operator++(Month& month, int)
{
	int month_int = static_cast<int>(month);
	month = static_cast<Month>(++month_int);
	return month;
}