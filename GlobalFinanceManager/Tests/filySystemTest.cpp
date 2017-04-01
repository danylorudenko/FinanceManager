#include <iostream>
#include "..\Include\Managers\GlobalManager.h"


int fileSystemmain()
{
	GlobalManager* glob_manager = new GlobalManager();

	//glob_manager->DeleteEmptyFiles();
	
	delete glob_manager;

	system("pause");
	return 0;
}