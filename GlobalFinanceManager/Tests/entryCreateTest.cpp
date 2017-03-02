#include <iostream>
#include <limits>
int main()
{
	std::cout << "Hello, world\n";

	std::cout << "unsigned long long size: " << sizeof(unsigned long long) << std::endl;

	std::cout << "unsigned long long max size: " << std::numeric_limits<unsigned long long>::max() << std::endl;

	system("pause");
	return 0;
}