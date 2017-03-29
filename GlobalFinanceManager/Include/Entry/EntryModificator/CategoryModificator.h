#ifndef __CATEGORY_MODIFICATOR_H__
#define __CATEGORY_MODIFICATOR_H__

#include "..\..\..\Include\Entry\EntryModificator\AEntryModificator.h"

class CategoryModificator : public AEntryModificator
{
public:
	virtual void Modify(FinanceEntry& entry) override;

	CategoryModificator(const std::string& content_to_insert);
};

#endif