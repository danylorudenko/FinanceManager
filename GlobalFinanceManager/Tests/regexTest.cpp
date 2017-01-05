#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int a()
{
	std::string strObj;
	
	std::ifstream inFile("Tests\\tagSample.txt", std::ios_base::in | std::ios_base::beg);
	if (!inFile.is_open()) {
		std::cout << "Error opening file\n";
	}

	std::string buffer;
	while (!inFile.eof()) {
		std::getline(inFile, buffer);
		strObj += buffer;
	}
	inFile.close();

	std::cout << strObj << std::endl;
	
	std::cmatch result;

	std::regex regularTag(
		"(<root>)"
		"([\\s\\S]+)"
		"(<\/root>)"
	);

	if (std::regex_search(strObj.c_str(), result, regularTag)) {
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