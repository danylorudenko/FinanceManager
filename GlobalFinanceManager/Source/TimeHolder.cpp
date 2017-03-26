#include <ctime>
#include <iostream>
#include <sstream>
#include <climits>
#include <regex>
#include <chrono>

#include "..\Include\Time\TimeHolder.h"
#include "..\Include\Time\MonthConverter.h"

TimeHolder::TimeHolder()
{
	time_t timeInSeconds = time(0);
	struct tm currentTime;
	localtime_s(&currentTime, &timeInSeconds);

	day_in_month_ = currentTime.tm_mday;
	month_ = static_cast<Month>(currentTime.tm_mon); 
	year_ = currentTime.tm_year;
}

TimeHolder::TimeHolder(int day_in_month, Month month, int year_since_1900) :
	day_in_month_(day_in_month), month_(month), year_(year_since_1900)
{

}

TimeHolder::TimeHolder(const std::string& source_string)
{
	std::regex regular_expression
	(
		"(\\d{1,2})"	  // 1
		"(\\.)"			  // 2
		"(\\d{1,2})"	  // 3
		"(\\.)"			  // 4
		"(\\d{3})"		  // 5
	);

	std::cmatch result;

	std::regex_search(source_string.c_str(), result, regular_expression);

	if (result.size() > 0) {
		day_in_month_ = std::stoi(result[1].str());

		month_ = static_cast<Month>(std::stoi(result[3].str()));

		year_ = std::stoi(result[5].str());
	}
	else {
		throw std::invalid_argument("TimeHolder constructor recieved ivalid serialized string.");
	}
}

TimeHolder::TimeHolder(const long long seconds_since_epoch)
{
	time_t since_epoch = (seconds_since_epoch);
	tm currentTime;
	localtime_s(&currentTime, &since_epoch);

	day_in_month_ = currentTime.tm_mday;
	month_ = MonthConverter::IntToMonth(currentTime.tm_mon); // tm_mon begins months from 0. But my struct Month - from 1
	year_ = currentTime.tm_year;
}

TimeHolder TimeHolder::Day()
{
	return TimeHolder(86400);
}

TimeHolder TimeHolder::Week()
{
	return TimeHolder(604800);
}

TimeHolder TimeHolder::Month30()
{
	return TimeHolder(2592000);
}

std::string TimeHolder::Serialize() const
{
	std::ostringstream serializedStringStream;

	serializedStringStream
		<< day_in_month_ << '.' 
		<< MonthConverter::MonthToInt(month_) << '.'
		<< year_;

	return serializedStringStream.str();
}

void TimeHolder::SetDate(int mDay, int month, int year)
{
	day_in_month_ = mDay;
	month_ = MonthConverter::IntToMonth(month);
	year_ = year;
}

bool TimeHolder::IsToday() const
{
	time_t timeInSeconds = time(0);
	tm currentTime;
	localtime_s(&currentTime, &timeInSeconds);

	if (currentTime.tm_mday == day_in_month_ &&
		MonthConverter::IntToMonth(currentTime.tm_mon + 1) == month_ &&
		(currentTime.tm_year) == year_)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TimeHolder::IsLater(const TimeHolder& other_holder) const
{
	if (this->GetSecondsSinceEpoch() > other_holder.GetSecondsSinceEpoch()) {
		return true;
	}

	return false;
}

bool TimeHolder::IsLaterOrEquals(const TimeHolder& other_holder) const
{
	if (this->GetSecondsSinceEpoch() >= other_holder.GetSecondsSinceEpoch()) {
		return true;
	}

	return false;
}

bool TimeHolder::IsEarlier(const TimeHolder& other_holder) const
{
	if (this->GetSecondsSinceEpoch() < other_holder.GetSecondsSinceEpoch()) {
		return true;
	}

	return false;
}

bool TimeHolder::IsEarlierOrEquals(const TimeHolder& other_holder) const
{
	if (this->GetSecondsSinceEpoch() <= other_holder.GetSecondsSinceEpoch()) {
		return true;
	}

	return false;
}

bool TimeHolder::operator<(const TimeHolder& rhs) const
{
	return IsEarlier(rhs);
}

bool TimeHolder::operator<=(const TimeHolder& rhs) const
{
	return IsEarlierOrEquals(rhs);
}

bool TimeHolder::operator>(const TimeHolder& rhs) const
{
	return IsLater(rhs);
}

bool TimeHolder::operator>=(const TimeHolder& rhs) const
{
	return IsLaterOrEquals(rhs);
}

time_t TimeHolder::GetSecondsSinceEpoch() const
{
	tm tm_temp;
	
	tm_temp.tm_sec = 0;
	tm_temp.tm_min = 0;
	tm_temp.tm_hour = 0;
	tm_temp.tm_mday = day_in_month_;
	tm_temp.tm_mon = MonthConverter::MonthToInt(month_);
	tm_temp.tm_year = year_;

	return mktime(&tm_temp);
}

TimeHolder& TimeHolder::operator=(const TimeHolder& rhs)
{
	if (this == &rhs) {
		return *this;
	}

	day_in_month_ = rhs.day_in_month_;
	month_ = rhs.month_;
	year_ = rhs.year_;

	return *this;
}

TimeHolder TimeHolder::operator+(const TimeHolder& rhs) const
{
	time_t this_since_epoch = GetSecondsSinceEpoch();
	time_t rhs_since_epoch = rhs.GetSecondsSinceEpoch();

	return TimeHolder(this_since_epoch + rhs_since_epoch);
}

TimeHolder TimeHolder::operator-(const TimeHolder& rhs) const
{
	time_t this_since_epoch = GetSecondsSinceEpoch();
	time_t rhs_since_epoch = rhs.GetSecondsSinceEpoch();
	
	return TimeHolder(this_since_epoch - rhs_since_epoch);
}

TimeHolder TimeHolder::operator*(const int rhs) const
{
	time_t this_since_epoch = GetSecondsSinceEpoch();

	return TimeHolder(this_since_epoch * rhs);
}

int TimeHolder::GetDay() const
{
	return day_in_month_;
}

Month TimeHolder::GetMonth() const
{
	return month_;
}

int TimeHolder::GetYear() const
{
	return year_;
}