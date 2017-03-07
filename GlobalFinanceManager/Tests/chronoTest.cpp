#include <iostream>
#include <ctime>
#include "..\Include\Time\TimeHolder.h"

int main()
{
	tm time;
	time.tm_sec = 1;
	time.tm_min = 25;
	time.tm_hour = 13;
	time.tm_mday = 1;
	time.tm_mon = 0;
	time.tm_year = 0;

	time_t since_epoch = mktime(&time);

	std::cout << since_epoch << std::endl;
	
	
	
	system("pause");
	return 0;
}