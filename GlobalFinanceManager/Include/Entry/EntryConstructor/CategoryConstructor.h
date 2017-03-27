#ifndef __CATEGORY_CONSTRUCTOR_H__
#define __CATEGORY_CONSTRUCTOR_H__

#include "..\..\..\Include\Entry\EntryConstructor\AEntryConstructor.h"

class CategoryConstructor : public AEntryConstructor
{
public:
	virtual void Construct(FinanceEntry& entry) override;
};

#endif