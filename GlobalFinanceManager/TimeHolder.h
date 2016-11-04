#ifndef __TIME_HOLDER__
#define __TIME_HOLDER__

#include <string>

class TimeHolder
{
public:
	static TimeHolder* WriteCurrentTime();
	std::string GetTimeString() const;
	void EditDate(int mDay, int mounth, int year);
	bool IsToday(TimeHolder toCheck) const;

private:
	TimeHolder(int min, int hour, int mDay, int month, int yearSince1900);
	TimeHolder();

	int minutes;
	int hours;
	int mDay;
	int month;
	int year;
};

//ctime::strftime - may be useful!

#endif