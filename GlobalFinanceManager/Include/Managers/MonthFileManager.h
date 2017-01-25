#ifndef __MONTH_FILE_MANAGER_H__
#define __MONTH_FILE_MANAGER_H__

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include "..\..\Include\Entry\FinanceEntry.h"
#include "..\..\Include\Misc\Request.h"

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