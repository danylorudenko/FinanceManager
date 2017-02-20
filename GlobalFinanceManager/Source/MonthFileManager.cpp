#include <algorithm>

#include "..\Include\Managers\MonthFileManager.h"

MonthFileManager::MonthFileManager(const std::string& file_name) : file_name_(file_name), is_dirty_(false)
{
	
}

void MonthFileManager::ReadFileToBuffer()
{
	file_stream_.open(file_name_.c_str(), std::ios_base::in | std::ios_base::ate);
	
	if (!file_stream_.is_open()) {
		throw std::ios_base::failure("Error opening file \"" + file_name_ + "\"");
	}
	file_stream_.seekp(0, std::ios_base::beg);

	entries_buffer_.clear();

	std::string string_buffer;
	FinanceEntry entry_buffer;

	// Reading file till the EOF (or failiure)
	while (std::getline(file_stream_, string_buffer)) {
		try {
			entry_buffer = FinanceEntry(string_buffer);
			entries_buffer_.push_back(entry_buffer);
		}
		catch (std::invalid_argument exception) {
			std::cout
				<< exception.what()
				<< std::endl
				<< "Invalid format of the file line.\n";
		}
	}

	file_stream_.close();
}

void MonthFileManager::AccessEntries(const Request& request)
{
	
}

void MonthFileManager::RewriteFileFromBuffer()
{
	// At first - truncate the file
	if (file_stream_.is_open()) {
		file_stream_.close();
	}
	file_stream_.open(file_name_, std::ios_base::trunc | std::ios_base::out);

	std::fstream *file_stream_pointer = &file_stream_;
	std::for_each(entries_buffer_.begin(), entries_buffer_.end(), [&, file_stream_pointer](FinanceEntry entry) 
	{
		*file_stream_pointer << entry.Serialize() << std::endl;
	});

	file_stream_.close();
}

void MonthFileManager::SortFile() 
{

}

void MonthFileManager::TestDisplay() const
{
	std::for_each(entries_buffer_.begin(), entries_buffer_.end(), [&](FinanceEntry entry) {entry.TestDisplay(); });
}