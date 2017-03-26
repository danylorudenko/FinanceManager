#ifndef __FINANCE_ENTRY_H__
#define __FINANCE_ENTRY_H__

#include <string>
#include "..\..\Include\Time\TimeHolder.h"

/*
	Class represents basic finance entry
*/
class FinanceEntry
{
public:
	FinanceEntry() = default;
	FinanceEntry(const FinanceEntry& anotherEntry) = default;
	FinanceEntry(const std::string& category, const int sum,  const std::string& description);

	// Constructs FinanceEntry instance from the formatted string from the file
	explicit FinanceEntry(const std::string& source_string);

	// Serializes instance to the string ready to be written in file
	std::string Serialize() const;

	void SetCategory(const std::string& categoryNew);
	void SetSum(const int newSum);
	void SetDescription(const std::string& newDescription);

	const TimeHolder& GetTime() const;
	int GetSum() const;
	const std::string& GetCategory() const;
	const std::string& GetDescription() const;

	// Does this record has negative sum value?
	bool IsExpence() const;
	bool IsLater(const FinanceEntry& anotherEntry) const;
	bool IsLater(const TimeHolder& time) const;
	bool IsLaterOrEquals(const FinanceEntry& anotherEntry) const;
	bool IsLaterOrEquals(const TimeHolder& time) const;
	bool IsEarlier(const FinanceEntry& anotherEntry) const;
	bool IsEarlier(const TimeHolder& time) const;
	bool IsEarlierOrEquals(const FinanceEntry& anotherEntry) const;
	bool IsEarlierOrEquals(const TimeHolder& time) const;

	static bool DateLessPredicate(const FinanceEntry& lhs, const FinanceEntry& rhs);
	static bool SumLessPredicate(const FinanceEntry& lhs, const FinanceEntry& rhs);
	static bool CategoryLessPredicate(const FinanceEntry& lhs, const FinanceEntry& rhs);

protected:
	
	TimeHolder time_;
	int sum_;
	std::string category_;
	std::string description_;
};

#endif