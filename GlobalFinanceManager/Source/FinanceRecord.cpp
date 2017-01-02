#include <iostream>
#include <exception>
#include "..\Include\Record\FinanceRecord.h"
#include "..\Include\Record\ExpenceRecord.h"
#include "..\Include\Record\IncomeRecord.h"

const int FinanceRecord::categoryLimit = 30;
const int FinanceRecord::descriptionLimit = 150;
const int FinanceRecord::totalRecordLength = categoryLimit + descriptionLimit + sizeof(TimeHolder) + sizeof(float) + sizeof(RecordType);


FinanceRecord* FinanceRecord::CreateRecord(const RecordType type, const std::string& category, float sum, const std::string& description = "")
{
	switch (type)
	{
	case RecordType::Expence:
		return new ExpenceRecord(category, sum, description);
		break;
	case RecordType::Income:
		return new IncomeRecord(category, sum, description);
		break;
	default:
		throw new std::invalid_argument("Invalid type of record");
	}
}

FinanceRecord::FinanceRecord(const std::string& newCategory, float newSum, const std::string& newDescription) :
	category(newCategory), sum(newSum), description(newDescription)
{
	time = new TimeHolder;
}

FinanceRecord::~FinanceRecord()
{
	delete time;
}

void FinanceRecord::EditCategory(const std::string& newCategory)
{
	category = newCategory;
}

void FinanceRecord::EditDescription(const std::string& newDescription)
{
	description = newDescription;
}

void FinanceRecord::TestDisplay() const
{
	std::cout << time->GetTimeString() << std::endl
		<< "Sum: " << sum << std::endl
		<< category << std::endl
		<< description << std::endl;
}

void FinanceRecord::EditSum(const float newSum)
{
	sum = newSum;
}

void FinanceRecord::Write(std::ofstream& outFile) 
{
	if (outFile.is_open())
	{
		std::cout << "File " << " was opened for writing." << std::endl;
	}
	else
	{
		std::cout << "Failed to open file for writing." << std::endl;
		return;
	}

	// TimeHolder self-writing
	time->Write(outFile);

	// Writing the sum value
	outFile.write(reinterpret_cast<const char*>(&sum), sizeof(decltype(sum)));

	// Writing category
	FinanceRecord::WriteString(outFile, category, categoryLimit);

	// Writing description
	FinanceRecord::WriteString(outFile, description, descriptionLimit);
	
	std::cout << "File was successfully written.\n";
}

void FinanceRecord::Read(std::ifstream& inFile)
{
	if (inFile.is_open())
	{
		std::cout << "File was opened for reading.\n";
	}
	else
	{
		std::cout << "Failder to open for reading.\n";
	}

	char* buffer = new char[FinanceRecord::totalRecordLength];
	int iterator = 0;

	// Reading TimeHolder
	if (time != nullptr) {
		delete time;
	}
	time = new TimeHolder(buffer, iterator);

	// Reading sum value
	sum = *(reinterpret_cast<float*>(buffer + iterator));

	// Reading category
	category.clear();
	for (int i = 0; i < categoryLimit; i++) {
		if (buffer[iterator] != '\0') {
			category += buffer[iterator];
		}
		iterator++;
	}

	// Reading description
	description.clear();
	for (int i = 0; i < descriptionLimit; i++) {
		if (buffer[iterator] != '\0') {
			description += buffer[iterator];
		}
		iterator++;
	}

	delete[] buffer;
	//char timeHolderBuffer[sizeof(TimeHolder)];
	//inFile.read(timeHolderBuffer, sizeof(TimeHolder)); //reading complete buffer for the TimeHolder
	//
	//int readingPosition = 0;
	//delete time; // deallocating the memory the old TimeHolder
	//time = new TimeHolder(timeHolderBuffer, readingPosition); // initializing TimeHolder with buffer. Returns bytes have read by ref(readingPosition)
	//
	//char floatBuffer[sizeof(float)];
	//inFile.read(floatBuffer, sizeof(float));
	//sum = *(reinterpret_cast<float*>(floatBuffer)); // reading float SUM
	//
	//int readStringSize;
	//const size_t intSize = sizeof(int);
	//char intBuffer[intSize];
	//inFile.read(intBuffer, intSize);
	//readStringSize = *(reinterpret_cast<int*>(intBuffer));
}

void FinanceRecord::WriteString(std::ofstream& outFile, std::string str, int limit) 
{
	int counter = 0;
	int stringSize = str.size();

	while (counter < limit && counter < stringSize) {
		outFile.write(reinterpret_cast<char*>(&str[counter]), sizeof(char));
		counter++;
	}

	// If unused space left, write null-characters
	char* nullChar = new char('\0');
	while (counter < limit) {
		outFile.write(nullChar, sizeof(decltype(nullChar)));
		counter++;
	}
	delete nullChar;
}