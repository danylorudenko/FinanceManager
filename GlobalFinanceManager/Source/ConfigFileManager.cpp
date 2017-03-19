#include "..\Include\Managers\ConfigFileManager.h"
#include "..\Include\Time\MonthConverter.h"

#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <iostream>

const char* ConfigFileManager::config_file_name_ = "test_config_file.txt";

bool ConfigFileManager::local_up_to_date_ = false;

ConfigInfo* ConfigFileManager::local_config_info_ = nullptr;

const ConfigInfo* const ConfigFileManager::GetConfigInfo()
{
	if (local_up_to_date_) {
		return local_config_info_;
	}
	else {
		delete local_config_info_;
		try {
			local_config_info_ = ReadConfigFromFile();
			return local_config_info_;
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;

			// Writing today time to the config file
			const std::string* valid_config_string = ConstructConfigString(TimeHolder());
			ConfigFileManager::RewriteConfigFile(valid_config_string);
			delete valid_config_string;

			// Updating local config according to the file
			delete local_config_info_;
			local_config_info_ = ConfigFileManager::ReadConfigFromFile();

			return local_config_info_;
		}
	}
}

ConfigInfo* ConfigFileManager::ReadConfigFromFile()
{
	std::string config_file_content;
	std::ifstream* in_stream = new std::ifstream(config_file_name_, std::ios_base::in | std::ios_base::ate);
	in_stream->seekg(0, std::ios_base::beg);

	while (std::getline(*in_stream, config_file_content));
	in_stream->close();
	delete in_stream;

	std::regex config_regular_expression
	(
		"(\\[)"			 // 1
		"(\\d{1,2})"	 // 2
		"(_)"			 // 3
		"(\\d{1,2})"	 // 4
		"(_)"   		 // 5
		"(\\d{3})"		 // 6
		"(\\])"			 // 7
	);

	std::cmatch result;

	std::regex_match(config_file_content.c_str(), result, config_regular_expression);

	if (result.size() > 0) {
		TimeHolder first(std::stoi(result[2].str()), MonthConverter::IntToMonth(std::stoi(result[4].str())), std::stoi(result[6].str()));

		local_up_to_date_ = true;
		return new ConfigInfo(first, TimeHolder());
	}
	else
	{
		throw std::exception("Fail to read config file.");
	}
}

void ConfigFileManager::TryWriteNewTime(const TimeHolder& time)
{
	// Construction of the new config string according to the new last time
	const ConfigInfo* config_info = ConfigFileManager::GetConfigInfo();
	
	if (config_info->GetFirstEdge() > time) {

		const std::string* config_string = ConfigFileManager::ConstructConfigString(time);
		ConfigFileManager::RewriteConfigFile(config_string);

		delete config_string;
	}
}

void ConfigFileManager::RewriteConfigFile(const std::string* string)
{
	std::ofstream* out_stream = new std::ofstream(config_file_name_, std::ios_base::out | std::ios_base::trunc);
	*out_stream << *string;
	out_stream->close();
	delete out_stream;

	local_up_to_date_ = false;
}

const std::string* ConfigFileManager::ConstructConfigString(const TimeHolder& new_oldest_time)
{
	std::stringstream& string_stream = std::stringstream();

	string_stream
		<< "["
		<< MonthConverter::MonthToInt(new_oldest_time.GetMonth())
		<< "_"
		<< new_oldest_time.GetYear()
		<< "]";

	return new std::string(string_stream.str());
}