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
	// Constructing TimeHolder equivalent of 24-hour period
	static TimeHolder Day();

	// Constructing TimeHolder equivalent of 7-days period
	static TimeHolder Week();

	// Constructing TimeHolder equivalent of 30-days period
	static TimeHolder Month30();

	TimeHolder();
	TimeHolder(const TimeHolder& otherHolder) = default;
	TimeHolder(int mDay, Month month, int yearSince1900);
	TimeHolder(const long long minutes);

	// Constucting TimeHolder instance from serialized string
	TimeHolder(const std::string& file_string);

	TimeHolder& operator=(const TimeHolder& rhs);
	TimeHolder operator+(const TimeHolder& rhs) const;
	TimeHolder operator-(const TimeHolder& rhs) const;
	TimeHolder operator*(const int rhs) const;

	bool operator<(const TimeHolder& rhs) const;
	bool operator>(const TimeHolder& rst) const;

	std::string Serialize() const;

	void SetDate(int mDay, int month, int year);
	bool IsToday() const;
	bool IsLaterThan(const TimeHolder& other_holder) const;
	bool IsEarlierThan(const TimeHolder& other_holder) const;

	int GetDay() const;
	Month GetMonth() const;
	int GetYear() const;

	// Returns time is seconds since 1970
	time_t GetSecondsSinceEpoch() const;

protected:
	int day_in_month_;
	Month month_;
	int year_; // since 1900
};

#endif