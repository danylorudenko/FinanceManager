#ifndef __MONTH_CONVERTER_H__
#define __MONTH_CONVERTER_H__

#include "..\..\Include\Enums\Month.h"

/*
	Utilite class to help converting data between types Month, int, std::string
*/
class MonthConverter
{
public:
	static Month IntToMonth(const int month);
	static int MonthToInt(const Month month);
	static int MonthToDays(const Month month, const int year);
	static std::string MonthToString(const Month month);
};

Month operator++(Month& month, int);

#endif