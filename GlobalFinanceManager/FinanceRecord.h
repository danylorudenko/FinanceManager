#ifndef __FINANCE_RECORD__
#define __FINANCE_RECORD__

#include <string>
#include "TimeHolder.h"

class FinanceRecord
{
public:
	static FinanceRecord* CreateRecord(bool expence, std::string category, float sum, std::string description);
	void EditCategory(std::string newCategory);
	void EditSum(float newSum);
	void EditDescription(std::string newDescription);

private:
	TimeHolder* time;

	bool expence;
	std::string category;
	float sum;
	std::string description;

private:
	FinanceRecord();
	FinanceRecord(bool expence, std::string category, float sum, std::string description);
	~FinanceRecord();
};

#endif