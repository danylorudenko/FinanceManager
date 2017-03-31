#include "..\Include\Entry\FinanceEntry.h"
#include <iostream>
#include <sstream>
#include <exception>
#include <regex>

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
		"(\\d{3})"  				//6	      These sould be passed as a single string to the TimeHolder contstructor
		"(\\|)"						//7
		"(.*)"						//8
		"(\\|)"						//9
		"(-?)"						//10
		"(\\d+)"					//11
		"(\\|)"						//12
		"(.*)"						//13
		"(\\])"						//14
	);
	std::cmatch result;
	std::string buffer;

	std::regex_match(source_string.c_str(), result, regular_expression);

	if (result.size() > 0) {
		
		// TimeHolder initialization
		for (int i = 2; i <= 6; i++) {
			buffer += result[i].str();
		}

		time_ = TimeHolder(buffer);

		// 8 is index of the category string in the regex result
		category_ = result[8].str();

		// 10 and 11 are indicies of the sum string in the regex result
		sum_ = std::stoi(result[10].str() + result[11].str());

		// 13 is index of the description string in the regex result
		description_ = result[13].str();
	}
	else {
		throw std::invalid_argument("FinanceEntry constructor recieved invalid string to deserealize.");
	}
}

void FinanceEntry::SetCategory(const std::string& category)
{
	category_ = category;
}

void FinanceEntry::SetDescription(const std::string& description)
{
	description_ = description;
}

void FinanceEntry::SetSum(const int sum)
{
	sum_ = sum;
}

const TimeHolder& FinanceEntry::GetTime() const
{
	return time_;
}

int FinanceEntry::GetSum() const
{
	return sum_;
}

const std::string& FinanceEntry::GetDescription() const
{
	return description_;
}

const std::string& FinanceEntry::GetCategory() const
{
	return category_;
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

bool FinanceEntry::IsLater(const FinanceEntry& anotherEntry) const
{
	return time_.IsLater(anotherEntry.time_);
}

bool FinanceEntry::IsLater(const TimeHolder& anotherTime) const
{
	return time_.IsLater(anotherTime);
}

bool FinanceEntry::IsLaterOrEquals(const FinanceEntry& anotherEntry) const
{
	return time_.IsLaterOrEquals(anotherEntry.time_);
}

bool FinanceEntry::IsLaterOrEquals(const TimeHolder& anotherTime) const
{
	return time_.IsLaterOrEquals(anotherTime);
}

bool FinanceEntry::IsEarlier(const FinanceEntry& anotherEntry) const
{
	return time_.IsEarlier(anotherEntry.time_);
}

bool FinanceEntry::IsEarlier(const TimeHolder& anotherTime) const
{
	return time_.IsEarlier(anotherTime);
}

bool FinanceEntry::IsEarlierOrEquals(const FinanceEntry& anotherEntry) const
{
	return (time_.IsEarlierOrEquals(anotherEntry.time_));
}

bool FinanceEntry::IsEarlierOrEquals(const TimeHolder& anotherTime) const
{
	return (time_.IsEarlierOrEquals(anotherTime));
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

bool FinanceEntry::DateLessPredicate(const FinanceEntry& lhs, const FinanceEntry& rhs)
{
	return lhs.IsEarlier(rhs);
}

bool FinanceEntry::SumLessPredicate(const FinanceEntry& lhs, const FinanceEntry& rhs)
{
	return lhs.GetSum() < rhs.GetSum();
}

bool FinanceEntry::CategoryLessPredicate(const FinanceEntry& lhs, const FinanceEntry& rhs)
{
	return lhs.category_ < rhs.category_;
}