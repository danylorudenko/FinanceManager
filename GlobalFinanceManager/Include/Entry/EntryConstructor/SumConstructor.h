#ifndef __SUM_CONSTRUCTOR_H__
#define __SUM_CONSTRUCTOR_H__

#include "..\..\..\Include\Entry\EntryConstructor\AEntryConstructor.h"

class SumConstructor : public AEntryConstructor
{
public:
	virtual void Construct(FinanceEntry& entry) override;
};

#endif