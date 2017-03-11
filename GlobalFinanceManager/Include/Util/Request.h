#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "..\..\Include\Enums\Direction.h"
#include "..\..\Include\Entry\FinanceEntry.h"
#include "..\..\Include\Managers\ConfigFileManager.h"

using FinancePredicate = bool(*)(const FinanceEntry& entry);

/*
	This class represents a user request to the manager.
	Main elements:
		- first time edge
		- second time edge
		- predicate to define if the FinanceRecord suits the request
*/
class Request
{
public:
	static Request* LastDays(int days = 1);
	static Request* LastWeeks(int weeks = 1);
	static Request* LastMonths(int months = 1);

protected:
	Request(const TimeHolder& first_edge, const TimeHolder& last_edge);
	Request(const TimeHolder& first_edge, const TimeHolder& last_edge, const FinancePredicate predicate);
	Request(const TimeHolder& edge, const Direction direction);
	Request(const TimeHolder& edge, const Direction direction, const FinancePredicate predicate);
	Request(const FinancePredicate predicate);
	Request();

	bool IsValid(const FinanceEntry& entry) const;

	const TimeHolder& GetFirstEdge() const;
	const TimeHolder& GetLastEdge() const;

	TimeHolder first_edge_;
	TimeHolder last_edge_;
	FinancePredicate predicate_;
};

#endif