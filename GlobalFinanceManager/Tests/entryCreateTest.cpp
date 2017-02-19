#include <iostream>
#include "..\Include\Entry\FinanceEntry.h"

int main()
{
	FinanceEntry testEntry("[5.13.16.3.2016|Sample category|3545|Sample description]");

	testEntry.TestDisplay();

	testEntry.TestDisplayTime();

	system("PAUSE");
	return 0;
}