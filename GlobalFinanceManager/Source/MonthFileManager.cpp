#include "..\Include\Managers\MonthFileManager.h"

MonthFileManager::MonthFileManager(const std::string& file_name) : file_name_(file_name), is_dirty_(false)
{
	file_stream_ = std::fstream(file_name_.c_str());
}

void MonthFileManager::AccessEntries(const Request& request)
{
	entries_buffer_.clear();

	if (!file_stream_.is_open()) {
		std::cout << "Something is wrong with the " << file_name_ << std::endl;
		return;
	}

	int line_counter = 0;
	FinanceEntry temp_entry;

	while (file_stream_.goodbit()) {
		temp_entry.Read(file_stream_);

		if (request.IsValid(temp_entry)) {
			entries_buffer_.push_back(LineEntryPair(line_counter, temp_entry));
		}

		line_counter++;
	}
}

void MonthFileManager::UpdateFile()
{
	if (is_dirty_) {
		// Update records
	}
}

void MonthFileManager::SortFile() 
{

}