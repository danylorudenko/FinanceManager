#ifndef __MONTH_FILE_MANAGER_H__
#define __MONTH_FILE_MANAGER_H__

#include <string>
#include <vector>
#include <iostream>

#include "..\..\Include\Entry\FinanceEntry.h"
#include "..\..\Include\Util\Request.h"

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
	using entry_binary_predicate = bool(*)(const FinanceEntry& lhs, const FinanceEntry& rhs);

	MonthFileManager(const std::string& file_name, const entry_binary_predicate sorting_predicate = FinanceEntry::DateLessPredicate);

	// Adding entry to the buffer
	void AddEntryToBuffer(const FinanceEntry& new_entry);

	// Reading whole file to the buffer
	void ReadFileToBuffer();

	// Complete rewriting the file from the buffer
	void RewriteFileFromBuffer();

	// Soring buffer with the predicate field
	void SortBuffer();

	void SetSotringPredicate(const entry_binary_predicate predicate);

	iterator Begin(const Request& request);
	iterator End(const Request& request);

private:
	void ConstructFile() const;

private:
	const std::string file_name_;

	container_type entries_buffer_;
	entry_binary_predicate sorting_predicate_;
};

#endif