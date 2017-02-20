#include "..\Include\Time\TimeHolder.h"
#include "..\Include\Time\MonthConverter.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <climits>
#include <regex>

TimeHolder::TimeHolder()
{
	time_t timeInSeconds = time(0);
	struct tm currentTime;
	localtime_s(&currentTime, &timeInSeconds);

	minutes_ = currentTime.tm_min;
	hours_ = currentTime.tm_hour;
	mDay_ = currentTime.tm_mday;
	month_ = static_cast<Month>(currentTime.tm_mon);
	year_ = currentTime.tm_year + 1900;
}

TimeHolder::TimeHolder(int min, int hour, int mDay, Month month, int yearSince1900)
{
	minutes_ = min;
	hours_ = hour;
	mDay_ = mDay;
	month_ = month;
	year_ = yearSince1900;
}

TimeHolder::TimeHolder(const std::string& source_string)
{
	std::regex regular_expression
	(
		"(\\d{1,2})"	   // 1
		"(\\.)"			   // 2
		"(\\d{1,2})"	   // 3
		"(\\.)"			   // 4
		"(\\d{1,2})"	   // 5
		"(\\.)"			   // 6
		"(\\d{1,2})"	   // 7
		"(\\.)"			   // 8
		"(\\d{4})"		   // 9
	);

	std::cmatch result;

	std::regex_search(source_string.c_str(), result, regular_expression);

	if (result.size() > 0) {
		minutes_ = std::stoi(result[1].str());

		hours_ = std::stoi(result[3].str());

		mDay_ = std::stoi(result[5].str());

		month_ = static_cast<Month>(std::stoi(result[7].str()));

		year_ = std::stoi(result[9].str());
	}
	else {
		throw std::invalid_argument("TimeHolder constructor recieved ivalid serialized string.");
	}
}

std::string TimeHolder::GetTimeString() const
{
	std::ostringstream timeStrStream;

	timeStrStream << hours_ << ":" << 
		minutes_ << ", " << 
		mDay_ <<  "." <<
		MonthConverter::MonthToInt(month_) << "." << 
		year_;

	return timeStrStream.str();
}

std::string TimeHolder::Serialize() const
{
	std::ostringstream serializedStringStream;

	serializedStringStream 
		<< minutes_ << '.' 
		<< hours_ << '.' 
		<< mDay_ << '.' 
		<< MonthConverter::MonthToInt(month_) << '.'
		<< year_;

	return serializedStringStream.str();
}

void TimeHolder::EditDate(int mDay, int month, int year)
{
	mDay_ = mDay;
	month_ = MonthConverter::IntToMonth(month);
	year_ = year;
}

bool TimeHolder::IsToday() const
{
	time_t timeInSeconds = time(0);
	struct tm currentTime;
	localtime_s(&currentTime, &timeInSeconds);

	if (currentTime.tm_mday == mDay_ &&
		MonthConverter::IntToMonth(currentTime.tm_mon + 1) == month_ &&
		(currentTime.tm_year + 1900) == year_)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TimeHolder::IsLaterThan(const TimeHolder& other_holder) const
{
	if (year_ > other_holder.year_) return true;
	if (month_ > other_holder.month_) return true;
	if (mDay_ > other_holder.mDay_) return true;
	if (hours_ > other_holder.hours_) return true;
	if (minutes_ > other_holder.minutes_) return true;

	return false;
}

bool TimeHolder::IsEarlierThan(const TimeHolder& other_holder) const
{
	return !(TimeHolder::IsLaterThan(other_holder));
}

void TimeHolder::ToZero()
{
	minutes_ = INT_MIN;
	hours_ = INT_MIN;
	mDay_ = INT_MIN;
	month_ = Month::NO_MONTH;
	year_ = INT_MIN;
}

void TimeHolder::ToMax()
{
	minutes_ = INT_MAX;
	hours_ = INT_MAX;
	mDay_ = INT_MAX;
	month_ = Month::Dec;
	year_ = INT_MAX;
}
