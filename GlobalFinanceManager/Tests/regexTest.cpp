#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int regexmain()
{
	std::string strObj("5698");
	
	std::cmatch result;

	std::regex regularTag(
		"(-?)"
		"([\\d]+)"
	);

	if (std::regex_match(strObj.c_str(), result, regularTag)) {
		for (int i = 0; i < result.size(); i++) {
			std::cout << result[i] << std::endl;
		}
	}
	else {
		std::cout << "False\n";
	}

	system("PAUSE");
	return 0;
}