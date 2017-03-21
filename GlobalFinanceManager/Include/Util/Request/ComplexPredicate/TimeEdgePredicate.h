#ifndef __TIME_EDGE_PREDICATE_H__
#define __TIME_EDGE_PREDICATE_H__

#include "..\..\..\..\Include\Util\Request\ComplexPredicate\AComplexPredicate.h"

class TimeEdgePredicate : public AComplexPredicate
{
public:
	virtual bool IsValid(const FinanceEntry& entry) const;

	// Shortuct for constructing proper request for N days from today 
	// (concerning config limits)
	static TimeEdgePredicate* LastDays(int days = 1);

	// Shortuct for constructing proper request for N Weeks from today 
	// (concerning config limits)
	static TimeEdgePredicate* LastWeeks(int weeks = 1);

	// Shortuct for constructing proper request for (N * 30) days from today 
	// (concerning config limits)
	static TimeEdgePredicate* LastMonths(int months = 1);

	const TimeHolder& GetFirstEdge() const;
	const TimeHolder& GetLastEdge() const;

protected:
	TimeEdgePredicate(const TimeHolder& first_edge, const TimeHolder& last_edge, AComplexPredicate* next_component = nullptr);

	// Augmenting first endge of the request so it doesn't overthrow existing data
	static void AugmentFirstEdgeByConfig(TimeHolder* first_edge);

	TimeHolder first_edge_;
	TimeHolder last_edge_;
};

#endif