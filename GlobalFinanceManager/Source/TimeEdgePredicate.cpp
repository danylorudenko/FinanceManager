#include "..\Include\Util\Request\ComplexPredicate\TimeEdgePredicate.h"
#include "..\Include\Managers\ConfigFileManager.h"

TimeEdgePredicate::TimeEdgePredicate(const TimeHolder& first_edge, const TimeHolder& last_edge, AComplexPredicate* next_component) :
	AComplexPredicate(next_component)
{
	if (first_edge.IsLaterThan(last_edge)) {
		throw std::invalid_argument("The first edge of TimeEdgePredicate can't be later than the last edge");
	}

	first_edge_ = first_edge;
	last_edge_ = last_edge;
}

void TimeEdgePredicate::AugmentFirstEdgeByConfig(TimeHolder* first_edge)
{
	const ConfigInfo& config_info = ConfigFileManager::GetConfigInfo();

	// if days are out of config edges, set first day from config 
	*first_edge =
		*first_edge < config_info.GetFirstEdge() ?
		config_info.GetFirstEdge() :
		*first_edge;
}

TimeEdgePredicate* TimeEdgePredicate::LastDays(int days)
{
	TimeHolder today;
	TimeHolder temp_first_edge = (today - (TimeHolder::Day() * days));

	AugmentFirstEdgeByConfig(&temp_first_edge);

	return new TimeEdgePredicate(temp_first_edge, TimeHolder());
}

TimeEdgePredicate* TimeEdgePredicate::LastWeeks(int weeks)
{
	TimeHolder today;
	TimeHolder temp_first_edge = (today - (TimeHolder::Week() * weeks));

	AugmentFirstEdgeByConfig(&temp_first_edge);

	return new TimeEdgePredicate(temp_first_edge, TimeHolder());
}

TimeEdgePredicate* TimeEdgePredicate::LastMonths(int months)
{
	TimeHolder today;
	TimeHolder temp_first_edge = (today - (TimeHolder::Month30() * months));

	AugmentFirstEdgeByConfig(&temp_first_edge);

	return new TimeEdgePredicate(temp_first_edge, TimeHolder());
}

bool TimeEdgePredicate::IsValid(const FinanceEntry& entry) const {

	if (entry.IsEarlierThan(first_edge_)) {
		return false;
	}

	if (entry.IsLaterThan(last_edge_)) {
		return false;
	}

	if (next_component_ == nullptr) {
		return true;
	}
	return next_component_->IsValid(entry);
}

const TimeHolder& TimeEdgePredicate::GetFirstEdge() const
{
	return first_edge_;
}

const TimeHolder& TimeEdgePredicate::GetLastEdge() const
{
	return last_edge_;
}