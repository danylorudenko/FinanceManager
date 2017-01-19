#include "..\Include\Time\TimeHolder.h"
#include "..\Include\Time\MonthConverter.h"
#include <ctime>
#include <iostream>
#include <sstream>

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

TimeHolder::TimeHolder(char* buffer, int& readPosition)
{
	minutes_ = *(reinterpret_cast<int*>(readPosition));
	readPosition += sizeof(int);

	hours_ = *(reinterpret_cast<int*>(readPosition));
	readPosition += sizeof(int);

	mDay_ = *(reinterpret_cast<int*>(readPosition));
	readPosition += sizeof(int);

	month_ = *(reinterpret_cast<Month*>(readPosition));
	readPosition += sizeof(Month);

	year_ = *(reinterpret_cast<int*>(readPosition));
	readPosition += sizeof(int);
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
