#ifndef __MONTH_FILE_MANAGER_H__
#define __MONTH_FILE_MANAGER_H__

#include <string>
#include <vector>
#include <iostream>

#include "..\..\Include\Entry\FinanceEntry.h"
#include "..\..\Include\Util\Request.h"

using EntryID = unsigned int;

/*
	This class represent an interface to the single file that should contain all finance records
	for one month.

	This manager has to understand the request and provide an answer for the requests
	
	Additional functionality: - editing existring recrods in the file (temp files, rewriting)
*/
class MonthFileManager
{
public:
	MonthFileManager(const std::string& file_name);

	std::vector<EntryID>* RequestEntries(const Request& request);
	//const FinanceEntry& AccessEntry(const EntryID entry_id);
	void ReadFileToBuffer();
	void RewriteFileFromBuffer();
	void SortFile();

	void EditEntrySum(EntryID buffer_index, int new_sum);
	void EditEntryCategory(EntryID buffer_index, std::string& new_category);
	void EditEntryDescription(EntryID buffer_index, std::string& new_description);

	void TestDisplay() const;

private:
	const std::string file_name_;

	std::vector<FinanceEntry> entries_buffer_;
};

#endif