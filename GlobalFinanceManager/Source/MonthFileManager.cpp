#include <algorithm>
#include <fstream>

#include "..\Include\Managers\MonthFileManager.h"
#include "..\Include\Util\EntryIterator.h"

MonthFileManager::MonthFileManager(const std::string& file_name, const entry_predicate sorting_predicate) :
	file_name_(file_name), sorting_predicate_(sorting_predicate)
{
	ReadFileToBuffer();
}

MonthFileManager::~MonthFileManager()
{
	RewriteFileFromBuffer();
}

void MonthFileManager::CreateFile() const
{
	std::ofstream stream(file_name_);
	stream.close();
}

bool MonthFileManager::IsFileEmpty() const
{
	std::ifstream stream(file_name_);
	std::string file_content;

	std::getline(stream, file_content);

	stream.close();

	if (file_content.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}

void MonthFileManager::DeleteFile() const
{
	remove(file_name_.c_str());
}

void MonthFileManager::ReadFileToBuffer()
{
	std::ifstream* file_stream = new std::ifstream(file_name_, std::ios_base::in);
	
	if (!file_stream->is_open()) {
		CreateFile();
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
	if (entries_buffer_.size() == 0) {
		return;
	}

	std::sort(entries_buffer_.begin(), entries_buffer_.end(), sorting_predicate_);
}

void MonthFileManager::SetSotringPredicate(const entry_predicate sorting_predicate)
{
	sorting_predicate_ = sorting_predicate;
}

MonthFileManager::iterator MonthFileManager::Begin(const Request* request)
{
	return iterator(&entries_buffer_, request).ToBegin();
}

MonthFileManager::iterator MonthFileManager::End(const Request* request)
{
	return iterator(&entries_buffer_, request).ToEnd();
}

void MonthFileManager::AddEntryToBuffer(const FinanceEntry& entry)
{
	entries_buffer_.push_back(entry);
}