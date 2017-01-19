#include "..\Include\Managers\Request.h"

#include <exception>

Request::Request(TimeHolder& first_edge, TimeHolder& last_edge) : first_edge_(first_edge), last_edge_(last_edge) { }

Request::Request(TimeHolder& first_edge, TimeHolder& last_edge, FinancePredicate predicate) :
	first_edge_(first_edge), 
	last_edge_(last_edge), 
	predicate_(predicate) 
{ }

Request::Request(TimeHolder& edge, int direction)
{
	if (direction > 0)
	{
		first_edge_ = edge;
		last_edge_ = TimeHolder();
	}
	else if (direction < 0)
	{
		first_edge_ = TimeHolder();
		last_edge_ = edge;
	}
	else
	{
		throw std::invalid_argument("Direction of the request may be only \"1\" or \"two\"");
	}
}

Request::Request(TimeHolder& edge, int direction, FinancePredicate predicate) : predicate_(predicate)
{
	if (direction > 0)
	{
		first_edge_ = edge;
		last_edge_ = TimeHolder();
	}
	else if (direction < 0)
	{
		first_edge_ = TimeHolder();
		last_edge_ = edge;
	}
	else
	{
		throw std::invalid_argument("Direction of the request may be only \"1\" or \"two\"");
	}
}