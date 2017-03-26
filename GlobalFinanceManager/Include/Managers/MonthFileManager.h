#ifndef __MONTH_FILE_MANAGER_H__
#define __MONTH_FILE_MANAGER_H__

#include <string>
#include <vector>
#include <iostream>

#include "..\..\Include\Entry\FinanceEntry.h"
#include "..\..\Include\Util\Request\Request.h"

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
	using entry_predicate = bool(*)(const FinanceEntry& lhs, const FinanceEntry& rhs);

	// Constructing manager of the month file. 
	// Name can't be changed after instantiation.
	// Default sorting binary predicate is FinanceEntry::DateLessPredicate
	MonthFileManager(const std::string& file_name, const entry_predicate sorting_predicate = FinanceEntry::DateLessPredicate);

	~MonthFileManager();

	// Adding entry to the buffer
	void AddEntryToBuffer(const FinanceEntry& new_entry);

	// Reading whole file to the buffer
	void ReadFileToBuffer();

	// Complete rewriting the file with the buffer
	void RewriteFileFromBuffer();

	// Soring buffer with the predicate field
	void SortBuffer();

	// Check is file has any data
	bool IsFileEmpty() const;

	// Permanent file deletion
	void DeleteFile() const;

	// Setting sorting predicate for FinanceEntries.
	// Predefined static predicates are in FinanceEntry:: scope
	void SetSotringPredicate(const entry_predicate predicate);

	// Constructing entry iteratator which points to the first valid entry
	// If there is no valid entry, iterator is invalid.
	// In this case when dereferencing std::lenth_error exception is thrown
	iterator Begin(const Request* request);

	// Constructing entry iteratator which points to (last + 1) valid entry
	// If there is no valid entry, iterator is invalid.
	// In this case when dereferencing std::lenth_error exception is thrown
	iterator End(const Request* request);

private:
	// Creating file with constant member string
	void CreateFile() const;

private:
	const std::string file_name_;

	container_type entries_buffer_;
	entry_predicate sorting_predicate_;
};

#endif