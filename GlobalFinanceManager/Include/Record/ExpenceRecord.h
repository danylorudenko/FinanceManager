#ifndef __EXPENCE_RECORD_H__
#define __EXPENCE_RECORD_H__

#include "..\..\Include\Record\FinanceRecord.h"

class ExpenceRecord : public FinanceRecord
{
public:
	ExpenceRecord(const ExpenceRecord& anotherRecord);
	ExpenceRecord(const std::string& category, float sum, const std::string& description);
	virtual void EditSum(const float sumNew) override;
	virtual void EditCategory(const std::string& categotyNew) override;
	virtual void EditDescription(const std::string& descriptionNew) override;

	virtual void Write(std::ofstream& outFile) override;
	virtual void Read(std::ifstream& inFile) override;
};

#endif