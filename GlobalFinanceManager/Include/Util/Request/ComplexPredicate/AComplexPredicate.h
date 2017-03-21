#ifndef __A_COMPLEX_PREDICATE_H__
#define __A_COMPLEX_PREDICATE_H__

#include "..\..\..\..\Include\Entry\FinanceEntry.h"

using FinancePredicate = bool(*)(const FinanceEntry& entry);

class AComplexPredicate
{
public:
	virtual bool IsValid(const FinanceEntry& entry) const = 0;
	void Decorate(AComplexPredicate* component);

	
	virtual ~AComplexPredicate();

protected:
	AComplexPredicate(AComplexPredicate* next_component = nullptr);

	// Object is responsible for deleting components
	AComplexPredicate* next_component_;
};

#endif