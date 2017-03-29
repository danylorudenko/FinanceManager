#ifndef __ENTRY_MODIFICATOR_H__
#define __ENTRY_MODIFICATOR_H__

#include "..\..\..\Include\Entry\FinanceEntry.h"

class AEntryModificator
{
public:
	virtual void Modify(FinanceEntry& entry) = 0;
	void Decorate(AEntryModificator* next_component);

	AEntryModificator(const std::string& content_to_insert);
	virtual ~AEntryModificator();

protected:
	std::string content_to_insert_;

	AEntryModificator* next_component_;
};

#endif