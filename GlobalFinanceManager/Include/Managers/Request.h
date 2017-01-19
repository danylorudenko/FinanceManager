#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "..\..\Include\Time\TimeHolder.h"
#include "..\..\Include\Entry\FinanceEntry.h"

class Request
{
private:
	using FinancePredicate = bool(*)(FinanceEntry& entry);

	TimeHolder first_edge_;
	TimeHolder last_edge_;
	FinancePredicate predicate_;

public:
	Request(TimeHolder& first_edge, TimeHolder& last_edge);
	Request(TimeHolder& first_edge, TimeHolder& last_edge, FinancePredicate predicate);
	Request(TimeHolder& edge, int direction);
	Request(TimeHolder& edge, int direction, FinancePredicate predicate);
};

#endif