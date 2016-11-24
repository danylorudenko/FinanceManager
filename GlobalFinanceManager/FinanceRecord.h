#ifndef __FINANCE_RECORD__
#define __FINANCE_RECORD__

#include <string>
#include "TimeHolder.h"
#include "Enums\RecordType.h"

class FinanceRecord
{
public:
	static FinanceRecord* CreateRecord(const RecordType type, const std::string& category, const float sum, const std::string& description);
	virtual void EditCategory(const std::string& categoryNew);
	virtual void EditSum(const float newSum);
	virtual void EditDescription(const std::string& newDescription);

	virtual void TestDisplay() const;

	virtual bool Write() = 0;
	virtual bool Read() = 0;
	FinanceRecord(const FinanceRecord& anotherRecord);
	~FinanceRecord();

protected:
	static const char* fileName;
	static const char stringSeparator; // not sure, if I still need it. May use this symbol in sth else later
	
	FinanceRecord(const std::string& category, float sum, const std::string& description);

	TimeHolder* time = nullptr;
	float sum;
	std::string category;
	std::string description;
};

#endif