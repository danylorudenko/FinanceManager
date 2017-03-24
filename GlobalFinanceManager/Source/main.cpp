#include <iostream>
#include "..\Include\Application.h"

int main()
{
	Application* application = new Application();

	while(application->Iterate());

	delete application;

	std::cout << "Bye\n";
	system("PAUSE");
	return 0;
}