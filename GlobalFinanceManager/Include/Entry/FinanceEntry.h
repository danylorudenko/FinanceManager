#ifndef __FINANCE_ENTRY_H__
#define __FINANCE_ENTRY_H__

#include <string>
#include <fstream>
#include "..\..\Include\Time\TimeHolder.h"
#include "..\..\Include\Enums\EntryType.h"

#include <string>

class FinanceEntry
{
public:
	FinanceEntry() = default;
	FinanceEntry(const FinanceEntry& anotherEntry) = default;
	FinanceEntry(const std::string& category, const int sum,  const std::string& description);

	void EditCategory(const std::string& categoryNew);
	void EditSum(const int newSum);
	void EditDescription(const std::string& newDescription);

	void TestDisplay() const;
	void TestDisplayTime() const;

	bool IsExpence() const;
	bool IsLaterThan(const FinanceEntry& anotherEntry) const;
	bool IsLaterThan(const TimeHolder& time) const;
	bool IsEarlierThan(const FinanceEntry& anotherEntry) const;
	bool IsEarlierThan(const TimeHolder& time) const;

	void Read(std::fstream& fileStream);

	std::string Serialize() const;

private:
	static const char entryStringTerminator;
	
	TimeHolder time_;
	int sum_;
	std::string category_;
	std::string description_;
};

#endif