#include "..\Include\Entry\EntryModificator\SumModificator.h"
#include <stdexcept>
#include <iostream>

const std::regex SumModificator::regex_sum_ = std::regex
(
	"(-?)"		// 1
	"(\\d+)"	// 2
	"(\\.)"		// 3
	"(\\d{2})"	// 4
);

SumModificator::SumModificator(const std::string& content_to_insert) :
	AEntryModificator(content_to_insert)
{

}

void SumModificator::Modify(FinanceEntry& entry)
{
	std::smatch result;
	if(std::regex_search(content_to_insert_, result, regex_sum_)) {
		int major_currency = 0;
		int minor_currency = 0;

		try {
			major_currency = std::stoi((result[1].str() + result[2].str()));
			minor_currency = std::stoi(result[4].str());
		}
		catch (std::invalid_argument& e) {
			std::cerr << e.what() << std::endl
				<< "Invalid format of the /s value." << std::endl;
			throw;
		}
		catch (std::out_of_range& e) {
			std::cerr << e.what() << std::endl
				<< "Value passed to /s is too large." << std::endl;
			throw;
		}

		int raw_sum = (major_currency * 100) + minor_currency;
		entry.SetSum(raw_sum);
		if (next_component_ != nullptr) {
			next_component_->Modify(entry);
		}
	}
	else {
		throw std::invalid_argument("Invalid /s argument provided.");
	}
}