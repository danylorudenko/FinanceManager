#include <iostream>
#include "..\Include\Entry\FinanceEntry.h"

int notmain156()
{
	FinanceEntry testEntry(EntryType::Expence, "MyCategory", 50.0f, "MyDescription");

	testEntry.TestDisplay();

	testEntry.TestDisplayTime();

	system("PAUSE");
	return 0;
}