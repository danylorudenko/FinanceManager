#include <chrono>
#include <iostream>

int main()
{
	using namespace std::chrono_literals;
	std::chrono::seconds sec = 3s;

	std::chrono::time_point<std::chrono::system_clock> point = std::chrono::system_clock::now();

	system("pause");
	return 0;
}