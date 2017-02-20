#include "..\Include\Util\Request.h"

#include <exception>

Request::Request(TimeHolder& first_edge, TimeHolder& last_edge) : 
	first_edge_(first_edge), 
	last_edge_(last_edge),
	predicate_(nullptr)
{ }

Request::Request(TimeHolder& first_edge, TimeHolder& last_edge, FinancePredicate predicate) :
	first_edge_(first_edge), 
	last_edge_(last_edge), 
	predicate_(predicate) 
{ }

Request::Request(TimeHolder& edge, Direction direction) : predicate_(nullptr)
{
	if (direction == Direction::Backward)
	{
		first_edge_ = edge;
		last_edge_ = TimeHolder();
	}
	else if (direction == Direction::Forward)
	{
		first_edge_ = TimeHolder();
		last_edge_ = edge;
	}
	else
	{
		throw std::invalid_argument("Direction of the request may be only \"-1\" or \"two\"");
	}
}

Request::Request(TimeHolder& edge, Direction direction, FinancePredicate predicate) : predicate_(predicate)
{
	if (direction == Direction::Backward)
	{
		first_edge_ = edge;
		last_edge_ = TimeHolder();
	}
	else if (direction == Direction::Forward)
	{
		first_edge_ = TimeHolder();
		last_edge_ = edge;
	}
	else
	{
		throw std::invalid_argument("Direction of the request may be only \"1\" or \"two\"");
	}
}

Request::Request(FinancePredicate predicate) : predicate_(predicate) 
{
	first_edge_.ToZero();
	last_edge_.ToMax();
}

Request::Request() : predicate_(nullptr)
{
	first_edge_.ToZero();
	last_edge_.ToMax();
}

bool Request::IsValid(const FinanceEntry& entry) const {
	
	if (predicate_ != nullptr && !predicate_(entry)) {
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