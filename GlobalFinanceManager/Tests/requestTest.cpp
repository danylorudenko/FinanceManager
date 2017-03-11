#include <iostream>

#include "..\Include\Util\Request.h"
#include "..\Include\Time\MonthConverter.h"

int main()
{
	Request* request = Request::LastWeeks(5);

	std::cout << request->GetFirstEdge().GetDay() << std::endl
		<< MonthConverter::MonthToInt(request->GetFirstEdge().GetMonth()) << std::endl
		<< request->GetFirstEdge().GetYear() << std::endl;

	std::cout << request->GetLastEdge().GetDay() << std::endl
		<< MonthConverter::MonthToInt(request->GetLastEdge().GetMonth()) << std::endl
		<< request->GetLastEdge().GetYear() << std::endl;


	delete request;

	system("pause");
	return 0;
}