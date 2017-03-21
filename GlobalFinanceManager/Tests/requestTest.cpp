#include <iostream>

#include "..\Include\Util\Request\Request.h"
#include "..\Include\Time\MonthConverter.h"

int requestmain()
{
	TimeEdgePredicate* time_predicate = TimeEdgePredicate::LastDays(7);
	Request* request = new Request(time_predicate);
	
	
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