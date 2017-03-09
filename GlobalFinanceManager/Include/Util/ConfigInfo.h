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
	ConfigInfo(const TimeHolder& first_valid_edge, const TimeHolder& last_valid_edge);

	/*Month GetFirstValidMonth() const;
	int GetFirstValidYear() const;
	Month GetLastValidMonth() const;
	int GetLastValidYear() const;*/

private:
	const TimeHolder first_valid_edge_;
	const TimeHolder last_valid_edge_;
};

#endif