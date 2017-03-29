#ifndef __SUM_MODIFICATOR_H__
#define __SUM_MODIFICATOR_H__

#include "..\..\..\Include\Entry\EntryModificator\AEntryModificator.h"

class SumModificator : public AEntryModificator
{
public:
	virtual void Modify(FinanceEntry& entry) override;

	SumModificator(const std::string& content_to_insert);
};

#endif