#include "..\Include\Managers\GlobalManager.h"
#include <iostream>

const std::string GlobalManager::balance_all_argument_ = "all";
const std::string GlobalManager::sum_argument_prefix_ = "s";

void GlobalManager::DisplayBalance(const std::string& params_string)
{
	if (params_string == "all") {
		std::cout
			<< "Current balance: "
			<< ConfigFileManager::GetConfigInfo().GetCurrentBalance()
			<< " UAH\n";
	}
	else {
		// TO DO
	}
}

void GlobalManager::DisplayBalanceByTime(std::string& time_param_string)
{
	std::cout << "NOT READY!\n";
}

void GlobalManager::GetRecords(const std::string& params)
{
	std::cout << "GetRecords\n";
}

void GlobalManager::GlobalSearch(const std::string& params)
{
	std::cout << "Global search\n";
}

void GlobalManager::EditEntry(const std::string& params)
{
	std::cout << "EditEntry\n";
}

void GlobalManager::AddEntry(const std::string& params)
{
	std::cout << "Add entry\n";
}