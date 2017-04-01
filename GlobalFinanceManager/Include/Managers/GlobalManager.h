#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "..\Include\Managers\MonthFileManager.h"

#include <string>
#include <list>
#include <vector>

class MonthFileManager;

/*
	This class is entended to give interface to access file system of the manager.
	File system in this case is a special structure of files and file names in the records data folder.

	In the future it should get the request, construct the list of files to open,
	construct according file managers and parse the request further.
*/
class GlobalManager
{
public:
	// Counds and displays total balance of all entries or of period of time.
	void DisplayBalance(std::string& params);

	// Displaying numerated list of records based on the user request.
	void GetRecords(std::string& params);

	// Works only if previous command was "get".
	// First argument is a number of entry to be changed.
	// Other params are the properties to be changed.
	void EditEntry(std::string& params);

	// Adding entry with the current date.
	// User can specify new entry properties with the params.
	void AddEntry(std::string& params);

	~GlobalManager();

protected:

	// Displaying balance by the past time (days/weeks/months)
	int CountBalanceByTime(const Request& time_param_string);

	// Reading request time range and creating all corresponding month managers
	void OpenManagers(const Request& request);

	// Proper closing of month managers
	void CloseManagers();

	// Deleting files with no data
	void DeleteEmptyFiles();

	// Sorting all opened buffers
	void SortBuffers();

	// Displaying buffers of the opened managers
	void DisplayManagersBuffers(const Request& request);

	static void FormatDisplayEntry(const FinanceEntry& entry);

protected:
	constexpr static char* balance_all_argument_ = "all";

	// List of month managers
	std::list<MonthFileManager> month_managers_;

	// Pointer to previously used request
	// Usually filled by "get" command
	Request* prev_request_;
};

#endif