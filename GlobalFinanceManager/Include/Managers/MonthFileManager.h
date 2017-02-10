#ifndef __MONTH_FILE_MANAGER_H__
#define __MONTH_FILE_MANAGER_H__

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include "..\..\Include\Entry\FinanceEntry.h"
#include "..\..\Include\Misc\Request.h"

/*
	This class represent an interface to the single file that should contain all finance records
	for one month.

	This manager has to understand the request and provide an answer for the requests
	
	Additional functionality: - editing existring recrods in the file (temp files, rewriting)
*/
class MonthFileManager
{
private:
	using LineEntryPair = typename std::pair<int, FinanceEntry>;

	bool is_dirty_;
	std::string file_name_;
	std::fstream file_stream_;

	std::vector<LineEntryPair> entries_buffer_;
	std::vector<LineEntryPair> dirty_entries_;

public:
	MonthFileManager(const std::string& file_name);

	void AccessEntries(const Request& request);
	void UpdateFile();
	void SortFile();
};

#endif