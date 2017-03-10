#include "..\Include\Util\ConfigInfo.h"

ConfigInfo::ConfigInfo(const TimeHolder& first_valid_edge, const TimeHolder& last_valid_edge) :
	first_valid_edge_(first_valid_edge), last_valid_edge_(last_valid_edge)
{

}

Month ConfigInfo::GetFirstValidMonth() const
{
	return first_valid_edge_.GetMonth();
}

int ConfigInfo::GetFirstValidYear() const
{
	return first_valid_edge_.GetYear();
}

Month ConfigInfo::GetLastValidMonth() const
{
	return last_valid_edge_.GetMonth();
}

int ConfigInfo::GetLastValidYear() const
{
	return last_valid_edge_.GetYear();
}