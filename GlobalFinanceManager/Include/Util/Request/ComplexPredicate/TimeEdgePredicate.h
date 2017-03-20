#ifndef __SUM_TYPE_PREDICATE_H__
#define __SUM_TYPE_PREDICATE_H__

#include "..\..\..\..\Include\Util\Request\ComplexPredicate\AComplexPredicate.h"

class TimeEdgePredicate : public AComplexPredicate
{
public:
	virtual bool IsValid(const FinanceEntry& entry) const;

protected:
	// Augmenting first endge of the request so it doesn't overthrow existing data
	static void AugmentFirstEdgeByConfig(TimeHolder* first_edge);

	TimeHolder first_edge_;
	TimeHolder last_edge_;
};

#endif