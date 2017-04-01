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
	delete prev_request_;
	prev_request_ = nullptr;
	
	if (params_string == "all") {
		std::cout
			<< "Current balance: "
			<< ConfigFileManager::GetConfigInfo().GetCurrentBalance()
			<< " UAH\n";
	}
	else {
		delete prev_request_;
		prev_request_ = RequestFactory::ConstructTimeRequest(params_string);
		if (prev_request_ == nullptr) {
			std::cout << "Can't construct request with the given arguments.\n";
			return;
		}

		OpenManagers(*prev_request_);
		SortBuffers();
		DisplayManagersBuffers(*prev_request_);

		int balance = CountBalanceByTime(*prev_request_);
		std::cout << "Balance: " << balance << " UAH\n";

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
	int minor_currency_amount = entry.GetSum() % 100;
	
	std::cout
		<< std::setw(6)
		<< std::right
		<< major_currency_amount
		<< ','
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
	OpenManagers(prev_request);
	
	AEntryModificator* modificator = EntryModificatorFactory::Construct(params);
	int counter = 0;

	auto managers_end = month_managers_.end();
	for (auto i = month_managers_.begin(); i != managers_end; ++i) {
		auto iter_begin = i->Begin(&prev_request);
		auto iter_end = i->End(&prev_request);

		for (auto j = iter_begin; j != iter_end; ++j) {
			if ((counter + 1) == id) {
				modificator->Modify(*j);
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
	delete prev_request_;
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
	modificator->Modify(new_entry);

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
	CloseManagers();
	delete prev_request_;
	prev_request_ = nullptr;
	DeleteEmptyFiles();
}