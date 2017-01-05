#ifndef __TIME_HOLDER_H__
#define __TIME_HOLDER_H__

#include <string>
#include <fstream>
#include "..\..\Include\Enums\Month.h"

class TimeHolder
{
public:
	TimeHolder();
	TimeHolder(TimeHolder& otherHolder) = default;
	TimeHolder(int min, int hour, int mDay, Month month, int yearSince1900);
	TimeHolder(char* buffer, int& readingPosition);

	TimeHolder& operator=(TimeHolder&) = default;

	std::string GetTimeString() const;
	std::string Serialize() const;
	void EditDate(int mDay, int month, int year);
	bool IsToday() const;

	std::string Serialize();

private:

	int minutes_;
	int hours_;
	int mDay_;
	Month month_;
	int year_;
};

//ctime::strftime - may be useful!

#endif