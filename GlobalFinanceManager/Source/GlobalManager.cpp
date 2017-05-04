#include "..\Include\Managers\GlobalManager.h"
#include "..\Include\Util\FileNames.h"
#include "..\Include\Util\Request\RequestFactory.h"
#include "..\Include\Util\EntryIterator.h"
#include "..\Include\Util\CommandParametersExtractor.h"
#include "..\Include\Entry\EntryModificator\EntryModificatorFactory.h"
#include "..\Include\Entry\EntryModificator\AEntryModificator.h"
#include "..\Include\Time\MonthConverter.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <filesystem>

void GlobalManager::DisplayBalance(std::string& params_string)
{
	if (params_string == "all") {
		int balance_source_int = ConfigFileManager::GetConfigInfo().GetCurrentBalance();
		int major_currency = balance_source_int / 100;
		int minor_currency = std::abs(balance_source_int % 100);
		
		std::cout
			<< "Current balance: "
			<< major_currency
			<< '.'
			<< (minor_currency < 10 ? "0" : "")
			<< minor_currency
			<< " UAH\n";
	}
	else {
		delete prev_request_;
		prev_request_ = nullptr;
		prev_request_ = RequestFactory::ConstructTimeRequest(params_string);
		if (prev_request_ == nullptr) {
			std::cout << "Can't construct request with the given arguments.\n";
			return;
		}

		OpenManagers(*prev_request_);
		SortBuffers();
		DisplayManagersBuffers(*prev_request_);

		int balance_source_int = CountBalanceByTime(*prev_request_);;
		int major_currency = balance_source_int / 100;
		int minor_currency = std::abs(balance_source_int % 100);

		std::cout
			<< "Balance by time: "
			<< major_currency
			<< ','
			<< (minor_currency < 10 ? "0" : "")
			<< minor_currency
			<< " UAH\n";

		CloseManagers();
	}
}

void GlobalManager::DisplayManagersBuffers(const Request& request)
{
	int counter = 1;
	std::cout << std::left;

	auto managers_end = month_managers_.end();
	for (auto i = month_managers_.begin(); i != managers_end; ++i)
	{
		auto iter_begin = i->Begin(&request);
		auto iter_end = i->End(&request);

		for (auto j = iter_begin; j != iter_end; ++j) {
			std::cout
				<< counter << ":\t";
			FormatDisplayEntry(*j);
			++counter;
		}
	}
	std::cout << std::endl;
}

void GlobalManager::FormatDisplayEntry(const FinanceEntry& entry)
{
	// ============ Date:
	// Day
	int day = entry.GetTime().GetDay();
	if (day < 10) {
		std::cout << '0';
	}

	std::cout << day << '.';

	// Month
	int month = MonthConverter::MonthToInt(entry.GetTime().GetMonth());
	if (month < 10) {
		std::cout << '0';
	}
	std::cout << (month + 1) << '.';

	// Year
	std::cout
		<< (entry.GetTime().GetYear() + 1900);
	// ============

	// ============ Sum:
	int major_currency_amount = entry.GetSum() / 100;
	int minor_currency_amount = std::abs(entry.GetSum() % 100);
	
	std::cout
		<< std::setw(6)
		<< std::right
		<< major_currency_amount
		<< '.'
		<< (minor_currency_amount < 10 ? "0" : "")
		<< minor_currency_amount
		<< " UAH,";

	// ============ Category:

	std::cout.width(13);
	std::cout
		<< entry.GetCategory()
		<< ", ";

	// ============ Description:
	std::cout << entry.GetDescription();
	std::cout << std::endl;
}

int GlobalManager::CountBalanceByTime(const Request& request)
{
	int balance = 0;

	auto managers_end = month_managers_.end();
	for (auto i = month_managers_.begin(); i != managers_end; ++i)
	{
		auto iter_begin = i->Begin(&request);
		auto iter_end = i->End(&request);

		for (auto j = iter_begin; j != iter_end; ++j) {
			balance += (*j).GetSum();
		}
	}

	return balance;
}

void GlobalManager::EditEntryByDisplayedId(const Request& prev_request, const int id, std::string& params)
{
	AEntryModificator* modificator = EntryModificatorFactory::Construct(params);
	if (modificator == nullptr) {
		std::cout << "Invalid parameters to edit entry!" << std::endl;
		return;
	}

	OpenManagers(prev_request);
	
	int counter = 0;

	auto managers_end = month_managers_.end();
	for (auto i = month_managers_.begin(); i != managers_end; ++i) {
		auto iter_begin = i->Begin(&prev_request);
		auto iter_end = i->End(&prev_request);

		for (auto j = iter_begin; j != iter_end; ++j) {
			if ((counter + 1) == id) {
				// Modifing entry in the buffer
				int prev_entry_sum = (*j).GetSum();
				try {
					modificator->Modify(*j);
				}
				catch (std::exception& e) {
					std::cerr << e.what() << std::endl
						<< "Unable to modify entry. You must have provided invalid arguments." << std::endl;
				}

				// Adjusting config data with the sum difference
				int new_entry_sum = (*j).GetSum();
				int difference = new_entry_sum - prev_entry_sum;
				ConfigFileManager::AdjustBalance(difference);

				// Displaying result, rewriting files
				DisplayManagersBuffers(prev_request);
				CloseManagers();
				delete modificator;
				return;
			}
			++counter;
		}
	}

	std::cout << "Your id didn't match any entry!\n";
	delete modificator;
	CloseManagers();
}

void GlobalManager::GetRecords(std::string& params)
{
	if (prev_request_ != nullptr) {
		delete prev_request_;
		prev_request_ = nullptr;
	}
	
	prev_request_ = RequestFactory::ConstructRequest(params);

	if (prev_request_ == nullptr) {
		std::cout << "Can't construct request: invalid parameters\n";
		return;
	}

	OpenManagers(*prev_request_);
	SortBuffers();
	DisplayManagersBuffers(*prev_request_);
	CloseManagers();
}

void GlobalManager::EditEntry(std::string& params)
{
	if (prev_request_ == nullptr) {
		std::cout << "There was no valid previous request." << std::endl;
		return;
	}
	std::regex regex("\\d+");
	std::smatch result;
	if(std::regex_search(params, result, regex)) {
		int id = std::stoi(result.str());
		int digits = id / 10;
		params.erase(0, (digits + 1));

		EditEntryByDisplayedId(*prev_request_, id, params);
	}
}

void GlobalManager::AddEntry(std::string& params)
{
	std::string fake_params("/tm:0");
	Request* request = RequestFactory::ConstructTimeRequest(fake_params);
	StringVector* file_names_p = FileNames::ConstructFileNames(*request);
	MonthFileManager* manager = new MonthFileManager(file_names_p->at(0));

	FinanceEntry new_entry;
	AEntryModificator* modificator = EntryModificatorFactory::Construct(params);
	if (modificator == nullptr) {
		std::cout << "Invalid arguments to modify entry." << std::endl;

		delete manager;
		delete file_names_p;
		delete request;
		return;
	}
	try {
		modificator->Modify(new_entry);
	}
	catch (std::exception& e) {
		std::cerr << e.what() 
			<< "Unable to modify entry! You must have provided invalid argumetns." << std::endl;
		
		delete manager;
		delete file_names_p;
		delete request;
		return;
	}
	
	manager->AddEntryToBuffer(new_entry);
	manager->SortBuffer();
	manager->RewriteFileFromBuffer();

	ConfigFileManager::AdjustBalance(new_entry.GetSum());

	delete modificator;
	delete manager;
	delete file_names_p;
	delete request;
}

void GlobalManager::OpenManagers(const Request& request)
{
	StringVector* file_names = FileNames::ConstructFileNames(request);

	std::for_each(file_names->begin(), file_names->end(),
		[&](std::string& name) {
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
	std::experimental::filesystem::directory_iterator dir_iter(FileNames::data_folder_name);

	std::ifstream stream;
	std::string buffer;

	for (auto& file : dir_iter) {
		stream.open(file.path());
		std::getline(stream, buffer);
		stream.close();
		if (buffer.size() == 0) {
			remove(file.path());
		}
	}
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
	if (prev_request_ != nullptr) {
		delete prev_request_;
		prev_request_ = nullptr;
	}

	CloseManagers();
	DeleteEmptyFiles();
}