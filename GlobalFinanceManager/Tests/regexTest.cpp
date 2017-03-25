#include <iostream>
#include <stdexcept>
#include "..\Include\Util\CommandParametersExtractor.h"

int regexmain()
{
	std::string strObj
	(
		"/t:10 /k:asad /r:lol"
	);

	CommandParametersExtractor params(strObj);

	try {
		std::cout << params.TryGetArgument("l") << std::endl;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
	
	
	system("PAUSE");
	return 0;
}