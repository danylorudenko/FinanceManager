#include "FinanceRecord.h"

FinanceRecord* FinanceRecord::CreateRecord(bool expence, std::string category, float sum, std::string description = "")
{
	return new FinanceRecord(expence, category, sum, description);
}

FinanceRecord::FinanceRecord()
{
	time = TimeHolder::WriteCurrentTime();
}

FinanceRecord::FinanceRecord(bool newExpence, std::string newCategory, float newSum, std::string newDescription) :
	expence(newExpence), category(newCategory), sum(newSum), description(newDescription)
{
	time = TimeHolder::WriteCurrentTime();
}

FinanceRecord::~FinanceRecord()
{
	delete time;
}

void FinanceRecord::EditCategory(std::string newCategory)
{
	category = newCategory;
}

void FinanceRecord::EditDescription(std::string newDescription)
{
	description = newDescription;
}

void FinanceRecord::EditSum(float newSum)
{
	sum = newSum;
}
