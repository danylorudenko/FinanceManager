#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include <vector>
#include "..\..\Include\Misc\Request.h"

class DataManager
{
private:
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

public:
	static std::vector<std::string> ConstructFileNames(const Request& request);
};

#endif