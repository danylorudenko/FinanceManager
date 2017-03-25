#include "..\Include\Util\ConfigInfo.h"

ConfigInfo::ConfigInfo(const TimeHolder& first_valid_edge, const TimeHolder& last_valid_edge, const int current_balance) :
	first_valid_edge_(first_valid_edge), last_valid_edge_(last_valid_edge), current_balance_(current_balance)
{

}

const TimeHolder& ConfigInfo::GetFirstEdge() const
{
	return first_valid_edge_;
}

const TimeHolder& ConfigInfo::GetLastEdge() const
{
	return last_valid_edge_;
}

const int ConfigInfo::GetCurrentBalance() const
{
	return current_balance_;
}