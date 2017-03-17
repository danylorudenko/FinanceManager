#include "..\Include\Util\EntryIterator.h"
#include "..\Include\Managers\MonthFileManager.h"
#include "..\Include\Util\FileNames.h"

int main()
{
	Request* request = Request::LastDays(2);

	StringVector* file_names = FileNames::ConstructFileNames(request);

	MonthFileManager* file_manager = new MonthFileManager((*file_names)[0]);

	file_manager->ReadFileToBuffer();

	MonthFileManager::iterator buffer_iter = file_manager->Begin(*request);

	try {
		std::cout << (*buffer_iter).Serialize << std::endl;
		buffer_iter++;
	}
	catch (std::length_error e) {
		std::cout << e.what() << std::endl;
	}


	delete file_manager;
	delete file_names;
	delete request;

	system("pause");
	return 0;
}