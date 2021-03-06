#include <iostream>
#include "..\Include\Util\EntryIterator.h"
#include "..\Include\Util\Request\ComplexPredicate\SumTypePredicate.h"
#include "..\Include\Managers\MonthFileManager.h"
#include "..\Include\Util\FileNames.h"

int monthFileManagermain()
{
	TimeEdgePredicate* time_predicate = TimeEdgePredicate::LastWeeks(2);

	Request* request = new Request(time_predicate);
	request->Decorate(new SumTypePredicate(EntrySumType::Income));

	StringVector* file_names = FileNames::ConstructFileNames(*request);

	MonthFileManager* manager = new MonthFileManager((*file_names)[0]);

	manager->ReadFileToBuffer();

	manager->SortBuffer();

	auto iter_begin = manager->Begin(request);
	auto iter_end = manager->End(request);

	try {
		int counter = 1;
		for (auto i = iter_begin; i != iter_end; ++i) {
			std::cout << counter << ". " << (*i).Serialize() << std::endl;
			++counter;
		}

		int input_index;
		std::string input_string;
		
		std::cout << "Index: ";
		std::cin >> input_string;
		input_index = std::stoi(input_string) - 1;

		std::cout << "New description: ";
		std::cin >> input_string;
		(*(iter_begin + input_index)).SetDescription(input_string);

		manager->RewriteFileFromBuffer();
		manager->ReadFileToBuffer();

		iter_begin = manager->Begin(request);
		iter_end = manager->End(request);

		counter = 1;
		for (auto i = iter_begin; i != iter_end; ++i) {
			std::cout << counter << ". " << (*i).Serialize() << std::endl;
			++counter;
		}

	}
	catch (std::length_error e) {
		std::cout << e.what() << std::endl;
	}

	delete manager;
	delete file_names;
	delete request;

	std::cout << "\n\n";
	system("pause");
	return 0;
}