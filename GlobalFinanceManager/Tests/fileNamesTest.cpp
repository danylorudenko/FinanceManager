#include <iostream>
#include <fstream>

#include "..\Include\Util\FileNames.h"

int fileNmaesmain()
{
	TimeEdgePredicate* time_predicate = TimeEdgePredicate::LastMonths();
	Request* request = new Request(time_predicate);
	
	StringVector* names = FileNames::ConstructFileNames(*request);

	for (size_t i = 0; i < names->size(); i++) {
		std::cout << (*names)[i] << std::endl;
	}

	delete names;
	delete request;

	system("pause");
	return 0;
}