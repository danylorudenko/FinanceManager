#include "..\Include\Managers\ConfigFileManager.h"
#include "..\Include\Time\MonthConverter.h"

#include <fstream>
#include <string>
#include <regex>
#include <iostream>

const char* ConfigFileManager::config_file_name_ = "Config_file_structure.txt";

ConfigInfo ConfigFileManager::GetConfigInfo()
{
	std::string config_file_content;
	std::ifstream* in_stream = new std::ifstream(config_file_name_, std::ios_base::in | std::ios_base::ate);
	in_stream->seekg(0, std::ios_base::beg);

	while (std::getline(*in_stream, config_file_content));
	in_stream->close();
	delete in_stream;

	std::regex config_regular_expression
	(
		"(\\[)"		   // 1
		"(\\d{1,2})"   // 2
		"(_)"		   // 3
		"(\\d{3})"	   // 4
		"(-)"		   // 5
		"(\\d{1,2})"   // 6
		"(_)"		   // 7
		"(\\d{3})"	   // 8
		"(\\])"		   // 9
	);

	std::cmatch result;

	std::regex_match(config_file_content.c_str(), result, config_regular_expression);

	if (result.size() > 0) {
		std::cout << "Have results\n";
		TimeHolder first(0, MonthConverter::IntToMonth(std::stoi(result[2].str())), std::stoi(result[4].str()));
		TimeHolder last(0, MonthConverter::IntToMonth(std::stoi(result[6].str())), std::stoi(result[8].str()));
		return ConfigInfo(first, last);
	}
	else
	{
		return ConfigInfo(TimeHolder(), TimeHolder());
	}
	
}