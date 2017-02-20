#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include <vector>
#include "..\..\Include\Util\Request.h"

/*
	This class is entended to give interface to access file system of the manager.
	File system in this case is a special structure of files and file names in the records data folder.

	In the future it should get the request, construct the list of files to open,
	construct according file managers and parse the request further.
*/
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