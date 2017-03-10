#include <iostream>
#include "..\Include\Time\TimeHolder.h"

int main()
{
	TimeHolder holder;
	std::cout << holder.Serialize() << std::endl;

	system("pause");
	return 0;
}