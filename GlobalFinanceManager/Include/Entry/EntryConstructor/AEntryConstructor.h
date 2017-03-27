#ifndef __ENTRY_CONSTRUCTOR_H__
#define __ENTRY_CONSTRUCTOR_H__

#include "..\..\..\Include\Entry\FinanceEntry.h"

class AEntryConstructor
{
public:
	virtual void Construct(FinanceEntry& entry) = 0;

	AEntryConstructor(const std::string& content_to_insert);

protected:
	std::string content_to_insert_;
};

#endif