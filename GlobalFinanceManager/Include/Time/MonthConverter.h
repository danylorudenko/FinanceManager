#ifndef __MONTH_CONVERTER_H__
#define __MONTH_CONVERTER_H__

#include "..\..\Include\Enums\Month.h"

/*
	Utilite class to help converting data between types Month, int, std::string
*/
class MonthConverter
{
public:
	static Month IntToMonth(int month);
	static int MonthToInt(Month month);
	static std::string MonthToString(Month month);
};

#endif