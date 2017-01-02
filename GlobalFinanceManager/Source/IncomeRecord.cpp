#include "..\Include\Record\IncomeRecord.h"

IncomeRecord::IncomeRecord(const IncomeRecord & anotherRecord) : FinanceRecord(anotherRecord) { }

IncomeRecord::IncomeRecord(const std::string& category, float sum, const std::string& description) :
	FinanceRecord(category, sum, description) { }

void IncomeRecord::EditSum(const float sumNew)
{
	FinanceRecord::EditSum(sumNew);
}

void IncomeRecord::EditCategory(const std::string & categotyNew)
{
	FinanceRecord::EditCategory(categotyNew);
}

void IncomeRecord::EditDescription(const std::string & descriptionNew)
{
	FinanceRecord::EditDescription(descriptionNew);
}

bool IncomeRecord::Write()
{
	return false;
}

bool IncomeRecord::Read()
{
	return false;
}


