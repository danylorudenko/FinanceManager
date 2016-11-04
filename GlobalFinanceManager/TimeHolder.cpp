#include "TimeHolder.h"
#include <ctime>

TimeHolder::TimeHolder(int min, int hour, int mDay, int month, int yearSince1900)
{
	minutes = min;
	hours = hour;
	this->mDay = mDay;
	this->month = month;
	year = yearSince1900;
}

TimeHolder* TimeHolder::WriteCurrentTime()
{
	time_t timeInSeconds = time(0);
	struct tm currentTime;
	localtime_s(&currentTime, &timeInSeconds);

	TimeHolder *holder = new TimeHolder(currentTime.tm_min,
										currentTime.tm_hour,
										currentTime.tm_mday, 
										currentTime.tm_mon, 
										currentTime.tm_year + 1900);
	return holder;
}

std::string TimeHolder::GetTimeString() const
{
	std::string timeString = hours + ":" + minutes;
	timeString += ",  " + mDay;
	timeString += "." + month;
	timeString += "." + year;

	return timeString;
}

void TimeHolder::EditDate(int mDay, int month, int year)
{
	this->mDay = mDay;
	this->month = month;
	this->year = year;
}

bool TimeHolder::IsToday(TimeHolder toCheck) const
{
	time_t timeInSeconds = time(0);
	struct tm currentTime;
	localtime_s(&currentTime, &timeInSeconds);

	if (currentTime.tm_mday == toCheck.mDay &&
		currentTime.tm_mon == toCheck.month &&
		(currentTime.tm_year + 1900) == toCheck.year)
	{
		return true;
	}
	else
	{
		return false;
	}
}
