#include "..\Include\Util\Request\RequestFactory.h"
#include <iostream>

int main()
{
	Request* request = RequestFactory::ConstructRequest("/tm:2 /c:lol");

	std::cout << "Hello\n";

	system("pause");
	return 0;
}