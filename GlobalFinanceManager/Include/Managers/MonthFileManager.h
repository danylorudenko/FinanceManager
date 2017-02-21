#ifndef __MONTH_FILE_MANAGER_H__
#define __MONTH_FILE_MANAGER_H__

#include <string>
#include <vector>
#include <iostream>

#include "..\..\Include\Entry\FinanceEntry.h"
#include "..\..\Include\Util\Request.h"

/*
	This class represent an interface to the single file that should contain all finance records
	for one month.

	This manager has to understand the request and provide an answer for the requests
	
	Additional functionality: - editing existring recrods in the file (temp files, rewriting)
*/
class MonthFileManager
{
private:

	bool is_dirty_;
	const std::string file_name_;

	std::vector<FinanceEntry> entries_buffer_;

public:
	MonthFileManager(const std::string& file_name);

	void ReadFileToBuffer();
	void AccessEntries(const Request& request);
	void RewriteFileFromBuffer();
	void SortFile();

	void EditEntrySum(int buffer_index, int new_sum);
	void EditEntryCategory(int buffer_index, std::string& new_category);
	void EditEntryDescription(int buffer_index, std::string& new_description);

	void TestDisplay() const;
};

#endif