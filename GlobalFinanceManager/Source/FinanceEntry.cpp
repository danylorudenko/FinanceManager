#include "..\Include\Entry\FinanceEntry.h"
#include <iostream>
#include <sstream>
#include <exception>
#include <regex>

const char FinanceEntry::entryStringTerminator = '\0';

FinanceEntry::FinanceEntry(const std::string& category, const int sum, const std::string& description) :
	category_(category), sum_(sum), description_(description) { }

FinanceEntry::FinanceEntry(const std::string& source_string)
{
	// Regular expression for serialized finance entry from the file
	std::regex regular_expression
	(
		"(\\[)"						//1
		"(\\d{1,2})"				//2		  These sould be passed as a single string to the TimeHolder contstructor
		"(\\.)"						//3		  These sould be passed as a single string to the TimeHolder contstructor
		"(\\d{1,2})"				//4		  These sould be passed as a single string to the TimeHolder contstructor
		"(\\.)"						//5		  These sould be passed as a single string to the TimeHolder contstructor
		"(\\d{1,2})"				//6		  These sould be passed as a single string to the TimeHolder contstructor
		"(\\.)"						//7		  These sould be passed as a single string to the TimeHolder contstructor
		"(\\d{1,2})"				//8		  These sould be passed as a single string to the TimeHolder contstructor
		"(\\.)"						//9		  These sould be passed as a single string to the TimeHolder contstructor
		"(\\d{4})"					//10	  These sould be passed as a single string to the TimeHolder contstructor
		"(\\|)"						//11
		"(.+)"						//12
		"(\\|)"						//13
		"(\\d+)"					//14
		"(\\|)"						//15
		"(.+)"						//16
		"(\\])"						//17
	);
	std::cmatch result;
	std::string buffer;

	std::regex_match(source_string.c_str(), result, regular_expression);

	if (result.size() > 0) {
		
		// TimeHolder initialization
		for (int i = 2; i <= 10; i++) {
			buffer += result[i].str();
		}

		time_ = TimeHolder(buffer);

		// 12 is index of the category string in the regex result
		category_ = result[12].str();

		// 14 is index of the sum string in the regex result
		sum_ = std::stoi(result[14].str());

		// 16 is index of the description string in the regex result
		description_ = result[16].str();
	}
	else {
		throw std::invalid_argument("FinanceEntry constructor recieved invalid string to deserealize.");
	}
}

void FinanceEntry::EditCategory(const std::string& category)
{
	category_ = category;
}

void FinanceEntry::EditDescription(const std::string& description)
{
	description_ = description;
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

bool FinanceEntry::IsLaterThan(const TimeHolder& anotherTime) const
{
	return time_.IsLaterThan(anotherTime);
}

bool FinanceEntry::IsEarlierThan(const FinanceEntry& anotherEntry) const
{
	return !(FinanceEntry::IsLaterThan(anotherEntry));
}

bool FinanceEntry::IsEarlierThan(const TimeHolder& anotherTime) const
{
	return !(time_.IsLaterThan(anotherTime));
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