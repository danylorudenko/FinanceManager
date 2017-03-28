#include "..\Include\Entry\EntryConstructor\SumConstructor.h"

SumConstructor::SumConstructor(const std::string& content_to_insert) :
	AEntryConstructor(content_to_insert)
{

}

void SumConstructor::Construct(FinanceEntry& entry)
{
	int sum = std::stoi(content_to_insert_);
	entry.SetSum(sum);
}