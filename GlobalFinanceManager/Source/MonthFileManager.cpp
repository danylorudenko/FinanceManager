#include <algorithm>
#include <fstream>

#include "..\Include\Managers\MonthFileManager.h"

MonthFileManager::MonthFileManager(const std::string& file_name) : file_name_(file_name), is_dirty_(false) { }

void MonthFileManager::ReadFileToBuffer()
{
	std::ifstream file_stream(file_name_.c_str(), std::ios_base::in | std::ios_base::ate);
	
	if (!file_stream.is_open()) {
		throw std::ios_base::failure("Error opening file \"" + file_name_ + "\"");
	}
	file_stream.seekg(0, std::ios_base::beg);

	entries_buffer_.clear();

	std::string string_buffer;
	FinanceEntry entry_buffer;

	// Reading file till the EOF (or failiure)
	while (std::getline(file_stream, string_buffer)) {
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

	file_stream.close();
}

void MonthFileManager::AccessEntries(const Request& request)
{
	if (entries_buffer_.size() > 0) {
		std::cout << "Warning: entries buffer is not empty.\n";
	}

	// std::count_if(entries_buffer_.begin(), entries_buffer_.end, [&](FinanceEntry entry) {});
}

void MonthFileManager::RewriteFileFromBuffer()
{
	
	std::fstream file_stream(file_name_, std::ios_base::trunc | std::ios_base::out);

	std::fstream *file_stream_pointer = &file_stream;
	std::for_each(entries_buffer_.begin(), entries_buffer_.end(), [&, file_stream_pointer](FinanceEntry entry) 
	{
		*file_stream_pointer << entry.Serialize() << std::endl;
	});

	file_stream.close();
}

void MonthFileManager::SortFile() 
{
	std::cout << "MonthFileManager::SortFile() is not ready yet!\n";
}

void MonthFileManager::EditEntrySum(int buffer_index, int new_sum)
{
	try {
		FinanceEntry& entry_reference = entries_buffer_.at(buffer_index);
		entry_reference.EditSum(new_sum);
	}
	catch (std::out_of_range) {
		std::cout << "Can't access " << buffer_index << " position in buffer.\n";
	}
}

void MonthFileManager::EditEntryDescription(int buffer_index, std::string& new_description)
{
	try {
		FinanceEntry& entry_reference = entries_buffer_.at(buffer_index);
		entry_reference.EditDescription(new_description);
	}
	catch (std::out_of_range) {
		std::cout << "Can't access " << buffer_index << " position in buffer.\n";
	}
}

void MonthFileManager::EditEntryCategory(int buffer_index, std::string& new_category)
{
	try {
		FinanceEntry& entry_reference = entries_buffer_.at(buffer_index);
		entry_reference.EditCategory(new_category);
	}
	catch (std::out_of_range) {
		std::cout << "Can't access " << buffer_index << " position in buffer.\n";
	}
}

void MonthFileManager::TestDisplay() const
{
	std::for_each(entries_buffer_.begin(), entries_buffer_.end(), [&](FinanceEntry entry) {entry.TestDisplay(); });
}