#include "..\Include\Entry\FinanceEntry.h"

#include <iostream>

int main()
{
	FinanceEntry* entry = new FinanceEntry(EntryType::Expence, "Sample category", 25.4f, "Sample description");

	std::cout << entry->Serialize();

	system("PAUSE");
	return 0;
}