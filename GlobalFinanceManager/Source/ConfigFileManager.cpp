#include "..\Include\Managers\ConfigFileManager.h"

#include <fstream>
#include <string>
#include <regex>

const char* ConfigFileManager::config_file_name_ = "config.txt";

ConfigInfo ConfigFileManager::GetConfigInfo()
{
	std::ifstream* in_stream = new std::ifstream(config_file_name_);
	std::string config_file_content;

	while (std::getline(*in_stream, config_file_content));
	delete in_stream;

	std::regex config_regular_expression
	(
		"(\\[)"
		"(\\d{1, 2})"
		"(\\d{3})"
		"(-)"
		"(\\d{1, 2})"
		"(\\d{3})"
		"(\\])"
	);

	std::cmatch result;

	std::regex_match(config_file_content.c_str(), result, config_regular_expression);

	for (int i = 0; i < result.size(); i++)
	{
		//printf("\s\n", result[i].str().c_str());
	}

	TimeHolder first;
	TimeHolder second;

	return ConfigInfo(first, second);
}