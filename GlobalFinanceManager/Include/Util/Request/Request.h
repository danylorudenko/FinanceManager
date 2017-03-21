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
	// Request is responsible for deleting predicate memory
	Request(TimeEdgePredicate* predicate);

	// Check of Entry is valid for this request
	bool IsValid(const FinanceEntry& entry) const;

	// Decorating internal complex predicate
	void Decorate(AComplexPredicate* next_component);

	const TimeHolder& GetFirstEdge() const;
	const TimeHolder& GetLastEdge() const;

	~Request();
protected:

	// Object is responsible for deleting it
	TimeEdgePredicate* time_predicate_;
};

#endif