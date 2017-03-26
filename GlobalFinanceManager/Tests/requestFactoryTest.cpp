#include "..\Include\Util\Request\RequestFactory.h"
#include <iostream>

int factorymain()
{
	
	std::string str("/c:lol, /tm:2");
	Request* request = RequestFactory::ConstructRequest(str);

	std::cout << "Hello\n";

	delete request;
	system("pause");
	return 0;
}