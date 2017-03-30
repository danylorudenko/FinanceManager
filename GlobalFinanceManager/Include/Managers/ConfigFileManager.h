#ifndef __CONFIG_FILE_MANAGER_H__
#define __CONFIG_FILE_MANAGER_H__

#include <string>

#include "..\..\Include\Util\ConfigInfo.h"

/*
	Static manager for operation in the config file of the program
	Config contains this data:
		- oldest data month and year
*/
class ConfigFileManager
{
public:

	// Returns object containing configuration info
	static const ConfigInfo& GetConfigInfo();

	// Attempt to write new time edge to the config file.
	// The time will be written if it is earlier than time in the file
	static void TryWriteNewTime(const TimeHolder& time);

	// Adding passed value to the balance in the config file
	static void AdjustBalance(const int to_add);

protected:
	// Reading configuration data directly from the file + updating local config data
	static ConfigInfo* ReadConfigFromFile();

	// Constructing valid config-data string
	static const std::string* ConstructConfigString(const TimeHolder& new_oldest_time, const int new_current_balance);

	// Rewriting config file with passed string
	static void RewriteConfigFile(const std::string* string);

protected:
	static const char* config_file_name_;

	static bool local_up_to_date_;
	static ConfigInfo* local_config_info_;
};

#endif