#include "..\Include\Managers\MonthFileManager.h"
#include "..\Include\Util\FileNames.h"

int motnhmain()
{
	Request* request = Request::LastDays();
	
	StringVector* file_names = FileNames::ConstructFileNames(request);

	MonthFileManager* file_manager = new MonthFileManager((*file_names)[0]);

	file_manager->ReadFileToBuffer();

	delete file_manager;
	delete file_names;
	delete request;

	system("pause");
	return 0;
}