#include <iostream>
#include "..\Include\Time\TimeHolder.h"

int lolmain()
{
	TimeHolder* holder = new TimeHolder();

	std::cout << holder->Serialize() << std::endl;

	unsigned long long minutes = holder->ToMinutes();
	std::cout << minutes << std::endl;

	TimeHolder* holder2 = new TimeHolder(minutes);
	std::cout << holder2->Serialize() << std::endl;
	std::cout << holder2->ToMinutes() << std::endl;

	delete holder;
	delete holder2;
	system("pause");
	return 0;
}