#include "..\Include\Entry\FinanceEntry.h"
#include <iostream>
#include <sstream>
#include <exception>

const char FinanceEntry::entryStringTerminator = '\0';

FinanceEntry::FinanceEntry(const EntryType type, const std::string& category, const int sum, const std::string& description) :
	type_(type), category_(category), sum_(sum), description_(description) { }

void FinanceEntry::EditCategory(const std::string& category)
{
	category_ = category;
}

void FinanceEntry::EditDescription(const std::string& description)
{
	description_ = description;
}

void FinanceEntry::TestDisplay() const
{
	std::cout 
		<< time_.GetTimeString() << std::endl
		<< "Sum: " << sum_ / 100 << '.' << sum_ % 100 << std::endl
		<< category_ << std::endl
		<< description_ << std::endl;
}

void FinanceEntry::TestDisplayTime() const
{
	std::cout << time_.GetTimeString();
}

void FinanceEntry::EditSum(const int sum)
{
	sum_ = sum;
}

bool FinanceEntry::IsExpence() const
{
	if (sum_ > 0) {
		return false;
	}
	else {
		return true;
	}
}

bool FinanceEntry::IsLaterThan(const FinanceEntry& anotherEntry) const
{
	return time_.IsLaterThan(anotherEntry.time_);
}

std::string FinanceEntry::Serialize() const
{
	std::ostringstream serailizedStringStream;
	
	serailizedStringStream << '[';

	serailizedStringStream
		<< time_.Serialize()
		<< '|'
		<< category_
		<< '|'
		<< sum_
		<< '|'
		<< description_;


	serailizedStringStream << ']';
	return serailizedStringStream.str();
}