#ifndef __MONTH_CONVERTER_H__
#define __MONTH_CONVERTER_H__

#include "..\..\Include\Enums\Month.h"

/*
	Utilite class to help converting data between types Month, int, std::string
*/
class MonthConverter
{
public:
	// Convertring Month enum to direct int equvivalent
	static Month IntToMonth(const int month);

	// Converting int to Month equivalent
	// If int is not between 0-11, Month::NO_MONTH is returned
	static int MonthToInt(const Month month);

	// Returns number in exact month of exact year
	static int MonthToDays(const Month month, const int year);

	// Returns std::string equivalent of Month enm
	static std::string MonthToString(const Month month);
};

Month operator++(Month& month, int);
Month operator++(Month& month);

#endif