#include "..\Include\Managers\GlobalManager.h"
#include "..\Include\Util\FileNames.h"
#include "..\Include\Util\Request\RequestFactory.h"
#include "..\Include\Util\EntryIterator.h"

#include <iostream>
#include <algorithm>

const std::string GlobalManager::balance_all_argument_ = "all";

void GlobalManager::DisplayBalance(std::string& params_string)
{
	if (params_string == "all") {
		std::cout
			<< "Current balance: "
			<< ConfigFileManager::GetConfigInfo().GetCurrentBalance()
			<< " UAH\n";
	}
	else {
		const Request* request = RequestFactory::ConstructTimeRequest(params_string);
		
		OpenManagers(*request);
		SortBuffers();
		DisplayManagersBuffers(*request);

		int balance = CountBalanceByTime(*request);
		std::cout << "Balance: " << balance << " UAH\n";
	}
}

void GlobalManager::DisplayManagersBuffers(const Request& request)
{
	int counter = 1;

	int managers_length = month_managers_.size();
	for(int i = 0; i < managers_length; ++i) 
	{
		auto iter_begin = month_managers_.at(i).Begin(&request);
		auto iter_end = month_managers_.at(i).End(&request);

		for (auto j = iter_begin; j != iter_end; ++j) {
			std::cout
				<< counter << ": "
				<< (*j).Serialize() << std::endl;
			++counter;
		}
	}
	std::cout << std::endl;
}

int GlobalManager::CountBalanceByTime(const Request& request)
{
	int balance = 0;

	int managers_length = month_managers_.size();
	for (int i = 0; i < managers_length; ++i)
	{
		auto iter_begin = month_managers_.at(i).Begin(&request);
		auto iter_end = month_managers_.at(i).End(&request);

		for (auto j = iter_begin; j != iter_end; ++j) {
			balance += (*j).GetSum();
		}
	}

	return balance;
}

void GlobalManager::GetRecords(std::string& params)
{
	std::cout << "GetRecords\n";
}

void GlobalManager::GlobalSearch(std::string& params)
{
	std::cout << "Global search\n";
}

void GlobalManager::EditEntry(std::string& params)
{
	std::cout << "EditEntry\n";
}

void GlobalManager::AddEntry(std::string& params)
{
	std::cout << "Add entry\n";
}

void GlobalManager::OpenManagers(const Request& request)
{
	StringVector* file_names = FileNames::ConstructFileNames(request);

	std::for_each(file_names->begin(), file_names->end(), 
		[&] (std::string& name) {
		month_managers_.push_back(MonthFileManager(name));
	});

	delete file_names;
}

void GlobalManager::CloseManagers()
{
	month_managers_.clear();
}

void GlobalManager::DeleteEmptyFiles()
{
	std::for_each(month_managers_.begin(), month_managers_.end(), 
		[](const MonthFileManager& manager) {
		if (manager.IsFileEmpty()) {
			manager.DeleteFile();
		}
	});
}

void GlobalManager::SortBuffers()
{
	std::for_each(month_managers_.begin(), month_managers_.end(), 
		[](MonthFileManager& manager) {
		manager.SortBuffer();
	});
}

GlobalManager::~GlobalManager()
{
	DeleteEmptyFiles();
}