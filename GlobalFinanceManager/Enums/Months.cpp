#include "Months.h"
#include <exception>

Month MonthConverter::IntToMonth(int month)
{
	if (month < 1 || month > 12)
	{
		throw std::invalid_argument("Trying to covert to enum Month ivalid number");
	}
	return static_cast<Month>(month);
}

int MonthConverter::MonthToInt(Month month)
{
	return static_cast<int>(month);
}

std::string MonthConverter::MonthToString(Month month)
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
