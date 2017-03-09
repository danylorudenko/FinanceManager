#include "..\Include\Entry\FinanceEntry.h"

#include <iostream>
#include <vector>

int notmain123465()
{
	printf_s("lol\n");

	std::vector<FinanceEntry> vec;

	FinanceEntry one("Category1", 1000, "Descritpion1");
	FinanceEntry two("Category2", 2000, "Description2");

	vec.push_back(one);

	//vec[0].TestDisplay();
	printf("\n");
	//two.TestDisplay();

	one = two;

	printf("\n\n");
	//vec[0].TestDisplay();

	system("PAUSE");
	return 0;
}