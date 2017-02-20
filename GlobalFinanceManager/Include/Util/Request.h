#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "..\..\Include\Time\TimeHolder.h"
#include "..\..\Include\Entry\FinanceEntry.h"

/*
	This class represents a user request to the manager.
	Main elements:
		- first time edge
		- second time edge
		- predicate to define if the FinanceRecord suits the request
*/
class Request
{
private:
	using FinancePredicate = bool(*)(const FinanceEntry& entry);
	
	TimeHolder first_edge_;
	TimeHolder last_edge_;
	FinancePredicate predicate_;

public:
	enum struct Direction
	{
		Forward = 1,
		Backward = -1
	};

	Request(TimeHolder& first_edge, TimeHolder& last_edge);
	Request(TimeHolder& first_edge, TimeHolder& last_edge, FinancePredicate predicate);
	Request(TimeHolder& edge, Direction direction);
	Request(TimeHolder& edge, Direction direction, FinancePredicate predicate);
	Request(FinancePredicate predicate);
	Request();

	bool IsValid(const FinanceEntry& entry) const;
};

#endif