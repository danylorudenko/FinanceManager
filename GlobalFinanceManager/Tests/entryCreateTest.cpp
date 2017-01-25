#include <iostream>
#include "..\Include\Entry\FinanceEntry.h"

int notmain156()
{
	FinanceEntry testEntry("MyCategory", 500, "MyDescription");

	testEntry.TestDisplay();

	testEntry.TestDisplayTime();

	system("PAUSE");
	return 0;
}