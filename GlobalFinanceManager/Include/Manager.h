#ifndef __MANAGER__
#define __MANAGER__

#include <memory>
#include <map>
#include "..\Include\Record\FinanceRecord.h"
#include "..\Include\Enums\Month.h"

class Manager
{
public:
	static Manager& Instance();

	void DisplayDayStats(int day = -1, Month month = Month::NO_MONTH, int year = 0);
	void DisplayWeekStats();
	void DisplayWeekStats(int weekNumber);
	void DisplayMonthStats(Month month = Month::NO_MONTH, int year = 0);

private:
	static Manager* instance;

	using BufferMap = std::map< int, std::shared_ptr<FinanceRecord> >;
	using BufferPair = BufferMap::value_type;

	BufferMap recordsBuffer;

	Manager();
	~Manager();
};

#endif