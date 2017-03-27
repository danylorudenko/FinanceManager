#include "..\Include\Entry\EntryConstructor\SumConstructor.h"

void SumConstructor::Construct(FinanceEntry& entry)
{
	int sum = std::stoi(content_to_insert_);
	entry.SetSum(sum);
}