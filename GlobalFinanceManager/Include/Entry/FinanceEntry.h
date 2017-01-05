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
	FinanceEntry(const EntryType type, const std::string& category, const float sum,  const std::string& description);
	FinanceEntry(FinanceEntry& anotherEntry) = default;

	virtual void EditCategory(const std::string& categoryNew);
	virtual void EditSum(const float newSum);
	virtual void EditDescription(const std::string& newDescription);

	virtual void TestDisplay() const;
	virtual void TestDisplayTime() const;

	virtual std::string Serialize();

protected:
	static const char entryStringTerminator;
	
	EntryType type_;
	TimeHolder time_;
	float sum_;
	std::string category_;
	std::string description_;
};

#endif