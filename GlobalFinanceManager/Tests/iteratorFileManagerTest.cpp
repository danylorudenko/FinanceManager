#include "..\Include\Util\EntryIterator.h"
#include "..\Include\Managers\MonthFileManager.h"
#include "..\Include\Util\FileNames.h"

int iteratormain()
{
	TimeEdgePredicate* time_predicate = TimeEdgePredicate::LastDays(3);
	Request* request = new Request(time_predicate);

	StringVector* file_names = FileNames::ConstructFileNames(*request);

	MonthFileManager* file_manager = new MonthFileManager((*file_names)[0]);

	file_manager->ReadFileToBuffer();

	auto buffer_begin = file_manager->Begin(request);

	try {
		auto buffer_2 = (buffer_begin + 1);

		std::cout << (*buffer_begin).Serialize() << std::endl;
		std::cout << (*buffer_2).Serialize() << std::endl << std::endl;

		/*std::cout << "buffer_begin < buffer_2  == " << (buffer_begin < buffer_2) << std::endl;
		std::cout << "buffer_begin <= buffer_2 == " << (buffer_begin <= buffer_2) << std::endl;
		std::cout << "buffer_begin > buffer_2  == " << (buffer_begin > buffer_2) << std::endl;
		std::cout << "buffer_begin >= buffer_2 == " << (buffer_begin >= buffer_2) << std::endl;
		std::cout << "buffer_begin == buffer_2 == " << (buffer_begin == buffer_2) << std::endl << std::endl << std::endl;

		--buffer_2;

		std::cout << "buffer_begin <= buffer_2 == " << (buffer_begin <= buffer_2) << std::endl;
		std::cout << "buffer_begin >= buffer_2 == " << (buffer_begin >= buffer_2) << std::endl;*/
	}
	catch (std::length_error e) {
		std::cout << e.what() << std::endl;
	}


	delete file_manager;
	delete file_names;
	delete request;


	std::cout << "\n";
	system("pause");
	return 0;
}