#include <iostream>
#include "..\Include\Application.h"

int main()
{
	Application* application = new Application();

	while(application->Iterate());

	delete application;
	return 0;
}