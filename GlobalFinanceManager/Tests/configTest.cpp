#include "..\Include\Managers\ConfigFileManager.h"
#include "..\Include\Time\MonthConverter.h"

#include <iostream>

int configmain()
{
	const ConfigInfo* info = ConfigFileManager::GetConfigInfo();

	std::cout << MonthConverter::MonthToInt(info->GetFirstValidMonth()) << std::endl
		<< info->GetFirstValidYear() << std::endl
		<< MonthConverter::MonthToInt(info->GetLastValidMonth()) << std::endl
		<< info->GetLastValidYear() << std::endl;

	delete info;
	system("pause");
	return 0;
}