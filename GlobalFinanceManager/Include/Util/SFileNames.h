#ifndef __FILE_NAMES_H__
#define __FILE_NAMES_H__

#include <vector>
#include <string>

#include "..\..\Include\Util\Request.h"

using StringVector = std::vector<std::string>;

/*
	Static-only class which provides logic for constructing
	resource file names according to the input Request instance
*/
class SFileNames
{
	static std::string* ConstructMonthFileNamePart(Month month);
	static std::string* ConstructMonthFileNamePartsBetween(Month first_month, Month second_month, int* names_count);
	static std::string* ConstructMonthFileNamePartsBeforeDec(Month first_month, int* names_count);
	static std::string* ConstructMonthFileNamePartsFromJan(Month last_month, int* names_count);
	
	static std::string* ConstructFileName(std::string* month_name, int year);

	static StringVector* ConstructFileNames(const Request& request);

	static const char* jan_file_name;
	static const char* feb_file_name;
	static const char* mar_file_name;
	static const char* apr_file_name;
	static const char* may_file_name;
	static const char* jun_file_name;
	static const char* jul_file_name;
	static const char* aug_file_name;
	static const char* sep_file_name;
	static const char* oct_file_name;
	static const char* nov_file_name;
	static const char* dec_file_name;
};

#endif