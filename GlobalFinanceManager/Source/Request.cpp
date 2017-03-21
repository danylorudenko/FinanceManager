#include <exception>

#include "..\Include\Util\Request\Request.h"

Request::Request(TimeEdgePredicate* time_predicate) :
	time_predicate_(time_predicate) 
{

}

Request::~Request()
{
	delete time_predicate_;
}

bool Request::IsValid(const FinanceEntry& entry) const {
	
	if (time_predicate_ != nullptr && !time_predicate_->IsValid(entry)) {
		return false;
	}

	return true;
}

void Request::Decorate(AComplexPredicate* next_component)
{
	time_predicate_->Decorate(next_component);
}

const TimeHolder& Request::GetFirstEdge() const
{
	return time_predicate_->GetFirstEdge();
}

const TimeHolder& Request::GetLastEdge() const
{
	return time_predicate_->GetLastEdge();
}