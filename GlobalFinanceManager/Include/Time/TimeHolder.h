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
	TimeHolder(int min, int hour, int mDay, Month month, int yearSince1900);
	TimeHolder(const std::string& file_string);

	TimeHolder& operator=(const TimeHolder&) = default;
	TimeHolder& operator+(const TimeHolder& rhs) const;
	TimeHolder& operator-(const TimeHolder& rhs) const;

	std::string GetTimeString() const;
	std::string Serialize() const;
	void EditDate(int mDay, int month, int year);
	bool IsToday() const;
	bool IsLaterThan(const TimeHolder& other_holder) const;
	bool IsEarlierThan(const TimeHolder& other_holder) const;

	void ToZero();
	void ToMax();

	int GetMinutes() const;
	int GetHours() const;
	int GetDay() const;
	Month GetMonth() const;
	int GetYear() const;

protected:
	static int GetMinutesInYear(int year);
	unsigned long long ToLongLong() const;

protected:
	int minutes_;
	int hours_;
	int mDay_;
	Month month_;
	int year_;
};

//ctime::strftime - may be useful!

#endif