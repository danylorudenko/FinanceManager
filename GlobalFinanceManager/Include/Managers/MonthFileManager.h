#ifndef __MONTH_FILE_MANAGER_H__
#define __MONTH_FILE_MANAGER_H__

#include <string>
#include <fstream>
#include <vector>

#include "..\..\Include\Entry\FinanceEntry.h"

class MonthFileManager
{
private:
	bool is_dirty_;
	std::string file_name_;
	std::fstream file_stream_;

	std::vector<FinanceEntry> entries_;

public:
	MonthFileManager(std::string& file_name);

	void GetFileData();
	void UpdateFile();
};

#endif