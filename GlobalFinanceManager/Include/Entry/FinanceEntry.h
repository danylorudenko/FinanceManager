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
	FinanceEntry(const EntryType type, const std::string& category, const int sum,  const std::string& description);
	FinanceEntry(FinanceEntry& anotherEntry) = default;

	virtual void EditCategory(const std::string& categoryNew);
	virtual void EditSum(const int newSum);
	virtual void EditDescription(const std::string& newDescription);

	virtual void TestDisplay() const;
	virtual void TestDisplayTime() const;

	virtual bool IsExpence() const;
	virtual bool IsLaterThan(const FinanceEntry& anotherEntry) const;

	virtual std::string Serialize() const;

private:
	static const char entryStringTerminator;
	
	EntryType type_;
	TimeHolder time_;
	int sum_;
	std::string category_;
	std::string description_;
};

#endif