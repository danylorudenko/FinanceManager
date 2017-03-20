#include <exception>

#include "..\Include\Util\Request\Request.h"

Request* Request::LastDays(int days)
{
	/*TimeHolder today;
	TimeHolder temp_first_edge = (today - (TimeHolder::Day() * days));

	AugmentFirstEdgeByConfig(&temp_first_edge);

	return new Request(temp_first_edge, TimeHolder());*/
}

Request* Request::LastWeeks(int weeks)
{
	/*TimeHolder today;
	TimeHolder temp_first_edge = (today - (TimeHolder::Week() * weeks));

	AugmentFirstEdgeByConfig(&temp_first_edge);

	return new Request(temp_first_edge, TimeHolder());*/
}

Request* Request::LastMonths(int months)
{
	/*TimeHolder today;
	TimeHolder temp_first_edge = (today - (TimeHolder::Month30() * months));

	AugmentFirstEdgeByConfig(&temp_first_edge);

	return new Request(temp_first_edge, TimeHolder());*/
}

Request::Request(const TimeEdgePredicate* predicate) :
	predicate_(predicate) 
{

}

Request::~Request()
{
	delete predicate_;
}

bool Request::IsValid(const FinanceEntry& entry) const {
	
	if (predicate_ != nullptr && !predicate_->IsValid(entry)) {
		return false;
	}

	if (entry.IsEarlierThan(first_edge_)) {
		return false;
	}

	if (entry.IsLaterThan(last_edge_)) {
		return false;
	}

	return true;
}

const TimeHolder& Request::GetFirstEdge() const
{
	return first_edge_;
}

const TimeHolder& Request::GetLastEdge() const
{
	return last_edge_;
}