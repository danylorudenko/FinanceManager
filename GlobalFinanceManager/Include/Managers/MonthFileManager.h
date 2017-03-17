#ifndef __MONTH_FILE_MANAGER_H__
#define __MONTH_FILE_MANAGER_H__

#include <string>
#include <vector>
#include <iostream>

#include "..\..\Include\Entry\FinanceEntry.h"
#include "..\..\Include\Util\Request.h"

using EntryID = unsigned int;

class EntryIterator;

/*
	This class represent an interface to the single file that should contain all finance records
	for one month.

	This manager has to understand the request and provide an answer for the requests
	
	Additional functionality: - editing existring recrods in the file (temp files, rewriting)
*/
class MonthFileManager
{
public:
	using iterator = EntryIterator;
	using container_type = std::vector<FinanceEntry>;

	MonthFileManager(const std::string& file_name);

	void ConstructFile() const;

	// Providing id-interface to access the elements of the buffer
	//void RequestEntries(const Request& request); // REVIEW

	// Adding entry to the buffer
	//void AddEntryToBuffer(FinanceEntry& new_entry);

	// Reading whole file to the buffer
	void ReadFileToBuffer();

	// Complete rewriting the file from the buffer
	void RewriteFileFromBuffer();

	// Buffer sorting
	void SortBuffer();

	iterator Begin(const Request& request);
	iterator End(const Request& request);

	void EditEntrySum(EntryID buffer_index, int new_sum);
	void EditEntryCategory(EntryID buffer_index, std::string& new_category);
	void EditEntryDescription(EntryID buffer_index, std::string& new_description);

	void TestDisplay() const;

private:
	const std::string file_name_;

	bool is_interface_dirty_;
	//std::vector<EntryID> entries_interface_buffer_;

	container_type entries_buffer_;
};

#endif