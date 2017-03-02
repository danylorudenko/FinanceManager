#ifndef __CONFIG_FILE_MANAGER_H__
#define __CONFIG_FILE_MANAGER_H__

#include <string>
#include <fstream>

/*
	Static manager for operation in the config file of the program
	Config is to contain data like:
		- valid limits for requests
		- user names
*/
class SConfigFileManagar
{
public:

private:
	static const char* config_file_name;
	static std::fstream config_file_stream_;
};

#endif