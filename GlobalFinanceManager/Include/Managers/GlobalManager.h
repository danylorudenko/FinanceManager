#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "..\..\Include\Util\Request\Request.h"

#include <string>

/*
	This class is entended to give interface to access file system of the manager.
	File system in this case is a special structure of files and file names in the records data folder.

	In the future it should get the request, construct the list of files to open,
	construct according file managers and parse the request further.
*/
class GlobalManager
{
public:
	using EntryID = unsigned int;

	void DisplayBalance(const std::string& params);

	void GetRecords(const std::string& params);

	void GlobalSearch(const std::string& params);

	void EditEntry(const std::string& params);

	void AddEntry(const std::string& params);

protected:

	// Checking if manager doesn't have needed file managers opened and opening them
	void CheckNeededFiles();

	// Preper closing of files which are unused for a couple of requests
	void CloseUnusedFiles();

	// Deleting files with no data
	void DeleteEmptyFiles();
};

#endif