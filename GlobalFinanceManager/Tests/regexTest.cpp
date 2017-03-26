#include <iostream>
#include <stdexcept>
#include "..\Include\Util\CommandParametersExtractor.h"

int regexmain()
{
	std::string str("/tm:2, /d:some cpappe, /c:kek");
	size_t pos = str.find("tm");
	str.erase(pos, pos + 2);

	CommandParametersExtractor params(str);

	try {
		std::cout << params.TryGetArgument("l") << std::endl;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
	
	
	system("PAUSE");
	return 0;
}