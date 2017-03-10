#include <iostream>
#include "..\Include\Time\TimeHolder.h"

int timeholdermain()
{
	TimeHolder* holder = new TimeHolder();

	std::cout << holder->Serialize() << std::endl;

	std::cout << (*holder - (TimeHolder::Day() * 4)).Serialize() << std::endl;

	delete holder;
	system("pause");
	return 0;
}