#include "..\Include\Util\EntryIterator.h"
#include "..\Include\Managers\MonthFileManager.h"
#include "..\Include\Util\FileNames.h"

int main()
{
	Request* request = Request::LastDays(2);

	StringVector* file_names = FileNames::ConstructFileNames(request);

	MonthFileManager* file_manager = new MonthFileManager((*file_names)[0]);

	file_manager->ReadFileToBuffer();

	MonthFileManager::iterator buffer_begin = file_manager->Begin(*request);

	try {
		MonthFileManager::iterator buffer_end = file_manager->End(*request);
		for (auto iter = buffer_begin; iter < buffer_end; ++iter) {
			std::cout << (*iter).Serialize() << std::endl;
		}
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