#ifndef __DESCRIPTION_MODIFICATOR_H__
#define __DESCRIPTION_MODIFICATOR_H__

#include "..\..\..\Include\Entry\EntryModificator\AEntryModificator.h"

class DescriptionModificator : public AEntryModificator
{
public:
	virtual void Modify(FinanceEntry& entry) override;

	DescriptionModificator(const std::string& content_to_insert);
};

#endif