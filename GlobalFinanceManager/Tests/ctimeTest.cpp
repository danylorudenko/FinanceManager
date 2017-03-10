#include <iostream>
#include <ctime>
#include "..\Include\Time\TimeHolder.h"

int ctimemain()
{
	tm time;
	time.tm_sec = 0;
	time.tm_min = 0;
	time.tm_hour = 25;
	time.tm_mday = 1;
	time.tm_mon = 0;
	time.tm_year = 70;

	time_t since_epoch = std::mktime(&time);

	std::cout << since_epoch << std::endl;
	
	
	
	system("pause");
	return 0;
}