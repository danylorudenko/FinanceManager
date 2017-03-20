#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "..\..\..\Include\Entry\FinanceEntry.h"
#include "..\..\..\Include\Managers\ConfigFileManager.h"
#include "..\..\..\Include\Util\Request\ComplexPredicate\TimeEdgePredicate.h"

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
	// Shortuct for constructing proper request for N days from today 
	// (concerning config limits)
	static Request* LastDays(int days = 1);

	// Shortuct for constructing proper request for N Weeks from today 
	// (concerning config limits)
	static Request* LastWeeks(int weeks = 1);

	// Shortuct for constructing proper request for (N * 30) days from today 
	// (concerning config limits)
	static Request* LastMonths(int months = 1);

public:
	// Check of Entry is valid for this request
	bool IsValid(const FinanceEntry& entry) const;

	const TimeHolder& GetFirstEdge() const;
	const TimeHolder& GetLastEdge() const;

protected:
	Request(const TimeEdgePredicate* predicate);

	~Request();

	// Object is responsible for deleting it
	const AComplexPredicate* predicate_;
};

#endif