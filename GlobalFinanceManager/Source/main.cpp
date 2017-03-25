#include <iostream>
#include "..\Include\Application.h"

int notmain()
{
	Application* application = new Application();

	while(application->Iterate());

	delete application;
	return 0;
}