#include "..\Include\Entry\FinanceEntry.h"
#include <iostream>
#include <iomanip>

int notmain()
{
	std::ofstream testOutFile("testExpences.bin", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
	
	std::string cat("MyCategory");
	std::string descr("MyDescription");
	
	//FinanceEntry* record = FinanceEntry::CreateEntry(EntryType::Expence, cat, 100.0f, descr);
	//record->TestDisplay();
	//
	//record->Write(testOutFile);

	system("PAUSE");
	return 0;
}