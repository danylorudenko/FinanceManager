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

private:
	TimeHolder first_valid_edge_;
	TimeHolder last_valid_edge_;
};

#endif