#include "..\Include\Entry\IncomeEntry.h"

IncomeEntry::IncomeEntry(IncomeEntry & anotherEntry) : FinanceEntry(anotherEntry) { }

IncomeEntry::IncomeEntry(const std::string& category, float sum, const std::string& description) :
	FinanceEntry(category, sum, description) { }

void IncomeEntry::EditSum(const float sumNew)
{
	FinanceEntry::EditSum(sumNew);
}

void IncomeEntry::EditCategory(const std::string & categotyNew)
{
	FinanceEntry::EditCategory(categotyNew);
}

void IncomeEntry::EditDescription(const std::string & descriptionNew)
{
	FinanceEntry::EditDescription(descriptionNew);
}

void IncomeEntry::Write(std::ofstream& outFile)
{

}

void IncomeEntry::Read(std::ifstream& inFile)
{
	
}


