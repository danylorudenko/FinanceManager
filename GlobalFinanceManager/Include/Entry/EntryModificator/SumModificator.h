#ifndef __SUM_MODIFICATOR_H__
#define __SUM_MODIFICATOR_H__

#include "..\..\..\Include\Entry\EntryModificator\AEntryModificator.h"

#include <regex>

class SumModificator : public AEntryModificator
{
public:
	virtual void Modify(FinanceEntry& entry) override;

	SumModificator(const std::string& content_to_insert);

protected:
	static const std::regex regex_sum_;
};

#endif