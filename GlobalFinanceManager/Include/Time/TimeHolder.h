#ifndef __TIME_HOLDER_H__
#define __TIME_HOLDER_H__

#include <string>
#include <fstream>
#include "..\..\Include\Enums\Month.h"

/*
	Class that holds data to describe single time point.
	The maximum precision is one minute
*/
class TimeHolder
{
public:
	TimeHolder();
	TimeHolder(const TimeHolder& otherHolder) = default;
	TimeHolder(int min, int hour, int mDay, Month month, int yearSince1970);
	TimeHolder(const std::string& file_string);
	TimeHolder(const long long minutes);

	TimeHolder& operator=(const TimeHolder&) = default;
	TimeHolder& operator+(const TimeHolder& rhs) const;
	TimeHolder& operator-(const TimeHolder& rhs) const;

	std::string GetTimeString() const;
	std::string Serialize() const;
	void EditDate(int mDay, int month, int year);
	bool IsToday() const;
	bool IsLaterThan(const TimeHolder& other_holder) const;
	bool IsEarlierThan(const TimeHolder& other_holder) const;

	// Set all data to minimum values
	void ToMin();

	// Set all data to maximum values
	void ToMax();

	int GetMinutes() const;
	int GetHours() const;
	int GetDay() const;
	Month GetMonth() const;
	int GetYear() const;

	static const int minutes_in_leap_year = 366 * 24 * 60;
	static const int minutes_in_regular_year = 365 * 24 * 60;
	static const int minutes_in_day = 24 * 60;
	static const int minutes_in_hour = 60;

protected:

	// Get amount of minutes in all years from 0 to year argument
	static long long GetMinutesPassedInYear(const int year);

public:
	// Get minutes representation of date in the TimeHolder
	long long ToMinutes() const;

protected:
	int minutes_;
	int hours_;
	int day_in_month_;
	Month month_;
	int year_; // since 1970
};

//ctime::strftime - may be useful!

#endif