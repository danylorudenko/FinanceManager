#include "..\Include\Managers\MonthFileManager.h"

MonthFileManager::MonthFileManager(std::string& file_name) : file_name_(file_name), is_dirty_(false)
{
	file_stream_ = std::fstream(file_name_.c_str());
}

void MonthFileManager::GetFileData()
{
	entries_.clear();
}

void MonthFileManager::UpdateFile()
{
	if (is_dirty_) {
		// Update records
	}
}