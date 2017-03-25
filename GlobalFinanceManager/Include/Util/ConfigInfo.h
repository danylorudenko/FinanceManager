#ifndef __CONFIG_INFO_H__
#define __CONFIG_INFO_H__

#include "..\Time\TimeHolder.h"

/*
	Class is an agregator of the configuration information:
		- valid limits for the requests;
		- other data (in the future)
*/
class ConfigInfo
{
public:
	ConfigInfo(const TimeHolder& first_valid_edge, const TimeHolder& last_valid_edge, const int current_balance);

	const TimeHolder& GetFirstEdge() const;
	const TimeHolder& GetLastEdge() const;

	const int GetCurrentBalance() const;

protected:
	const TimeHolder first_valid_edge_;
	const TimeHolder last_valid_edge_;

	const int current_balance_;
};

#endif