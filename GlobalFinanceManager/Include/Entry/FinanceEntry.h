#ifndef __FINANCE_ENTRY_H__
#define __FINANCE_ENTRY_H__

#include <string>
#include <fstream>
#include "..\..\Include\Entry\Time\TimeHolder.h"
#include "..\..\Include\Enums\EntryType.h"

class FinanceEntry
{
public:
	static FinanceEntry* CreateEntry(const EntryType type, const std::string& category, const float sum, const std::string& description);
	virtual void EditCategory(const std::string& categoryNew);
	virtual void EditSum(const float newSum);
	virtual void EditDescription(const std::string& newDescription);

	virtual void TestDisplay() const;

	virtual void Write(std::ofstream& outFile) = 0;
	virtual void Read(std::ifstream& inFile) = 0;

protected:
	static const char recordStringTerminator;
	
	FinanceEntry(const std::string& category, float sum, const std::string& description);
	FinanceEntry(FinanceEntry& anotherEntry) = default;
	static void WriteString(std::ofstream& outFile, std::string str, int limit);

	TimeHolder time;
	float sum;
	std::string category;
	std::string description;
};

#endif