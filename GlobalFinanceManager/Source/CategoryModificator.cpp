#include "..\Include\Entry\EntryModificator\CategoryModificator.h"

CategoryModificator::CategoryModificator(const std::string& content_to_insert) :
	AEntryModificator(content_to_insert)
{

}

void CategoryModificator::Modify(FinanceEntry& entry)
{
	entry.SetCategory(content_to_insert_);
	if (next_component_ != nullptr) {
		next_component_->Modify(entry);
	}
}