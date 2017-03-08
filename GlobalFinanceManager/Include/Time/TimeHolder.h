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
	static TimeHolder Hour();
	static TimeHolder Day();
	static TimeHolder Week();
	static TimeHolder Month30();

	TimeHolder();
	TimeHolder(const TimeHolder& otherHolder) = default;
	TimeHolder(int min, int hour, int mDay, Month month, int yearSince1900);
	TimeHolder(const std::string& file_string);
	TimeHolder(const long long minutes);

	TimeHolder& operator=(const TimeHolder&) = default;
	TimeHolder operator+(const TimeHolder& rhs) const;
	TimeHolder operator-(const TimeHolder& rhs) const;
	TimeHolder operator*(const int rhs) const;

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

	time_t GetSecondsSinceEpoch() const;

protected:
	int minutes_;
	int hours_;
	int day_in_month_;
	Month month_;
	int year_; // since 1900
};

//ctime::strftime - may be useful!

#endif