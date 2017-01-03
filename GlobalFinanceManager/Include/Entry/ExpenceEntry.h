#ifndef __EXPENCE_ENTRY_H__
#define __EXPENCE_ENTRY_H__

#include "..\..\Include\Entry\FinanceEntry.h"

class ExpenceEntry : public FinanceEntry
{
public:
	ExpenceEntry(ExpenceEntry& anotherEntry);
	ExpenceEntry(const std::string& category, float sum, const std::string& description);
	virtual void EditSum(const float sumNew) override;
	virtual void EditCategory(const std::string& categotyNew) override;
	virtual void EditDescription(const std::string& descriptionNew) override;

	virtual void Write(std::ofstream& outFile) override;
	virtual void Read(std::ifstream& inFile) override;
};

#endif