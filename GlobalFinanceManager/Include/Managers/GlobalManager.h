#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "..\..\Include\Util\Request\Request.h"

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

	void DisplayBalance(const Request* request);

	void DisplayRecords(const Request* request);

	void GlobalFind(const Request* request);

	bool EditEntry(const EntryID id, std::string& params_string);

	bool AddEntry(const std::string& params_string);

protected:

	// Checking if manager doesn't have needed file managers opened and opening them
	void CheckNeenedFiles();

	// Preper closing of files which are unused for a couple of requests
	void CloseUnusedFiles();

	// Deleting files with no data
	void DeleteEmptyFiles();
};

#endif