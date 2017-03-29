#include "..\Include\Entry\EntryModificator\DescriptionModificator.h"

DescriptionModificator::DescriptionModificator(const std::string& content_to_insert) :
	AEntryModificator(content_to_insert)
{

}

void DescriptionModificator::Modify(FinanceEntry& entry)
{
	entry.SetDescription(content_to_insert_);
	if (next_component_ != nullptr) {
		next_component_->Modify(entry);
	}
}