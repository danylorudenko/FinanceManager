#ifndef __DESCRIPTION_CONSTRUCTOR_H__
#define __DESCRIPTION_CONSTRUCTOR_H__

#include "..\..\..\Include\Entry\EntryConstructor\AEntryConstructor.h"

class DescriptionConstructor : public AEntryConstructor
{
public:
	virtual void Construct(FinanceEntry& entry) override;
};

#endif