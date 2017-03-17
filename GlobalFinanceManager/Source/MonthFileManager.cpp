#include <algorithm>
#include <fstream>

#include "..\Include\Managers\MonthFileManager.h"
#include "..\Include\Util\EntryIterator.h"

MonthFileManager::MonthFileManager(const std::string& file_name) : 
	file_name_(file_name), is_interface_dirty_(true)
{

}

void MonthFileManager::ConstructFile() const
{
	std::ofstream stream(file_name_);
	stream.close();
}

void MonthFileManager::ReadFileToBuffer()
{
	std::ifstream* file_stream = new std::ifstream(file_name_, std::ios_base::in);
	
	if (!file_stream->is_open()) {
		ConstructFile();
		file_stream->clear();
		file_stream->open(file_name_);
	}

	file_stream->seekg(0, std::ios_base::beg);

	entries_buffer_.clear();

	std::string string_buffer;
	FinanceEntry entry_buffer;

	// Reading file till the EOF (or failiure)
	while (std::getline(*file_stream, string_buffer)) {
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

	file_stream->close();
	delete file_stream;
}

//void MonthFileManager::RequestEntries(const Request& request)
//{
//	entries_interface_buffer_.clear();
//
//	size_t entry_buffer_size = entries_buffer_.size();
//	for (size_t i = 0; i < entry_buffer_size; i++) {
//		if (request.IsValid(entries_buffer_[i])) {
//			entries_interface_buffer_.push_back(i);
//		}
//	}
//}

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

void MonthFileManager::SortBuffer() 
{
	std::cout << "MonthFileManager::SortBuffer() is not ready yet!\n";
}

MonthFileManager::iterator MonthFileManager::Begin(const Request& request) const
{
	//return iterator(&entries_buffer_, request).ToBegin();
	return iterator(&entries_buffer_, request);
}

MonthFileManager::iterator MonthFileManager::End(const Request& request) const
{
	return iterator(&entries_buffer_, request);
}

void MonthFileManager::EditEntrySum(EntryID buffer_index, int new_sum)
{
	try {
		FinanceEntry& entry_reference = entries_buffer_.at(buffer_index);
		entry_reference.EditSum(new_sum);
	}
	catch (std::out_of_range) {
		std::cout << "Can't access " << buffer_index << " position in buffer.\n";
	}
}

void MonthFileManager::EditEntryDescription(EntryID buffer_index, std::string& new_description)
{
	try {
		FinanceEntry& entry_reference = entries_buffer_.at(buffer_index);
		entry_reference.EditDescription(new_description);
	}
	catch (std::out_of_range) {
		std::cout << "Can't access " << buffer_index << " position in buffer.\n";
	}
}

void MonthFileManager::EditEntryCategory(EntryID buffer_index, std::string& new_category)
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
	//std::for_each(entries_buffer_.begin(), entries_buffer_.end(), [&](FinanceEntry entry) {entry.TestDisplay(); });
}