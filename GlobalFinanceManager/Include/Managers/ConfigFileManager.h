#ifndef __CONFIG_FILE_MANAGER_H__
#define __CONFIG_FILE_MANAGER_H__

#include "..\..\Include\Util\ConfigInfo.h"

#include <string>

/*
	Static manager for operation in the config file of the program
	Config contains this data:
		- oldest data month and year
*/
class ConfigFileManager
{
public:
	static const ConfigInfo* const GetConfigInfo();
	static void LogNewTime(const TimeHolder& time);

private:
	// Reading configuration data directly from the file + updating local config data
	static ConfigInfo* ReadConfigFromFile();

	// Constructing valid config-data string
	static const std::string* ConstructConfigString(const TimeHolder& new_oldest_time);

	// Rewriting config file with passed string
	static void RewriteConfigFile(const std::string* string);

private:
	static const char* config_file_name_;

	static bool local_up_to_date_;
	static ConfigInfo* local_config_info_;
};

#endif