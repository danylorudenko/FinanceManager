#ifndef __FILE_NAMES_H__
#define __FILE_NAMES_H__

#include <vector>
#include <string>

#include "..\..\Include\Util\Request\Request.h"

using StringVector = std::vector<std::string>;

/*
	Static-only class which provides logic for constructing
	resource file names according to the input Request instance
*/
class FileNames
{
public:
	// Constructing proper list of file names for passed request
	static StringVector* ConstructFileNames(const Request& request);
	
private:
	// Constructing file name month part to the dest argument
	static void ConstructMonthFileNamePart(Month month, std::string& dest);

	// Constructing continious array of month file names between passed months (inclusive)
	static std::string* ConstructMonthFileNamePartsBetween(Month first_month, Month second_month, int* names_count);
	
	// Shortcut for ConstructMonthFileNamePartsBetween(user_month, Month::Dec);
	static std::string* ConstructMonthFileNamePartsBeforeDec(Month first_month, int* names_count);

	// Shortcut for ConstructMonthFileNamePartsBetween(Month::Jan, user_month);
	static std::string* ConstructMonthFileNamePartsFromJan(Month last_month, int* names_count);
	
	// Constructing ready-to-use file name (without folder part)
	static std::string* ConstructFileName(std::string* month_name, int year);

public:
	// Folder where app data is kept
	static const char* data_folder_name;

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