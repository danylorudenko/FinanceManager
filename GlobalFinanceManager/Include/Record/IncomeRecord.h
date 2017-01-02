#ifndef __INCOME_RECORD_H__
#define __INCOME_RECORD_H__

#include <string>
#include "..\..\Include\Record\FinanceRecord.h"

class IncomeRecord : public FinanceRecord
{
public:
	IncomeRecord(const IncomeRecord& anotherRecord);
	IncomeRecord(const std::string& category, float sum, const std::string& description);
	virtual void EditSum(const float sumNew) override;
	virtual void EditCategory(const std::string& categotyNew) override;
	virtual void EditDescription(const std::string& descriptionNew) override;

	virtual void Write(std::ofstream& outFile) override;
	virtual void Read(std::ifstream& inFile) override;
};

#endif