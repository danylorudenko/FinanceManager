#include "..\Include\Managers\ConfigFileManager.h"
#include "..\Include\Time\MonthConverter.h"

#include <iostream>

int configmain()
{
	//ConfigFileManager::LogNewTime(TimeHolder(3, Month::Jul, 115));

	const ConfigInfo* info = &(ConfigFileManager::GetConfigInfo());

	std::cout << MonthConverter::MonthToInt(info->GetFirstEdge().GetMonth()) << std::endl
		<< info->GetFirstEdge().GetYear() << std::endl
		<< MonthConverter::MonthToInt(info->GetLastEdge().GetMonth()) << std::endl
		<< info->GetLastEdge().GetYear() << std::endl;

	delete info;
	system("pause");
	return 0;
}