#include <iostream>
#include <algorithm>
#include "..\Include\Managers\MonthFileManager.h"
int main()
{
	MonthFileManager *manager = new MonthFileManager("file_to_read.txt");
	manager->ReadFileToBuffer();

	// manager->TestDisplay();

	//Request* request = new Request(TimeHolder(0, 0, 0, Month::Jan, 116), Request::Direction::Forward);
	Request* request = new Request();

	auto selection = manager->RequestEntries(*request);

	manager->EditEntrySum((*selection)[0], 1000);

	manager->RewriteFileFromBuffer();
	manager->ReadFileToBuffer();
	manager->TestDisplay();

	system("PAUSE");
	return 0;
}