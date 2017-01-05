#include "..\Include\Entry\FinanceEntry.h"
#include <iostream>
#include <sstream>
#include <exception>

const char FinanceEntry::entryStringTerminator = '\0';

FinanceEntry::FinanceEntry(const EntryType type, const std::string& category, const float sum, const std::string& description) :
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
		<< "Sum: " << sum_ << std::endl
		<< category_ << std::endl
		<< description_ << std::endl;
}

void FinanceEntry::TestDisplayTime() const
{
	std::cout << time_.GetTimeString();
}

void FinanceEntry::EditSum(const float sum)
{
	sum_ = sum;
}

std::string FinanceEntry::Serialize()
{
	std::ostringstream serailizedStringStream;
	serailizedStringStream.setf(std::ios_base::fixed, std::ios_base::floatfield);
	serailizedStringStream.precision(2);
	
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