#ifndef __MONTHS_H__
#define __MONTHS_H__

#include <string>

enum struct Month
{
	Jan = 1,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec,
	NO_MONTH
};

class MonthConverter
{
public:
	static Month IntToMonth(int month);
	static int MonthToInt(Month month);
	static std::string MonthToString(Month month);
};

#endif