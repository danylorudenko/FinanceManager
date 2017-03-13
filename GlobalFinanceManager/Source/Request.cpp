#include <exception>

#include "..\Include\Util\Request.h"

Request* Request::LastDays(int days)
{
	TimeHolder today;
	TimeHolder temp_first_edge = (today - (TimeHolder::Day() * days));

	AugmentFirstEdgeByConfig(&temp_first_edge);

	return new Request(temp_first_edge, TimeHolder());
}

Request* Request::LastWeeks(int weeks)
{
	TimeHolder today;
	TimeHolder temp_first_edge = (today - (TimeHolder::Week() * weeks));

	AugmentFirstEdgeByConfig(&temp_first_edge);

	return new Request(temp_first_edge, TimeHolder());
}

Request* Request::LastMonths(int months)
{
	TimeHolder today;
	TimeHolder temp_first_edge = (today - (TimeHolder::Month30() * months));

	AugmentFirstEdgeByConfig(&temp_first_edge);

	return new Request(temp_first_edge, TimeHolder());
}

Request::Request(const TimeHolder& first_edge, const TimeHolder& last_edge) :
	first_edge_(first_edge), 
	last_edge_(last_edge),
	predicate_(nullptr)
{
	if (first_edge_.IsLaterThan(last_edge_)) {
		throw std::invalid_argument("First edge of the request can't be earlier than the last edge.\n");
	}
}

Request::Request(const TimeHolder& first_edge, const TimeHolder& last_edge, FinancePredicate predicate) :
	first_edge_(first_edge), 
	last_edge_(last_edge), 
	predicate_(predicate) 
{
	if (first_edge_.IsLaterThan(last_edge_)) {
		throw std::invalid_argument("First edge of the request can't be earlier than the last edge.\n");
	}
}

Request::Request(const Request& rhs) :
	first_edge_(rhs.first_edge_), last_edge_(rhs.last_edge_), predicate_(rhs.predicate_)
{

}

void Request::AugmentFirstEdgeByConfig(TimeHolder* first_edge)
{
	const ConfigInfo* config_info = ConfigFileManager::GetConfigInfo();

	// if days are out of config edges, set first day from config 
	*first_edge =
		*first_edge < config_info->GetFirstEdge() ?
		config_info->GetFirstEdge() :
		*first_edge;
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

const TimeHolder& Request::GetFirstEdge() const
{
	return first_edge_;
}

const TimeHolder& Request::GetLastEdge() const
{
	return last_edge_;
}