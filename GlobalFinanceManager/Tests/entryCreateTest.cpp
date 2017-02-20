#include <iostream>
#include "..\Include\Managers\MonthFileManager.h"
int main()
{
	MonthFileManager *manager = new MonthFileManager("file_to_read.txt");
	manager->ReadFileToBuffer();

	manager->TestDisplay();

	system("PAUSE");
	return 0;
}