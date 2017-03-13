#include <iostream>
#include <fstream>

int streammain()
{
	std::ofstream outfile("DATA\\file.txt", std::ios_base::out | std::ios_base::in);

	std::cout << outfile.is_open() << std::endl;

	outfile << "FUCK!2" << std::endl;

	outfile.close();

	system("PAUSE");
	return 0;
}