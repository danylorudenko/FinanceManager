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

const ConfigInfo& ConfigFileManager::GetConfigInfo()
{
	if (local_up_to_date_) {
		return *local_config_info_;
	}
	else {
		delete local_config_info_;
		try {
			local_config_info_ = ReadConfigFromFile();
			return *local_config_info_;
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;

			// Writing today time to the config file
			const std::string* valid_config_string = ConstructConfigString(TimeHolder(), 0);
			ConfigFileManager::RewriteConfigFile(valid_config_string);
			delete valid_config_string;

			// Updating local config according to the file
			delete local_config_info_;
			local_config_info_ = ConfigFileManager::ReadConfigFromFile();

			return *local_config_info_;
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

		"(\\[)"			 // 8
		"(-?)"		     // 9
		"(\\d*)"	     // 10
		"(\\])"			 // 11
	);

	std::cmatch result;

	std::regex_match(config_file_content.c_str(), result, config_regular_expression);

	if (result.size() > 0) {
		// first edge
		TimeHolder first(std::stoi(result[2]), MonthConverter::IntToMonth(std::stoi(result[4])), std::stoi(result[6]));

		// current balance
		std::string current_balance_string = (result[9].str() + result[10].str());
		int current_balance = std::stoi(current_balance_string);

		local_up_to_date_ = true;
		return new ConfigInfo(first, TimeHolder(), current_balance);
	}
	else
	{
		throw std::exception("Fail to read config file.");
	}
}

void ConfigFileManager::TryWriteNewTime(const TimeHolder& time)
{
	// Construction of the new config string according to the new last time
	const ConfigInfo& config_info = ConfigFileManager::GetConfigInfo();
	
	if (config_info.GetFirstEdge() > time) {

		const std::string* config_string = ConfigFileManager::ConstructConfigString(time, ConfigFileManager::GetConfigInfo().GetCurrentBalance());
		ConfigFileManager::RewriteConfigFile(config_string);

		delete config_string;
	}
}

void ConfigFileManager::AdjustBalance(const int to_add)
{
	const ConfigInfo& config_info = ConfigFileManager::GetConfigInfo();
	int current_balance = config_info.GetCurrentBalance();
	int new_balance = current_balance + to_add;

	const std::string* config_string = ConfigFileManager::ConstructConfigString(config_info.GetFirstEdge(), new_balance);
	ConfigFileManager::RewriteConfigFile(config_string);

	delete config_string;
}

void ConfigFileManager::RewriteConfigFile(const std::string* string)
{
	std::ofstream* out_stream = new std::ofstream(config_file_name_, std::ios_base::out | std::ios_base::trunc);
	*out_stream << *string;
	out_stream->close();
	delete out_stream;

	local_up_to_date_ = false;
}

const std::string* ConfigFileManager::ConstructConfigString(const TimeHolder& new_oldest_time, const int new_current_balance)
{
	std::stringstream& string_stream = std::stringstream();

	string_stream
		<< "["
		<< new_oldest_time.GetDay()
		<< "_"
		<< MonthConverter::MonthToInt(new_oldest_time.GetMonth())
		<< "_"
		<< new_oldest_time.GetYear()
		<< "]"

		<< "["
		<< new_current_balance
		<< "]";

	return new std::string(string_stream.str());
}