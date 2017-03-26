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
	// Counds and displays total balance of all records or of period of time
	void DisplayBalance(std::string& params);

	void GetRecords(std::string& params);

	void GlobalSearch(std::string& params);

	void EditEntry(std::string& params);

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

	void DisplayManagersBuffers(const Request& request);

protected:
	const static std::string balance_all_argument_;

	// List of month managers
	std::vector<MonthFileManager> month_managers_;
};

#endif