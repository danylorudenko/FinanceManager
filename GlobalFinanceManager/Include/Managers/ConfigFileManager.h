#ifndef __CONFIG_FILE_MANAGER_H__
#define __CONFIG_FILE_MANAGER_H__

#include "..\..\Include\Util\ConfigInfo.h"

/*
	Static manager for operation in the config file of the program
	Config is to contain data like:
		- valid limits for requests
		- user names
*/
class ConfigFileManager
{
public:
	static ConfigInfo GetConfigInfo();

private:
	static const char* config_file_name_;
};

#endif