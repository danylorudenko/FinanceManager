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
	void CloseUnusedFiles();

	void DeleteEmptyFiles();
};

#endif