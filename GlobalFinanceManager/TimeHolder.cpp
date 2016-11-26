#include "TimeHolder.h"
#include <ctime>
#include <iostream>
#include <sstream>

TimeHolder::TimeHolder()
{
	time_t timeInSeconds = time(0);
	struct tm currentTime;
	localtime_s(&currentTime, &timeInSeconds);

	minutes = currentTime.tm_min;
	hours = currentTime.tm_hour;
	mDay = currentTime.tm_mday;
	month = static_cast<Month>(currentTime.tm_mon);
	year = currentTime.tm_year + 1900;
}

TimeHolder::TimeHolder(int _min, int _hour, int _mDay, Month _month, int _yearSince1900)
{
	minutes = _min;
	hours = _hour;
	mDay = _mDay;
	month = _month;
	year = _yearSince1900;
}

TimeHolder::TimeHolder(char * buffer, int& readPosition)
{
	minutes = *(reinterpret_cast<int*>(readPosition));
	readPosition += sizeof(int);

	hours = *(reinterpret_cast<int*>(readPosition));
	readPosition += sizeof(int);

	mDay = *(reinterpret_cast<int*>(readPosition));
	readPosition += sizeof(int);

	month = *(reinterpret_cast<Month*>(readPosition));
	readPosition += sizeof(Month);

	year = *(reinterpret_cast<int*>(readPosition));
	readPosition += sizeof(int);
}

std::string TimeHolder::GetTimeString() const
{
	std::ostringstream timeStrStream;

	timeStrStream << hours << ":" << 
		minutes << ", " << 
		mDay <<  "." <<
		MonthConverter::MonthToInt(month) << "." << 
		year;

	return timeStrStream.str();
}

void TimeHolder::EditDate(int _mDay, int _month, int _year)
{
	mDay = _mDay;
	month = MonthConverter::IntToMonth(_month);
	year = _year;
}

bool TimeHolder::IsToday() const
{
	time_t timeInSeconds = time(0);
	struct tm currentTime;
	localtime_s(&currentTime, &timeInSeconds);

	if (currentTime.tm_mday == mDay &&
		MonthConverter::IntToMonth(currentTime.tm_mon + 1) == month &&
		(currentTime.tm_year + 1900) == year)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TimeHolder::Write(std::ofstream& fileStream)
{
	//minutes, hours, mDay, month, year
	fileStream.write(reinterpret_cast<const char*>(&minutes), sizeof(decltype(minutes)));
	fileStream.write(reinterpret_cast<const char*>(&hours), sizeof(decltype(hours)));
	fileStream.write(reinterpret_cast<const char*>(&mDay), sizeof(decltype(mDay)));
	fileStream.write(reinterpret_cast<const char*>(&month), sizeof(decltype(month)));
	fileStream.write(reinterpret_cast<const char*>(&year), sizeof(decltype(hours)));
}
