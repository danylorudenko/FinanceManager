#include "..\Include\Entry\EntryModificator\SumModificator.h"

SumModificator::SumModificator(const std::string& content_to_insert) :
	AEntryModificator(content_to_insert)
{

}

void SumModificator::Modify(FinanceEntry& entry)
{
	int sum = std::stoi(content_to_insert_);
	entry.SetSum(sum);
	if (next_component_ != nullptr) {
		next_component_->Modify(entry);
	}
}