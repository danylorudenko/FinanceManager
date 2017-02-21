#ifndef __FINANCE_ENTRY_H__
#define __FINANCE_ENTRY_H__

#include <string>
#include "..\..\Include\Time\TimeHolder.h"

#include <string>


/*
	Class represents basic finance entry
*/
class FinanceEntry
{
public:
	FinanceEntry() = default;
	FinanceEntry(const FinanceEntry& anotherEntry) = default;
	FinanceEntry(const std::string& category, const int sum,  const std::string& description);
	FinanceEntry(const std::string& source_string);

	void EditCategory(const std::string& categoryNew);
	void EditSum(const int newSum);
	void EditDescription(const std::string& newDescription);

	void TestDisplay() const;
	void TestDisplayTime() const;

	// Does this record has negative sum value?
	bool IsExpence() const;
	bool IsLaterThan(const FinanceEntry& anotherEntry) const;
	bool IsLaterThan(const TimeHolder& time) const;
	bool IsEarlierThan(const FinanceEntry& anotherEntry) const;
	bool IsEarlierThan(const TimeHolder& time) const;

	std::string Serialize() const;

private:
	static const char entryStringTerminator;
	
	TimeHolder time_;
	int sum_;
	std::string category_;
	std::string description_;
};

#endif