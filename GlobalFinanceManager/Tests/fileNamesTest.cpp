#include <iostream>

#include "..\Include\Util\FileNames.h"

int main()
{
	Request* request = Request::LastMonths(35);
	
	StringVector* names = FileNames::ConstructFileNames(request);

	for (size_t i = 0; i < names->size(); i++) {
		std::cout << (*names)[i] << std::endl;
	}

	delete names;
	delete request;

	system("pause");
	return 0;
}