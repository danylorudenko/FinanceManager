#ifndef __TIME_HOLDER__
#define __TIME_HOLDER__

#include <string>
#include <fstream>
#include "Enums\Months.h"

class TimeHolder
{
public:
	TimeHolder();
	TimeHolder(TimeHolder& otherHolder) = default;
	TimeHolder(int min, int hour, int mDay, Month month, int yearSince1900);
	TimeHolder(char* buffer, int& readingPosition);

	TimeHolder& operator=(TimeHolder&) = default;

	std::string GetTimeString() const;
	void EditDate(int mDay, int month, int year);
	bool IsToday() const;

	void Write(std::ofstream& fileStream);

private:

	int minutes;
	int hours;
	int mDay;
	Month month;
	int year;
};

//ctime::strftime - may be useful!

#endif